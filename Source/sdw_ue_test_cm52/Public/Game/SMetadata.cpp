#include "SMetadata.h"

namespace Super2048UE
{
	SMetadata::SMetadata(n32 a_nScore, bool a_bOver, bool a_bWon, n32 a_nBestScore, bool a_bTerminated)
	{
		Score = a_nScore;
		Over = a_bOver;
		Won = a_bWon;
		BestScore = a_nBestScore;
		Terminated = a_bTerminated;
	}
}
