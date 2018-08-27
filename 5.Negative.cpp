void CWinDIPDoc::C3_2_1Negative()
{
	int wx, wy, address;

	int x, y, i;

	int b, g, r; //unsigned char���� int�� �����ص� �����ϴ�.

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
			r = *(m_InputImg + address + 2); //input image�� rgb���� ���ʴ�� �����´�.

			*(m_OutputImg + address) = 255 - b;
			*(m_OutputImg + address + 1) = 255 - g;
			*(m_OutputImg + address + 2) = 255 - r; //output image



													// bgr ���� 2�� ������ ������ 256���� 128������ �ٲپ� ��Ӱ��ϱ� ���ؼ��̴�.
		}
	}


	UpdateAllViews(FALSE); //ȭ������� ����.
}
int CWinDIPDoc::BmpAddress(int x, int y, CSize iSize)
{ //when image is saved on memory, it goes upside down 
  //considering that fact, this function gets the address

	address = ((iSize.cy - 1 - y) * iSize.cx + x) * 3;

	return address;
}

