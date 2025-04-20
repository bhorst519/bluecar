#ifndef KLINE_MODULE_HPP
#define KLINE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "klineCommTypes.hpp"
#include "klineData.hpp"
#include "klineInterface.hpp"
#include "moduleBase.hpp"

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
        constexpr const KlineData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        KlineData_S m_outputData {};
        Kline_State_E m_state {Kline_State_E::INIT_PEND};

        // State management
        Kline_State_E RunStateMachine(void);
        Kline_State_E RunInitPendState(void) const;
        Kline_State_E RunInitState(void);
        Kline_State_E RunActiveState(void);
        void ExecuteStateTransition(const Kline_State_E nextState);

        // Communication
        uint8_t CalculateCrc(const uint8_t * const pData, const uint8_t numBytes) const;
        bool VerifyCrc(const Kline_Comm_Response_U * const pResponse) const;
        bool VerifyResponse(const Kline_Comm_Request_U * const pRequest, const Kline_Comm_Response_U * const pResponse) const;
        bool Transceive(const Kline_Request_E request, Kline_Comm_Response_U *& pResponse) const;
        bool SendRequest(const Kline_Request_E request);

        // Process data
        void ProcessData(const Kline_Comm_TableResponse_S * const pTableResponse);
        void InvalidateData(void);
};

} // namespace Eim

#endif // KLINE_MODULE_HPP
