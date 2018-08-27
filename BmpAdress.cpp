int CWinDIPDoc::BmpAddress(int x, int y, CSize iSize)
{ //when image is saved on memory, it goes upside down 
  //considering that fact, this function gets the address

	address = ((iSize.cy - 1 - y) * iSize.cx + x) * 3;

	return address;
}