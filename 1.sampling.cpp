void CWinDIPDoc::C2_4_1Sampling(int blockSize)
{
	int	  x, y, i;
	ColorRGB mean;
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;

	//Initializing
	for (i = 0; i < iSize.cx * iSize.cy * 3; i++)
		*(m_OutputImg + i) = 255;

	for (y = 0; y < iSize.cy - blockSize; y = y + blockSize)
	{
		for (x = 0; x < iSize.cx - blockSize; x = x + blockSize)
		{
			GetMean(m_InputImg, blockSize, x, y, iSize, &mean);
			PutMean(m_OutputImg, blockSize, x, y, iSize, mean);
		}
	}

	UpdateAllViews(FALSE); //renew output of display
						 
}

void CWinDIPDoc::GetMean(BYTE *inputImage, int blockSize, int x, int y, CSize iSize, ColorRGB *mean)
{
	
	int b, g, r, wx, wy;
	int totalB, totalG, totalR;
	int address;
	int blockSizeSquare;

	totalB = 0, totalG = 0, totalR = 0;

	blockSizeSquare = blockSize * blockSize;

	for (wy = 0; wy < blockSize; wy++)
	{
		for (wx = 0; wx < blockSize; wx++)
		{
			address = BmpAddress(x + wx, y + wy, iSize);

			b = *(inputImage + address);
			g = *(inputImage + address + 1);
			r = *(inputImage + address + 2);

			totalB += b;
			totalG += g;
			totalR += r;
		}
	}
	//0.5 is for rounding off to the nearest interger
	mean->b = (unsigned char)((double)totalB / (double)blockSizeSquare + 0.5);
	mean->g = (unsigned char)((double)totalG / (double)blockSizeSquare + 0.5);
	mean->r = (unsigned char)((double)totalR / (double)blockSizeSquare + 0.5);
}

int CWinDIPDoc::BmpAddress(int x, int y, CSize iSize)
{ //when image is saved on memory, it goes upside down 
	//considering that fact, this function gets the address

	address = ((iSize.cy - 1 - y) * iSize.cx + x) * 3;

	return address;
}

void CWinDIPDoc::PutMean(BYTE *outputImage, int blockSize, int x, int y, CSize iSize, ColorRGB mean)
{
	//output in blocksize
	int wx, wy, address;

	for (wy = 0; wy < blockSize; wy++)
	{
		for (wx = 0; wx < blockSize; wx++)
		{
			address = BmpAddress(x + wx, y + wy, iSize);

			*(outputImage + address) = mean.b;
			*(outputImage + address + 1) = mean.g;
			*(outputImage + address + 2) = mean.r;
		}
	}
}
