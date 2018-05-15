global _add3v_4s:label;

macro add3v_4s_tail(N)
	rep N ram  = [ar0++];
	rep N data = [ar1++] with ram + data;
	delayed goto Tail_End;
		rep N data = [ar2++] with data+afifo;
		rep N [ar6++]= afifo;
	nul;
	nul;
end add3v_4s_tail;

begin ".text_life"
<_add3v_4s>
.branch;
	ar5 = sp - 2;	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar6,gr6;
	ar0 = [--ar5];	//first vector
	ar1 = [--ar5];	//second vector
	ar2 = [--ar5];	//third vector 
	ar6 = [--ar5];	//result
	gr0 = [--ar5];	//size
	nb1=88888888h	with	gr0>>=4;
	gr1=gr0>>5;
	wtw;
	gr1--;
<Next32>
	rep 32 ram  = [ar0++];
	rep 32 data = [ar1++] with ram + data;
	if > delayed goto Next32 with gr1--;
		rep 32 data = [ar2++] with data+afifo;
		rep 32 [ar6++]= afifo;
	
	Tail:label;
	Tail_End: label;
	gr1=gr0>>5;
	gr1<<=5;
	ar3=Tail with gr3=gr0-gr1;
	gr3<<=3;	
	ar3+=gr3;
	delayed goto ar3;
		nul;
		nul;
		nul;
<Tail>
	delayed goto Tail_End;
		nul;
		nul;
	nul;nul;nul;nul;
	add3v_4s_tail(1);
	add3v_4s_tail(2);
	add3v_4s_tail(3);
	add3v_4s_tail(4);
	add3v_4s_tail(5);
	add3v_4s_tail(6);
	add3v_4s_tail(7);
	add3v_4s_tail(8);
	add3v_4s_tail(9);
	add3v_4s_tail(10);
	add3v_4s_tail(11);
	add3v_4s_tail(12);
	add3v_4s_tail(13);
	add3v_4s_tail(14);
	add3v_4s_tail(15);
	add3v_4s_tail(16);
	add3v_4s_tail(17);
	add3v_4s_tail(18);
	add3v_4s_tail(19);
	add3v_4s_tail(20);
	add3v_4s_tail(21);
	add3v_4s_tail(22);
	add3v_4s_tail(23);
	add3v_4s_tail(24);
	add3v_4s_tail(25);
	add3v_4s_tail(26);
	add3v_4s_tail(27);
	add3v_4s_tail(28);
	add3v_4s_tail(29);
	add3v_4s_tail(30);
	add3v_4s_tail(31);
<Tail_End>
	pop ar6,gr6;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;
end ".text_life"; 
