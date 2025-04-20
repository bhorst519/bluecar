#ifndef TACH_MESSAGE_MODULE_HPP
#define TACH_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "tachInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class TachMessageModule final : public TachOutputInterface
{
    private:
        const TachData_S& m_dataRef;

    public:
        constexpr TachMessageModule(
                const TachData_S& dataRef
            ) :
                TachOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(TachMessageModule);

        virtual float_q GetFreq(void) const override
        {
            return m_dataRef.freq;
        }

        virtual float_q GetRpm(void) const override
        {
            return m_dataRef.rpm;
        }
};

} // namespace Eim

#endif // TACH_MESSAGE_MODULE_HPP
