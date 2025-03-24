#ifndef APP_HPP
#define APP_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "dataChannel.hpp"
#include "nocopy.hpp"
#include "taskBase.hpp"

// Modules
#include "adcModule.hpp"
#include "canModule.hpp"
#include "ioIntModule.hpp"
#include "klineModule.hpp"
#include "rxModule.hpp"
#include "servoModule.hpp"
#include "txModule.hpp"

// Message modules
#include "adcMessageModule.hpp"
#include "ioIntMessageModule.hpp"
#include "klineMessageModule.hpp"
#include "rxMessageModule.hpp"
#include "servoMessageModule.hpp"

// Input message modules
#include "ioIntInputMessageModule.hpp"
#include "servoInputMessageModule.hpp"

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
            m_task100Hz.Init();
            m_task10Hz.Init();
            m_task1Hz.Init();
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
        Task100Hz    Task100Hz_t{};
        Task10Hz     Task10Hz_t{};
        Task1Hz      Task1Hz_t{};

        RxNoneModule m_rxNoneModule {};
        TxNoneModule m_txNoneModule {};

        //------------------------------------------------------------------------------------------
        // 1kHz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules

        // Inputs

        // Modules
        CanModule m_canModule {};

        // Module list
        static constexpr size_t m_numberOfModules1kHz = 1U;
        ModuleBase * const m_moduleList1kHz[m_numberOfModules1kHz] =
        {
            &m_canModule,
        };

        //------------------------------------------------------------------------------------------
        // 100Hz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules
        Rx100HzModule m_rx100HzModule {};
        Tx100HzModule m_tx100HzModule {
            m_adcMessageModule100Hz,
            m_ioIntMessageModule100Hz
        };

        // Inputs
        IoIntInputMessageModule m_ioIntInput {
            m_rx100HzMessageModule100Hz
        };

        // Modules
        AdcModule m_adcModule {};
        IoIntModule m_ioIntModule {
            m_ioIntInput
        };

        // Module list
        static constexpr size_t m_numberOfModules100Hz = 2U;
        ModuleBase * const m_moduleList100Hz[m_numberOfModules100Hz] =
        {
            &m_adcModule,
            &m_ioIntModule,
        };

        //------------------------------------------------------------------------------------------
        // 10Hz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules
        Rx10HzModule m_rx10HzModule {};
        Tx10HzModule m_tx10HzModule {
            m_servoMessageModule10Hz
        };

        // Inputs
        ServoInputMessageModule m_servoInput {
            m_rx10HzMessageModule10Hz
        };

        // Modules
        ServoModule m_servoModule {
            m_servoInput
        };

        // Module list
        static constexpr size_t m_numberOfModules10Hz = 1U;
        ModuleBase * const m_moduleList10Hz[m_numberOfModules10Hz] =
        {
            &m_servoModule,
        };

        //------------------------------------------------------------------------------------------
        // 1Hz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules
        Tx1HzModule m_tx1HzModule {
            m_klineMessageModule1Hz
        };

        // Inputs

        // Modules
        KlineModule m_klineModule {};

        // Module list
        static constexpr size_t m_numberOfModules1Hz = 1U;
        ModuleBase * const m_moduleList1Hz[m_numberOfModules1Hz] =
        {
            &m_klineModule,
        };

        //------------------------------------------------------------------------------------------
        // Data channels
        //------------------------------------------------------------------------------------------
        // 100Hz source
        DataChannel< AdcData_S
                   , Task100Hz  // source task
                          >m_adcDataChannel{ m_adcModule.GetOutputDataReference() };
        AdcMessageModule m_adcMessageModule100Hz { m_adcDataChannel.GetBuffer(Task100Hz_t) };

        DataChannel< IoIntData_S
                   , Task100Hz  // source task
                          >m_ioIntDataChannel{ m_ioIntModule.GetOutputDataReference() };
        IoIntMessageModule m_ioIntMessageModule100Hz { m_ioIntDataChannel.GetBuffer(Task100Hz_t) };

        DataChannel< Rx100HzData_S
                   , Task100Hz  // source task
                           >m_rx100HzDataChannel{ m_rx100HzModule.GetOutputDataReference() };
        Rx100HzMessageModule m_rx100HzMessageModule100Hz { m_rx100HzDataChannel.GetBuffer(Task100Hz_t) };

        // 10Hz source
        DataChannel< Rx10HzData_S
                   , Task10Hz   // source task
                           >m_rx10HzDataChannel{ m_rx10HzModule.GetOutputDataReference() };
        Rx10HzMessageModule m_rx10HzMessageModule10Hz { m_rx10HzDataChannel.GetBuffer(Task10Hz_t) };

        DataChannel< ServoData_S
                   , Task10Hz   // source task
                          >m_servoDataChannel{ m_servoModule.GetOutputDataReference() };
        ServoMessageModule m_servoMessageModule10Hz { m_servoDataChannel.GetBuffer(Task10Hz_t) };

        // 1Hz source
        DataChannel< KlineData_S
                   , Task1Hz    // source task
                          >m_klineDataChannel{ m_klineModule.GetOutputDataReference() };
        KlineMessageModule m_klineMessageModule1Hz { m_klineDataChannel.GetBuffer(Task1Hz_t) };

        static constexpr size_t m_numberOfDataChannels = 6U;
        DataChannelBase * const m_dataChannelList[m_numberOfDataChannels] =
        {
            // 100Hz source
            &m_adcDataChannel,
            &m_ioIntDataChannel,
            &m_rx100HzDataChannel,
            // 10Hz source
            &m_rx10HzDataChannel,
            &m_servoDataChannel,
            // 1Hz source
            &m_klineDataChannel,
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
                        , m_rxNoneModule
                        , m_txNoneModule
                    };
        TaskBase    m_task100Hz{
                          Task100Hz_t
                        , m_moduleList100Hz
                        , m_numberOfModules100Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                        , m_rx100HzModule
                        , m_tx100HzModule
                    };
        TaskBase    m_task10Hz{
                          Task10Hz_t
                        , m_moduleList10Hz
                        , m_numberOfModules10Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                        , m_rx10HzModule
                        , m_tx10HzModule
                    };
        TaskBase    m_task1Hz{
                          Task1Hz_t
                        , m_moduleList1Hz
                        , m_numberOfModules1Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                        , m_rxNoneModule
                        , m_tx1HzModule
                    };
};

} // namespace Eim

#endif // APP_HPP
