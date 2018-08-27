void CWinDIPDoc::C3_7_2Laplacian(int mask)
{	
	//high frequency-> bigger difference betwwen values  
	//low frequency -> small difference -> values look like changing slowly, gradually
	//leave only high freq ->only outline is left
	//high freq + original -> make image clear
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	double lapMask[3][3];

	LaplacianMasking(lapMask, mask);
	LaplacianFilteringOperation(m_InputImg, m_OutputImg, lapMask, mask, iSize);

	UpdateAllViews(FALSE); /

						   /*
						   
						   high freq make outline clear but also could emphasize noise too
						   low freq is opposite
						   

						   dy	f(x+dx)-f(x)
						   --- = ---------------
						   dx	   dx

						   image is two dimention souse r instead of d
						  
						   */
}

void CWinDIPDoc::LaplacianMasking(double lapMask[][3], int mask)
{	
	lapMask[0][0] = 0; lapMask[0][1] = 1; lapMask[0][2] = 0;
	lapMask[1][0] = 1; lapMask[1][1] = -4; lapMask[1][2] = 1;
	lapMask[2][0] = 0; lapMask[2][1] = 1; lapMask2][2] = 0;

	//since values around the center is low, the center looks brighter

}

void CWinDIPDoc::LaplacianFilteringOperation(BYTE *input, BYTE *output, double lapMask[][3], int mask,
	CSize iSize)
{
	int x, y, wHalfSize, address;
	ColorRGB pixel;

	wHalfSize = mask / 2;

	for (y = wHalfSize; y < iSize.cy - wHalfSize; y++)
	{
		for (x = wHalfSize; x < iSize.cx - wHalfSize; x++)
		{
			LaplacianMaskOperation(x, y, input, iSize, mask, maskSum, maskSize, lapMask);

			address = BmpAddress(x, y, iSize);

			*(output + address) = pixel.b;
			*(output + address + 1) = pixel.g;
			*(output + address + 2) = pixel.r;
		}
	}

}

void CWinDIPDoc::LaplacianMaskOperation(int x, int y, BYTE *input, CSize iSize, double lapMask[][3],
	int mask, ColorRGB *pixel)
{
	int wx, wy, address;
	double bgrSum[3] = { 0, 0, 0 };
	int b, g, r, maskX = 0, maskY = 0;
	int scale = 3;

	int wx, wy, address;
	double bSum = 0;
	int b, g, r, maskX = 0, maskY = 0;
	int scale = 1;

	for (wy = -1; wy <= 1; wy++)
	{
		maskX = 0;
		for (wx = -1; wx <= 1; wx++)
		{
			address = BmpAddress(x + wx, y + wy, iSize);

			b = *(input + address);

			bSum += lapMask[maskY][maskX] * b;
			maskX++;
		}
		maskY++;
	}


	if (bSum > 255) pixel->b = 255;
	else if (bSum < 0)  pixel->b = 0;
	else pixel->b = (BYTE)bSum;
	pixel->g = pixel->b;
	pixel->r = pixel->b;


	/*
	// make it between -128~127 
	for( int bgr = 0; bgr<3; bgr++ )
	{
	bgrSum[bgr] = bgrSum[bgr] * scale;

	if( bgrSum[bgr] > 127 ) bgrSum[bgr] = 127;
	if( bgrSum[bgr] < -128 ) bgrSum[bgr] = -128;
	}

	//make it betwen 0~255 
	pixel->b = (BYTE)( bgrSum[0] + 128 );
	pixel->g = (BYTE)( bgrSum[1] + 128 );
	pixel->r = (BYTE)( bgrSum[2] + 128 );
	*/

}
