#include "hal_target.h"
#include "life.h"
#include "malloc32.h"
#include <time.h>
#include <stdio.h>
	
int srcFrmSize = 1920*1080+1920*2*8;		//byte
int dstSize = 1920*1080+64*2;				//byte

int main()
{  
	int* sharedBuffer=halMalloc32(srcFrmSize/4 + dstSize/4);
	nm32s* srcFrm=(nm32s*)sharedBuffer;
	nm32s* dst=nmppsAddr_32s(srcFrm,srcFrmSize/4);

	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}
	//printf("TARGET:Handshake OK!\n");

	// Get image parameters from host
	int width = halHostSync(0);
	int height= halHostSync(1);
	int size  = width*height;
	nm8u* src = nmppsAddr_8u((nm8u*)srcFrm,1920*8);
	nmppsSet_32s(srcFrm,0,srcFrmSize/4);
	nmppsSet_32s(dst,0,dstSize/4);
	
	// Check memory allocation
	if (src ==0 || dst==0){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)src);		// Send source buffer address to host
	
	
	clock_t t0,t1;
	halHostSync(0);	// Wait source buffer till is ready 
	unsigned f = 0;
	while(1){					// Start life in loop 
		t0=clock();
		int ok = life((unsigned char*)src,(unsigned char*)dst, width, height);
		if (ok){
			halHostSync(0xDEADB00F);
			halHostSync(ok);
		}
		t1=clock();

		ok = halHostSync(t1-t0);	// Send elapsed time 
		if(ok==0xABC00ABC){
			break;
		}
		
		nmppsCopy_8s((nm8s*)dst,(nm8s*)src,size);
	}
	return 1; 
} 

