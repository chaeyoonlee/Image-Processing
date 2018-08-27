void CWinDIPDoc::C3_6_2Median(int maskSize)
{	//non linear filer (<-> lowpass filtering)
	//not average. using median
	//slat and pepper -> valuse has weird difference all of sudden
	CSize iSize;
	iSize.cx = width;
	iSize.cy = height;
	int *maskArray;

	maskArray = (int*)malloc(maskSize * maskSize * sizeof(int)); 

	MedianFilteringOperation(m_InputImg, m_OutputImg, iSize, maskArray, maskSize);

	free(maskArray); 
	UpdateAllViews(FALSE); 
}

void CWinDIPDoc::MedianFilteringOperation(BYTE *input, BYTE *output, CSize iSize, int *maskArray,
	int maskSize)
{
	int x, y, wHalfSize;
	int address;
	int medianValue;
	int maskSum = maskSize * maskSize;

	wHalfSize = maskSize / 2;

	for (y = wHalfSize; y < iSize.cy - wHalfSize; y++) {		// making less exception
		for (x = wHalfSize; x < iSize.cx - wHalfSize; x++) {

			GetMaskArray(x, y, input, iSize, maskArray, maskSize);	

			medianValue = bubbleSort(maskArray, maskSum);	

			address = BmpAddress(x, y, iSize);	

			*(output + address) = medianValue;	
			*(output + address + 1) = medianValue; 
			*(output + address + 2) = medianValue;
		}
	}
}

void CWinDIPDoc::GetMaskArray(int x, int y, BYTE *input, CSize iSize, int *maskArray, int maskSize)
{
	int wx, wy, wHalfSize, address;
	int i = 0;
	wHalfSize = maskSize / 2;

	for (wy = -wHalfSize; wy <= wHalfSize; wy++) {
		for (wx = -wHalfSize; wx <= wHalfSize; wx++, i++) {

			address = BmpAddress(wx + x, wy + y, iSize);

			*(maskArray + i) = *(input + address); // save
		}
	}
}
