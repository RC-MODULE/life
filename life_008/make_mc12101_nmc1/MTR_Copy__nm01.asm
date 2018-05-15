//------------------------------------------------------------------------
//
//  $Workfile:: mtrCopyMatrix08.as $
//
//  Векторно-матричная библиотека


begin ".text_life"
/////////////////////////////////////////////////////////////////////////////////
// Copying long submatrix from 8 bit odd position of source matrix
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------
//! \fn void nmppmCopy_8s(  nm8s* pSrcMtr, int nSrcStride,  nm8s* pDstMtr, int nDstStride, int nHeight, int nWidth)
//!
//! \perfinclude _nmppmCopy_8s.html
//--------------------------------------------------------------------

global _nmppmCopy_1:label;
<_nmppmCopy_1>
.branch;

	ar5 = sp-2		with gr7=false;	

	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;


	ar0 = [--ar5];	// nm1*	SrcMtr,			// Src matrix				:long Local   [nSrcRows*nSrcStride]
	gr0 = [--ar5];	// int		nSrcStride,	// Src matrix Stride		:nSrcStride=[0,1,2,3....]
	ar6 = [--ar5];	// nm1*	DstMtr,			// Dst matrix				:long Global  [nDstRows*nDstStride]
	gr6 = [--ar5];	// int		nDstStride,	// Dst matrix Stride		:nDstRows=[0,1,2,3,...]
	gr2 = [--ar5];	// int		nHeight,		// Dst matrix height		:nDstRows=[0,1,2,3,...]
	gr3 = [--ar5];	// int		nWidth		// Dst matrix width			:nDstStride =[0,8,16,24..]

	gr3>>=5;
	gr0>>=5;
	gr6>>=5;
	ar3=gr3;
<NextWidth>
	gr3=ar3;	
	ar1=ar0;
	ar5=ar6	with gr3--;
<Next>
	if > delayed goto Next with gr3--;
		gr1=[ar1++];
		[ar5++]=gr1;
		
	gr2--;
	if > delayed goto NextWidth;
		ar0+=gr0;
		ar6+=gr6;
	
	
/*	delayed call mtr_CpyCore_nm64 with gr3>>=3;
		with gr1>>=2;
		with gr4>>=2;*/


	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

return;
/////////////////////////////////////////////////////////////////////////////////
.wait;
end ".text_life";