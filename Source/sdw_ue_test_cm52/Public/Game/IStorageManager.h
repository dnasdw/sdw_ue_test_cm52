#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	struct SGameState;

	class IStorageManager
	{
	public:
		virtual bool Init(n32 a_nRow, n32 a_nColumn) SDW_PURE;

		virtual n32 GetBestScore() SDW_PURE;

		virtual void SetBestScore(n32 a_nScore) SDW_PURE;

		virtual SGameState* GetGameState() SDW_PURE;

		virtual void SetGameState(SGameState* a_pGameState) SDW_PURE;

		virtual void ClearGameState() SDW_PURE;
	};
}
