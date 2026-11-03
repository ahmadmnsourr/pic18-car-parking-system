// IncBcd(f): 4 Tcy, DecBcd(f): 5 Tcy, IncBcdE(f): 10 Tcy, DecBcdE(f): 13 Tcy (w/o call/ret)

#define IncBcd(f)	{_asm movlb f	incf 	f,0,1	daw 	movwf 	f,1  _endasm}
#define DecBcd(f)	{_asm movlb f 	movlw 	0x99 	addwf 	f,0,1 	daw  movwf f,1 _endasm}

#define IncBcdE(f)	{IncBcd(f) _asm  tstfsz	 f,1   bra 4  _endasm  IncBcd(f+1)}
#define DecBcdE(f)	{DecBcd(f) _asm  movlw	 0x99  subwf  f,0,1	   bnz 5 _endasm DecBcd(f+1)}

void Bin2Bcd(unsigned char N, char *a)			// max of 423 cycles
{
	a[2] = N % 10;					// least significant digit
	N = N / 10;
	a[1] = N % 10;					// middle significant digit
	a[0] = N / 10;					// most significant digit
}

void Bin2BcdE(unsigned int N, char *a)			// max of 2160 cycles
{
	unsigned char i;

	for (i = 0; i < 4; i++)
	{
		a[4-i] = N % 10;			// rem of division by 10
		N = N / 10;
	}
	a[0] = N;
}

void Bcd2Bin(char *a, unsigned int *reg)  		// Convert 3-byte BCD array to binary
{
	*reg = (int) a[0] * 100 + a[1] * 10 + a[2];
}

void Bcd2BinE(char *a, unsigned int *reg)  		// Convert 4-byte BCD array to binary
{
	*reg = (int) a[0] * 1000 + a[1] * 100 + a[2] * 10 + a[3];
}

void BcdInc(unsigned char *reg)
{
	*reg = (*reg / 16) * 10 + (*reg % 16);          // packed BCD to binary
	*reg = *reg != 99? *reg + 1: 0;			// add 1 to reg
	*reg = (*reg / 10) * 16 + (*reg % 10);          // binary to packed BCD
}

void BcdDec(unsigned char *reg)
{
	*reg = (*reg / 16) * 10 + (*reg % 16);          // packed BCD to binary
	*reg = *reg != 0? *reg - 1: 99;			// sub 1 to reg
	*reg = (*reg / 10) * 16 + (*reg % 10);          // binary to packed BCD
}

void BcdAdd(unsigned char *reg, unsigned char val)
{
	*reg = (*reg / 16) * 10 + (*reg % 16);          // packed BCD to binary
	*reg += val;					// binary add val to reg
	*reg = (*reg / 10) * 16 + (*reg % 10);          // binary to packed BCD
}

