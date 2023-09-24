#pragma once

#include "../libsundaowen/sdw.h"
#include "SGameState.h"

namespace Super2048UE
{
	class IActuator;
	class IInputManager;
	class IStorageManager;
	class CGrid;
	enum EDirection;

	class CGameManager
	{
	public:
		CGameManager(n32 a_nRow, n32 a_nColumn, IInputManager* a_pInputManager, IActuator* a_pActuator, IStorageManager* a_pStorageManager);
		~CGameManager();

	private:
		bool isGameTerminated();
		/// <summary>
		/// Set up the game
		/// </summary>
		void setup();
		/// <summary>
		/// Set up the initial tiles to start the game with
		/// </summary>
		void addStartTiles();
		/// <summary>
		/// Adds a tile in a random position
		/// </summary>
		void addRandomTile();
		// TODO: test begin
		//void addRandomTile2(n32 a_nN);
		// TODO: test end
		/// <summary>
		/// Sends the updated grid to the actuator
		/// </summary>
		void actuate();

	private:
		/// <summary>
		/// Row of the grid
		/// </summary>
		n32 m_nRow;
		/// <summary>
		/// Column of the grid
		/// </summary>
		n32 m_nColumn;
		IInputManager* m_pInputManager;
		IStorageManager* m_pStorageManager;
		IActuator* m_pActuator;
		n32 m_nStartTiles;
		SGameState m_GameState;
		CGrid* m_pGrid;
		n32 m_nScore;
		bool m_bOver;
		bool m_bWon;
		bool m_bKeepPlaying;

		static bool s_bAIIsEnabled;
		// TODO: impl
		EDirection m_eAIDir;
	};
}
