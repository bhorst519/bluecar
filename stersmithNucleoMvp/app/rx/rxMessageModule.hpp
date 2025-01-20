#ifndef RX_MESSAGE_MODULE_HPP
#define RX_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "rxInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class Rx10HzMessageModule final : public Rx10HzOutputInterface
{
    private:
        const Rx10HzData_S& m_dataRef;

    public:
        constexpr Rx10HzMessageModule(
                const Rx10HzData_S& dataRef
            ) :
                Rx10HzOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(Rx10HzMessageModule);

        virtual float_q GetServoPositionRequest(void) const override
        {
            return m_dataRef.servoPositionRequest;
        }
};

} // namespace Eim

#endif // RX_MESSAGE_MODULE_HPP
