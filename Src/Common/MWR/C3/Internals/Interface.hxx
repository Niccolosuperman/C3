#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename BridgeT>
void MWR::C3::Interface<BridgeT>::OnAttach(std::shared_ptr<BridgeT> const& bridge)
{
	// Store relay pointer.
	m_Bridge = bridge;

	// Pass all previously stored messages to the Relay.
	for (auto& element : m_PreLog)
		bridge->Log(element);

	// Release internal buffer to save memory.
	std::vector<LogMessage>().swap(m_PreLog);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename BridgeT>
void MWR::C3::Interface<BridgeT>::Log(LogMessage const& message)
{
	// If Relay is already connected then forward this call. Otherwise store messages internally until we get connected.
	if (auto bridge = GetBridge())
		bridge->Log(message);
	else
		m_PreLog.push_back(message);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename BridgeT>
void MWR::C3::Interface<BridgeT>::Detach()
{
	if (auto bridge = GetBridge())
	{
		bridge->Detach();
		m_Bridge.reset();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename BridgeT>
MWR::ByteVector MWR::C3::Interface<BridgeT>::OnRunCommand(ByteView command)
{
	throw std::logic_error{ OBF("This Device doesn't support any Commands.") };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename BridgeT>
std::shared_ptr<BridgeT> MWR::C3::Interface<BridgeT>::GetBridge() const
{
	return m_Bridge.lock();
}
