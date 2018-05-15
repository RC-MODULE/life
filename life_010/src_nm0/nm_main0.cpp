#include "hal_target.h"
#include "life.h"
#include "malloc32.h"
#include <time.h>
#include <stdio.h>

int srcFrmSize = 1280*960+(1280+2*64)*2*64;		//size in bits
int dstFrmSize = 1280*960+8*64*2;				//size in bits

int main()
{  
	int procNo=halGetProcessorNo();
	int* sharedBuffer=halMalloc32(srcFrmSize/32 + dstFrmSize/32 +4 +4);
	(sharedBuffer, srcFrmSize/32 + dstFrmSize/32+4+4);
	nm64s* srcFrm=(nm64s*)sharedBuffer;
	nm64s* dstFrm=srcFrm+srcFrmSize/64;

	unsigned int* procCounter = (unsigned int*) (sharedBuffer + srcFrmSize/32+ dstFrmSize/32) ;
	unsigned int* timer = (unsigned int*) procCounter + 4;
	
	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);
	int halfHeight= halHostSync(1);
	int halfSize  = width*halfHeight;
	
	nmppsSet_64s(srcFrm,0,srcFrmSize/64);
	nmppsSet_64s(dstFrm,0,dstFrmSize/64);
	
	LifeSpec spec;	
	int smallWidth  = width/4;
	int smallHeight = halfHeight/2;	
	nm1* src = nmppsAddr_1((nm1*)srcFrm,(1280+2*64)*64);
	nm1* dst = (nm1*)dstFrm;
	
	int ok=lifeInit(width, halfHeight, smallWidth, smallHeight, &spec);
	if (ok){
		halHostSync(ok);	// send error to host
		return -1;
	}

	// Check memory allocation
	if (src ==0 || dst==0){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)src);		// Send source buffer address to host
		
	
	clock_t t0,t1;
	procCounter[0]=0;
	procCounter[1]=0;
	procCounter[2]=0;
	procCounter[3]=0;
	halHostSync(0);	// Wait source buffer till is ready 	
	unsigned f;
	nm1 *srcCopy, *dstCopy;
	while(1){					
		t0=clock();	
		//------------------------------------------------------
		srcCopy = nmppsAddr_1((nm1*)src,2*halfSize-width*spec.yBorder);
		dstCopy = nmppsAddr_1((nm1*)src,-width*spec.yBorder);
		nmppsCopy_8u((nm8u*)srcCopy,(nm8u*)dstCopy,width*spec.yBorder/8);
		//------------------------------------------------------
		procCounter[0]++;
		while(procCounter[0]!=procCounter[1]);
		lifeRectangle((nm1*)src,(nm1*)dst,&spec);
		t1=clock();	
		int f = halHostSync(t1-t0);	// send 0 Ready .Send elapsed time 
		if (f==0xABC00ABC)
			break;
		// pc - readmemblock
		halHostSync(0x110);	// Send elapsed time */
	
		nmppsCopy_8s((nm8s*)dst,(nm8s*)src,halfSize/8);

		procCounter[2]++;
		while(procCounter[2]!=procCounter[3]);
		
//		t1=clock();	
		timer[0]=t1-t0;
	}
	lifeFree(&spec);
	return 1; 
} 

