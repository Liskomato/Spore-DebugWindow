#pragma once

#include <Spore\BasicIncludes.h>
#include "DebugWindowKeybind.h"

#define DebugUpdaterPtr intrusive_ptr<DebugUpdater>
#define DebugUpdater (*cDebugUpdater::Get())

class cDebugUpdater 
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("DebugUpdater");
	static cDebugUpdater* Get();

	void Initialize();
	void Dispose();

	bool visible;
	DebugWindowKeybindPtr keybind;
	
	~cDebugUpdater();

	void ScenarioPlayModeUpdate();
	
	int AddRef() override;
	int Release() override;
	void Update() override;
	void* Cast(uint32_t type) const override;
private:
	cDebugUpdater();
	static cDebugUpdater* ptr;
};
