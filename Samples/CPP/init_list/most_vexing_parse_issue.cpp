#include<iostream>


class test
{
private:
		int test_var;

public:

		test(int t):test_var(t)
		{

		}
		
		void print()
		{
			std::cout << "Test_var=" << test_var << std::endl;				
		}
};


class test_2
{
	int i;
	int j;
	
public:
	test_2(int a,int b):i(a),j(b)
	{
		std::cout << "Constructor called \n";				
	}
	
	test_2(const test_2& tmp)
	{
		i = tmp.i;
		i = tmp.j;
		std::cout << "Copy Constructor called \n";				
	}
	
	test_2& operator = (const test_2& tmp)
	{
		i = tmp.i;
		i = tmp.j;
		std::cout << "Operator overlaod called \n";				
	}
	
	~test_2()
	{
		std::cout << "Distructor called \n";				
	}	
	void print()
	{
		std::cout << "i=" << i << "j=" << j << std::endl;				
	}
	
	
};

test_2 test_api_1()
{
	test_2 t(1,2);
	return t;
}

//test_2 test_api_2()
//{
//	return {1,2};	
//}


int main()
{

	//test t();			//No error here becuse compilte will think t is function decalreation wich return test call object 
	
	//------------------------------------------------------------
	// Issue originates from the fact that parenthesis are used as well for function declarations, function calls and initializations.
	// The simplest example is the “explicit call of a default constructor” which is not possible in C++03. 
	// If a call with one argument looks like `C c(22);`, then with zero arguments it should look like `C
	// c();`. However, the compiler parses this as a declaration of a function `c`, returning a `C` and taking no arguments. 
	// We therefore had to rely on an implicit call of the default constructor, writing `C c;`
	// -------------------------------------------------------------
	//t.print(); //Error here please refer above note 
	
	test_2 t1 = test_api_1();
	//test_2 t3 = test_api_2();
	
	return 0;
}
