#include "CGrid.h"
#include "CRandom.h"
#include "CTile.h"
#include "SPosition.h"

namespace Super2048UE
{
	CGrid::CGrid(n32 a_nRow, n32 a_nColumn, const vector<vector<n32>>* a_pPreviousState /* = nullptr */)
		: Row(a_nRow)
		, Column(a_nColumn)
		, Cells(a_pPreviousState != nullptr ? fromState(*a_pPreviousState) : empty())
	{
	}

	CGrid::~CGrid()
	{
		for (vector<vector<CTile*>>::iterator itRow = Cells.begin(); itRow != Cells.end(); ++itRow)
		{
			for (vector<CTile*>::iterator itColumn = itRow->begin(); itColumn != itRow->end(); ++itColumn)
			{
				CTile* pTile = *itColumn;
				if (pTile != nullptr)
				{
					delete pTile;
					pTile = nullptr;
				}
			}
		}
	}

	SPosition* CGrid::RandomAvailableCell()
	{
		static vector<SPosition> vCells;
		vCells = availableCells();

		if (!vCells.empty())
		{
			n32 nSize = vCells.size();
			n32 nIndex = clamp(static_cast<n32>(floor(CRandom::Random() * nSize)), 0, nSize - 1);
			return &vCells[nIndex];
		}
		else
		{
			return nullptr;
		}
	}

	bool CGrid::CellsAvailable()
	{
		return !availableCells().empty();
	}

	void CGrid::InsertTile(CTile* a_pTile)
	{
		Cells[a_pTile->Y][a_pTile->X] = a_pTile;
	}

	vector<vector<CTile*>> CGrid::empty()
	{
		vector<vector<CTile*>> vCells;

		for (n32 r = 0; r < Row; r++)
		{
			vector<CTile*> vRow;

			for (n32 c = 0; c < Column; c++)
			{
				vRow.push_back(nullptr);
			}

			vCells.push_back(vRow);
		}

		return vCells;
	}

	vector<vector<CTile*>> CGrid::fromState(const vector<vector<n32>>& a_vState)
	{
		vector<vector<CTile*>> vCells;

		for (n32 r = 0; r < Row; r++)
		{
			vector<CTile*> vRow;

			for (n32 c = 0; c < Column; c++)
			{
				n32 nValue = a_vState[r][c];
				vRow.push_back(nValue != 0 ? new CTile(SPosition(c, r), nValue) : nullptr);
			}

			vCells.push_back(vRow);
		}

		return vCells;
	}

	vector<SPosition> CGrid::availableCells()
	{
		vector<SPosition> vCells;

		for (n32 r = 0; r < Row; r++)
		{
			for (n32 c = 0; c < Column; c++)
			{
				CTile* pTile = Cells[r][c];
				if (pTile == nullptr)
				{
					vCells.push_back(SPosition(c, r));
				}
			}
		}

		return vCells;
	}
}
