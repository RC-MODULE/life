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

int lifeInit(int fullWidth, int fullHeight,int smallWidth,int smallHeight, LifeSpec* spec)
{	
	spec->isReady = false;
	spec->xBorder = 8;
	spec->yBorder = 8;
	spec->nColumns = fullWidth/smallWidth;
	spec->nLines = fullHeight/smallHeight;
	ASSERTE(fullWidth %smallWidth ==0);
	ASSERTE(fullHeight%smallHeight==0);
	spec->widthWindow = smallWidth;
	ASSERTE(spec->widthWindow%8==0);
	spec->heightWindow = smallHeight;

	int SizeAnd4Line = (spec->widthWindow+2*spec->xBorder)*(spec->heightWindow+2*spec->yBorder+4);

	if (nmppiFilterInitAlloc_8s16s(&spec->pState,lifeCentre,3,3,spec->widthWindow+2*spec->xBorder))
		return -1;

	spec->extOut = nmppsMalloc_16s(SizeAnd4Line);	
	spec->temp1 = nmppsMalloc_8u(SizeAnd4Line);
	spec->temp2 = nmppsMalloc_8u(SizeAnd4Line);
	spec->extWindow= nmppsMalloc_8u(SizeAnd4Line);

	if (nmppsMallocFail())			
		return -2;
	
	nmppsSet_8s((nm8s*)spec->extWindow,0,SizeAnd4Line);
	nmppsSet_8s((nm8s*)spec->temp1,0,SizeAnd4Line);
	nmppsSet_8s((nm8s*)spec->temp2,0,SizeAnd4Line);
	nmppsSet_16s((nm16s*)spec->extOut,0,SizeAnd4Line);

	spec->window = nmppsAddr_8u(spec->extWindow,2*(spec->widthWindow+2*spec->xBorder));
	spec->Out = nmppsAddr_16s(spec->extOut,2*(spec->widthWindow+2*spec->xBorder));

	spec->isReady = true;
	return 0;
}

bool lifeFree(LifeSpec* spec){
	nmppsFree(spec->extOut);
	nmppsFree(spec->temp1);
	nmppsFree(spec->temp2);
	nmppsFree(spec->extWindow);
	nmppiFilterFree(spec->pState);
	return true;
}

int life(const unsigned char* source, unsigned char* result, LifeSpec* spec)
{
	if (!spec->isReady)
		return -1;
	int width  = spec->widthWindow+2*spec->xBorder;
	int height = spec->heightWindow+2*spec->yBorder;

	NmppiFilterState* pState = spec->pState;
	int size=width*height;	
	nm16s* Out = spec->Out;		
	nm8u* temp1 = spec->temp1;
	nm8u* temp2 = spec->temp2;	
	
	nmppiFilter_8s16s ((nm8s*) source, Out	, width, height, pState); 
	
	nmppsConvert_16s8s( Out, (nm8s*) temp1,size);	
	
	nmppsCmpEqC_8u7b((nm8u7b*) temp1,  4,  (nm8s*) temp2, size, -1);
	nmppsAnd_8u((nm8u*)source,(nm8u*)temp2,(nm8u*)temp2,size);
	
	nmppsCmpEqC_8u7b((nm8u7b*) temp1,  3,  (nm8s*) temp1, size, -1);
	
	nmppsOr_8u   	  ((nm8u*) temp1 , (nm8u*) temp2, (nm8u*) result, size);		//merger
	
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
	unsigned int crc = 0;
	for (y=0;y<bigHeight;y+=height)
	{
		for (x=0;x<bigWidth;x+=width)
		{
			src = nmppsAddr_8u((nm8u*)source,bigWidth*(y-yBorder)+x-xBorder);
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