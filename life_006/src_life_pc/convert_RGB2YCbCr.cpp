
/* float kShift[3] = {0,128,128};
 float kShiftRGB[3] = {0,0,0};
float kYCbCr[9] = {	0.299,	    0.587,		 0.114,
					-0.168736,  -0.331264,	 0.5,
					0.5,	   -0.418688,	-0.081312};

float kRGB[9] = {	1,		0,			 1.402,
					1,		-0.34414,	-0.71414,
					1,		1.772,		 0}; */
					
/*short kShift[3] = {16,128,128};
short kShiftRGB[3] = {0,0,0};
short kYCbCr[9] = {	65,	129, 25,
					-38,  -74,	 112,
					112,  -94,	-18};

short kRGB[9] = {	298, 0,	409,
					298, -100,-208,
					298,516, 0};*/

short kShift[3] = {16,128,128};
//short kShiftRGB[3] = {-222.921,135.576,276.836};
short kShiftRGB[3] = {0,0,0};
short kYCbCr[9] = {	65.738,	129.057, 25.064,
					-37.945,  -74.494,	 112.439,
					112.439,  -94.154,	-18.285};

short kRGB[9] = {	298.082, 0,	408.583,
					298.082, -100.291,-208.120,
					298.082,516.412, 0};

					
/* short kShift[3] = {16,128,128};
short kShiftRGB[3] = {0,0,0};
short kYCbCr[9] = {	 65.738,   129.057,  25.064,
					-37.945,  -74.494 ,	  112.439,
					 112.439 ,  -94.154 ,	-18.285};
short kRGB[9] = {	298.082,	0,			 408.583,
					298.082,	-100.291,	-208.120,
					298.082,	516.412,		 0};*/
					



void convert_RGB24_YCbCr(signed char* pSrcRGB, signed char* pDstY, signed char* pDstCb, signed char* pDstCr, int nSize){
	for(int i=0;i<nSize;i++){
		signed char ucBlue  = pSrcRGB[3*i];
		signed char ucGreen = pSrcRGB[3*i+1];
		signed char ucRed   = pSrcRGB[3*i+2];
		
		short temp;
		temp = kYCbCr[0]*ucRed + kYCbCr[1]*ucGreen + kYCbCr[2]*ucBlue;
		pDstY[i]   = (temp>>8)+kShift[0];
		temp = kYCbCr[3]*ucRed + kYCbCr[4]*ucGreen + kYCbCr[5]*ucBlue;
		pDstCb[i]  = (temp>>8)+kShift[1];
		temp = kYCbCr[6]*ucRed + kYCbCr[7]*ucGreen + kYCbCr[8]*ucBlue;
		pDstCr[i]  = (temp>>8)+kShift[2];

		/*pDstY[i]  = (pDstY[i] <16 -128) ? 219-128	: pDstY[i];
		pDstY[i]  = (pDstY[i] >219-128) ? 16 -128		: pDstY[i];
		pDstCb[i] = (pDstCb[i]<16 -128) ? 219-128	: pDstCb[i];
		pDstCb[i] = (pDstCb[i]>219-128) ? 16 -128		: pDstCb[i];
		pDstCr[i] = (pDstCr[i]<16 -128) ? 219-128	: pDstCr[i];
		pDstCr[i] = (pDstCr[i]>219-128) ? 16 -128	: pDstCr[i];*/ 

	}
}

void convert_YCbCr_RGB24(signed char* pDstRGB, signed char* pSrcY, signed char* pSrcCb, signed char* pSrcCr, int nSize){
	for(int i=0;i<nSize;i++){	
		pSrcY[i] -=kShift[0];
		pSrcCb[i]-=kShift[1];
		pSrcCr[i]-=kShift[2];
		short ucRed   = kRGB[0]*pSrcY[i] + kRGB[1]*pSrcCb[i] + kRGB[2]*pSrcCr[i];
		short ucGreen = kRGB[3]*pSrcY[i] + kRGB[4]*pSrcCb[i] + kRGB[5]*pSrcCr[i];
		short ucBlue  = kRGB[6]*pSrcY[i] + kRGB[7]*pSrcCb[i] + kRGB[8]*pSrcCr[i];
		pDstRGB[3*i] =   (ucBlue >>8) + kShiftRGB[0];
		pDstRGB[3*i+1] = (ucGreen>>8) + kShiftRGB[1];
		pDstRGB[3*i+2] = (ucRed  >>8) + kShiftRGB[2];

		/* if ((pDstRGB[3*i]  >240-128) && 
			(pDstRGB[3*i+1]>240-128) &&
			(pDstRGB[3*i+2]>240-128)){
			pDstRGB[3*i] = 240-128;
			pDstRGB[3*i+1] = 240-128;
			pDstRGB[3*i+2] = 240-128;
		} */ 

		/* pDstRGB[3*i]   = (pDstRGB[3*i]<16-128)		 ? 240-128	: pDstRGB[3*i];
		pDstRGB[3*i]   = (pDstRGB[3*i]>240-128)	 ? 16-128	: pDstRGB[3*i];
		pDstRGB[3*i+1] = (pDstRGB[3*i+1]==16-128)	 ? 240-128	: pDstRGB[3*i+1];
		pDstRGB[3*i+1] = (pDstRGB[3*i+1]==240-128)  ? 16-128	: pDstRGB[3*i+1];
		pDstRGB[3*i+2] = (pDstRGB[3*i+2]==16-128)	 ? 240-128	: pDstRGB[3*i+2];
		pDstRGB[3*i+2] = (pDstRGB[3*i+2]==240-128)  ? 16-128	: pDstRGB[3*i+2];*/

	}
}