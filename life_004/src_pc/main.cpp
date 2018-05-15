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

#define PROGRAM "life.abs"

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

	int width =640;
	int height=480;
	int size  =width*height;

	VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for 8-bit source grayscale image

	halSync(width);		// Send width to nmc
	halSync(height);		// Send height to nmc
	int ok=halSync(0);	// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
	//	printf("Memory allocation error!");
		return -1;
	}
	unsigned srcAddr=halSync(0);
	
	unsigned char*  srcFrm8=  new unsigned char [size+32*width+32];
	unsigned char*  srcImg8 = nmppsAddr_8u(srcFrm8,16*width+16);
	int i;	

	nmppsSet_8s((nm8s*) srcFrm8,  0, size+32*width+32);
//	nmppsRandUniform_64s((nm64s*) srcImg8, size/8);
	for (i=0;i<height;i++)
	{
		nmppsSet_32s((nm32s*) (srcImg8+i*width+2*i), 0x00FF00FF , width/20);
	}
			
	nmppsRShiftC_8s ((nm8s*) srcImg8, 7, (nm8s*) srcImg8, size);	//do 0 or -1
	halWriteMemBlock((unsigned*)srcImg8, srcAddr, size/4);
	ok=halSync(0);

	while(VS_Run())	{

 		VS_SetData(1, srcImg8);				// Put source image in window ?1
		
		unsigned t=halSync(0);
		if (t==0xDEADB00F)
			break;
		halReadMemBlock ((unsigned*)srcImg8, srcAddr, size/4);
		
		VS_Text("%u clocks per frame , %.2f clocks per pixel, %.2f fps\r\n", t, 1.0*t/size, 320000000.0/t );
		VS_Draw(VS_DRAW_ALL);
	}
	halSync(0xABC00ABC);
	halClose();
	delete srcFrm8;
    return 0;
}
