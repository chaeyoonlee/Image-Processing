void CWinDIPDoc::C3_2_4BitPlaneSlicing(int planeNum)
{ 
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	int x, y, gray, address;

	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			gray = *(m_InputImg + address);//just only get B since I will make all the color's grey by making all the color same
										   
			*(m_OutputImg + address) = BitSlicing(gray, planeNum);
			*(m_OutputImg + address + 1) = BitSlicing(gray, planeNum);
			*(m_OutputImg + address + 2) = BitSlicing(gray, planeNum);
		}
	}
	UpdateAllViews(FALSE); .
}

//gray :
//planeNum :
int CWinDIPDoc::BitSlicing(int gray, int planeNum)
{/*
 one pixel is 7~0, 8 bits. planebum is the position of bits
 
 */
	int mask;
	mask = pow(2, planeNum);//make bitmask in order to know it's 0 or 1
	if (gray && mask) {
		return 255;
	}
	else return 0;

	return 0;
}
