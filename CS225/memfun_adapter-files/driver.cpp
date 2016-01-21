#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdio> //sscanf

#include "memfun.adapter.h"

class A {
	int i;
	public:
		A(int _i) : i(_i) {}
		const int& Get() const { return i; }
        int Power( unsigned exp ) {
            int res = 1;
            for ( unsigned p=0; p<exp; ++p ) res *= i;
            return res;
        }
};

////////////////////////////////////////////////////////////////////////////////
void test0 () {
    MFA_1arg< int, A, unsigned> mfp1( &A::Power );
    A a(2);
    std::cout << mfp1( a, 10 ) << std::endl; //2^10 = 1024
}

////////////////////////////////////////////////////////////////////////////////
void test1 () {
    A a(2);
    std::cout << mfp_1arg( &A::Power )( a,9 ) << std::endl; //2^9 = 512
    //          call helper function | operator() on the mfp_1arg object 
}

////////////////////////////////////////////////////////////////////////////////
class C {
	int i;
	public:
		C( int _i ) : i(_i)          {}
		A Multiply(const int& arg2)  { return A(i*arg2); }
		const int& Get() const       { return i; }
};
void test2 () {
	std::vector<C> v;
	for (int i=0;i<10; ++i) v.push_back( C(i) );
	std::vector<C>::const_iterator it=v.begin(), it_end=v.end();
	for ( ; it!=it_end; ++it) { std::cout << "C(" << it->Get() << ") "; }
	std::cout << std::endl;

	//second input range for transform
	std::list<int> list;
	for (int i=0;i<10; ++i) list.push_back( 10-i );
	//output range for transform (filled with garbage)
	std::vector<A> out;
	for (int i=0;i<10; ++i) out.push_back( A(0) );

	//=====================================
	std::transform( 
			v.begin(), v.end(), list.begin(), out.begin(), mfp_1arg( &C::Multiply ) );

	for ( std::vector<A>::const_iterator itA=out.begin(); itA!=out.end(); ++itA) { 
		std::cout << "A(" << itA->Get() << ") "; 
	}
	std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
void (*pTests[])() = { test0,test1,test2 };

////////////////////////////////////////////////////////////////////////////////
int main (int argc, char ** argv) {
	if (argc >1) {
		int test = 0;
		std::sscanf(argv[1],"%i",&test);
		try {
            pTests[test]();
		} catch( const char* msg) {
			std::cerr << msg << std::endl;
		}
	}
	return 0;
}
