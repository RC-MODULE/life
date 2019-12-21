#include "nmpli.h"
#include "nmpp.h"

#define N_ITER 1

struct LifeSpec
{
	void* pool1;
	void* pool2;
	void* pool3;

	int widthWindow;
	int heightWindow;
	bool isReady;	
	nm4u* temp1;
	nm4u* temp2;
	nm4u* temp3;
	nm1* window;
	nm1* extWindow;
	int xBorder;
	int yBorder;
	int nLines;
	int nColumns;
	NmppiFilterState* pState;
};


int lifeRectangle(const nm1* source, nm1* result, LifeSpec* spec);
int lifeInit(int fullWidth, int fullHeight,int smallWidth,int smallHeight, LifeSpec* spec);
bool lifeFree(LifeSpec* spec);
int life(const nm1* srcImage, nm1* dstImage, LifeSpec* spec);
