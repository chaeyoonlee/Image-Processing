void CWinDIPDoc::C2_4_5Zooming_Bilinear(int scale)
{
	BYTE pixelColor[2][2][3];
	double dx, dy;
	int outY, outX;
	int y, x;
	int rY, rX;
	int bgr;
	int pixelValue;
	CSize inSize, outSize;
	inSize.cx = width;
	inSize.cy = height;

	for (y = 0; y < (inSize.cy - 1) / scale; y++)
	{
		for (x = 0; x < (inSize.cx - 1) / scale; x++)
		{
			GetPixel4(m_InputImg, x, y, pixelColor, inSize);

			outY = y * scale;
			for (rY = 0; rY < scale; rY++, outY++)
			{
				outX = x * scale;
				for (rX = 0; rX < scale; rX++, outX++)
				{
					dx = (double)rX / (double)scale;
					dy = (double)rY / (double)scale;

					for (bgr = 0; bgr < 3; bgr++)
					{
						pixelValue = Interpolation(pixelColor, dx, dy, bgr);
						if (outX < inSize.cx - 1 && outY < inSize.cy - 1)
							PutPixel(m_OutputImg, pixelValue, outX, outY, bgr, inSize);
					}
				}
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
