#ifndef IO_INT_MESSAGE_MODULE_HPP
#define IO_INT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "ioIntInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
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

        virtual bool GetGearN(void) const override
        {
            return m_dataRef.gearN;
        }

        virtual bool GetGear1(void) const override
        {
            return m_dataRef.gear1;
        }

        virtual bool GetGear2(void) const override
        {
            return m_dataRef.gear2;
        }

        virtual bool GetGear3(void) const override
        {
            return m_dataRef.gear3;
        }

        virtual bool GetGear4(void) const override
        {
            return m_dataRef.gear4;
        }

        virtual bool GetGear5(void) const override
        {
            return m_dataRef.gear5;
        }

        virtual bool GetGear6(void) const override
        {
            return m_dataRef.gear6;
        }

        virtual GearSelect_E GetGearSelect(void) const override
        {
            return m_dataRef.gearSelect;
        }
};

} // namespace Eim

#endif // IO_INT_MESSAGE_MODULE_HPP
