// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelScriptActor.generated.h"

UCLASS()
class SDW_UE_TEST_CM52_API AGameLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AGameLevelScriptActor();

private:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGamePanel> m_GamePanelClass;
	class UGamePanel* m_pGamePanel;
};
