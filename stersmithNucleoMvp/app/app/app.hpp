#ifndef APP_HPP
#define APP_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "dataChannel.hpp"
#include "nocopy.hpp"
#include "taskBase.hpp"

#include "canModule.hpp"
#include "klineModule.hpp"
#include "servoModule.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class App final
{
    public:
        constexpr App()
        {}

        NOCOPY_NOMOVE(App);

        void Init(void)
        {
            m_task1kHz.Init();
            m_task10Hz.Init();
            m_task1Hz.Init();
        }

        void RunTask1kHz(void)
        {
            m_task1kHz.Run();
        }

        void RunTask10Hz(void)
        {
            m_task10Hz.Run();
        }

        void RunTask1Hz(void)
        {
            m_task1Hz.Run();
        }

    private:
        using DataChannelBase   = Shared::DataChannelBase;
        template<typename T, typename SourceTask, typename... DestTasks>
        using DataChannel       = Shared::DataChannel<T, SourceTask, DestTasks...>;
        using ModuleBase        = Shared::ModuleBase;
        using TaskBase          = Shared::TaskBase;

        Task1kHz     Task1kHz_t{};
        Task10Hz     Task10Hz_t{};
        Task1Hz      Task1Hz_t{};

        //------------------------------------------------------------------------------------------
        // 1kHz objects
        //------------------------------------------------------------------------------------------
        CanModule m_canModule {};

        static constexpr size_t m_numberOfModules1kHz = 1U;
        ModuleBase * const m_moduleList1kHz[m_numberOfModules1kHz] =
        {
            &m_canModule,
        };

        //------------------------------------------------------------------------------------------
        // 10Hz objects
        //------------------------------------------------------------------------------------------
        ServoModule m_servoModule {};

        static constexpr size_t m_numberOfModules10Hz = 1U;
        ModuleBase * const m_moduleList10Hz[m_numberOfModules10Hz] =
        {
            &m_servoModule,
        };

        //------------------------------------------------------------------------------------------
        // 1Hz objects
        //------------------------------------------------------------------------------------------
        KlineModule m_klineModule {};

        static constexpr size_t m_numberOfModules1Hz = 1U;
        ModuleBase * const m_moduleList1Hz[m_numberOfModules1Hz] =
        {
            &m_klineModule,
        };

        //------------------------------------------------------------------------------------------
        // Data channels
        //------------------------------------------------------------------------------------------
        static constexpr size_t m_numberOfDataChannels = 0U;
        DataChannelBase * const m_dataChannelList[m_numberOfDataChannels] =
        {
        };

        //------------------------------------------------------------------------------------------
        // Task objects
        //------------------------------------------------------------------------------------------
        TaskBase    m_task1kHz{
                          Task1kHz_t
                        , m_moduleList1kHz
                        , m_numberOfModules1kHz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                    };
        TaskBase    m_task10Hz{
                          Task10Hz_t
                        , m_moduleList10Hz
                        , m_numberOfModules10Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                    };
        TaskBase    m_task1Hz{
                          Task1Hz_t
                        , m_moduleList1Hz
                        , m_numberOfModules1Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                    };
};

} // namespace Eim

#endif // APP_HPP
