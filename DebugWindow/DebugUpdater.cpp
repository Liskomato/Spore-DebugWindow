#include "stdafx.h"
#include "DebugUpdater.h"
#include "DebugWindowKeybind.h"

cDebugUpdater* cDebugUpdater::ptr = nullptr;

cDebugUpdater::cDebugUpdater()
{
	visible = false;
	hexDisplay = false;
	keybind = new DebugWindowKeybind();
}


cDebugUpdater::~cDebugUpdater()
{
}

cDebugUpdater* cDebugUpdater::Get() {
	if (ptr == nullptr) {
		ptr = new cDebugUpdater();
	}
	return ptr;
}

void cDebugUpdater::Initialize() {
	App::AddUpdateFunction(this);
}

void cDebugUpdater::Update() {
	if (Simulator::IsScenarioMode()) {
		if (ScenarioMode.GetMode() == App::cScenarioMode::Mode::PlayMode) {
			ScenarioPlayModeUpdate();
		}
		else if (WindowManager.GetMainWindow()->FindWindowByID(id("playModeDebug")) != nullptr) {
			WindowManager.GetMainWindow()->FindWindowByID(id("playModeDebug"))->SetVisible(false);
		}
			ScenarioDataUpdate();
	}
	else {
		if (WindowManager.GetMainWindow()->FindWindowByID(id("playModeDebug")) != nullptr) {
			WindowManager.GetMainWindow()->RemoveWindow(WindowManager.GetMainWindow()->FindWindowByID(id("playModeDebug")));
		}
		if (WindowManager.GetMainWindow()->FindWindowByID(id("dataDebug")) != nullptr) {
			WindowManager.GetMainWindow()->RemoveWindow(WindowManager.GetMainWindow()->FindWindowByID(id("dataDebug")));
		}
	}
}

void cDebugUpdater::Dispose() {
	WindowManager.GetMainWindow()->RemoveWinProc(keybind.get());
	keybind = nullptr;
	ptr = nullptr;
}

void cDebugUpdater::ScenarioPlayModeUpdate() {
	if (WindowManager.GetMainWindow()->FindWindowByID(id("playModeDebug")) != nullptr)
	{

		IWindowPtr debug = WindowManager.GetMainWindow()->FindWindowByID(id("playModeDebug"));
		debug->SetVisible(visible);
		if (debug->IsVisible())
		{
			string16 debugtext = u"cScenarioPlayMode fields:\n", debug2;
			cScenarioPlayModePtr play = ScenarioMode.GetPlayMode();
			auto avatar = GameNounManager.GetAvatar();
			int f_78 = play->field_78,
				f_90 = (int)play->mCurrentPlayModeState,
				f_94 = play->mCurrentEndCinematicState,
				cinDelay = play->mCinematicDelay.GetElapsedTime(),
				f_b0 = play->field_B0,
				f_b4 = play->field_B4,
				f_b8 = play->mCurrentActIndex,
				f_c0 = play->mCurrentTimeMS,
				f_c4 = play->mAdventurePoints,
				f_c8 = play->field_C8,
				f_cc = play->field_CC,
				f_d0 = play->field_D0,
				f_d4 = play->mCurrentDialogBoxIndex,
				f_d8 = play->field_D8,
				f_100 = play->field_100;
			float f_dc = play->mDistanceToClosestMoveToTarget,
				f_e0_x = play->mMoveToGoalLocation.x,
				f_e0_y = play->mMoveToGoalLocation.y,
				f_e0_z = play->mMoveToGoalLocation.z,
				f_f8 = play->mIntroFadeinTimer;
			bool f_ec = play->field_EC,
				f_fc = play->mIsIntroFadeinActive,
				f_fd = play->mIsAdventureActive;
			uint32_t musicID = play->mCurrentMusicId;
			long f_bc = play->mTimeLimitMS;

			Math::Vector3 avatar_pos = avatar->GetPosition();
			auto avatar_rot = avatar->GetOrientation();
			auto avatar_speed = avatar->GetVelocity();
			auto avatar_scale = avatar->GetScale();

			if (hexDisplay) {
				debug2.append_sprintf(u"field_78: %#010x\nmCurrentPlayModeState: %d\nmCurrentEndCinematicState: %d\nmCinematicDelay: %#010x\nfield_B0: %#010x\nfield_B4: %#010x\nmCurrentActIndex: %d\nmTimeLimitMS: %ld\nmCurrentTimeMS: %d\nmAdventurePoints: %d\nfield_C8: %#010x\nfield_CC: %#010x\nfield_D0: %#010x\nmCurrentDialogBoxIndex: %d\nfield_D8: %#010x\nmDistanceToClosestMoveToTarget: %f\nmMoveToGoalLocation: (%f, %f, %f)\nfield_EC: %s\nmCurrentMusicId: %#x\nfield_F8: %f\nmIsIntroFadeinActive: %s\nmIsAdventureActive: %s\nfield_100: %#010x\n", f_78, f_90, f_94, cinDelay, f_b0, f_b4, f_b8, f_bc, f_c0, f_c4, f_c8, f_cc, f_d0, f_d4, f_d8, f_dc, f_e0_x, f_e0_y, f_e0_z, f_ec ? u"true" : u"false", musicID, f_f8, f_fc ? u"true" : u"false", f_fd ? u"true" : u"false", f_100);
			}
			else {
				debug2.append_sprintf(u"field_78: %d\nmCurrentPlayModeState: %d\nmCurrentEndCinematicState: %d\nmCinematicDelay: %d\nfield_B0: %d\nfield_B4: %d\nmCurrentActIndex: %d\nmTimeLimitMS: %ld\nmCurrentTimeMS: %d\nmAdventurePoints: %d\nfield_C8: %d\nfield_CC: %d\nfield_D0: %d\nmCurrentDialogBoxIndex: %d\nfield_D8: %d\nmDistanceToClosestMoveToTarget: %f\nmMoveToGoalLocation: (%f, %f, %f)\nfield_EC: %s\nmCurrentMusicId: %#x\nfield_F8: %f\nmIsIntroFadeinActive: %s\nmIsAdventureActive: %s\nfield_100: %d\n", f_78, f_90, f_94, cinDelay, f_b0, f_b4, f_b8, f_bc, f_c0, f_c4, f_c8, f_cc, f_d0, f_d4, f_d8, f_dc, f_e0_x, f_e0_y, f_e0_z, f_ec ? u"true" : u"false", musicID, f_f8, f_fc ? u"true" : u"false", f_fd ? u"true" : u"false", f_100);
			}
			debug2.append_sprintf(u"\n\nAvatar data:\nPosition: (%f, %f, %f)\nOrientation: (%f, %f, %f, %f)\nVelocity: (%f, %f, %f)\nScale: %f",avatar_pos.x,avatar_pos.y,avatar_pos.z,avatar_rot.x,avatar_rot.y,avatar_rot.z,avatar_rot.w,avatar_speed.x,avatar_speed.y,avatar_speed.z,avatar_scale);
			debugtext += debug2;
			debug->SetCaption(debugtext.c_str());
		}
	}
}

