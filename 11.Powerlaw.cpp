void CWinDIPDoc::C3_2_3Powerlaw(int m_Edit)
{
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	int x, y, b, g, r, address;
	double gamma;
	double c;

	gamma = GetGammaValue(m_Edit); /
	c = 255.0 / pow(255.0, gamma); // initialzing the coefficient for PowerLaw calculation 

	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			b = *(m_InputImg + address);
			g = *(m_InputImg + address + 1);
			r = *(m_InputImg + address + 2);

			
			*(m_OutputImg + address) = (BYTE)(c * pow(b, gamma));
			*(m_OutputImg + address + 1) = (BYTE)(c * pow(g, gamma));
			*(m_OutputImg + address + 2) = (BYTE)(c * pow(r, gamma));
		}
	}
	UpdateAllViews(FALSE); 
}

double CWinDIPDoc::GetGammaValue(int value)
{
	double gamma;

	if (value == 0) gamma = 0.04;
	else if (value == 1) gamma = 0.10;
	else if (value == 2) gamma = 0.20;
	else if (value == 3) gamma = 0.40;
	else if (value == 4) gamma = 0.67;
	else if (value == 5) gamma = 1.0;
	else if (value == 6) gamma = 1.5;
	else if (value == 7) gamma = 2.5;
	else if (value == 8) gamma = 5.0;
	else if (value == 9) gamma = 10.0;
	else gamma = 25.0;

	return gamma;
}
