#include "CColorExtension.h"

#include "libsundaowen/sdw.h"
#include "CoreMinimal.h"

namespace UnityEngineExtension
{
	FColor CColorExtension::Lighten(const FColor& a_Color, float a_fAmount)
	{
		FLinearColor linearColor = a_Color.ReinterpretAsLinear();
		linearColor = linearColor.LinearRGBToHSV();
		linearColor = HSVToHSL(linearColor);
		linearColor.B = clamp(linearColor.B + a_fAmount, 0.0f, 1.0f);
		linearColor = HSLToHSV(linearColor);
		linearColor = linearColor.HSVToLinearRGB();
		return linearColor.QuantizeRound();
	}

	FLinearColor CColorExtension::HSVToHSL(const FLinearColor& a_HSV)
	{
		f32 fH = a_HSV.R;
		f32 fL = a_HSV.B * (1.0f - a_HSV.G / 2.0f);
		f32 fS = fL == 0.0f || fL == 1.0f ? 0.0f : (a_HSV.B - fL) / min(fL, 1.0f - fL);
		f32 fA = a_HSV.A;
		return FLinearColor(fH, fS, fL, fA);
	}

	FLinearColor CColorExtension::HSLToHSV(const FLinearColor& a_HSL)
	{
		f32 fH = a_HSL.R;
		f32 fV = a_HSL.B + a_HSL.G * min(a_HSL.B, 1.0f - a_HSL.B);
		f32 fS = fV == 0.0f ? 0.0f : 2.0f * (1.0f - a_HSL.B / fV);
		f32 fA = a_HSL.A;
		return FLinearColor(fH, fS, fV, fA);
	}
}
