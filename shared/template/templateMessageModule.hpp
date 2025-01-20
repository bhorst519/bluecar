#ifndef TEMPLATE_MESSAGE_MODULE_HPP
#define TEMPLATE_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "templateInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Template
{

class TemplateMessageModule final : public TemplateOutputInterface
{
    private:
        const TemplateData_S& m_dataRef;

    public:
        constexpr TemplateMessageModule(
                const TemplateData_S& dataRef
            ) :
                TemplateOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(TemplateMessageModule);

        virtual uint8_t GetCounter(void) const override
        {
            return m_dataRef.counter;
        }
};

} // namespace Template

#endif // TEMPLATE_MESSAGE_MODULE_HPP
