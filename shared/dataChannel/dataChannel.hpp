#ifndef DATA_CHANNEL_HPP
#define DATA_CHANNEL_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "taskId.hpp"
#include "util.h"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Shared
{

// This handles the case where the parameter pack is empty
template <typename...>
struct GetIndex
{
    static constexpr int32_t Of(TaskId, int32_t)
    {
       return -1;
    }
};

// This handles the case where the parameter pack has at least one element
template<typename First, typename... More>
struct GetIndex<First, More...>
{
    static constexpr int32_t Of(const TaskId task, const int32_t index)
    {
       return (task == First{}) ? index : GetIndex<More...>::Of(task, index+1);
    }
};

//--------------------------------------------------------------------------------------------------
// DataChannel base class
//--------------------------------------------------------------------------------------------------
class DataChannelBase
{
    public:
        constexpr DataChannelBase()
        {}

        NOCOPY_NOMOVE(DataChannelBase);

        virtual void Publish(const TaskId task) = 0;
        virtual void Update(const TaskId task) = 0;
        void Lock(void) const;
        void Unlock(void) const;
};

//--------------------------------------------------------------------------------------------------
// DataChannel with destination tasks
//--------------------------------------------------------------------------------------------------
template<typename T, typename SourceTask, typename... DestTasks>
class DataChannel : public DataChannelBase
{
    public:
        constexpr DataChannel(
                const T& sourceData
            ) :
                DataChannelBase(),
                m_sourceData(sourceData)
        {}

        NODEFAULT_NOCOPY_NOMOVE(DataChannel);

    private:
        static constexpr int32_t NUM_DEST_TASKS = static_cast<int32_t>(sizeof...(DestTasks));

        template<typename DestTask>
        static constexpr int32_t FindIndex(void)
        {
            return GetIndex<DestTasks...>::Of(DestTask{}, 0);
        }

        static constexpr int32_t FindIndex(const TaskId task)
        {
            return GetIndex<DestTasks...>::Of(task, 0);
        }

        const T& m_sourceData;
        T m_dataSnapshot {};
        T m_destinationData[NUM_DEST_TASKS] {};
        bool m_newData[NUM_DEST_TASKS] {};

    public:
        constexpr const T& GetBuffer(SourceTask) const
        {
            return m_sourceData;
        }

        template<typename DestTask, int32_t i=FindIndex<DestTask>()>
        constexpr const T& GetBuffer(DestTask) const
        {
            UTIL_ASSERT( ((i >= 0) && (i < NUM_DEST_TASKS)), "Invalid destination task");
            return m_destinationData[i];
        }

        // When task has completed - publish the associated source data snapshot that destination
        // tasks can consume when ready to run
        virtual void Publish(const TaskId task) override
        {
            if (task == SourceTask{})
            {
                Lock();
                m_dataSnapshot = m_sourceData;
                for (int32_t i = 0; i < NUM_DEST_TASKS; ++i)
                {
                    // new data is available for all destination tasks
                    m_newData[i] = true;
                }
                Unlock();
            }
        }

        // When task is ready to run - update its respective destination data from the source data snapshot
        virtual void Update(const TaskId task) override
        {
            const int32_t i = FindIndex(task);

            if ((i >= 0) && (i < NUM_DEST_TASKS))
            {
                if (m_newData[i])
                {
                    Lock();
                    m_destinationData[i] = m_dataSnapshot;
                    m_newData[i] = false;
                    Unlock();
                }
            }
        }
};

//--------------------------------------------------------------------------------------------------
// DataChannel with no destination tasks
//--------------------------------------------------------------------------------------------------
template<typename T, typename SourceTask>
class DataChannel<T, SourceTask> : public DataChannelBase
{
    public:
        constexpr DataChannel(
                const T& sourceData
            ) :
                DataChannelBase(),
                m_sourceData(sourceData)
        {}

        NODEFAULT_NOCOPY_NOMOVE(DataChannel);

    private:
        const T& m_sourceData;

    public:
        constexpr const T& GetBuffer(SourceTask) const
        {
            return m_sourceData;
        }

        virtual void Publish(const TaskId) override
        {
            // Nothing to do
        }

        virtual void Update(const TaskId) override
        {
            // Nothing to do
        }
};

} // namespace Shared

#endif // DATA_CHANNEL_HPP
