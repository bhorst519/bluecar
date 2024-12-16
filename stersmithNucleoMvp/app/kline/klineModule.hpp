#ifndef KLINE_MODULE_HPP
#define KLINE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "klineCommTypes.hpp"
#include "moduleBase.hpp"
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

enum class Kline_State_E
{
    INIT_PEND,
    INIT,
    ACTIVE,
};

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
class KlineModule final : public Shared::ModuleBase
{
    public:
        constexpr KlineModule(
            ) :
                ModuleBase()
        {}

        NOCOPY_NOMOVE(KlineModule);

        virtual void Init(void) override;
        virtual void Run(void) override;

        uint16_t GetRpm(void) const;
        float GetTpsVoltage(void) const;
        float GetTpsAngle(void) const;
        float GetEctVoltage(void) const;
        float GetEctTemp(void) const;
        float GetIatVoltage(void) const;
        float GetIatTemp(void) const;
        float GetMapVoltage(void) const;
        float GetMapPressure(void) const;
        float GetBatteryVoltage(void) const;
        float GetVehicleSpeed(void) const;

    private:
        Kline_State_E m_state {Kline_State_E::INIT_PEND};
        uint16_t m_rpm {0U};
        float m_tpsVoltage {0.0F};
        float m_tpsAngle {0.0F};
        float m_ectVoltage {0.0F};
        float m_ectTemp {0.0F};
        float m_iatVoltage {0.0F};
        float m_iatTemp {0.0F};
        float m_mapVoltage {0.0F};
        float m_mapPressure {0.0F};
        float m_batteryVoltage {0.0F};
        float m_vehicleSpeed {0.0F};

        // State management
        Kline_State_E RunStateMachine(void);
        Kline_State_E RunInitPendState(void) const;
        Kline_State_E RunInitState(void);
        Kline_State_E RunActiveState(void);
        void ExecuteStateTransition(const Kline_State_E nextState) const;

        // Communication
        uint8_t CalculateCrc(const uint8_t * const pData, const uint8_t numBytes) const;
        bool VerifyCrc(const Kline_Comm_Response_U * const pResponse) const;
        bool VerifyResponse(const Kline_Comm_Request_U * const pRequest, const Kline_Comm_Response_U * const pResponse) const;
        bool Transceive(const Kline_Request_E request, Kline_Comm_Response_U * pResponse) const;
        bool SendRequest(const Kline_Request_E request);

        // Process data
        void ProcessData(const Kline_Comm_TableResponse_S * const pTableResponse);
};

} // namespace Eim

#endif // KLINE_MODULE_HPP
