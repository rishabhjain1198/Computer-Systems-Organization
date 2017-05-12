float u2f(unsigned in)
{
	return *((float*)&in);
}

float fpwr4(int x)
{
	unsigned exp, frac;
	unsigned u;

	if(x < -74)
	{
		exp = 0;
		frac = 0;
	}
	
	else if(x < -63)
	{
		exp = 0;
		frac = 1<<(x+74);
	}
	
	else if(x < 64)
	{
		frac = 0;
		exp = x + 63;
	}
	
	else
	{
		exp = 255;
		frac = 0;
	}
	
	u = exp << 23 | frac;
	return u2f(u);
}
