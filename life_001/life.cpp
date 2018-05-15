

void life(unsigned char* srcImage, unsigned char* dstImage, int width, int height)
{
	int size = width*height;
	int i,j, sum,w[9];
	unsigned char* src;
	unsigned char* dst;
	unsigned char k[9];
	
	src = srcImage;
	dst = srcImage+size;
	for(i=0;i<width;i++)
		dst[i]=src[i];

	src = srcImage+size-width;
	dst = srcImage-width;
	for(i=0;i<width;i++)
		dst[i]=src[i];
	
	src = srcImage;
	dst = dstImage;
	
	//main loop
	for(i=0;i<size;i++)
	{
		
		k[0]= *(src-width-1);	k[1]= *(src-width);		k[2]= *(src-width+1);
		k[3]= *(src-1)	   ;	k[4]= *(src);			k[5]= *(src+1);
		k[6]= *(src+width-1);	k[7]= *(src+width);		k[8]= *(src+width+1);
	
		for(j=0;j<9;j++)
			w[j] = (int)k[j] & 0x1;
		
		sum = 	w[0]+w[1]+w[2]+
				w[3]+  0 +w[5]+
				w[6]+w[7]+w[8];
		
		// 0xFF = cell is alive (white color)
		// 0x00 = cell is dead  (black color)
		
		if (*src==0)
			if (sum==3)
				*dst=-1;
			else
				*dst=0;
			
		else
			if ((sum==2 || sum==3))
				*dst=-1;
			else
				*dst=0;
		src++;
		dst++;
	}
	
}


