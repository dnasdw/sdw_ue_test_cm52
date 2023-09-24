#pragma once

#include "CoreMinimal.h"

namespace UnityEnginePort
{
	class CColor32
	{
	private:
		CColor32();

	public:
		static FColor Lerp(const FColor& a, const FColor& b, float t);
	};
}
