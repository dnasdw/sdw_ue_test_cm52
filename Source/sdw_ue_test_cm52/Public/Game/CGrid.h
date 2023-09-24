#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	class CTile;
	struct SPosition;

	class CGrid
	{
	public:
		CGrid(n32 a_nRow, n32 a_nColumn, const vector<vector<n32>>* a_pPreviousState = nullptr);
		~CGrid();
		/// <summary>
		/// Find the first available random position
		/// </summary>
		/// <returns></returns>
		SPosition* RandomAvailableCell();
		bool CellsAvailable();
		/// <summary>
		/// Inserts a tile at its position
		/// </summary>
		/// <param name="a_pTile"></param>
		void InsertTile(CTile* a_pTile);

	private:
		/// <summary>
		/// Build a grid of the specified size
		/// </summary>
		/// <returns></returns>
		vector<vector<CTile*>> empty();
		vector<vector<CTile*>> fromState(const vector<vector<n32>>& a_vState);
		vector<SPosition> availableCells();

	public:
		n32 Row;
		n32 Column;
		vector<vector<CTile*>> Cells;
	};
}
