#include "malloc32.h"
#include "life.h"
#include "time.h"
#include <stdio.h>
#define ENABLE_ASSERTE
#include <crtdbg2.h>


#ifdef __NM__ 
extern "C" {
#endif
	
	void filter3h_2s4s(nm2s* pSrcMtr, nm4s* pDstMtr, int nSize);
	void add3v_4s(nm4s* SrcVec1, nm4s* SrcVec2, nm4s* SrcVec3, nm4s* DstVec, int nSize);

#ifdef __NM__ 
}
#endif


int lifeInit(int fullWidth, int fullHeight,int smallWidth,int smallHeight, LifeSpec* spec)
{	
	nmppsMallocSetRouteMode  ();
	nmppsMallocSpec.route[0]=0x3321;

	spec->xBorder = 64;
	spec->yBorder = 64;
	spec->nColumns = fullWidth/smallWidth;
	spec->nLines = fullHeight/smallHeight;
	ASSERTE(fullWidth %smallWidth ==0);
	ASSERTE(fullHeight%smallHeight==0);
	spec->widthWindow = smallWidth;
	ASSERTE(spec->widthWindow%64==0);
	spec->heightWindow = smallHeight;

	int SizeAnd4Line = (spec->widthWindow+2*spec->xBorder)*(spec->heightWindow+2*spec->yBorder+4);

	spec->pool1 = nmppsMalloc_4u(SizeAnd4Line);
	spec->pool2 = nmppsMalloc_4u(SizeAnd4Line);
	spec->pool3 = nmppsMalloc_4u(SizeAnd4Line);
	spec->extWindow= nmppsMalloc_1(SizeAnd4Line);

	if (nmppsMallocFail())			
		return -1;
		
	nmppsSet_8u((nm8u*) spec->pool1,  0, SizeAnd4Line/2);
	spec->temp1 = nmppsAddr_4u((nm4u*)spec->pool1	,2*(spec->widthWindow+2*spec->xBorder));

	nmppsSet_8u((nm8u*) spec->pool2,  0, SizeAnd4Line/2);
	spec->temp2 = nmppsAddr_4u((nm4u*)spec->pool2	,2*(spec->widthWindow+2*spec->xBorder));

	nmppsSet_8u((nm8u*) spec->pool3,  0, SizeAnd4Line/2);
	spec->temp3	= nmppsAddr_4u((nm4u*)spec->pool3	,2*(spec->widthWindow+2*spec->xBorder));

	nmppsSet_8u((nm8u*)spec->extWindow,  0, SizeAnd4Line/8);
	spec->window = nmppsAddr_1(spec->extWindow		,2*(spec->widthWindow+2*spec->xBorder));

	spec->isReady = true;
	return 0;
}

bool lifeFree(LifeSpec* spec){
	nmppsFree(spec->pool1);
	nmppsFree(spec->pool2);
	nmppsFree(spec->pool3);
	nmppsFree(spec->extWindow);
	return true;
}

int life(const nm1* source, nm1* result, LifeSpec* spec)
{
	if (!spec->isReady)
		return false;

	int	width  = spec->widthWindow +2*spec->xBorder;
	int	height = spec->heightWindow+2*spec->yBorder;

	int size=width*height;		
	nm4u* temp1 = spec->temp1;
	nm4u* temp2 = spec->temp2;
	nm4u* temp3	= spec->temp3;	

	nmppsConvert_1s2s((nm1*)source ,(nm2s*)temp1,size);
	
	nm2s* src2sUpLine = nmppsAddr_2s((nm2s*)temp1,-width);
	nm4s* dst4sUpLine = nmppsAddr_4s((nm4s*)temp2,-width);
	filter3h_2s4s((nm2s*) src2sUpLine, (nm4s*) dst4sUpLine, size+2*width);	

	nm4s* UpLine = nmppsAddr_4s((nm4s*)temp2, width);
	nm4s* DnLine = nmppsAddr_4s((nm4s*)temp2,-width);

	add3v_4s(DnLine, (nm4s*) temp2, UpLine, (nm4s*) temp1, size);
		
	nm64u pnBits = 0;
	nmppsAndC_8u((nm8u*)temp1,0x77,(nm8u*)temp3,size/2);		// 1000 (8(-8))->0000, 1001 (9(-7))->0001

	nmppsCmpEqC_4u3b((nm4u3b*) temp3,  4,  (nm4s*) temp2, size, -1);
	//nmppsConvert_4s1s((nm4s*)temp2, (nm1*)temp1,size);
	nmppsConvert_4s2s((nm4s*)temp2, (nm2s*)temp1,size);
	nmppsConvert_2s1s((nm2s*)temp1, (nm1*)temp1,size);
	nmppsFwdShiftBitstream((nm64u*) temp1, (nm64u*) temp2, &pnBits, 1, size/64);	
	nmppsAnd_1((nm1*)temp2,(nm1*)source,(nm1*)temp1,size);
		
	nmppsCmpEqC_4u3b((nm4u3b*) temp3,  3,  (nm4s*) temp2, size, -1);	
	//nmppsConvert_4s1s((nm4s*)temp2, (nm1*)temp3,size);
	nmppsConvert_4s2s((nm4s*)temp2, (nm2s*)temp3,size);
	nmppsConvert_2s1s((nm2s*)temp2, (nm1*)temp3,size);
	nmppsFwdShiftBitstream((nm64u*) temp3, (nm64u*) temp2, &pnBits, 1, size/64);	

	nmppsOr_1   	((nm1*) temp1 , (nm1*) temp2, (nm1*) result, size);	
	
	return 0;
}


int lifeRectangle(const nm1* source, nm1* result, LifeSpec* spec)
{
	nm1* dst;
	nm1* src;
	int nIter=1;
	int y,x,i;
	
	int width = spec->widthWindow;
	int height = spec->heightWindow;
	int xBorder = spec->xBorder;
	int yBorder = spec->yBorder;
	int bigWidth = width*(spec->nColumns);
	int bigHeight = height*(spec->nLines);
	nm1* window = spec->window;
	nm1* srcLived;
	
	unsigned int crc=0;	

	for (y=0;y<bigHeight;y+=height)
	{
		for (x=0;x<bigWidth;x+=width)
		{
			src = nmppsAddr_1(source, bigWidth*(y-yBorder)+x-xBorder);
			nmppmCopy_1 (src, bigWidth, window, width+2*xBorder, height+2*yBorder, width+2*xBorder);

			for (i=0;i<nIter;i++)
				life(window, window, spec);	
			
			srcLived = nmppsAddr_1((nm1*)window,(width+2*xBorder)*yBorder+xBorder);
			dst = nmppsAddr_1((nm1*)result,bigWidth*y+x);
			
			nmppmCopy_1 ((nm1*) srcLived, width+2*xBorder,  (nm1*) dst, bigWidth, height, width);
		}
	}
	return 0;
}

