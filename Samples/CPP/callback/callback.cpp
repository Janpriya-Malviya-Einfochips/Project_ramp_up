#include<iostream>
#include<functional>
#include<string>

using namespace std;



class test
{

public:
	
	void print(const std::string& name , unsigned int age)
	{
		cout << "Name : " << name << "\n";
		cout << "Age  : " << age  << "\n";
	}
};

int main()
{
	test t;
	
	{
		cout << "Test Callback with fixed values \n";
		auto f = std::bind( &test::print, t, "Callback_1", 1 );
		f();
	}
	{
		cout << "Test Callback One fixed value \n";
		auto f = std::bind( &test::print, t, "Callback_2", std::placeholders::_1 );
		f(2);
	}
	{
		cout << "Test Callback with Variable values \n";
		auto f = std::bind( &test::print, t, std::placeholders::_1, std::placeholders::_2 );
		f("JanpriyaMalviya",3);
		f("MalviyaJanpriya",4);
	}
	{
		cout << "Test Callback with swap placeholder \n";
		auto f = std::bind( &test::print, t, std::placeholders::_2, std::placeholders::_1 );
		f(5,"JollyMalviya",3);
		f(6,"MalviyaJolly",4);
	}	
	
	return 0;
}
