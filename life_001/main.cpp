//------------------------------------------------------------------------
//  Game Life 
//
//  Author: Ivan Zhilenkov
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "VShell.h"
#include "life.h"


int main()
{
	
	if(!VS_Init())
		return 0;

	int width = 640;
	int height= 480;
	int size  = width*height;

	VS_CreateImage("Life", 1, width, height, VS_RGB8, 0);
	
	unsigned char* srcFrame = new unsigned char[width*height+2*width+2];
	unsigned char* srcImage = srcFrame+width+1;
	unsigned char* dstImage = new unsigned char[width*height+2*width];
	
	int i,j;
	
	for(i=0;i<width*height+2*width+2;i++)
		srcFrame[i] = 0;

	

	for (i=0;i<height;i++)
	{
		for(j=0;j<width/20;j++)
		{
			srcImage[i*width+2*i+4*j]=0x00;
			srcImage[i*width+2*i+1+4*j]=0xFF;
			srcImage[i*width+2*i+2+4*j]=0x00;
			srcImage[i*width+2*i+3+4*j]=0xFF;
		}
	}

	while(VS_Run())	{

		VS_SetData(1, srcImage);

		life(srcImage, dstImage, width, height);
		
		for(i=0;i<size;i++)
			srcImage[i]=dstImage[i];
		
		VS_Draw(VS_DRAW_ALL);
		
	}
    
	delete srcFrame;
	delete dstImage;
    return 0;
}
