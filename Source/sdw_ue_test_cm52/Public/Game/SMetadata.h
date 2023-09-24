#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	struct SMetadata
	{
	public:
		n32 Score;
		bool Over;
		bool Won;
		n32 BestScore;
		bool Terminated;

		SMetadata(n32 a_nScore, bool a_bOver, bool a_bWon, n32 a_nBestScore, bool a_bTerminated);
	};
}
