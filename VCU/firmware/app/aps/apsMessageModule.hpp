#ifndef APS_MESSAGE_MODULE_HPP
#define APS_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "apsInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Vcu
{

class ApsMessageModule final : public ApsOutputInterface
{
    private:
        const ApsData_S& m_dataRef;

    public:
        constexpr ApsMessageModule(
                const ApsData_S& dataRef
            ) :
                ApsOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(ApsMessageModule);

        virtual float_q GetAps1Frac(void) const override
        {
            return m_dataRef.aps1Frac;
        }

        virtual float_q GetAps2Frac(void) const override
        {
            return m_dataRef.aps2Frac;
        }
};

} // namespace Vcu

#endif // APS_MESSAGE_MODULE_HPP
