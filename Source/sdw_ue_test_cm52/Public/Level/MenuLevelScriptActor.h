// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MenuLevelScriptActor.generated.h"

UCLASS()
class SDW_UE_TEST_CM52_API AMenuLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AMenuLevelScriptActor();

private:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuPanel> m_MenuPanelClass;
	class UMenuPanel* m_pMenuPanel;
};
