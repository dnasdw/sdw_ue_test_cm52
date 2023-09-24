#pragma once

#include "CoreMinimal.h"

namespace UnityEngineExtension
{
	class CColorExtension
	{
	private:
		CColorExtension();

	public:
		static FColor Lighten(const FColor& a_Color, float a_fAmount);
		static FLinearColor HSVToHSL(const FLinearColor& a_HSV);
		static FLinearColor HSLToHSV(const FLinearColor& a_HSL);
	};
}
