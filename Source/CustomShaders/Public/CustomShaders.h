// CustomShaders/Public/CustomShaders.h

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCustomShaders: public IModuleInterface {
public:
	virtual void StartupModule() override;
};