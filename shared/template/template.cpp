/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "template.hpp"
#include "template.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static uint8_t gCounter {0U};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
extern "C" {

void TemplateInit(void)
{
    gCounter = 0U;
}

void TemplateRun(void)
{
    ++gCounter;
}

} // extern "C"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Template
{

void TemplateClass::Init(void)
{
    m_counter = COUNTER_INIT;
}

void TemplateClass::Run(void)
{
    IncrementCounter(m_counter);
}

void TemplateClass::IncrementCounter(uint8_t& counter) const
{
    if (++counter > COUNTER_MAX)
    {
        counter = 0U;
    }
}

} // namespace Template