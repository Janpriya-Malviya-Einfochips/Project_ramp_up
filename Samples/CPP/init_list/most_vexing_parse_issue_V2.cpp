

D { int i; float f; };


class C
{
    POD p;
    int iarr[3];
    double d;
public:
    C() : d(3.14)
    {
        p.i=2;
        p.f=22.34;

        for (unsigned i = 0; i < 3; ++i) iarr[i] = i;
    }
};

class D
{
public:
    D(C const&, POD const&) {}
};

int main()
{
    C c;

	//Issue found here . Compiler will thing function call d which takes two agruments as  C and POD and return class D her
	//Solution 1: D d{c{},POD{}}
	//Solution 2: create function in class D which takes two argument as C and POD , return object of class D. after that u can call 
	//			 D d{{},{}}

    D d(C(), POD());	// Issue found here . Compiler will thing function call d which takes two agruments as  C and POD and return class D here.
    int i = int();
    POD p = {i, 6.5};
    POD* pp = new POD();
    pp->i = 4;
    pp->f = 22.1;
    float pf* = new float[2];
    pf[0] = 1.2f;
    pf[1] = 2.3f;
}
