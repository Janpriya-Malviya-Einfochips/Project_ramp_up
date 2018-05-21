#include<iostream>
#include<functional>
#include<string>

#if 0	
//Empty class struct
template<class... T> 
struct tuple 
{
	tuple()
	{
		 std::cout <<"Fixed class construction    "<< __PRETTY_FUNCTION__ << "\n";
	}
};

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...>	// struct tuple<T, Ts...> Inherited from struct tuple<Ts...>
{
	//tuple construction
	tuple(T t, Ts... ts) : tuple<Ts...>(ts...),tail(t)
	{
		 std::cout <<"Varodic class construction    "<< __PRETTY_FUNCTION__ << "\n";
	}
	T tail;
};


template <class T, class... Ts>
struct elem_type_holder<0, tuple<T, Ts...>> 
{
	elem_type_holder()
	{
		 std::cout <<"Fixed class construction    "<< __PRETTY_FUNCTION__ << "\n";
	}
  typedef T type;
};

template <size_t k, class T, class... Ts>
struct elem_type_holder<k, tuple<T, Ts...>> 
{
	typedef typename elem_type_holder<k - 1, tuple<Ts...>>::type type;
	
	
};
#endif
#if 0
template<typename T, typename ... TArgs>
T* create(TArgs ... args)
{
    std::cout << "Creating " << typeid(T).name() << std::endl;
    T* obj = new T(args ...);
    return obj;
}

class A
{
public:
    A(int x, double y = 42.3){}    // (1)
    A(){ std::cout << "Creating A" << __PRETTY_FUNCTION__ << "\n";}                          // (2)
};

class B
{
public:
    B(const std::string& s){}      // (3)
    B() {std::cout << "Creating B" << __PRETTY_FUNCTION__ << "\n";}
};

template<typename ... Mixins>
class X : public Mixins...
{
public:
    X(const Mixins&... mixins) : Mixins(mixins)... {}
};

int main()
{
	//tuple<double, uint64_t, const char*> t1(12.2, 42, "big");
	//A* a1 = create<A>();              // Calls (2)
	//A* a2 = create<A>(16, 9.4);       // Calls (1)
	//A* a3 = create<A>(23);            // Calls (1)
	//A* a4 = create<A>("Hi mum!");     // Error

	//B* b1 = create<B>("Hi mum!");     // Calls (3)
	//B* b2 = create<B>(std::string()); // Calls (3)
	//B* b3 = create<B>();              // Error
	
	
	A a;
	B b;
	X<A,B> xab(a,b);
	return 0;
	
}
#endif


//template<typename... Ps> class CallbackUnwrapper;

template <typename... Ps>
class Callback
{
    typedef std::function<void( const Ps&... )> FunctionType;
public:
    Callback()
    {
		std::cout << "Empty Construction called " << __PRETTY_FUNCTION__ << "\n";
	}
	
    template<typename F> 
    Callback( const F& _f ) : m_f( _f ) 
    {
		std::cout << "Construction with args called  Typeid= " << typeid(F).name() << __PRETTY_FUNCTION__ << "\n";
	}
	
    void operator()( const Ps&... ps ) const
    {
        Send( ps... );
    }

    void Send( const Ps&... ps ) const
    {
		std::cout << "Init to send  \n";
        if( m_f )
        {
			std::cout << "Function called \n";
            m_f( ps... );
        }
    }

    //void Clear()
    //{
    //    m_f = FunctionType();
    //}
    //bool Empty() const
    //{
    //   return !m_f;
    //}
private:
    FunctionType m_f;
    //friend class CallbackUnwrapper<Ps...>;
    //friend class CallbackUnwrapper<void>;
};

#if 0	
template<>
class Callback<void> : public Callback<>
{
    typedef std::function<void ()> FunctionType;
public:
    Callback() {}
    template<class F> Callback( const F& _f )
        : Callback<>( _f )
    {
    }
};
#endif

void call_test1(int i,int j)
{
	std::cout << "Init i=> " << i << "J=" << j << "\n";
}

void call_test2(int i,int j,int k)
{
	std::cout << "Init i=> " << i << "J=" << j << "K=" << k << "\n";
}

//void call_mycallback(std::function<> cb)
//{
//	cb();
//}
	
int main()
{
	auto f = Callback<int,int>(call_test1);
	f(10,5);
	auto g = Callback<int,int,int>(call_test2);
	g(10,5,6);
	
	auto h = &call_test1;
	h(20,5);
	
	return 0;
}
	
	
	
	
