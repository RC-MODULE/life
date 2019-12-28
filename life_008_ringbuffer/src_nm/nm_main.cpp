#include "hal_target.h"
#include "life.h"
#include "malloc32.h"
#include <time.h>
#include <stdio.h>
#include <ringbuffer.h>
#include <ringbuffert.h>
#include <hal_target.h>


//#define FRAME_BIT_SIZE = (FRAME_WIDTH*FRAME_HIGHT+(FRAME_WIDTH+2*64)*2*64)		//size in bits
				//size in bits

#define INNER_COUNT 8

#define LIFE_WIDTH 1280
#define LIFE_HEIGHT 960
#define size  LIFE_WIDTH*LIFE_HEIGHT
#define width  1280
#define height 960

struct Life {
	nm64u dummy0;	// top guard line
	nm64u mirrorBottom[LIFE_WIDTH*N_ITER/64];
	struct SS {
		nm64u top   [LIFE_WIDTH*N_ITER /64];
		nm64u main  [LIFE_WIDTH*LIFE_HEIGHT / 64];	
		nm64u bottom[LIFE_WIDTH*N_ITER /64];
	} state;
	nm64u mirrorTop   [LIFE_WIDTH*N_ITER /64];
	nm64u dummy1;	// top guard line
};


int main()
{  
	nmc_malloc_set_heap(0);
	HalRingBufferConnector<Life, 16>  lifeRingBuffer;
	lifeRingBuffer.create();
	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}
		
	LifeSpec specWindow;
	int smallWidth  = LIFE_WIDTH /4;
	int smallHeight = LIFE_HEIGHT /4;
	int ok = lifeInit(LIFE_WIDTH, LIFE_HEIGHT, smallWidth, smallHeight, &specWindow);
	if (ok){
		halHostSync(ok);	// send error to host
		return -1;
	}

	// Check memory allocation
	if (lifeRingBuffer.container == 0){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)lifeRingBuffer.container);		// Send source buffer address to host	
		
	clock_t t0,t1;
	Life* srcLife;
	Life* dstLife = lifeRingBuffer.ptrHead();
	nmppsRandUniform_64s((nm64s*)dstLife->state.top, size/64);
	lifeRingBuffer.incHead();

	while(1){			
		while (lifeRingBuffer.isFull()) {
			halSleep(10);
		}
		
		srcLife = dstLife;
		dstLife = lifeRingBuffer.ptrHead();

		t0=clock();	
		nmppsCopy_64u(srcLife->state.top,    srcLife->mirrorTop, LIFE_WIDTH*N_ITER /64);
		nmppsCopy_64u(srcLife->state.bottom, srcLife->mirrorBottom, LIFE_WIDTH*N_ITER / 64);
		//------------------------------------------------------
		ok = lifeRectangle((nm1*)srcLife->state.top,(nm1*)dstLife->state.top,&specWindow);
		t1=clock();
		//
		int time = t1 - t0;
		printf("time=%d %f\n", time, time*1.0/LIFE_WIDTH/LIFE_HEIGHT);
		

		lifeRingBuffer.incHead();
	
	}
	lifeFree(&specWindow);
	return 1; 
} 

