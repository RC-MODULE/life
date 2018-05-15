#include "malloc32.h"
#include "life.h"
#include <stdio.h>
#define ENABLE_ASSERTE
#include <crtdbg2.h>
int lifeCentre [9] = {
		-1, -1, -1,
		-1, -1, -1,
		-1, -1, -1
};
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
	spec->isReady = false;
	spec->xBorder = 16;
	spec->yBorder = 16;
	spec->nColumns = fullWidth/smallWidth;
	spec->nLines = fullHeight/smallHeight;
	ASSERTE(fullWidth %smallWidth ==0);
	ASSERTE(fullHeight%smallHeight==0);
	spec->widthWindow = smallWidth;
	ASSERTE(spec->widthWindow%8==0);
	spec->heightWindow = smallHeight;

	int SizeAnd4Line = (spec->widthWindow+2*spec->xBorder)*(spec->heightWindow+2*spec->yBorder+4);

	spec->pool1 = nmppsMalloc_8u(SizeAnd4Line);
	spec->pool2 = nmppsMalloc_8u(SizeAnd4Line);
	spec->pool3 = nmppsMalloc_8u(SizeAnd4Line);
	spec->extWindow= nmppsMalloc_8u(SizeAnd4Line);

	if (nmppsMallocFail())			
		return -1;
		
	nmppsSet_8u((nm8u*) spec->pool1,  0, SizeAnd4Line);
	spec->temp1 = nmppsAddr_8u((nm8u*)spec->pool1	,2*(spec->widthWindow+2*spec->xBorder));

	nmppsSet_8u((nm8u*) spec->pool2,  0, SizeAnd4Line);
	spec->temp2 = nmppsAddr_8u((nm8u*)spec->pool2	,2*(spec->widthWindow+2*spec->xBorder));

	nmppsSet_8u((nm8u*) spec->pool3,  0, SizeAnd4Line);
	spec->temp3	= nmppsAddr_8u((nm8u*)spec->pool3	,2*(spec->widthWindow+2*spec->xBorder));

	nmppsSet_8u(spec->extWindow,  0, SizeAnd4Line);
	spec->window = nmppsAddr_8u(spec->extWindow		,2*(spec->widthWindow+2*spec->xBorder));

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

int life(const unsigned char* source, unsigned char* result, LifeSpec* spec)
{
	if (!spec->isReady)
		return -1;
	int width  = spec->widthWindow +2*spec->xBorder;
	int height = spec->heightWindow+2*spec->yBorder;
	int size=width*height;	
	nm8u* temp1 = spec->temp1;
	nm8u* temp2 = spec->temp2;
	nm8u* temp3	= spec->temp3;	
	nm8u* source4s = spec->temp2;

	nmppsConvert_8s4s((nm8s*)source,(nm4s*)source4s,size);
	nmppsConvert_4s2s((nm4s*)source4s,(nm2s*)temp1,size);

	nm2s* src2sUpLine = nmppsAddr_2s((nm2s*)temp1,-width);
	nm4s* dst4sUpLine = nmppsAddr_4s((nm4s*)temp3,-width);
	filter3h_2s4s((nm2s*) src2sUpLine, (nm4s*) dst4sUpLine, size+2*width);

	nm4s* UpLine = nmppsAddr_4s((nm4s*)temp3, width);
	nm4s* DnLine = nmppsAddr_4s((nm4s*)temp3,-width);
	add3v_4s(DnLine, (nm4s*) temp3, UpLine, (nm4s*) temp1, size);
	
	nm64u* pnBits = nmppsAddr_64u((nm64u*) temp1,-1);
	nmppsFwdShiftBitstream((nm64u*) temp1, (nm64u*) temp3, pnBits, 4, size/16);
	nmppsAndC_8u((nm8u*)temp3,0x77,(nm8u*)temp1,size/2);		// 1000 (8(-8))->0000, 1001 (9(-7))->0001

	nmppsCmpEqC_4u3b((nm4u3b*) temp1,  4,  (nm4s*) temp3, size, -1);
	nmppsAnd_4u		((nm4u*)temp3,(nm4u*)source4s,(nm4u*)temp2,size);
	
	nmppsCmpEqC_4u3b((nm4u3b*) temp1,  3,  (nm4s*) temp3, size, -1);	
		
	nmppsOr_4u   	((nm4u*) temp2 , (nm4u*) temp3, (nm4u*) temp1, size);		//merger

	nmppsConvert_4s8s((nm4s*) temp1,(nm8s*)result,size);

	return 0;
}


int lifeRectangle(const unsigned char* source, unsigned char* result, LifeSpec* spec)
{
	nm8u* dst;
	nm8u* src;
	int nIter=1;
	int y,x,i;
	
	int width = spec->widthWindow;
	int height = spec->heightWindow;
	int xBorder = spec->xBorder;
	int yBorder = spec->yBorder;
	int bigWidth = width*(spec->nColumns);
	int bigHeight = height*(spec->nLines);
	nm8u* window = spec->window;
	nm8u* srcLived;
	unsigned int crc=0;		
	for (y=0;y<bigHeight;y+=height)
	{
		for (x=0;x<bigWidth;x+=width)
		{
			src = nmppsAddr_8u((nm8u*)source, bigWidth*(y-yBorder)+x-xBorder);
			nmppmCopy_8s ((nm8s*) src, bigWidth, (nm8s*) window, width+2*xBorder, height+2*yBorder, width+2*xBorder);
			
			for (i=0;i<nIter;i++)
				life((unsigned char*) window, (unsigned char*) window, spec);

			srcLived = nmppsAddr_8u((nm8u*)window,(width+2*xBorder)*yBorder+xBorder);
			dst = nmppsAddr_8u((nm8u*)result,bigWidth*y+x);
			nmppmCopy_8s ((nm8s*) srcLived, width+2*xBorder,  (nm8s*) dst, bigWidth, height, width);
		}
	}
	return 0;
}