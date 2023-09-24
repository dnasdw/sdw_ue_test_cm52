#include "CMathf.h"

namespace UnityEnginePort
{
	float CMathf::Clamp01(float value)
	{
		if (value < 0.0f)
		{
			return 0.0f;
		}

		if (value > 1.0f)
		{
			return 1.0f;
		}

		return value;
	}
}
