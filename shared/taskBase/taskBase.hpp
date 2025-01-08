#ifndef TASK_BASE_HPP
#define TASK_BASE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "dataChannel.hpp"
#include "moduleBase.hpp"
#include "nocopy.hpp"
#include "taskId.hpp"
#include "util.h"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Shared
{

class TaskBase
{
    private:
        using ModuleBasePtr = ModuleBase * const;
        using DataChannelBasePtr = DataChannelBase * const;

    public:
        constexpr TaskBase(
                const TaskId taskId,
                ModuleBasePtr * const pModulePtrList,
                const size_t numberOfModules,
                DataChannelBasePtr * const pDataChannelPtrList,
                const size_t numberOfDataChannels
            ) :
                m_taskId(taskId),
                m_pModulePtrList(pModulePtrList),
                m_numberOfModules(numberOfModules),
                m_pDataChannelPtrList(pDataChannelPtrList),
                m_numberOfDataChannels(numberOfDataChannels)
        {}

        NODEFAULT_NOCOPY_NOMOVE(TaskBase);

        void Init(void) const;
        void Run(void) const;

    private:
        const TaskId                m_taskId;
        ModuleBasePtr * const       m_pModulePtrList;
        const size_t                m_numberOfModules;
        DataChannelBasePtr * const  m_pDataChannelPtrList;
        const size_t                m_numberOfDataChannels;

        // Private Methods
        void Update(void) const;
        void Publish(void) const;
};

} // namespace Shared

#endif // TASK_BASE_HPP
