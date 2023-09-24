#include "CTile.h"
#include "SPosition.h"

namespace Super2048UE
{
	CTile::CTile(const SPosition& a_Position, n32 a_nValue /* = 2 */)
		: X(a_Position.X)
		, Y(a_Position.Y)
		, Value(a_nValue)
		, PreviousPosition(nullptr)
	{
	}
}
