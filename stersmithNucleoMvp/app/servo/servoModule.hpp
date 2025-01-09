#ifndef SERVO_MODULE_HPP
#define SERVO_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "servoCommTypes.hpp"
#include "servoData.hpp"
#include "servoInterface.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class ServoModule final : public Shared::ModuleBase
{
    public:
        constexpr ServoModule(
                const ServoInputInterface& inputRef
            ) :
                ModuleBase(),
                m_inputData(inputRef)
        {}

        NOCOPY_NOMOVE(ServoModule);

        void Init(void) override;
        void Run(void) override;
        constexpr const ServoData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        const ServoInputInterface& m_inputData;

        ServoData_S m_outputData {};
        bool m_initialRead {false};

        // Data to set
        uint8_t m_idToSet {0U};
        float m_positionDegreesToSet {0.0F};
        float m_lossOfCommPositionDegreesToSet {0.0F};
        float m_lossOfCommTimeoutToSet {0.0F};

        void SanitizeInputs(void);

        uint16_t CalculateCrc(const uint8_t (&data)[SERVO_FRAME_NUM_DATA_BYTES]) const;
        bool VerifyCrc(const Servo_Comm_Frame_U& frame) const;
        bool VerifyResponse(const Servo_Request_E request, const Servo_Comm_Frame_U& frame, const uint16_t requestData) const;
        bool Transceive(const Servo_Request_E request, const bool checkRequest) const;
        bool PrepareRequest(const Servo_Request_E request, uint16_t& data) const;
        bool PrepareSpecialRequest(const Servo_Special_Request_E request, uint16_t& data) const;
        bool ProcessResponse(const Servo_Request_E request, const uint16_t data);
        bool SendRequest(const Servo_Request_E request, bool checkRequest=true);
        bool SendSpecialRequest(const Servo_Special_Request_E request);
};

} // namespace Eim

#endif // SERVO_MODULE_HPP
