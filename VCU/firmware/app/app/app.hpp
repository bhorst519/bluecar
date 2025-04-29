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
#include "rxModule.hpp"
#include "txModule.hpp"

// Message modules
#include "adcMessageModule.hpp"
#include "ioIntMessageModule.hpp"
#include "rxMessageModule.hpp"

// Input message modules

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

        // Inputs

        // Modules
        AdcModule m_adcModule {};
        IoIntModule m_ioIntModule {};

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

        // Inputs

        // Modules

        // Module list
        // static constexpr size_t m_numberOfModules10Hz = 0U;
        // ModuleBase * const m_moduleList10Hz[m_numberOfModules10Hz] =
        // {
        // };

        //------------------------------------------------------------------------------------------
        // 1Hz objects
        //------------------------------------------------------------------------------------------
        // TX/RX modules
        Tx1HzModule m_tx1HzModule {};

        // Inputs

        // Modules

        // Module list
        // static constexpr size_t m_numberOfModules1Hz = 0U;
        // ModuleBase * const m_moduleList1Hz[m_numberOfModules1Hz] =
        // {
        // };

        //------------------------------------------------------------------------------------------
        // Data channels
        //------------------------------------------------------------------------------------------
        DataChannel< AdcData_S
                   , Task100Hz  // source task
                          >m_adcDataChannel{ m_adcModule.GetOutputDataReference() };
        AdcMessageModule m_adcMessageModule100Hz { m_adcDataChannel.GetBuffer(Task100Hz_t) };

        DataChannel< IoIntData_S
                   , Task100Hz  // source task
                          >m_ioIntDataChannel{ m_ioIntModule.GetOutputDataReference() };
        IoIntMessageModule m_ioIntMessageModule100Hz { m_ioIntDataChannel.GetBuffer(Task100Hz_t) };

        static constexpr size_t m_numberOfDataChannels = 2U;
        DataChannelBase * const m_dataChannelList[m_numberOfDataChannels] =
        {
            // 1kHz source
            // 100Hz source
            &m_adcDataChannel,
            &m_ioIntDataChannel,
            // 10Hz source
            // 1Hz source
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
                        , m_rxNoneModule
                        , m_txNoneModule
                    };
        TaskBase    m_task10Hz{
                          Task10Hz_t
                        // , m_moduleList10Hz
                        // , m_numberOfModules10Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                        , m_rxNoneModule
                        , m_txNoneModule
                    };
        TaskBase    m_task1Hz{
                          Task1Hz_t
                        // , m_moduleList1Hz
                        // , m_numberOfModules1Hz
                        , m_dataChannelList
                        , m_numberOfDataChannels
                        , m_rxNoneModule
                        , m_tx1HzModule
                    };
};

} // namespace Vcu

#endif // APP_HPP
