#include "stdafx.h"
#include "DebugWindowKeybind.h"
#include "DebugUpdater.h"

DebugWindowKeybind::DebugWindowKeybind()
{
}


DebugWindowKeybind::~DebugWindowKeybind()
{
}

// For internal use, do not modify.
int DebugWindowKeybind::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int DebugWindowKeybind::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* DebugWindowKeybind::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(DebugWindowKeybind);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int DebugWindowKeybind::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool DebugWindowKeybind::HandleUIMessage(IWindow* window, const Message& message)
{
	if (message.IsType(kMsgKeyDown) && (message.Key.vkey == '§' || message.Key.vkey == '`') && message.Key.modifiers == kModifierAltDown) {
		DebugUpdater.visible = !DebugUpdater.visible;
		return true;
	}
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
