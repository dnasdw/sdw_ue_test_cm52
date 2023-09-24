#include "CGaussBlur.h"

namespace Super2048UE
{
	vector<n32> CGaussBlur::boxesForGauss(f32 a_fSigma, n32 a_nN)
	{
		// Ideal averaging filter width 
		f32 fWIdeal = sqrt((12 * a_fSigma * a_fSigma / a_nN) + 1);
		n32 nWL = static_cast<n32>(floor(fWIdeal));
		if (nWL % 2 == 0)
		{
			nWL--;
		}
		n32 nWU = nWL + 2;

		f32 fMIdeal = (12 * a_fSigma * a_fSigma - a_nN * nWL * nWL - 4 * a_nN * nWL - 3 * a_nN) / (-4 * nWL - 4);
		n32 nM = lround(fMIdeal);
		//f32 fSigmaActual = sqrt((nM * nWL * nWL + (a_nN - nM) * nWU * nWU - a_nN) / 12.0f);

		vector<n32> vSizes(a_nN);
		for (n32 i = 0; i < a_nN; i++)
		{
			vSizes[i] = i < nM ? nWL : nWU;
		}
		return vSizes;
	}

	void CGaussBlur::gaussBlur_4(vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, f32 a_fSigma)
	{
		vector<n32> vBoxes = boxesForGauss(a_fSigma, 3);
		boxBlur_4(a_vSourceChannel, a_vTargetChannel, a_nWidth, a_nHeight, (vBoxes[0] - 1) / 2);
		boxBlur_4(a_vTargetChannel, a_vSourceChannel, a_nWidth, a_nHeight, (vBoxes[1] - 1) / 2);
		boxBlur_4(a_vSourceChannel, a_vTargetChannel, a_nWidth, a_nHeight, (vBoxes[2] - 1) / 2);
	}

	void CGaussBlur::boxBlur_4(vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, n32 a_nRadius)
	{
		for (n32 i = 0; i < a_vSourceChannel.size(); i++)
		{
			a_vTargetChannel[i] = a_vSourceChannel[i];
		}
		boxBlurHorizontal_4(a_vTargetChannel, a_vSourceChannel, a_nWidth, a_nHeight, a_nRadius);
		boxBlurTotal_4(a_vSourceChannel, a_vTargetChannel, a_nWidth, a_nHeight, a_nRadius);
	}

	void CGaussBlur::boxBlurHorizontal_4(const vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, n32 a_nRadius)
	{
		f32 fIarr = 1.0f / (a_nRadius + a_nRadius + 1);
		for (n32 i = 0; i < a_nHeight; i++)
		{
			n32 nTargetIndex = i * a_nWidth;
			n32 nLeftIndex = nTargetIndex;
			n32 nRightIndex = nTargetIndex + a_nRadius;
			f32 fFirstValue = a_vSourceChannel[nTargetIndex];
			f32 fLastValue = a_vSourceChannel[nTargetIndex + a_nWidth - 1];
			f32 fValue = (a_nRadius + 1) * fFirstValue;
			for (n32 j = 0; j < a_nRadius; j++)
			{
				fValue += a_vSourceChannel[nTargetIndex + j];
			}
			for (n32 j = 0; j <= a_nRadius; j++)
			{
				fValue += a_vSourceChannel[nRightIndex++] - fFirstValue;
				a_vTargetChannel[nTargetIndex++] = static_cast<u8>(lround(fValue * fIarr));
			}
			for (n32 j = a_nRadius + 1; j < a_nWidth - a_nRadius; j++)
			{
				fValue += a_vSourceChannel[nRightIndex++] - a_vSourceChannel[nLeftIndex++];
				a_vTargetChannel[nTargetIndex++] = static_cast<u8>(lround(fValue * fIarr));
			}
			for (n32 j = a_nWidth - a_nRadius; j < a_nWidth; j++)
			{
				fValue += fLastValue - a_vSourceChannel[nLeftIndex++];
				a_vTargetChannel[nTargetIndex++] = static_cast<u8>(lround(fValue * fIarr));
			}
		}
	}

	void CGaussBlur::boxBlurTotal_4(const vector<u8>& a_vSourceChannel, vector<u8>& a_vTargetChannel, n32 a_nWidth, n32 a_nHeight, n32 a_nRadius)
	{
		f32 fIarr = 1.0f / (a_nRadius + a_nRadius + 1);
		for (n32 i = 0; i < a_nWidth; i++)
		{
			n32 nTargetIndex = i;
			n32 nLeftIndex = nTargetIndex;
			n32 nRightIndex = nTargetIndex + a_nRadius * a_nWidth;
			f32 fFirstValue = a_vSourceChannel[nTargetIndex];
			f32 fLastValue = a_vSourceChannel[nTargetIndex + a_nWidth * (a_nHeight - 1)];
			f32 fValue = (a_nRadius + 1) * fFirstValue;
			for (n32 j = 0; j < a_nRadius; j++)
			{
				fValue += a_vSourceChannel[nTargetIndex + j * a_nWidth];
			}
			for (n32 j = 0; j < a_nRadius; j++)
			{
				fValue += a_vSourceChannel[nRightIndex] - fFirstValue;
				a_vTargetChannel[nTargetIndex] = static_cast<u8>(lround(fValue * fIarr));
				nRightIndex += a_nWidth;
				nTargetIndex += a_nWidth;
			}
			for (n32 j = a_nRadius + 1; j < a_nHeight - a_nRadius; j++)
			{
				fValue += a_vSourceChannel[nRightIndex] - a_vSourceChannel[nLeftIndex];
				a_vTargetChannel[nTargetIndex] = static_cast<u8>(lround(fValue * fIarr));
				nLeftIndex += a_nWidth;
				nRightIndex += a_nWidth;
				nTargetIndex += a_nWidth;
			}
			for (n32 j = a_nHeight - a_nRadius; j < a_nHeight; j++)
			{
				fValue += fLastValue - a_vSourceChannel[nLeftIndex];
				a_vTargetChannel[nTargetIndex] = static_cast<u8>(lround(fValue * fIarr));
				nLeftIndex += a_nWidth;
				nTargetIndex += a_nWidth;
			}
		}
	}
}
