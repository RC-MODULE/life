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

	int width =1280;
	int height=960;
	int size  =width*height;

	VS_CreateImage("Source Image", 1, width, height, VS_RGB1, 0);	// Create window for 8-bit source grayscale image
	VS_OpRunForward();

	halSync(width);		// Send width to nmc
	halSync(height);		// Send height to nmc
	int ok=halSync(0);	// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!");
		return -1;
	}
	unsigned srcAddr=halSync(0);
	
	nm1* srcFrm=nmppsMalloc_1 (size+256*width+256);
	nm1* srcImg=nmppsAddr_1(srcFrm,128*width+128);
	nm1* dstImg=nmppsMalloc_1 (size);

	int i;
	nmppsSet_8s((nm8s*) srcFrm,  0, (size+256*width+256)/8);
	nmppsSet_8s((nm8s*) dstImg,  0, size/8);
//	nmppsRandUniform_64s((nm64s*) srcImg8, size/64);

	for (int i=4;i<height/2;i++)
	{
		nmppsSet_32s((nm32s*) srcImg+i*width/32,  0xFFFFFFFF, width/32/2);
	}
	
	halWriteMemBlock((unsigned*)srcImg, srcAddr, size/32);
	halSync(0);

	while(VS_Run())	{

		Inv_1((nm1*)srcImg,(nm1*)dstImg,size);
 		VS_SetData(1, dstImg);				// Put source image in window ?1
		
		unsigned t=halSync(0);
		halReadMemBlock ((unsigned*)srcImg, srcAddr, size/32);
		
		VS_Text("%u clocks per frame , %.2f clocks per pixel, %.2f fps\r\n", t, 1.0*t/size, 320000000.0/t );
		VS_Draw(VS_DRAW_ALL);
	}
	halSync(0xABC00ABC);
	halClose();
	nmppsFree(srcFrm);
	nmppsFree(dstImg);
    return 0;
}
