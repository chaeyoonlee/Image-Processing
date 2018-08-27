void CWinDIPDoc::C3_7_3Sobel()
{
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;

	int x, y, address;
	IntRGB pixel1 = { 0, 0, 0 }, pixel2 = { 0, 0, 0 };
	int sobelMask1[3][3], sobelMask2[3][3];

	SobelMasking(sobelMask1, 1);
	SobelMasking(sobelMask2, 2);

	for (y = 1; y < iSize.cy - 1; y++) {
		for (x = 1; x < iSize.cx - 1; x++) {

			SobelMaskOperation(x, y, m_InputImg, iSize, sobelMask1, &pixel1);
			SobelMaskOperation(x, y, m_InputImg, iSize, sobelMask2, &pixel2);

			address = BmpAddress(x, y, iSize);

			*(m_OutputImg + address) = (BYTE)((pixel1.b + pixel2.b));
			*(m_OutputImg + address + 1) = (BYTE)((pixel1.g + pixel2.g));
			*(m_OutputImg + address + 2) = (BYTE)((pixel1.r + pixel2.r));
		}
	}

	UpdateAllViews(FALSE); 
}

void CWinDIPDoc::SobelMasking(int sobelMask[][3], int mask)
{

}

void CWinDIPDoc::SobelMaskOperation(int x, int y, BYTE *input, CSize iSize, int sobelMask[][3], IntRGB *pixel)
{
	int wx, wy, address, bgrSum[3] = { 0, 0, 0 };
	int b, g, r, maskX = 0, maskY = 0;


}
