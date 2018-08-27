void CWinDIPDoc::C3_6_1LowpassFiltering(int maskSize)
{	//earasing noise
	
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	int i, **mask, maskSum;

	mask = (int**)malloc(sizeof(int*) * maskSize);

	for (i = 0; i < maskSize; i++)
		*(mask + i) = (int*)malloc(sizeof(int) * maskSize);

	LowPassMask(mask, &maskSum, maskSize);
	FilteringOperation(m_InputImg, m_OutputImg, iSize, mask, maskSum, maskSize);

	free(mask);
	UpdateAllViews(FALSE); 

						   //low pass -> integral
						   //high pass-> differential
}

void CWinDIPDoc::LowPassMask(int **mask, int *maskSum, int maskSize)
{
	int x, y;

	for (y = 0; y < maskSize; y++)
	{
		for (x = 0; x < maskSize; x++)
			mask[x][y] = 1;
	}

	*maskSum = maskSize * maskSize;

	/*
	Gaussian filter

	more clear than lowpass because	of giving weight at ahe center

	mask[0][0] = 1; mask[0][1] = 2;mask[0][2] = 1;
	mask[1][0] = 2; mask[1][1] = 4;mask[1][2] = 2;
	mask[2][0] = 1; mask[2][1] = 2;mask[2][2] = 1;


	*maskSum = 16;
	}
	*/
}

void CWinDIPDoc::FilteringOperation(BYTE *input, BYTE *output, CSize iSize, int **mask, int maskSum,
	int maskSize)
{
	int x, y, wHalfSize, address;
	ColorRGB pixel;

	wHalfSize = maskSize / 2;

	for (y = wHalfSize; y < iSize.cy - wHalfSize; y++)
	{
		for (x = wHalfSize; x < iSize.cx - wHalfSize; x++)
		{
			MaskOperation(x, y, input, iSize, mask, maskSum, maskSize, &pixel);

			address = BmpAddress(x, y, iSize);

			*(output + address) = pixel.b;
			*(output + address + 1) = pixel.g;
			*(output + address + 2) = pixel.r;
		}
	}
}

void CWinDIPDoc::MaskOperation(int x, int y, BYTE *input, CSize iSize, int **mask, int maskSum,
	int maskSize, ColorRGB *pixel)
{
	int wx, wy, wHalfSize, address, bSum = 0, gSum = 0, rSum = 0;
	int b, g, r, maskX = 0, maskY = 0;

	wHalfSize = maskSize / 2;
	maskSum = maskSize * maskSize;

	for (wy = -wHalfSize; wy <= wHalfSize; wy++)//left is - right is +
	{
		maskX = 0;
		for (wx = -wHalfSize; wx <= wHalfSize; wx++)
		{
			address = BmpAddress(x + wx, y + wy, iSize);

			b = *(input + address);
			g = *(input + address + 1);
			r = *(input + address + 2);

			bSum += mask[maskX][maskY] * b;
			gSum += mask[maskX][maskY] * g;
			rSum += mask[maskX][maskY] * r;

			maskX++;
		}
		maskY++;
	}

	pixel->b = bSum / maskSum;
	pixel->g = gSum / maskSum;
	pixel->r = rSum / maskSum;
}
