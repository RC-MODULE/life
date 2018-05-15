#include "nmpli.h"
#include "nmpp.h"

struct LifeSpec
{
	int widthWindow;
	int heightWindow;
	bool isReady;
	nm16s* Out;		
	nm8u* temp0;
	nm8u* temp1;
	nm8u* temp2;
	nm8u* window;
	nm8u* extWindow;
	NmppiFilterState* pState;
};


int lifeInit(int fullWidth, int fullHeight, LifeSpec* spec);
bool lifeFree(LifeSpec* spec);
int life(const unsigned char* srcImage, unsigned char* dstImage, LifeSpec* spec);



