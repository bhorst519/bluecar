#ifndef TACH_MODULE_HPP
#define TACH_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "nocopy.hpp"
#include "tachInterface.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class TachModule final : public Shared::ModuleBase
{
    public:
        constexpr TachModule(
            ) :
                ModuleBase()
        {}

        NOCOPY_NOMOVE(TachModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const TachData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        TachData_S m_outputData {};
};

} // namespace Eim

#endif // TACH_MODULE_HPP
