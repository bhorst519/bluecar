#ifndef IO_INT_MODULE_HPP
#define IO_INT_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "ioIntInterface.hpp"
#include "moduleBase.hpp"
#include "nocopy.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class IoIntModule final : public Shared::ModuleBase
{
    public:
        constexpr IoIntModule(
                const IoIntInputInterface& inputRef
            ) :
                ModuleBase(),
                m_inputData(inputRef)
        {}

        NOCOPY_NOMOVE(IoIntModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const IoIntData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        const IoIntInputInterface& m_inputData;

        IoIntData_S m_outputData {};
        GearSelect_E m_gearSelectCandidate {GearSelect_E::ERROR};
        uint8_t m_gearSelectCandidateCounter {0U};
        bool * m_pGears[MAX_NUM_GEAR_SELECT] { // Order must align with GearSelect_E
            &m_outputData.gearN,
            &m_outputData.gear1,
            &m_outputData.gear2,
            &m_outputData.gear3,
            &m_outputData.gear4,
            &m_outputData.gear5,
            &m_outputData.gear6,
        };

        void ProcessIO(void);
        void GearSelect(void);
};

} // namespace Eim

#endif // IO_INT_MODULE_HPP
