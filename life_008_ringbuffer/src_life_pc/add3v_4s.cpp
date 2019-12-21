#include "malloc32.h"
#include "life.h"

void add3v_4s(nm4s* SrcVec1, nm4s* SrcVec2, nm4s* SrcVec3, nm4s* DstVec, int nSize)
{
	nmppsAdd_4s(SrcVec1,SrcVec2,DstVec,nSize);
	nmppsAdd_4s(DstVec ,SrcVec3,DstVec,nSize);
}