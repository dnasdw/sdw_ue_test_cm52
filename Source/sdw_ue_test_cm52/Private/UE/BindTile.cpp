// Fill out your copyright notice in the Description page of Project Settings.


#include "UE/BindTile.h"

#include "Game/CGaussBlur.h"
#include "Unity/CColor32.h"
#include "Unity/Extension/CColorExtension.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

using Super2048UE::CGaussBlur;
using UnityEngineExtension::CColorExtension;
using UnityEnginePort::CColor32;

n32 UBindTile::s_nInitFontSize = 45;

FColor UBindTile::s_BrightTextColor = FColor(0xf9, 0xf6, 0xf2, 0xff);

FColor UBindTile::s_TileColor = FColor(0xee, 0xe4, 0xda, 0xff);
FColor UBindTile::s_TileGoldColor = FColor(0xed, 0xc2, 0x2e, 0xff);
FColor UBindTile::s_TileGoldGlowColor = CColorExtension::Lighten(s_TileGoldColor, 0.15f);

FColor UBindTile::s_SuperBackgroundColor = CColor32::Lerp(s_TileGoldColor, FColor(0x33, 0x33, 0x33, 0xff), 0.95f);

n32 UBindTile::s_nShadowSize = 216;
FVector2D UBindTile::s_ShadowSize = FVector2D(UBindTile::s_nShadowSize, UBindTile::s_nShadowSize);
vector<u8> UBindTile::s_vAlpha;
TMap<n32, UTexture2D*> UBindTile::s_mShadow;
map<n32, pair<FColor, bool>> UBindTile::s_mColor;

UBindTile::UBindTile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, m_pTitleWidget(nullptr)
	, m_pTileImage(nullptr)
	, m_pTextBlock(nullptr)
	, m_pShadowImage(nullptr)
	, m_nClass(2)
{
}

