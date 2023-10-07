#include "stdafx.h"
#include "DebugUpdater.h"
#include "DebugWindowKeybind.h"

cDebugUpdater::cDebugUpdater()
{
	visible = false;
	keybind = new DebugWindowKeybind();
}


cDebugUpdater::~cDebugUpdater()
{
	keybind = nullptr;
}

cDebugUpdater* cDebugUpdater::Get() {
	if (ptr == nullptr) {
		ptr = new cDebugUpdater();
		return ptr;
	}
	else {
		return ptr;
	}
}

void cDebugUpdater::Initialize() {
	App::AddUpdateFunction(this);
}

void cDebugUpdater::Update() {
	if (Simulator::IsScenarioMode() && ScenarioMode.GetMode() == App::cScenarioMode::Mode::PlayMode) {
		ScenarioPlayModeUpdate();
	}
	else {
		if (WindowManager.GetMainWindow()->FindWindowByID(id("TextDebug")) != nullptr) {
			WindowManager.GetMainWindow()->RemoveWindow(WindowManager.GetMainWindow()->FindWindowByID(id("TextDebug")));
		}
	}
}

void cDebugUpdater::Dispose() {
	ptr = nullptr;
}

void cDebugUpdater::ScenarioPlayModeUpdate() {
	if (WindowManager.GetMainWindow()->FindWindowByID(id("TextDebug")) != nullptr)
	{

		IWindowPtr debug = WindowManager.GetMainWindow()->FindWindowByID(id("TextDebug"));
		debug->SetVisible(visible);
		if (debug->IsVisible())
		{
			string16 debugtext = u"cScenarioPlayMode fields:\n", debug2;
			cScenarioPlayModePtr play = ScenarioMode.GetPlayMode();
			int f_78 = play->field_78,
				f_90 = play->field_90,
				f_94 = play->field_94,
				cinDelay = play->mCinematicDelay.GetElapsedTime(),
				f_b0 = play->field_B0,
				f_b4 = play->field_B4,
				f_b8 = play->mCurrentActIndex,
				f_c0 = play->mCurrentTimeMS,
				f_c4 = play->mAdventurePoints,
				f_c8 = play->field_C8,
				f_cc = play->field_CC,
				f_d0 = play->field_D0,
				f_d4 = play->field_D4,
				f_d8 = play->field_D8,
				f_100 = play->field_100;
			float f_dc = play->field_DC,
				f_e0_x = play->field_E0.x,
				f_e0_y = play->field_E0.y,
				f_e0_z = play->field_E0.z,
				f_f8 = play->field_F8;
			bool f_ec = play->field_EC,
				f_fc = play->field_FC,
				f_fd = play->field_FD;
			uint32_t musicID = play->mCurrentMusicId;
			long f_bc = play->mTimeLimitMS;

			debug2.append_sprintf(u"field_78: %d\nfield_90: %d\nfield_94: %d\nmCinematicDelay: %d\nfield_B0: %d\nfield_B4: %d\nmCurrentActIndex: %d\nmTimeLimitMS: %ld\nmCurrentTimeMS: %d\nmAdventurePoints: %d\nfield_C8: %d\nfield_CC: %d\nfield_D0: %d\nfield_D4: %d\nfield_D8: %d\nfield_DC: %f\nfield_E0: (%f, %f, %f)\nfield_EC: %s\nmCurrentMusicId: %#x\nfield_F8: %f\nfield_FC: %s\nfield_FD: %s\nfield_100: %d\n", f_78, f_90, f_94, cinDelay, f_b0, f_b4, f_b8, f_bc, f_c0, f_c4, f_c8, f_cc, f_d0, f_d4, f_d8, f_dc, f_e0_x, f_e0_y, f_e0_z, f_ec ? u"true" : u"false", musicID, f_f8, f_fc ? u"true" : u"false", f_fd ? u"true" : u"false", f_100);
			debugtext += debug2;
			debug->SetCaption(debugtext.c_str());
		}
	}
}

// For internal use, do not modify.
int cDebugUpdater::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cDebugUpdater::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cDebugUpdater::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cDebugUpdater);
	return nullptr;
}
