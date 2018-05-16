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
	int* sharedBuffer;
	int  sharedSize32;
	nm64s* srcFrm=(nm64s*)sharedBuffer;
	nm64s* dstFrm=srcFrm+srcFrmSize/64;
	int ok=0;

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
		
	LifeSpec spec;	
	int smallWidth  = width/4;
	int smallHeight = halfHeight/2;
	ok=lifeInit(width, halfHeight, smallWidth, smallHeight, &spec);
	if (ok){
		halHostSync(ok);	// send error to host
		return -1;
	}

	nm1* src = nmppsAddr_1((nm1*)srcFrm,halfSize+(1280+2*64)*64);
	nm1* dst = nmppsAddr_1((nm1*)dstFrm,halfSize);

	// Check memory allocation
	if (src ==0 || dst==0){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)src);
	
	clock_t t0,t1;
	halHostSync(0);	// Wait source buffer till is ready 	
	unsigned f;
	nm1 *srcCopy, *dstCopy;
	while(1){					
		t0=clock();	
		//------------------------------------------------------
		srcCopy = nmppsAddr_1((nm1*)srcFrm,(1280+2*64)*64);
		dstCopy = nmppsAddr_1((nm1*)srcFrm,2*halfSize+(1280+2*64)*64);
		nmppsCopy_8u((nm8u*)srcCopy,(nm8u*)dstCopy,width*spec.yBorder/8);
		//------------------------------------------------------
		procCounter[1]++;
		while(procCounter[0]!=procCounter[1]);
//			printf("* %d %d\n",procCounter[0],procCounter[1]);

		lifeRectangle((nm1*)src,(nm1*)dst,&spec);
		t1=clock();

		f = halHostSync(t1-t0);	// Send elapsed time 
		if (f==0xABC00ABC)
			break;
		// pc - readmemblock
		halHostSync(0x220);	// Send elapsed time */

		nmppsCopy_8s((nm8s*)dst,(nm8s*)src,halfSize/8);

		procCounter[3]++;
		while(procCounter[2]!=procCounter[3]);
//			printf("%d %d\n",procCounter[2],procCounter[3]);
		
//		t1=clock();	
		timer[1]=t1-t0;
	}
	lifeFree(&spec);
	return 1; 
} 