void UBindTile::Init(n32 a_nRowColumnMaxSize, n32 a_nTileSize)
{
	if (a_nRowColumnMaxSize == 4)
	{
		s_nInitFontSize = 45;
	}
	else if (a_nRowColumnMaxSize == 5)
	{
		s_nInitFontSize = 40;
	}

	n32 nBlurRadius = 30;
	n32 nSpreadRadius0 = 10;
	n32 nSpreadRadius1 = 1;
	// https://dbaron.org/log/20110225-blur-radius
	f32 fSigma = nBlurRadius / 2.0f;
	n32 nSpreadSigma3 = lround(fSigma * 3);
	s_nShadowSize = a_nTileSize + nSpreadRadius0 * 2 + nSpreadSigma3 * 2;
	s_ShadowSize = FVector2D(s_nShadowSize, s_nShadowSize);
	s_vAlpha.resize(s_nShadowSize * s_nShadowSize);
	vector<u8> vAlpha0(s_nShadowSize * s_nShadowSize);
	for (n32 y = 0; y < s_nShadowSize; y++)
	{
		for (n32 x = 0; x < s_nShadowSize; x++)
		{
			u8 uAlpha = static_cast<u8>(y >= nSpreadSigma3 && y < s_nShadowSize - nSpreadSigma3 && x >= nSpreadSigma3 && x < s_nShadowSize - nSpreadSigma3 ? 255 : 0);
			vAlpha0[y * s_nShadowSize + x] = uAlpha;
		}
	}
	CGaussBlur::gaussBlur_4(vAlpha0, s_vAlpha, s_nShadowSize, s_nShadowSize, fSigma);
	for (n32 y = 0; y < s_nShadowSize; y++)
	{
		for (n32 x = 0; x < s_nShadowSize; x++)
		{
			if (y >= nSpreadSigma3 + nSpreadRadius0 && y < s_nShadowSize - nSpreadSigma3 - nSpreadRadius0 && x >= nSpreadSigma3 + nSpreadRadius0 && x < s_nShadowSize - nSpreadSigma3 - nSpreadRadius0)
			{
				s_vAlpha[y * s_nShadowSize + x] = 0;
			}
		}
	}

	n32 nBase = 2;
	n32 nExponent = 1;
	n32 nLimit = 11;

	static const FColor c_Color8(0xf7, 0x8e, 0x48, 0xff);
	static const FColor c_Color16(0xfc, 0x5e, 0x2e, 0xff);
	static const FColor c_Color32(0xff, 0x33, 0x33, 0xff);
	static const FColor c_Color64(0xff, 0x00, 0x00, 0xff);
	// Colors for all 11 states, null = no special color
	static map<n32, pair<const FColor*, bool>> c_mSpecialColors =
	{
		{ 2, { nullptr, false } },
		{ 4, { nullptr, false } },
		{ 8, { &c_Color8, true } },
		{ 16, { &c_Color16, true } },
		{ 32, { &c_Color32, true } },
		{ 64, { &c_Color64, true } },
		{ 128, { nullptr, true } },
		{ 256, { nullptr, true } },
		{ 512, { nullptr, true } },
		{ 1024, { nullptr, true } },
		{ 2048, { nullptr, true } }
	};

	// Build tile colors
	n32 nPower = 1;
	for (n32 i = nExponent; i <= nLimit; i++)
	{
		nPower *= nBase;

		// Calculate base background color
		f32 fGoldPercent = static_cast<f32>(i - 1) / (nLimit - 1);
		FColor mixedBackground = CColor32::Lerp(s_TileColor, s_TileGoldColor, fGoldPercent);

		const pair<const FColor*, bool>& pNthColor = c_mSpecialColors[nPower];

		const FColor* pSpecialBackground = pNthColor.first;
		bool bBrightColor = pNthColor.second;

		if (pSpecialBackground != nullptr)
		{
			mixedBackground = CColor32::Lerp(mixedBackground, *pSpecialBackground, 0.55f);
		}

		pair<FColor, bool>& pColor = s_mColor[nPower];

		// Set background
		pColor.first = mixedBackground;

		pColor.second = bBrightColor;

		if (pSpecialBackground != nullptr)
		{
			s_mShadow.Add(nPower, nullptr);
		}
		else
		{
			// Add glow
			f32 fGlowOpacity = max<f32>(i - 4, 0) / (nLimit - 4);
			if (fGlowOpacity == 0.0f)
			{
				s_mShadow.Add(nPower, nullptr);
			}
			else
			{
				UTexture2D* pTexture2D = UTexture2D::CreateTransient(s_nShadowSize, s_nShadowSize, PF_B8G8R8A8);
				u8* pTexture2DData = static_cast<u8*>(pTexture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
				for (n32 y = 0; y < s_nShadowSize; y++)
				{
					bool bYInset = (y >= nSpreadSigma3 + nSpreadRadius0 && y < nSpreadSigma3 + nSpreadRadius0 + nSpreadRadius1) || (y >= s_nShadowSize - nSpreadSigma3 - nSpreadRadius0 - nSpreadRadius1 && y < s_nShadowSize - nSpreadSigma3 - nSpreadRadius0);
					for (n32 x = 0; x < s_nShadowSize; x++)
					{
						bool bXInset = (x >= nSpreadSigma3 + nSpreadRadius0 && x < nSpreadSigma3 + nSpreadRadius0 + nSpreadRadius1) || (x >= s_nShadowSize - nSpreadSigma3 - nSpreadRadius0 - nSpreadRadius1 && x < s_nShadowSize - nSpreadSigma3 - nSpreadRadius0);
						u32 uTexture2DDataIndex = (y * s_nShadowSize + x) * 4;
						if ((bYInset && x >= nSpreadSigma3 + nSpreadRadius0 && x < s_nShadowSize - nSpreadSigma3 - nSpreadRadius0) || (bXInset && y >= nSpreadSigma3 + nSpreadRadius0 && y < s_nShadowSize - nSpreadSigma3 - nSpreadRadius0))
						{
							pTexture2DData[uTexture2DDataIndex] = 255;
							pTexture2DData[uTexture2DDataIndex + 1] = 255;
							pTexture2DData[uTexture2DDataIndex + 2] = 255;
							pTexture2DData[uTexture2DDataIndex + 3] = static_cast<u8>(255 * (fGlowOpacity / 3));
						}
						else
						{
							pTexture2DData[uTexture2DDataIndex] = s_TileGoldGlowColor.B;
							pTexture2DData[uTexture2DDataIndex + 1] = s_TileGoldGlowColor.G;
							pTexture2DData[uTexture2DDataIndex + 2] = s_TileGoldGlowColor.R;
							pTexture2DData[uTexture2DDataIndex + 3] = static_cast<u8>(s_vAlpha[y * s_nShadowSize + x] * (fGlowOpacity / 1.8f));
						}
					}
				}
				pTexture2D->PlatformData->Mips[0].BulkData.Unlock();
				pTexture2D->UpdateResource();
				s_mShadow.Add(nPower, pTexture2D);
			}
		}
	}
}

void UBindTile::SetClass(n32 a_nClass)
{
	m_nClass = a_nClass;
	map<n32, pair<FColor, bool>>::const_iterator it = s_mColor.find(m_nClass);
	const UObject* pFontFamily = m_pTextBlock->GetFont().FontObject;
	const FName& sTypeface = m_pTextBlock->GetFont().TypefaceFontName;
	if (it != s_mColor.end())
	{
		const pair<FColor, bool>& pColor = it->second;
		if (pColor.second)
		{
			m_pTextBlock->SetColorAndOpacity(FLinearColor(s_BrightTextColor));
		}
		m_pTileImage->SetBrushTintColor(FLinearColor(pColor.first));

		if (m_nClass < 100)
		{
			// 45 = (55 / 6 * 5)
			m_pTextBlock->SetFont(FSlateFontInfo(pFontFamily, s_nInitFontSize, sTypeface));
		}
		else if (m_nClass >= 100 && m_nClass < 1000)
		{
			// 36 = (45 = (55 / 6 * 5)) / 11 * 9
			m_pTextBlock->SetFont(FSlateFontInfo(pFontFamily, static_cast<n32>(floor(s_nInitFontSize / 11.0f * 9.0f)), sTypeface));
		}
		else if (m_nClass >= 1000)
		{
			// 28 = (45 = (55 / 6 * 5)) / 11 * 7
			m_pTextBlock->SetFont(FSlateFontInfo(pFontFamily, static_cast<n32>(floor(s_nInitFontSize / 11.0f * 7.0f)), sTypeface));
		}

		UTexture2D** ppTexture2D = s_mShadow.Find(m_nClass);
		if (ppTexture2D != nullptr)
		{
			UTexture2D* pTexture2D = *ppTexture2D;
			if (pTexture2D != nullptr)
			{
				UCanvasPanelSlot* pShadowImageSlot = Cast<UCanvasPanelSlot>(m_pShadowImage->Slot);
				pShadowImageSlot->SetSize(s_ShadowSize);
				m_pShadowImage->SetBrushTintColor(FLinearColor(FColor::White));
				m_pShadowImage->SetBrushFromTexture(pTexture2D);
				m_pShadowImage->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	else
	{
		m_pTextBlock->SetColorAndOpacity(FLinearColor(s_BrightTextColor));
		m_pTileImage->SetBrushTintColor(FLinearColor(s_SuperBackgroundColor));
		// 24 = (45 = (55 / 6 * 5)) / 11 * 6
		m_pTextBlock->SetFont(FSlateFontInfo(pFontFamily, static_cast<n32>(floor(s_nInitFontSize / 11.0f * 6.0f)), sTypeface));
	}
}

void UBindTile::NativeConstruct()
{
	Super::NativeConstruct();
}
