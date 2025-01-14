#ifndef KLINE_MESSAGE_MODULE_HPP
#define KLINE_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "klineData.hpp"
#include "klineInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class KlineMessageModule final : public KlineOutputInterface
{
    private:
        const KlineData_S& m_dataRef;

    public:
        constexpr KlineMessageModule(
                const KlineData_S& dataRef
            ) :
                KlineOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(KlineMessageModule);

        virtual float_q GetBatteryVoltage(void) const override
        {
            return m_dataRef.batteryVoltage;
        }

        virtual float_q GetEctTemp(void) const override
        {
            return m_dataRef.ectTemp;
        }

        virtual float_q GetEctVoltage(void) const override
        {
            return m_dataRef.ectVoltage;
        }

        virtual float_q GetIatTemp(void) const override
        {
            return m_dataRef.iatTemp;
        }

        virtual float_q GetIatVoltage(void) const override
        {
            return m_dataRef.iatVoltage;
        }

        virtual float_q GetMapPressure(void) const override
        {
            return m_dataRef.mapPressure;
        }

        virtual float_q GetMapVoltage(void) const override
        {
            return m_dataRef.mapVoltage;
        }

        virtual uint16_q GetRpm(void) const override
        {
            return m_dataRef.rpm;
        }

        virtual float_q GetTpsAngle(void) const override
        {
            return m_dataRef.tpsAngle;
        }

        virtual float_q GetTpsVoltage(void) const override
        {
            return m_dataRef.tpsVoltage;
        }

        virtual float_q GetVehicleSpeed(void) const override
        {
            return m_dataRef.vehicleSpeed;
        }
};

} // namespace Eim

#endif // KLINE_MESSAGE_MODULE_HPP
