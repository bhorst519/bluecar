#ifndef APP_HPP
#define APP_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "dataChannel.hpp"
#include "halWrappersComponentSpecific.hpp"
#include "nocopy.hpp"
#include "taskBase.hpp"

// Modules
#include "adcModule.hpp"
#include "canModule.hpp"
#include "ioIntModule.hpp"
#include "klineModule.hpp"
#include "rxModule.hpp"
#include "servoModule.hpp"
#include "tachModule.hpp"
#include "throttleModule.hpp"
#include "txModule.hpp"

// Message modules
#include "adcMessageModule.hpp"
#include "ioIntMessageModule.hpp"
#include "klineMessageModule.hpp"
#include "rxMessageModule.hpp"
#include "servoMessageModule.hpp"
#include "tachMessageModule.hpp"
#include "throttleMessageModule.hpp"

// Input message modules
#include "ioIntInputMessageModule.hpp"
#include "servoInputMessageModule.hpp"
#include "throttleInputMessageModule.hpp"

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

        using KlineModule           = Shared::KlineModule;
        using KlineData_S           = Shared::KlineData_S;
        using KlineMessageModule    = Shared::KlineMessageModule;

        using ServoModule           = Shared::ServoModule;
        using ServoData_S           = Shared::ServoData_S;
        using ServoMessageModule    = Shared::ServoMessageModule;

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
        Tx1kHzModule m_tx1kHzModule {
            m_tachMessageModule1kHz
        };

        // Inputs

        // Modules
        CanModule m_canModule {};
        TachModule m_tachModule {};

        // Module list
        static constexpr size_t m_numberOfModules1kHz = 2U;
        ModuleBase * const m_moduleList1kHz[m_numberOfModules1kHz] =
        {
            &m_canModule,
            &m_tachModule,
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
            m_throttleMessageModule10Hz
        };
        ThrottleInputMessageModule m_throttleInput {
            m_rx10HzMessageModule10Hz
        };

        // Modules
        ServoModule m_servoModule {
            m_servoInput,
            gHalWrappers,
            gHalWrappers,
        };
        ThrottleModule m_throttleModule {
            m_throttleInput
        };

        // Module list
        static constexpr size_t m_numberOfModules10Hz = 2U;
        ModuleBase * const m_moduleList10Hz[m_numberOfModules10Hz] =
        {
            &m_throttleModule,
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
        KlineModule m_klineModule {
            gHalWrappers,
            gHalWrappers
        };

        // Module list
        static constexpr size_t m_numberOfModules1Hz = 1U;
        ModuleBase * const m_moduleList1Hz[m_numberOfModules1Hz] =
        {
            &m_klineModule,
        };

        //------------------------------------------------------------------------------------------
        // Data channels
        //------------------------------------------------------------------------------------------
        // 1kHz source
        DataChannel< TachData_S
                   , Task1kHz   // source task
                          >m_tachDataChannel{ m_tachModule.GetOutputDataReference() };
        TachMessageModule m_tachMessageModule1kHz { m_tachDataChannel.GetBuffer(Task1kHz_t) };

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

        DataChannel< ThrottleData_S
                   , Task10Hz   // source task
                             >m_throttleDataChannel{ m_throttleModule.GetOutputDataReference() };
        ThrottleMessageModule m_throttleMessageModule10Hz { m_throttleDataChannel.GetBuffer(Task10Hz_t) };

        // 1Hz source
        DataChannel< KlineData_S
                   , Task1Hz    // source task
                          >m_klineDataChannel{ m_klineModule.GetOutputDataReference() };
        KlineMessageModule m_klineMessageModule1Hz { m_klineDataChannel.GetBuffer(Task1Hz_t) };

        static constexpr size_t m_numberOfDataChannels = 8U;
        DataChannelBase * const m_dataChannelList[m_numberOfDataChannels] =
        {
            // 1kHz source
            &m_tachDataChannel,
            // 100Hz source
            &m_adcDataChannel,
            &m_ioIntDataChannel,
            &m_rx100HzDataChannel,
            // 10Hz source
            &m_rx10HzDataChannel,
            &m_servoDataChannel,
            &m_throttleDataChannel,
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
                        , m_tx1kHzModule
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