void cDebugUpdater::ScenarioDataUpdate() {
	if (WindowManager.GetMainWindow()->FindWindowByID(id("dataDebug")) != nullptr)
	{

		IWindowPtr debug = WindowManager.GetMainWindow()->FindWindowByID(id("dataDebug"));
		debug->SetVisible(visible);
		if (debug->IsVisible())
		{
			string16 debugtext = u"cScenarioData fields:\n", debug2;
			auto data = ScenarioMode.GetData();
			auto avatar = GameNounManager.GetAvatar();
			
			int& data_f18 = data->field_18,
				data_f20 = data->field_20,
				data_f24 = data->field_24,
				data_f28 = data->field_28,
				data_f30 = data->field_30,
				data_f34 = data->field_34,
				data_f40 = data->field_40,
				data_f44 = data->field_44,
				data_f48 = data->field_48,
				data_f80 = data->field_80,
				data_f88 = data->field_88,
				data_fE8 = data->field_E8,
				data_fEC = data->field_EC,
				data_fF0 = data->field_F0,
				data_fF4 = data->field_F4,
				data_fF8 = data->field_F8,
				data_fFC = data->field_FC,
				data_f100 = data->field_100,
				data_f104 = data->field_104,
				data_f108 = data->field_108,
				data_f10C = data->field_10C,
				data_f110 = data->field_110,
				data_f114 = data->field_114,
				data_f118 = data->field_118,
				data_f11C = data->field_11C,
				data_f120 = data->field_120;

			debug2.append_sprintf(u"BOOLS\nmHasLoaded: %s\nmHadMissingAssets: %s\nmGenreHasChanged: %s\nmMetadataHasChanged: %s\nfield_1C: %s\nfield_2C: %s\n",data->mHasLoaded ? u"true" : u"false",data->mHadMissingAssets ? u"true" : u"false",data->mGenreHasChanged ? u"true" : u"false",data->mMetadataHasChanged ? u"true" : u"false",data->field_1C ? u"true" : u"false",data->field_2C ? u"true" : u"false");
			if (hexDisplay) {
				debug2.append_sprintf(u"INTEGERS\nfield_18: %#010x\nfield_20: %#010x\nfield_24: %#010x\nfield_28: %#010x\nfield_30: %#010x\nfield_34: %#010x\nfield_40: %#010x\nfield_44: %#010x\nfield_48: %#010x\nfield_88: %#010x\nfield_E8: %#010x\nfield_EC: %#010x\nfield_F0: %#010x\nfield_F4: %#010x\nfield_F8: %#010x\nfield_FC: %#010x\nfield_100: %#010x\nfield_104: %#010x\nfield_108: %#010x\nfield_10C: %#010x\nfield_110: %#010x\nfield_114: %#010x\nfield_118: %#010x\nfield_11C: %#010x\nfield_120: %#010x", data_f18, data_f20, data_f24, data_f28, data_f30, data_f34, data_f40, data_f44, data_f48, data_f80, data_f88, data_fE8, data_fEC, data_fF0, data_fF4, data_fF8, data_fFC, data_f100, data_f104, data_f108, data_f10C, data_f110, data_f114, data_f118, data_f11C, data_f120);
			}
			else {
				debug2.append_sprintf(u"INTEGERS\nfield_18: %d\nfield_20: %d\nfield_24: %d\nfield_28: %d\nfield_30: %d\nfield_34: %d\nfield_40: %d\nfield_44: %d\nfield_48: %d\nfield_88: %d\nfield_E8: %d\nfield_EC: %d\nfield_F0: %d\nfield_F4: %d\nfield_F8: %d\nfield_FC: %d\nfield_100: %d\nfield_104: %d\nfield_108: %d\nfield_10C: %d\nfield_110: %d\nfield_114: %d\nfield_118: %d\nfield_11C: %d\nfield_120: %d", data_f18, data_f20, data_f24, data_f28, data_f30, data_f34, data_f40, data_f44, data_f48, data_f80, data_f88, data_fE8, data_fEC, data_fF0, data_fF4, data_fF8, data_fFC, data_f100, data_f104, data_f108, data_f10C, data_f110, data_f114, data_f118, data_f11C, data_f120);
			}
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
