#ifndef MODULE_BASE_HPP
#define MODULE_BASE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Shared
{

class ModuleBase
{
    public:
        constexpr ModuleBase()
        {}

        NOCOPY_NOMOVE(ModuleBase);

        virtual void Init(void) = 0;
        virtual void Run(void) = 0;
};

} // namespace Shared

#endif // MODULE_BASE_HPP
