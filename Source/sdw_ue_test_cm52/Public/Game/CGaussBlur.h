#pragma once

#include "../libsundaowen/sdw.h"

namespace Super2048UE
{
	// https://blog.ivank.net/fastest-gaussian-blur.html
	class CGaussBlur
	{
	private:
		CGaussBlur();

	public:
		static void gaussBlur_4(vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, f32 a_fSigma);

	private:
		// standard deviation, number of boxes
		static vector<n32> boxesForGauss(f32 a_fSigma, n32 a_nN);
		static void boxBlur_4(vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, n32 a_nRadius);
		static void boxBlurHorizontal_4(const vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, n32 a_nRadius);
		static void boxBlurTotal_4(const vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, n32 a_nRadius);
	};
}
