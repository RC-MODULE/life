#include "hal_target.h"
#include "life.h"
#include "malloc32.h"
#include <time.h>

int srcFrmSize = 1280*960+(1280+2*64)*2*64;		//size in bits
int dstSize = 1280*960+8*64;					//size in bits

int main()
{  
	int* sharedBuffer=halMalloc32(srcFrmSize/32 + dstSize/32);
	(sharedBuffer, srcFrmSize/32 + dstSize/32);
	nm64s* srcFrm=(nm64s*)sharedBuffer;
	nm64s* dst=srcFrm+srcFrmSize/64;

	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);
	int height= halHostSync(1);
	int size  = width*height;
	nm1* src = nmppsAddr_1((nm1*)srcFrm,(1280+2*64)*64);
	nmppsSet_64s(srcFrm,0,srcFrmSize/64);
	nmppsSet_64s(srcFrm,0,dstSize/64);
	
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
	if (src ==0 || dst==0){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)src);		// Send source buffer address to host
		
	
	clock_t t0,t1;
	halHostSync(0x111);	// Wait source buffer till is ready 	
	unsigned f;
	nm1 *srcCopy, *dstCopy;
	while(1){					
		t0=clock();	
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
				
		ok = halHostSync(t1-t0);	// Send elapsed time 
		if (ok==0xABC00ABC)
			break;
		nmppsCopy_8s((nm8s*)dst,(nm8s*)src,size/8);
	}
	lifeFree(&specWindow);
	return 1; 
} 

