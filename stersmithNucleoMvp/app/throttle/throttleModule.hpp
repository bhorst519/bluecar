#ifndef THROTTLE_MODULE_HPP
#define THROTTLE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "throttleCommTypes.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class ThrottleModule final : public Shared::ModuleBase
{
    public:
        constexpr ThrottleModule()
        {}

        NOCOPY_NOMOVE(ThrottleModule);

        void Init(void) override;
        void Run(void) override;

    private:
        uint8_t m_id {};

        uint16_t CalculateCrc(const uint8_t (&data)[THROTTLE_FRAME_NUM_DATA_BYTES]) const;
        bool VerifyCrc(const Throttle_Comm_Frame_U& frame) const;
        bool SendRequest(const Throttle_Request_E request, bool checkRequest) const;
        bool SendSpecialRequest(const Throttle_Special_Request_E request, bool checkRequest) const;
};

} // namespace Eim

#endif // THROTTLE_MODULE_HPP
