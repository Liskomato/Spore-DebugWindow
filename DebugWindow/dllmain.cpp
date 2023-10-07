// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "EnableDebug.h"
#include "DebugUpdater.h"

UILayoutPtr debugWindow = nullptr;

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	DebugUpdater.Initialize();
	CheatManager.AddCheat("debugwindow",new EnableDebug());
}

member_detour(cScenarioPlayMode_Initialize_detour, Simulator::cScenarioPlayMode, void(void)) {

	void detoured()
	{
		// We want the original function to run first, so we can do our things afterwards.
		original_function(this);
		// Debug text layout
		IWindowPtr text;
		if (debugWindow->LoadByName(u"TimerDebug")) {
			debugWindow->SetParentWindow(WindowManager.GetMainWindow());
			if (debugWindow->FindWindowByID(id("TextDebug")) != nullptr) {
				text = debugWindow->FindWindowByID(id("TextDebug"));
				text->SetLocation(10, 400);
				text->SetVisible(DebugUpdater.visible);
				if (DebugUpdater.keybind != nullptr) {
					text->AddWinProc(DebugUpdater.keybind.get());
				}
			}
		}


	}

};

void Dispose()
{
	DebugUpdater.Dispose();
	debugWindow = nullptr;
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
	cScenarioPlayMode_Initialize_detour::attach(GetAddress(Simulator::cScenarioPlayMode, Initialize));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

