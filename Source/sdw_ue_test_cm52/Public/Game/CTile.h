#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	struct SPosition;

	class CTile
	{
	public:
		CTile(const SPosition& a_Position, n32 a_nValue = 2);

	public:
		n32 X;
		n32 Y;
		n32 Value;
		SPosition* PreviousPosition;
	};
}
