// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/GameLevelScriptActor.h"

#include "Blueprint/UserWidget.h"
#include "UE/GamePanel.h"

AGameLevelScriptActor::AGameLevelScriptActor()
	: m_pGamePanel(nullptr)
{
}

void AGameLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	m_pGamePanel = CreateWidget<UGamePanel>(GetWorld(), m_GamePanelClass);
	if (m_pGamePanel != nullptr)
	{
		m_pGamePanel->AddToViewport();
	}
}
