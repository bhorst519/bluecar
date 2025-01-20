#ifndef TEMPLATE_INTERFACE_HPP
#define TEMPLATE_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "templateData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Template
{

class TemplateInputInterface
{
    public:
        constexpr TemplateInputInterface()
        {}

        NOCOPY_NOMOVE(TemplateInputInterface);

        virtual bool GetInputBool(void) const = 0;
};

class TemplateOutputInterface
{
    public:
        constexpr TemplateOutputInterface()
        {}

        NOCOPY_NOMOVE(TemplateOutputInterface);

        virtual uint8_t GetCounter(void) const = 0;
};

} // namespace Template

#endif // TEMPLATE_INTERFACE_HPP
