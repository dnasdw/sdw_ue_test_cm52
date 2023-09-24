// Fill out your copyright notice in the Description page of Project Settings.


#include "UE/MenuPanel.h"

#include "libsundaowen/sdw.h"
#include "Game/CGameData.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

using Super2048UE::CGameData;

UMenuPanel::UMenuPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_pButtonGame5x5(nullptr)
	, m_pButtonGame4x4(nullptr)
{
}

void UMenuPanel::NativeConstruct()
{
	Super::NativeConstruct();

	m_pButtonGame5x5->OnClicked.AddDynamic(this, &UMenuPanel::OnButtonGame5x5Clicked);
	m_pButtonGame4x4->OnClicked.AddDynamic(this, &UMenuPanel::OnButtonGame4x4Clicked);
}

void UMenuPanel::OnButtonGame5x5Clicked()
{
	OnButtonGameClicked("5x5");
}

void UMenuPanel::OnButtonGame4x4Clicked()
{
	OnButtonGameClicked("4x4");
}

void UMenuPanel::OnButtonGameClicked(const std::string& a_sRowAndColumn)
{
	vector<string> vValue = Split(a_sRowAndColumn, "x");
	if (vValue.size() != 2)
	{
		return;
	}
	n32 nRow = SToN32(vValue[0], 10);
	n32 nColumn = SToN32(vValue[1], 10);
	CGameData::s_nRow = nRow;
	CGameData::s_nColumn = nColumn;
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Scenes/Game"));
}
