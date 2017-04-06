// Addition that saturates to TMin or TMax */

int saturating_add(int x, int y)
{
	int w = sizeof(int)<<3;
	int signx = x >> w & 0x01;
	int signy = y >> w & 0x01;
	int sum = x + y;
	int signsum = sum >> w & 0x01;
	int samesign = ~(signx ^ signy); //is 1 if overflow can occur	
	int overflowed = (signsum ^ signx) && samesign;
	//overflowed is 1 if overflow occured, 0 if not
	
	return overflowed;
}

int main()
{
return 0;
}
