// Fill out your copyright notice in the Description page of Project Settings.

#include "Level/MenuLevelScriptActor.h"

#include "Blueprint/UserWidget.h"
#include "UE/MenuPanel.h"

AMenuLevelScriptActor::AMenuLevelScriptActor()
	: m_pMenuPanel(nullptr)
{
}

void AMenuLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	m_pMenuPanel = CreateWidget<UMenuPanel>(GetWorld(), m_MenuPanelClass);
	if (m_pMenuPanel != nullptr)
	{
		m_pMenuPanel->AddToViewport();
	}
}
