// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "libsundaowen/sdw.h"
#undef UpdateResource

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BindTile.generated.h"

UCLASS()
class SDW_UE_TEST_CM52_API UBindTile : public UUserWidget
{
	GENERATED_BODY()

public:
	UBindTile(const FObjectInitializer& ObjectInitializer);

	static void Init(n32 a_nRowColumnMaxSize, n32 a_nTileSize);
	void SetClass(n32 a_nClass);

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWidget* m_pTitleWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* m_pTileImage;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* m_pTextBlock;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* m_pShadowImage;

	static n32 s_nInitFontSize;

private:
	static FColor s_BrightTextColor;

	static FColor s_TileColor;
	static FColor s_TileGoldColor;
	static FColor s_TileGoldGlowColor;

	static FColor s_SuperBackgroundColor;

	static n32 s_nShadowSize;
	static FVector2D s_ShadowSize;
	static vector<u8> s_vAlpha;
	static TMap<n32, UTexture2D*> s_mShadow;
	static map<n32, pair<FColor, bool>> s_mColor;

	n32 m_nClass;
};
