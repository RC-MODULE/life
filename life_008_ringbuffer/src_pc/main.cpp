//------------------------------------------------------------------------
//  Game Life 
//
//  Author: Ivan Zhilenkov
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "hal_host.h"
#include "VShell.h"
#include "nmpp.h"
#include "stdio.h"
#include "ringbuffert.h"

#define PROGRAM "life.abs"

void Inv_1(nm1* pSrcVec,nm1* pDstVec,int nSize)
{
	int i,j;
	nm8s*pi8Dst = (nm8s*)pDstVec;
	int iSize = nSize >> 3;
	signed char uiSrc, *puiSrc = (nm8s*)pSrcVec;
	
	for(i=0; i<iSize; i++)
	{
		uiSrc = puiSrc[i];
		for(j=0;j<8;j++)
		{
			pi8Dst[i] <<= 1;
			pi8Dst[i] |= uiSrc & 0x1;
			uiSrc >>= 1;
		}
	}
}

#define N_ITER 1
#define LIFE_WIDTH 1280
#define LIFE_HEIGHT 960
#define width  1280
#define height 960
#define size  LIFE_WIDTH*LIFE_HEIGHT

struct Life {
	nm64u dummy0;	// top guard line
	nm64u mirrorBottom[LIFE_WIDTH*N_ITER / 64];
	struct  {
		nm64u top[LIFE_WIDTH*N_ITER / 64];
		nm64u main[LIFE_WIDTH*LIFE_HEIGHT / 64];
		nm64u bottom[LIFE_WIDTH*N_ITER / 64];
	} state;
	nm64u mirrorTop[LIFE_WIDTH*N_ITER / 64];
	nm64u dummy1;	// top guard line
} viewLife, invLife;



void*  writeMemBlock(const void* src, void* dst, unsigned int size32) {
	halWriteMemBlock(src, (unsigned int)dst, size32, 0);
	return 0;
}

void* readMemBlock(const void* src, void* dst, unsigned int size32) {
	halReadMemBlock(dst, (unsigned int)src, size32, 0);
	return 0;
}



int main()
{
	#ifdef NMPU1
	halOpen("",PROGRAM,NULL);
	#else
	halOpen(PROGRAM,NULL);
	#endif

	int handshake= halSync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
	//	printf("Handshake with mc5103 error!");
		return -1;
	}
	
	if(!VS_Init())
		return 0;


	VS_CreateImage("Source Image", 1, LIFE_WIDTH, LIFE_HEIGHT, VS_RGB1, 0);	// Create window for 8-bit source grayscale image
	VS_OpRunForward();

	int ok=halSync(0);	// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!");
		return -1;
	}
	unsigned addrImageRB = halSync(0);

	HalRingBufferConnector<Life, 16>  lifeRingBuffer;
	lifeRingBuffer.connect(addrImageRB, writeMemBlock, readMemBlock);


	
	while(VS_Run())	{
		lifeRingBuffer.pop(&viewLife, 1);
		Inv_1((nm1*)viewLife.state.top,(nm1*)invLife.state.top,size);
 		VS_SetData(1, invLife.state.top);				// Put source image in window ?1
	
		//VS_Text("%u clocks per frame , %.2f clocks per pixel, %.2f fps\r\n", t, 1.0*t/size, 320000000.0/t );
		VS_Draw(VS_DRAW_ALL);
	}
	halSync(0xABC00ABC);
	halClose();
	//nmppsFree(srcFrm);
	//nmppsFree(dstImg);
    return 0;
}
