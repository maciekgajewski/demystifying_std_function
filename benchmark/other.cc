// some stuff is in separate compilation unit, to prevent inlining


int global_counter()
{
	static int c = 0;
	return c++;
}

struct icounter
{
	virtual int count() = 0;
};

struct vcounter : public icounter
{
	int c;
	
	virtual int count() { return c++; }
};

icounter& get_counter()
{
	static vcounter vc;
	return vc;
}