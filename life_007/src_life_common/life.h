#include "nmpli.h"
#include "nmpp.h"

struct LifeSpec
{
	void* pool1;
	void* pool2;
	void* pool3;

	int widthWindow;
	int heightWindow;
	bool isReady;	
	nm8u* temp1;
	nm8u* temp2;
	nm8u* temp3;
	nm8u* window;
	nm8u* extWindow;
	int xBorder;
	int yBorder;
	int nLines;
	int nColumns;
	NmppiFilterState* pState;
};


int lifeRectangle(const unsigned char* source, unsigned char* result, LifeSpec* spec);
int lifeInit(int fullWidth, int fullHeight,int smallWidth,int smallHeight, LifeSpec* spec);
bool lifeFree(LifeSpec* spec);
int life(const unsigned char* srcImage, unsigned char* dstImage, LifeSpec* spec);
