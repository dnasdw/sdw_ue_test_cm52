// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "libsundaowen/sdw.h"
#include "Game/IStorageManager.h"

#include "CoreMinimal.h"

using Super2048UE::IStorageManager;

namespace Super2048UE
{
	class SDW_UE_TEST_CM52_API CStorageManager : public IStorageManager
	{
	public:
		CStorageManager();
		~CStorageManager();

		virtual bool Init(n32 a_nRow, n32 a_nColumn) override;

		virtual n32 GetBestScore() override;

		virtual void SetBestScore(n32 a_nScore) override;

		virtual SGameState* GetGameState() override;

		virtual void SetGameState(SGameState* a_pGameState) override;

		virtual void ClearGameState() override;
	};
}
