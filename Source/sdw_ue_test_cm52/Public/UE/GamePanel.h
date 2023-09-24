// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "libsundaowen/sdw.h"
#include "Game/IActuator.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePanel.generated.h"

namespace Super2048UE
{
	class CGameManager;
	class CStorageManager;
	class CTile;
	struct SMetadata;
}

using Super2048UE::CGrid;
using Super2048UE::CGameManager;
using Super2048UE::CStorageManager;
using Super2048UE::CTile;
using Super2048UE::IActuator;
using Super2048UE::SMetadata;

UCLASS()
class SDW_UE_TEST_CM52_API UGamePanel : public UUserWidget, public IActuator
{
	GENERATED_BODY()

public:
	UGamePanel(const FObjectInitializer& ObjectInitializer);

	virtual bool Init() override;

	virtual void Actuate(CGrid* a_pGrid, SMetadata a_Metadata, n32 a_nStateCount = 0) override;

	virtual void ContinueGame() override;

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonStartAIClicked();
	UFUNCTION()
	void OnButtonStopAIClicked();
	UFUNCTION()
	void OnButtonBackClicked();

	static void clearContainer(class UPanelWidget* a_pContainer);
	void addTile(const CTile* a_pTile);
	FVector2D getAnchoredPosition(n32 a_nX, n32 a_nY);
	FVector2D getSizeDalta();

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWidget* m_pTitleWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWidget* m_pAIWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* m_pStartAIButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* m_pStopAIButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* m_pButtonBack;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UPanelWidget* m_pGameContainerPanelWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UPanelWidget* m_pGridContainerPanelWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UPanelWidget* m_pTileContainerPanelWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> m_GridCellClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBindTile> m_TileClass;

	static const n32 s_nTileSizeRaito = 7;
	static const n32 s_nGridSpacingRaito = 1;

	n32 m_nRow;
	n32 m_nColumn;
	n32 m_nWidth;
	n32 m_nHeight;
	n32 m_nTileSize;
	n32 m_nGridSpacing;

	n32 m_nScore;

	CStorageManager* m_pStorageManager;
	CGameManager* m_pGameManager;
};
