void CWinDIPDoc::C2_4_1Quantization(int level)
{
	int wx, wy, address;

	int x, y, i;

	int b, g, r; //originally it's unsigned char but int is okay

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
			r = *(m_InputImg + address + 2); //get rgb from image
											 
			if (level == 128) {//hightest level

				if (g >= 128) g = 255;
				else		  g = 0;
				if (b >= 128) b = 255;
				else		  b = 0;
				if (r >= 128) r = 255;
				else		  r = 0;

				// bgr :  0~127 / 128 => 0  ,  128~255 / 128 => 1    0,1 * 128 => 0,128   ==> 0, 255
				*(m_OutputImg + address) = b;				//	/ level * level;
				*(m_OutputImg + address + 1) = g;			//	/ level * level;
				*(m_OutputImg + address + 2) = r;			//	/ level * level; //output image

			
			/* plusing levle/2  is for rounding off 
				when level==4, 0->1  2,3 ->4
				through this, image gets less darker but it makes holes on image due to overflow(>255) for rounding off
				the higher level is, the worse this phenomenon gets
			*/

			}
			else {

				if ((b + level / 2) / level * level >= 255) {//overflow
					*(m_OutputImg + address) = 255;
					*(m_OutputImg + address + 1) = 255;
					*(m_OutputImg + address + 2) = 255;
				}
				else
				{//256 dividing 2 makes image darker
					*(m_OutputImg + address) = (b + level / 2) / level * level; //dividing and then multilying make te number smaller due to rounding off -> the higher level is the more number is cut -> smaller lever gets brighter
					*(m_OutputImg + address + 1) = (g + level / 2) / level * level;
					*(m_OutputImg + address + 2) = (r + level / 2) / level * level; //output image
				}
			}



			// bgr 값을 2로 나누는 이유는 256값을 128값으로 바꾸어 어둡게하기 위해서이다.
		}
	}

	UpdateAllViews(FALSE); 

						  


}
int CWinDIPDoc::BmpAddress(int x, int y, CSize iSize)
{ //when image is saved on memory, it goes upside down 
  //considering that fact, this function gets the address

	address = ((iSize.cy - 1 - y) * iSize.cx + x) * 3;

	return address;
}
