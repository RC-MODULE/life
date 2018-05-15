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

int lifeInit(int fullWidth, int fullHeight, LifeSpec* spec)
{	
	spec->isReady = false;
	spec->widthWindow = fullWidth;
	ASSERTE(spec->widthWindow%8==0);
	spec->heightWindow = fullHeight;
	int SizeAnd4Line = (spec->widthWindow)*(spec->heightWindow+4);

	if (nmppiFilterInitAlloc_8s16s(&spec->pState,lifeCentre,3,3,spec->widthWindow))
		return -1;

	spec->Out = nmppsMalloc_16s(SizeAnd4Line);	
	spec->temp1 = nmppsMalloc_8u(SizeAnd4Line);
	spec->temp2 = nmppsMalloc_8u(SizeAnd4Line);
	spec->extWindow= nmppsMalloc_8u(SizeAnd4Line);

	if (nmppsMallocFail())			
		return -2;	
	
	nmppsSet_8s((nm8s*)spec->extWindow,0,SizeAnd4Line);
	spec->window = nmppsAddr_8u(spec->extWindow,2*spec->widthWindow);

	spec->isReady = true;
	return 0;
}

bool lifeFree(LifeSpec* spec){
	nmppsFree(spec->Out);
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
	int width  = spec->widthWindow;
	int height = spec->heightWindow;

	NmppiFilterState* pState = spec->pState;
	int size=width*height;
	nm8u* window = spec->window;		
	nm16s* Out = spec->Out;		
	nm8u* temp1 = spec->temp1;
	nm8u* temp2 = spec->temp2;

	
//-------------------copy-to-window------------------
	nm8u* SrcCopy;
	nm8u* DstCopy;
	//centre
	SrcCopy = (nm8u*)source;
	DstCopy = (nm8u*)window;
	nmppsCopy_8u(SrcCopy, DstCopy, size);
	//up
	SrcCopy = nmppsAddr_8u((nm8u*)source,size-width);
	DstCopy = nmppsAddr_8u((nm8u*)window,-width);
	nmppsCopy_8u(SrcCopy, DstCopy, width);
	//down
	DstCopy = nmppsAddr_8u((nm8u*)window, size);
	SrcCopy = (nm8u*) source;
	nmppsCopy_8u(SrcCopy , DstCopy, width);
//-----------------------------------------------------

	nmppiFilter_8s16s ((nm8s*) window, Out	, width, height, pState); 
	
	nmppsConvert_16s8s( Out, (nm8s*) temp1,size);			
	
	nmppsCmpEqC_8u7b((nm8u7b*) temp1,  4,  (nm8s*) temp2, size, -1);
	nmppsAnd_8u((nm8u*)source,(nm8u*)temp2,(nm8u*)temp2,size);
	
	nmppsCmpEqC_8u7b((nm8u7b*) temp1,  3,  (nm8s*) temp1, size, -1);
	
	nmppsOr_8u   	  ((nm8u*) temp1 , (nm8u*) temp2, (nm8u*) result, size);		//merger
	
	return 0;
}
