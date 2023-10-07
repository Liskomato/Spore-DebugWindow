#include "stdafx.h"
#include "EnableDebug.h"
#include "DebugUpdater.h"

EnableDebug::EnableDebug()
{
}


EnableDebug::~EnableDebug()
{
}


void EnableDebug::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.

	DebugUpdater.visible = !DebugUpdater.visible;
	App::ConsolePrintF("Debug window status: %s",DebugUpdater.visible ? "Enabled" : "Disabled");

}

const char* EnableDebug::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Enables Debug Window.";
	}
	else {
		return "EnableDebug: Toggles the visibility of the debug window added with the Debug Window mod.";
	}
}
