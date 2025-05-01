#ifndef IO_INT_MESSAGE_MODULE_HPP
#define IO_INT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "ioIntInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Vcu
{

class IoIntMessageModule final : public IoIntOutputInterface
{
    private:
        const IoIntData_S& m_dataRef;

    public:
        constexpr IoIntMessageModule(
                const IoIntData_S& dataRef
            ) :
                IoIntOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(IoIntMessageModule);

        virtual bool GetBrakeSwitch(void) const override
        {
            return m_dataRef.brakeSwitch;
        }

        virtual bool GetEngineEnable(void) const override
        {
            return m_dataRef.engineEnable;
        }

        virtual bool GetEngineStart(void) const override
        {
            return m_dataRef.engineStart;
        }

        virtual bool GetUserSwitch(void) const override
        {
            return m_dataRef.userSwitch;
        }
};

} // namespace Vcu

#endif // IO_INT_MESSAGE_MODULE_HPP
