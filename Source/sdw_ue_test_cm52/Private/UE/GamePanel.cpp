// Fill out your copyright notice in the Description page of Project Settings.


#include "UE/GamePanel.h"

#include "Game/CGameData.h"
#include "Game/CGameManager.h"
#include "Game/CGrid.h"
#include "Game/CTile.h"
#include "Game/SMetadata.h"
#include "Game/SPosition.h"
#include "UE/BindTile.h"
#include "UE/CStorageManager.h"

#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

using Super2048UE::CGameData;
using Super2048UE::SPosition;

UGamePanel::UGamePanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_pTitleWidget(nullptr)
	, m_pAIWidget(nullptr)
	, m_pStartAIButton(nullptr)
	, m_pStopAIButton(nullptr)
	, m_pButtonBack(nullptr)
	, m_pGameContainerPanelWidget(nullptr)
	, m_pGridContainerPanelWidget(nullptr)
	, m_pTileContainerPanelWidget(nullptr)
	, m_nRow(4)
	, m_nColumn(4)
	, m_nWidth(500)
	, m_nHeight(500)
	, m_nTileSize(106)
	, m_nGridSpacing(15)
	, m_nScore(0)
	, m_pStorageManager(nullptr)
	, m_pGameManager(nullptr)
{
}

bool UGamePanel::Init()
{
	m_pGridContainerPanelWidget->ClearChildren();
	clearContainer(m_pTileContainerPanelWidget);

	m_nRow = CGameData::s_nRow;
	m_nColumn = CGameData::s_nColumn;

	UCanvasPanelSlot* pGameContainerSlot = Cast<UCanvasPanelSlot>(m_pGameContainerPanelWidget->Slot);
	m_nWidth = static_cast<n32>(pGameContainerSlot->GetSize().X);
	m_nHeight = static_cast<n32>(pGameContainerSlot->GetSize().Y);
	f32 fGridHSpacing = static_cast<f32>(m_nWidth) / static_cast<f32>(m_nColumn * (s_nTileSizeRaito + s_nGridSpacingRaito) + s_nGridSpacingRaito);
	f32 fGridVSpacing = static_cast<f32>(m_nHeight) / static_cast<f32>(m_nRow * (s_nTileSizeRaito + s_nGridSpacingRaito) + s_nGridSpacingRaito);
	f32 fGridSpacing = min<f32>(fGridHSpacing, fGridVSpacing);
	m_nTileSize = static_cast<n32>(fGridSpacing * s_nTileSizeRaito) / 2 * 2;
	m_nGridSpacing = static_cast<n32>(fGridSpacing * s_nGridSpacingRaito);
	m_nWidth = static_cast<n32>(Align(m_nColumn * (m_nTileSize + m_nGridSpacing) + m_nGridSpacing, 2));
	m_nHeight = static_cast<n32>(Align(m_nRow * (m_nTileSize + m_nGridSpacing) + m_nGridSpacing, 2));

	pGameContainerSlot->SetSize(FVector2D(m_nWidth, m_nHeight));
	for (n32 r = 0; r < m_nRow; r++)
	{
		for (n32 c = 0; c < m_nColumn; c++)
		{
			UUserWidget* pGridCell = CreateWidget(m_pGridContainerPanelWidget, m_GridCellClass);
			if (pGridCell != nullptr)
			{
				m_pGridContainerPanelWidget->AddChild(pGridCell);
				pGridCell->Rename(Format(USTR("grid_cell_%d_%d"), c, r).c_str());
				UCanvasPanelSlot* pGridCellSlot = Cast<UCanvasPanelSlot>(pGridCell->Slot);
				pGridCellSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
				pGridCellSlot->SetPosition(getAnchoredPosition(c, r));
				pGridCellSlot->SetSize(getSizeDalta());
				pGridCellSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			}
		}
	}

	m_nScore = 0;

	n32 nSizeMax = max<n32>(m_nRow, m_nColumn);
	UBindTile::Init(nSizeMax, m_nTileSize);

	return true;
}

