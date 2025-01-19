#ifndef TEMPLATE_MODULE_HPP
#define TEMPLATE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "nocopy.hpp"
#include "templateInterface.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Template
{

static constexpr uint8_t COUNTER_INIT   { 50U };
static constexpr uint8_t COUNTER_MAX    { 100U };

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/

/***************************************************************************************************
*                     P U B L I C   F U N C T I O N   D E C L A R A T I O N S                      *
***************************************************************************************************/

/***************************************************************************************************
*                          P U B L I C   I N L I N E   F U N C T I O N S                           *
***************************************************************************************************/

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
class TemplateModule final : public Shared::ModuleBase
{
    public:
        constexpr TemplateModule(
                const TemplateInputInterface& inputRef
            ) :
                ModuleBase(),
                m_inputData(inputRef)
        {}

        NOCOPY_NOMOVE(TemplateModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const TemplateData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        const TemplateInputInterface& m_inputData;

        TemplateData_S m_outputData {};

        void IncrementCounter(uint8_t& counter) const;
};

} // namespace Template

#endif // TEMPLATE_MODULE_HPP
