


global _nmppsCopy_8s:label;
global _nmppsCopy_8u:label;

begin ".text_life"
<_nmppsCopy_8s>
<_nmppsCopy_8u>
.branch;
    ar5 = sp - 2	with gr7=gr5;
	push ar0,gr0;
	push ar6,gr6;
    ar0 = [--ar5];		// pSrcVec
	ar6 = [--ar5];		// pDstVec
	gr5 = [--ar5];		// nSize
	gr5>>=2;
	gr5--;
<NEXT>
	if > delayed goto NEXT with gr5--;
		gr0=[ar0++];
		[ar6++]=gr0;
	
	pop ar6,gr6;
	pop ar0,gr0		with gr5=gr7;
	return;
.wait;
end ".text_life";