void UGamePanel::Actuate(CGrid* a_pGrid, SMetadata a_Metadata, n32 a_nStateCount /* = 0 */)
{
	clearContainer(m_pTileContainerPanelWidget);

	const vector<vector<CTile*>>& vCells = a_pGrid->Cells;
	for (vector<vector<CTile*>>::const_iterator itRow = vCells.begin(); itRow != vCells.end(); ++itRow)
	{
		const vector<CTile*>& vRow = *itRow;
		for (vector<CTile*>::const_iterator itColumn = vRow.begin(); itColumn != vRow.end(); ++itColumn)
		{
			const CTile* pTile = *itColumn;
			if (pTile != nullptr)
			{
				addTile(pTile);
			}
		}
	}

	// TODO: impl
}

void UGamePanel::ContinueGame()
{
	// TODO: impl
}

void UGamePanel::NativeConstruct()
{
	Super::NativeConstruct();

	m_nRow = CGameData::s_nRow;
	m_nColumn = CGameData::s_nColumn;

	bool bAIEnabled = m_nRow == 4 && m_nColumn == 4;
	UCanvasPanelSlot* pSlot = Cast<UCanvasPanelSlot>(m_pTitleWidget->Slot);
	if (pSlot != nullptr)
	{
		if (bAIEnabled)
		{
			pSlot->SetSize(FVector2D(250.0f, 70.0f));
		}
		else
		{
			pSlot->SetSize(FVector2D(250.0f, 160.0f));
		}
	}
	m_pAIWidget->SetIsEnabled(bAIEnabled);
	m_pAIWidget->SetVisibility(bAIEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	m_pStartAIButton->SetIsEnabled(bAIEnabled);
	m_pStartAIButton->SetVisibility(bAIEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	m_pStopAIButton->SetIsEnabled(bAIEnabled);
	m_pStopAIButton->SetVisibility(bAIEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	m_pStartAIButton->OnClicked.AddDynamic(this, &UGamePanel::OnButtonStartAIClicked);
	m_pStopAIButton->OnClicked.AddDynamic(this, &UGamePanel::OnButtonStopAIClicked);
	m_pButtonBack->OnClicked.AddDynamic(this, &UGamePanel::OnButtonBackClicked);

	m_pStorageManager = new CStorageManager();
	m_pGameManager = new CGameManager(m_nRow, m_nColumn, nullptr, this, m_pStorageManager);
}

void UGamePanel::OnButtonStartAIClicked()
{
	// TODO: impl
}

void UGamePanel::OnButtonStopAIClicked()
{
	// TODO: impl
}

void UGamePanel::OnButtonBackClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Scenes/Menu"));
}

void UGamePanel::clearContainer(class UPanelWidget* a_pContainer)
{
	a_pContainer->ClearChildren();
}

void UGamePanel::addTile(const CTile* a_pTile)
{
	UBindTile* pBindTile = CreateWidget<UBindTile>(m_pTileContainerPanelWidget, m_TileClass);
	if (pBindTile != nullptr)
	{
		m_pTileContainerPanelWidget->AddChild(pBindTile);
		UWidget* pWrapper = pBindTile->m_pTitleWidget;
		UTextBlock* pInner = pBindTile->m_pTextBlock;
		SPosition position = a_pTile->PreviousPosition != nullptr ? *a_pTile->PreviousPosition : SPosition(a_pTile->X, a_pTile->Y);
		UCanvasPanelSlot* pBindTileSlot = Cast<UCanvasPanelSlot>(pBindTile->Slot);
		pBindTileSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.0f, 0.0f));
		pBindTileSlot->SetPosition(getAnchoredPosition(position.X, position.Y));
		pBindTileSlot->SetSize(getSizeDalta());
		pBindTileSlot->SetAlignment(FVector2D(0.5f, 0.5f));

		pBindTile->SetClass(a_pTile->Value);

		pInner->SetText(FText::FromString(Format("%d", a_pTile->Value).c_str()));

		// TODO: impl
	}
}

FVector2D UGamePanel::getAnchoredPosition(n32 a_nX, n32 a_nY)
{
	return FVector2D(a_nX * (m_nTileSize + m_nGridSpacing) + m_nGridSpacing + m_nTileSize / 2, a_nY * (m_nTileSize + m_nGridSpacing) + m_nGridSpacing + m_nTileSize / 2);
}

FVector2D UGamePanel::getSizeDalta()
{
	return FVector2D(m_nTileSize, m_nTileSize);
}
