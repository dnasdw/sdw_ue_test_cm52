#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	class IInputManager
	{
	public:
		virtual bool Init() SDW_PURE;

		virtual void On(string a_sEvent, void (*a_Callback)()) SDW_PURE;
	};
}
