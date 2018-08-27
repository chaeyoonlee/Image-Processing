void CWinDIPDoc::C3_2_1Negative()
{
	int wx, wy, address;

	int x, y, i;

	int b, g, r; //unsigned char지만 int로 선언해도 무방하다.

	CSize iSize;

	iSize.cx = width;
	iSize.cy = height;

	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			b = *(m_InputImg + address);
			g = *(m_InputImg + address + 1);
			r = *(m_InputImg + address + 2); //input image에 rgb값을 차례대로 가져온다.

			*(m_OutputImg + address) = 255 - b;
			*(m_OutputImg + address + 1) = 255 - g;
			*(m_OutputImg + address + 2) = 255 - r; //output image



													// bgr 값을 2로 나누는 이유는 256값을 128값으로 바꾸어 어둡게하기 위해서이다.
		}
	}


	UpdateAllViews(FALSE); //화면출력의 갱신.
}
int CWinDIPDoc::BmpAddress(int x, int y, CSize iSize)
{ //when image is saved on memory, it goes upside down 
  //considering that fact, this function gets the address

	address = ((iSize.cy - 1 - y) * iSize.cx + x) * 3;

	return address;
}

