#include "CColor32.h"
#include "CMathf.h"

#include "libsundaowen/sdw.h"

namespace UnityEnginePort
{
	FColor CColor32::Lerp(const FColor& a, const FColor& b, float t)
	{
		t = CMathf::Clamp01(t);
		return FColor((u8)((float)(int)a.R + (float)(b.R - a.R) * t), (u8)((float)(int)a.G + (float)(b.G - a.G) * t), (u8)((float)(int)a.B + (float)(b.B - a.B) * t), (u8)((float)(int)a.A + (float)(b.A - a.A) * t));
	}
}
