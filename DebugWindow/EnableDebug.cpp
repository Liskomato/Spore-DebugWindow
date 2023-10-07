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

}

const char* EnableDebug::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "EnableDebug: Elaborate description of what this cheat does.";
	}
}
