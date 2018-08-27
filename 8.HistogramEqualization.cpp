void CWinDIPDoc::C3_3_1HistogramEqualization()
{	//get probability using the graph
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	IntRGB numPixel[256], mTable[256];
	Prob prob[256];
	/*
	ColorFrequencyCounting( m_InputImg, numPixel, iSize ); 
	ColorProbability( numPixel, prob, iSize ); 
	ColorInterval( prob );
	ColorMappingTable( prob, mTable );
	ColorMapping( m_InputImg, m_OutputImg, mTable, iSize );
	*/

	int wx, wy, address;

	int x, y, i;

	int b, g, r; 
	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			b = *(m_InputImg + address);
			g = *(m_InputImg + address + 1);
			r = *(m_InputImg + address + 2); 


			if (b <= 150) { b -= 110; g -= 110; r -= 110; }
			else if (b <= 170) { b -= 125; g -= 125; r -= 125; }
			else if (b <= 180) { b -= 100; g -= 100; r -= 100; }
			else if (b <= 190) { b -= 80; g -= 80; r -= 80; }
			else if (b <= 200) { b -= 60; g -= 60; r -= 60; }
			else if (b <= 210) { b -= 40; g -= 40; r -= 40; }
			else if (b <= 220) { b -= 30; g -= 30; r -= 30; }
			else if (b <= 230) { b -= 20; g -= 20; r -= 20; }
			else if (b <= 255) { b -= 10; g -= 10; r -= 10; }

			*(m_OutputImg + address) = b;				//	/ level * level;
			*(m_OutputImg + address + 1) = g;			//	/ level * level;
			*(m_OutputImg + address + 2) = r;			//	/ level * level; //output image
		}

	}



	UpdateAllViews(FALSE); 
}

void CWinDIPDoc::ColorFrequencyCounting(BYTE *input, IntRGB numPixel[], CSize iSize)
{
	int x, y, b, g, r, gray;
	int	address;
	
	for (gray = 0; gray < 256; gray++)
	{//ini
		numPixel[gray].b = 0;
		numPixel[gray].g = 0;
		numPixel[gray].r = 0;
	}

	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			b = *(input + address);
			g = *(input + address + 1);
			r = *(input + address + 2);

			numPixel[b].b += 1;
			numPixel[g].g += 1;
			numPixel[r].r += 1;
		}
	}
}

void CWinDIPDoc::ColorProbability(IntRGB numPixel[], Prob prob[], CSize iSize)
{
	int gray;
	double size;

	size = iSize.cx * iSize.cy;

	for (gray = 0; gray < 256; gray++)
	{
		prob[gray].b = (double)numPixel[gray].b / size;
		prob[gray].g = (double)numPixel[gray].g / size;
		prob[gray].r = (double)numPixel[gray].r / size;
	}
}

void CWinDIPDoc::ColorInterval(Prob prob[])
{//put percentage of how many bgrs each of 0~255 has
	int gray;

	for (gray = 0; gray < 256; gray++)
	{
		prob[gray].b *= 255.0;
		prob[gray].g *= 255.0;
		prob[gray].r *= 255.0;
	}
}

void CWinDIPDoc::ColorMappingTable(Prob prob[], IntRGB mTable[])
{
 //0 -> 0
 //1 -> 0+1
 //2 -> 0+1+2
 //the last one will be 255
 //if the brightest one is 50, mtable's 50th wil be 255(the table is form 0 to 50, thre's no valuse for the others)
 //=>>> overall num(value) will be increased, so that image will be brighter and the difference between pixel will be outstanding.
	int     gray;
	double	sumR, sumG, sumB;

	sumB = 0.0;
	sumG = 0.0;
	sumR = 0.0;

	for (gray = 0; gray < 256; gray++)
	{
		sumB += prob[gray].b;
		sumG += prob[gray].g;
		sumR += prob[gray].r;

		mTable[gray].b = (unsigned char)sumB;
		mTable[gray].g = (unsigned char)sumG;
		mTable[gray].r = (unsigned char)sumR;
	}
}

void CWinDIPDoc::ColorMapping(BYTE *input, BYTE *output, IntRGB mTable[], CSize iSize)
{//ouput
	int x, y, b, g, r, address;

	for (y = 0; y < iSize.cy; y++)
	{
		for (x = 0; x < iSize.cx; x++)
		{
			address = BmpAddress(x, y, iSize);

			b = *(input + address);
			g = *(input + address + 1);
			r = *(input + address + 2);

			*(output + address) = mTable[b].b;
			*(output + address + 1) = mTable[g].g;
			*(output + address + 2) = mTable[r].r;
		}
	}
}
