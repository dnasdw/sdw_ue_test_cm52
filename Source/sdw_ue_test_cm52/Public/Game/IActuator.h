#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	class CGrid;
	struct SMetadata;

	class IActuator
	{
	public:
		virtual bool Init() SDW_PURE;

		virtual void Actuate(CGrid* a_pGrid, SMetadata a_Metadata, n32 a_nStateCount = 0) SDW_PURE;

		virtual void ContinueGame() SDW_PURE;
	};
}
