/* Return 1 when any odd bit of x equals 1; 0 otherwise. w= 32 */

int any_odd_one(unsigned x)
{
	return (x & 0x55555555) > 0;
}

int main()
{
return 0;
}

