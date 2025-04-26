#ifndef APP_HPP
#define APP_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "dataChannel.hpp"
// #include "halWrappersComponentSpecific.hpp"
#include "nocopy.hpp"
#include "taskBase.hpp"

// Modules
// #include "canModule.hpp"
#include "rxModule.hpp"
#include "txModule.hpp"

// Message modules
#include "rxMessageModule.hpp"

// Input message modules

#include "taskId.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Vcu
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
            m_task100Hz.Init();
            m_task10Hz.Init();
        }

        void RunTask1kHz(void)
        {
            m_task1kHz.Run();
        }

        void RunTask100Hz(void)
        {
            m_task100Hz.Run();
        }

        void RunTask10Hz(void)
        {
            m_task10Hz.Run();
        }

    private:
        using DataChannelBase   = Shared::DataChannelBase;
        template<typename T, typename SourceTask, typename... DestTasks>
        using DataChannel       = Shared::DataChannel<T, SourceTask, DestTasks...>;
        using ModuleBase        = Shared::ModuleBase;
        using TaskBase          = Shared::TaskBase;

        Task1kHz     Task1kHz_t{};
        Task100Hz    Task100Hz_t{};
        Task10Hz     Task10Hz_t{};

        RxNoneModule m_rxNoneModule {};
        TxNoneModule m_txNoneModule {};

        //------------------------------------------------------------------------------------------
        // 1kHz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules

        // Inputs

        // Modules

        // Module list
        // static constexpr size_t m_numberOfModules1kHz = 0U;
        // ModuleBase * const m_moduleList1kHz {nullptr};
        // ModuleBase * const m_moduleList1kHz[m_numberOfModules1kHz] =
        // {
        // };

        //------------------------------------------------------------------------------------------
        // 100Hz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules

        // Inputs

        // Modules

        // Module list
        // static constexpr size_t m_numberOfModules100Hz = 0U;
        // ModuleBase * const m_moduleList100Hz[m_numberOfModules100Hz] =
        // {
        // };

        //------------------------------------------------------------------------------------------
        // 10Hz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules

        // Inputs

        // Modules

        // Module list
        // static constexpr size_t m_numberOfModules10Hz = 0U;
        // ModuleBase * const m_moduleList10Hz[m_numberOfModules10Hz] =
        // {
        // };

        //------------------------------------------------------------------------------------------
        // Data channels
        //------------------------------------------------------------------------------------------
        // static constexpr size_t m_numberOfDataChannels = 0U;
        // DataChannelBase * const m_dataChannelList[m_numberOfDataChannels] =
        // {
        //     // 1kHz source
        //     // 100Hz source
        //     // 10Hz source
        // };

        //------------------------------------------------------------------------------------------
        // Task objects
        //------------------------------------------------------------------------------------------
        TaskBase    m_task1kHz{
                          Task1kHz_t
                        // , m_moduleList1kHz
                        // , m_numberOfModules1kHz
                        // , m_dataChannelList
                        // , m_numberOfDataChannels
                        , m_rxNoneModule
                        , m_txNoneModule
                    };
        TaskBase    m_task100Hz{
                          Task100Hz_t
                        // , m_moduleList100Hz
                        // , m_numberOfModules100Hz
                        // , m_dataChannelList
                        // , m_numberOfDataChannels
                        , m_rxNoneModule
                        , m_txNoneModule
                    };
        TaskBase    m_task10Hz{
                          Task10Hz_t
                        // , m_moduleList10Hz
                        // , m_numberOfModules10Hz
                        // , m_dataChannelList
                        // , m_numberOfDataChannels
                        , m_rxNoneModule
                        , m_txNoneModule
                    };
};

} // namespace Vcu

#endif // APP_HPP
