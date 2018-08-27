void CWinDIPDoc::C2_4_5Shrinking(double shrink)
{
	BYTE pixelColor[2][2][3];
	int pixelValue;
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;

	int x, y, i;
	int Xint, Yint;
	int out_height = (int)(iSize.cy * shrink);
	int out_width = (int)(iSize.cx * shrink);

	double Xreal, Yreal;
	double Xdiffer, Ydiffer;

	for (i = 0; i < iSize.cx * iSize.cy * 3; i++)
		*(m_OutputImg + i) = 255;

	if (shrink == 1) {
		for (i = 0; i < iSize.cx * iSize.cy * 3; i++)
			*(m_OutputImg + i) = *(m_InputImg + i);
	}
	else {
		for (y = 0; y < out_height; y++)
			for (x = 0; x < out_width; x++)
			{
				Yreal = y / shrink;
				Xreal = x / shrink;

				Yint = (int)(Yreal);
				Xint = (int)(Xreal);

				Xdiffer = Xreal - Xint;
				Ydiffer = Yreal - Yint;

				GetPixel4(m_InputImg, Xint, Yint, pixelColor, iSize);

				for (int bgr = 0; bgr < 3; bgr++)
				{
					pixelValue = Interpolation(pixelColor, Xdiffer, Ydiffer, bgr);
					PutPixel(m_OutputImg, pixelValue, x, y, bgr, iSize);
				}
			}
	}

	UpdateAllViews(FALSE); 
}
int CWinDIPDoc::Interpolation(BYTE pixelColor[][2][3], double dx, double dy, int bgr)
{
	double pixelValue;

	pixelValue = (1.0 - dx) * (1.0 - dy) * (double)pixelColor[0][0][bgr] +
		dx * (1.0 - dy) * (double)pixelColor[1][0][bgr] +
		(1.0 - dx) *   dy     * (double)pixelColor[0][1][bgr] +
		dx * dy     * (double)pixelColor[1][1][bgr];

	return (int)(pixelValue + 0.5);
}
void CWinDIPDoc::GetPixel4(BYTE *inputImage, int x, int y, BYTE pixelColor[][2][3], CSize iSize)
{
	int address;
	int wx, wy;

	for (wy = 0; wy < 2; wy++)
	{
		for (wx = 0; wx < 2; wx++)
		{
			address = BmpAddress(x + wx, y + wy, iSize);

			pixelColor[wx][wy][0] = *(inputImage + address);
			pixelColor[wx][wy][1] = *(inputImage + address + 1);
			pixelColor[wx][wy][2] = *(inputImage + address + 2);
		}
	}
}
void CWinDIPDoc::PutPixel(BYTE *image, int pixelValue, int x, int y, int bgr, CSize iSize)
{
	int address;

	address = BmpAddress(x, y, iSize);

	*(image + address + bgr) = pixelValue;
}
int CWinDIPDoc::BmpAddress(int x, int y, CSize iSize)
{ //when image is saved on memory, it goes upside down 
  //considering that fact, this function gets the address

	address = ((iSize.cy - 1 - y) * iSize.cx + x) * 3;

	return address;
}


