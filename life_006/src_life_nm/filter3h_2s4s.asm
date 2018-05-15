

data ".data_life"
	global _weights111: long[96] = (	
								0000000000000000fhl,
								000000000000000ffhl,
								00000000000000fffhl,
								0000000000000fff0hl,
								000000000000fff00hl,
								00000000000fff000hl,
								0000000000fff0000hl,
								000000000fff00000hl,
								00000000fff000000hl,
								0000000fff0000000hl,
								000000fff00000000hl,
								00000fff000000000hl,
								0000fff0000000000hl,
								000fff00000000000hl,
								00fff000000000000hl,
								0fff0000000000000hl,
								0ff00000000000000hl,
								0f000000000000000hl,
								0hl dup 14,
								
								0hl dup 16,
								0000000000000000fhl,
								000000000000000ffhl,
								00000000000000fffhl,
								0000000000000fff0hl,
								000000000000fff00hl,
								00000000000fff000hl,
								0000000000fff0000hl,
								000000000fff00000hl,
								00000000fff000000hl,
								0000000fff0000000hl,
								000000fff00000000hl,
								00000fff000000000hl,
								0000fff0000000000hl,
								000fff00000000000hl,
								00fff000000000000hl,
								0fff0000000000000hl,
								
								0ff00000000000000hl,
								0f000000000000000hl,
								0hl dup 30
								);
end ".data_life";

macro  filter_2s4s_tail (N)
	rep N data,ram	 = [ar0++],wtw 	with vsum, data, 0;	
	rep 32 wfifo = [ar4++],ftw;								//3 to shadow
	rep N [ar6++gr6] = afifo,wtw 	with vsum, ram, 0;
	vnul;
	delayed goto End_tail;
		rep N data = [ar1++] 		with vsum,data,afifo;
		rep N [ar5++gr5] = afifo;
end filter_2s4s_tail;


global _filter3h_2s4s:label;
begin ".text_life"
<_filter3h_2s4s>
.branch;
	ar5 = sp - 2;	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;
	ar0 = [--ar5]	with gr6=false;	//Source
	ar6 = [--ar5]	with gr6++;		//Result
	gr3 = [--ar5]	with gr6<<=2;	//size	gr6=4;
	ar1=ar0			with  gr5=gr6;	//gr5=4;
	ar5=ar6;
	ar1+=2;
	ar5+=2;
	
	nb1=88888888h	with gr3>>=5;				//size/32 elements in vector
	sb=0AAAAAAAAh 	with gr4 = gr3 >> 5;		//
//	wtw;
	if =0 delayed goto tail_filter_2s4s;
		ar3 = _weights111;
		
	ar4=ar3  	with gr4--;
	rep 32 wfifo = [ar4++],ftw,wtw;	//1
	rep 32 wfifo = [ar4++],ftw;		//2 in shadow
	
	<Next32>
		rep 32 data,ram =  [ar0++],wtw 		with vsum, data, 0;	
		rep 32 wfifo = [ar4++],ftw;					//3 to wfifo
		rep 32 [ar6++gr6] = afifo,wtw 		with vsum, ram, 0;
		ar4=ar3;
		rep 32 wfifo = [ar4++],ftw;					//1
		rep 32 data = [ar1++],wtw	 		with vsum,data,afifo;
		if > delayed goto Next32 with gr4--;
			rep 32 wfifo = [ar4++],ftw;
			rep 32 [ar5++gr5] = afifo;
<tail_filter_2s4s>
	Tail: label;
	ar2=Tail	with	gr4 = gr3 >> 5;
	gr4 <<= 5;
	gr2= gr3-gr4;
	ar4=ar3		with gr2<<=3;
	ar2+=gr2;	
	delayed goto ar2;
		rep 32 wfifo = [ar4++],ftw,wtw;	//1
		rep 32 wfifo = [ar4++],ftw;		//2 in shadow
		nul;
<Tail>
	delayed goto End_tail;
		wtw;
		nul;
	nul;nul;nul;nul;
	filter_2s4s_tail (1);
	filter_2s4s_tail (2);
	filter_2s4s_tail (3);
	filter_2s4s_tail (4);
	filter_2s4s_tail (5);
	filter_2s4s_tail (6);
	filter_2s4s_tail (7);
	filter_2s4s_tail (8);
	filter_2s4s_tail (9);
	filter_2s4s_tail (10);
	filter_2s4s_tail (11);
	filter_2s4s_tail (12);
	filter_2s4s_tail (13);
	filter_2s4s_tail (14);
	filter_2s4s_tail (15);
	filter_2s4s_tail (16);
	filter_2s4s_tail (17);
	filter_2s4s_tail (18);
	filter_2s4s_tail (19);
	filter_2s4s_tail (20);
	filter_2s4s_tail (21);
	filter_2s4s_tail (22);
	filter_2s4s_tail (23);
	filter_2s4s_tail (24);
	filter_2s4s_tail (25);
	filter_2s4s_tail (26);
	filter_2s4s_tail (27);
	filter_2s4s_tail (28);
	filter_2s4s_tail (29);
	filter_2s4s_tail (30);
	filter_2s4s_tail (31);	
<End_tail>	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
.wait;
end ".text_life"; 
