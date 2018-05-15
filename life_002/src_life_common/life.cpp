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

int life(const unsigned char* source, unsigned char* result, int width,int height)
{

	int size = width*height;
	
	NmppiFilterState* pState;
	if (nmppiFilterInitAlloc_8s16s(&pState,lifeCentre,3,3,width))
		return -1;
	
	nm16s* Out = nmppsMalloc_16s(size);	
	nm8u* temp1 = nmppsMalloc_8u(size);
	nm8u* temp2 = nmppsMalloc_8u(size);
	nm8u* extWindow= nmppsMalloc_8u(size+4*width);

	if (nmppsMallocFail())			
		return -2;		
	
	nmppsSet_8u(extWindow,0,size+4*width);
	nm8u* window = nmppsAddr_8u(extWindow,2*width);
//---------------------------copy-to-window-------------------------
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
//------------------------------------------------------------------	

	nmppiFilter_8s16s ((nm8s*) window, Out, width, height, pState); 
	
	nmppsConvert_16s8s( Out, (nm8s*) temp1,size);		

	nmppsCmpEqC_8u7b((nm8u7b*) temp1,  4,  (nm8s*) temp2, size, -1);
	nmppsAnd_8u		((nm8u*)temp2,(nm8u*)source,(nm8u*)temp2,size);

	nmppsCmpEqC_8u7b((nm8u7b*) temp1,  3,  (nm8s*) temp1, size, -1);
	
	nmppsOr_8u   	  ((nm8u*) temp1	 , (nm8u*) temp2, (nm8u*) result, size);		//merger

	nmppsFree(Out);
	nmppsFree(temp1);
	nmppsFree(temp2);
	nmppsFree(extWindow);
	nmppiFilterFree(pState);
	
	return 0;
}
