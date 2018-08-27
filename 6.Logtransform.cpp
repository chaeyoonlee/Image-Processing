void CWinDIPDoc::C3_2_2Logtransform()
{
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	int x, y, b, g, r, address;

	double c = 255 / log(1. + 255.); //initializing

	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			b = *(m_InputImg + address);
			g = *(m_InputImg + address + 1);
			r = *(m_InputImg + address + 2);

			//do log
			*(m_OutputImg + address) = (BYTE)(c * log(1. + (double)b));
			*(m_OutputImg + address + 1) = (BYTE)(c * log(1. + (double)g));
			*(m_OutputImg + address + 2) = (BYTE)(c * log(1. + (double)r));
		}
	}
	UpdateAllViews(FALSE); 
}

