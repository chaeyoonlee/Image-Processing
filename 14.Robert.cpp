void CWinDIPDoc::C3_7_3Robert()
{	//same with the other. just with different mask
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	int scale = 2;

	int x, y, address;
	IntRGB pixel1 = { 0, 0, 0 }, pixel2 = { 0, 0, 0 };
	int robMask1[2][2], robMask2[2][2];

	RobertMasking(robMask1, 1);
	RobertMasking(robMask2, 2);

	for (y = 0; y < iSize.cy - 1; y++) {
		for (x = 0; x < iSize.cx - 1; x++) {

			RobertMaskOperation(x, y, m_InputImg, iSize, robMask1, &pixel1);
			RobertMaskOperation(x, y, m_InputImg, iSize, robMask2, &pixel2);

			address = BmpAddress(x, y, iSize);

			*(m_OutputImg + address) = (BYTE)((pixel1.b + pixel2.b) * scale);
			*(m_OutputImg + address + 1) = (BYTE)((pixel1.g + pixel2.g) * scale);
			*(m_OutputImg + address + 2) = (BYTE)((pixel1.r + pixel2.r) * scale);
		}
	}

	UpdateAllViews(FALSE);
}

void CWinDIPDoc::RobertMasking(int robMask[][2], int mask)
{


	if (mask == 1) {
		robMask[0][0] = -1, robMask[0][1] = 0,
			robMask[1][0] = 0, robMask[1][1] = 1;
	}
	else {
		robMask[0][0] = 0, robMask[0][1] = -1,
			robMask[1][0] = 1, robMask[1][1] = 0;
	}
	/*
	if( mask == 1 ){
	robMask[0][0] = -1, robMask[0][1] = -2,robMask[0][2] = -1,
	robMask[1][0] = 0,  robMask[1][1] = 0, robMask[1][2] = 0,
	robMask[2][0] = 1,  robMask[2][1] = 2, robMask[2][2] = 1;
	}
	else{
	robMask[0][0] = -1, robMask[0][1] = 0,robMask[0][2] = 1,
	robMask[1][0] = -2,  robMask[1][1] = 0, robMask[1][2] = 2,
	robMask[2][0] = -1,  robMask[2][1] = 0, robMask[2][2] = 1;
	}

	*/
}

void CWinDIPDoc::RobertMaskOperation(int x, int y, BYTE *input, CSize iSize, int robMask[][2], IntRGB *pixel)
{
	int wx, wy, address, bgrSum[3] = { 0, 0, 0 };
	int b, g, r, maskX = 0, maskY = 0;

	for (wy = 0; wy <= 1; wy++)
	{
		maskX = 0;
		for (wx = 0; wx <= 1; wx++)
		{
			address = BmpAddress(x + wx, y + wy, iSize);

			b = *(input + address);
			g = *(input + address + 1);
			r = *(input + address + 2);

			bgrSum[0] += robMask[maskX][maskY] * b;
			bgrSum[1] += robMask[maskX][maskY] * g;
			bgrSum[2] += robMask[maskX][maskY] * r;

			maskX++;
		}
		maskY++;
	}
	//absolute value
	pixel->b = abs(bgrSum[0]);
	pixel->g = abs(bgrSum[1]);
	pixel->r = abs(bgrSum[2]);
}
