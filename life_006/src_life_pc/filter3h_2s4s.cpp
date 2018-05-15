#include "malloc32.h"
#include "nmpp.h"

int lifeK [3] = {-1,-1,-1};

void filter3h_2s4s(nm2s* pSrcMtr, nm4s* pDstMtr, int nSize){

	int iSize = nSize/16;
	int uiSrc, *puiSrc = (nm32s*)pSrcMtr;
	int src1,src2,src3;
	long long int uiDst,*puiDst = (nm64s*)pDstMtr,DstTemp;
	int i,j;

	for(i=0;i<iSize;i++)
	{
		//last element in long word
		puiDst[i] <<= 4;
		uiSrc = puiSrc[i+1];
		src1 = (uiSrc<<28);
		src1 = ((src1>>30) * lifeK[2]) & 0xf;
		src2 = (uiSrc<<30);
		src2 = ((src2>>30) * lifeK[1]) & 0xf;
		uiSrc = puiSrc[i];
		src3 = ((uiSrc>>30)* lifeK[0]) & 0xf;
		puiDst[i] |= (src1+src2+src3) & 0xf;
		
		//last but one element in long word
		puiDst[i] <<= 4;uiSrc = puiSrc[i+1];
		src1 = (uiSrc<<30);
		src1 = ((src1>>30) * lifeK[2]) & 0xf;
		uiSrc = puiSrc[i];
		src2 = ((uiSrc>>30)* lifeK[1]) & 0xf;
		src3 = uiSrc << 2;
		src3 = ((src3 >> 30) * lifeK[0]) & 0xf;
		puiDst[i] |= (src1+src2+src3) & 0xf;

		for(j=0;j<14;j++)
		{
			puiDst[i] <<= 4;
			src1 = ((uiSrc>> 30) * lifeK[2]) & 0xf;
			src2 = uiSrc << 2;
			src2 = ((src2 >> 30) * lifeK[1]) & 0xf;
			src3 = uiSrc << 4;
			src3 = ((src3 >> 30) * lifeK[0]) & 0xf;
			puiDst[i] |= (src1+src2+src3) & 0xf;
			uiSrc <<=2;
		}
	}

}