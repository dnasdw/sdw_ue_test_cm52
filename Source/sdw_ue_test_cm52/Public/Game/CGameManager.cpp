#include "CGameManager.h"
#include "CGrid.h"
#include "CRandom.h"
#include "CTile.h"
#include "IActuator.h"
#include "SMetadata.h"

namespace Super2048UE
{
	bool CGameManager::s_bAIIsEnabled = false;

	CGameManager::CGameManager(n32 a_nRow, n32 a_nColumn, IInputManager* a_pInputManager, IActuator* a_pActuator, IStorageManager* a_pStorageManager)
		: m_nRow(a_nRow)
		, m_nColumn(a_nColumn)
		, m_pInputManager(a_pInputManager)
		, m_pActuator(a_pActuator)
		, m_pStorageManager(a_pStorageManager)
		, m_nStartTiles(2)
		, m_pGrid(nullptr)
		, m_nScore(0)
		, m_bOver(false)
		, m_bWon(false)
		, m_bKeepPlaying(false)
	{
		// TODO: test begin
		//m_nStartTiles(a_nRow* a_nColumn)
		// TODO: test end
		// TODO: impl
		m_pActuator->Init();

		s_bAIIsEnabled = false;
		if (m_nRow == 4 && m_nColumn == 4)
		{
			// TODO: impl
		}

		// TODO: impl

		setup();
	}

	CGameManager::~CGameManager()
	{
	}

	bool CGameManager::isGameTerminated()
	{
		return m_bOver || (m_bWon && !m_bKeepPlaying);
	}

	void CGameManager::setup()
	{
		// TODO: impl
		SGameState* pPreviousState = nullptr;

		if (pPreviousState != nullptr)
		{
			// TODO: impl
		}
		else
		{
			// TODO: impl
			m_pGrid = new CGrid(m_nRow, m_nColumn);
			m_nScore = 0;
			m_bOver = false;
			m_bWon = false;
			m_bKeepPlaying = false;

			// Add the initial tiles
			addStartTiles();
		}

		actuate();
	}

	void CGameManager::addStartTiles()
	{
		for (n32 i = 0; i < m_nStartTiles; i++)
		{
			addRandomTile();
			// TODO: test begin
			//addRandomTile2(2 << i);
			// TODO: test end
		}
	}

	void CGameManager::addRandomTile()
	{
		if (m_pGrid->CellsAvailable())
		{
			n32 nValue = CRandom::Random() < 0.9 ? 2 : 4;
			SPosition* pPosition = m_pGrid->RandomAvailableCell();
			if (pPosition != nullptr)
			{
				CTile* pTile = new CTile(*pPosition, nValue);

				m_pGrid->InsertTile(pTile);
			}
		}
	}

	// TODO: test begin
	//void CGameManager::addRandomTile2(n32 a_nN)
	//{
	//	if (m_pGrid->CellsAvailable())
	//	{
	//		n32 nValue = a_nN;
	//		SPosition* pPosition = m_pGrid->RandomAvailableCell();
	//		if (pPosition != nullptr)
	//		{
	//			CTile* pTile = new CTile(*pPosition, nValue);

	//			m_pGrid->InsertTile(pTile);
	//		}
	//	}
	//}
	// TODO: test end

	void CGameManager::actuate()
	{
		// TODO: impl

		// TODO: impl

		// TODO: impl

		// TODO: impl
		m_pActuator->Actuate(m_pGrid
			, SMetadata
			(
				m_nScore,
				m_bOver,
				m_bWon,
				0,
				isGameTerminated()
			)
			// TODO: impl
			, 0);
	}
}
