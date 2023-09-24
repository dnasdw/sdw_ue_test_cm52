#include "CRandom.h"

namespace Super2048UE
{
	f64 CRandom::Random()
	{
		static random_device rd;
		static mt19937 gen(rd());
		f64 fRandom = generate_canonical<f64, 1>(gen);
		return fRandom;
	}
}
