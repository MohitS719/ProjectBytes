// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Project_BytesHUD.generated.h"

UCLASS()
class AProject_BytesHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProject_BytesHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

