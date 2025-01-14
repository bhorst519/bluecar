/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "taskBase.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Shared
{

void TaskBase::Init(void) const
{
    Update();

    for (size_t i = 0U; i < m_numberOfModules; i++)
    {
        if (m_pModulePtrList[i] != nullptr)
        {
            m_pModulePtrList[i]->Init();
        }
    }

    Publish();
}

void TaskBase::Run(void) const
{
    Update();
    m_rxModuleRef.Receive();

    // Execute modules in list order
    for (size_t i = 0U; i < m_numberOfModules; i++)
    {
        if (m_pModulePtrList[i] != nullptr)
        {
            m_pModulePtrList[i]->Run();
        }
    }

    m_txModuleRef.Transmit();
    Publish();
}

void TaskBase::Update(void) const
{
    for (size_t i = 0U; i < m_numberOfDataChannels; i++)
    {
        if (m_pDataChannelPtrList[i] != nullptr)
        {
            m_pDataChannelPtrList[i]->Update(m_taskId);
        }
    }
}

void TaskBase::Publish(void) const
{
    for (size_t i = 0U; i < m_numberOfDataChannels; i++)
    {
        if (m_pDataChannelPtrList[i] != nullptr)
        {
            m_pDataChannelPtrList[i]->Publish(m_taskId);
        }
    }
}

} // namespace Shared
