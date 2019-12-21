#include "hal_target.h"
#include "life.h"
#include "malloc32.h"
#include <time.h>
#include <stdio.h>
#include <ringbuffer.h>
#include <hal_target.h>

int srcFrmSize = 1280*960+(1280+2*64)*2*64;		//size in bits
				//size in bits

#define INNER_COUNT 8

int main()
{  
	nmc_malloc_set_heap(0);
	int* sharedBuffer=halMalloc32(INNER_COUNT * srcFrmSize / 32);
	HalRingBuffer* imageRB = (HalRingBuffer*)halMalloc32(sizeof32(HalRingBuffer));
	halRingBufferInit(imageRB, sharedBuffer, srcFrmSize / 32, INNER_COUNT, 0, 0, 0);

	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);
	int height= halHostSync(1);
	int size  = width*height;

	//nmppsMallocSetRouteMode();
	//nmppsMallocSpec.route[0]=0x3321;
		
	LifeSpec specWindow;
	int smallWidth  = width/4;
	int smallHeight = height/4;
	int ok = lifeInit(width, height, smallWidth, smallHeight, &specWindow);
	if (ok){
		halHostSync(ok);	// send error to host
		return -1;
	}

	// Check memory allocation
	if (sharedBuffer == 0){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)imageRB);		// Send source buffer address to host	
		
	clock_t t0,t1;
	halHostSync(0x111);	// Wait source buffer till is ready 		

	unsigned f;
	nm1 *srcCopy, *dstCopy;
	while(1){			
		while (halRingBufferIsFull(imageRB));

		t0=clock();	
		imageRB->head--;
		nm1* src = nmppsAddr_1((nm1*)halRingBufferHead(imageRB), width*specWindow.yBorder);
		imageRB->head++;
		nm1* dst = nmppsAddr_1((nm1*)halRingBufferHead(imageRB), width*specWindow.yBorder);
		//-----------------------up-----------------------------
		srcCopy = (nm1*)src;
		dstCopy = nmppsAddr_1((nm1*)src,size);
		nmppsCopy_8u((nm8u*)srcCopy,(nm8u*)dstCopy,width*specWindow.yBorder/8);
		//----------------------down----------------------------
		srcCopy = nmppsAddr_1((nm1*)src,size-width*specWindow.yBorder);
		dstCopy = nmppsAddr_1((nm1*)src,-width*specWindow.yBorder);
		nmppsCopy_8u((nm8u*)srcCopy,(nm8u*)dstCopy,width*specWindow.yBorder/8);
		//------------------------------------------------------
		ok = lifeRectangle((nm1*)src,(nm1*)dst,&specWindow);
		t1=clock();

		int time = t1 - t0;
		printf("time=%d\n", time/ N_ITER);
		//halHostSync(t1 - t0);

		imageRB->head++;
	
	}
	lifeFree(&specWindow);
	return 1; 
} 

