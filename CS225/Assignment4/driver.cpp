#include "statistics.h"
#include <iostream>
#include <fstream> //ifstream
#include <functional> //bind2nd

void test0() {
    short a[] = {1,2,2,3,3,3,5,5};
    Statistics stat1( a, a + sizeof(a)/sizeof(*a) );
    std::cout << "Data: " << stat1 << std::endl;
    std::cout << "Average: " << stat1.Average() << std::endl;
    std::cout << "Deviation: " << stat1.Deviation() << std::endl;
}
void test1() {
    short a[] = {1,2,2,3,3,3,5,5};
    Statistics stat1( a, a + sizeof(a)/sizeof(*a) );
    stat1.RemoveIf( std::bind2nd( std::greater<int>(), 3) );
    std::cout << "Data: " << stat1 << std::endl;
    std::cout << "Average: " << stat1.Average() << std::endl;
    std::cout << "Deviation: " << stat1.Deviation() << std::endl;
}

struct PrintMultiplicity {
    void operator() ( std::pair<int,int> const& p ) const {
        std::cout << "Value " << p.first << " occures " << p.second << " times\n";
    }
};
void test2() {
      
    /*Statistics mytest;
  
    for(int i = 0; i < 10000000; i++)
      mytest.data.push_back(rand() % 100 + 1);*/
    
    Statistics stat2;
    std::ifstream file( "data2" );
    file >> stat2;
    file.close();
    std::cout << stat2.Average() << std::endl;
    std::cout << stat2.Deviation() << std::endl;
    std::cout << "Multiples:\n";
    std::map<int,int> counts = stat2.OccuresMoreThan(3);
    std::for_each( counts.begin(), counts.end(), PrintMultiplicity() );
}

//prints content of the bin, since wewant enumerate bins - add state (counter)
struct PrintBin {
    int counter;
    PrintBin() : counter(0) {}
    void operator() ( int const& bin_value ) {
        std::cout << "Bin #" << counter++ << ":  " << bin_value << "\n";
    }
};
void test3() {
    Statistics stat2;
    std::ifstream file( "data2" ); // uniformly distributed values from 0 to 999
    file >> stat2;
    file.close();
    std::cout << "Bins:\n";
    std::vector<int> bins = stat2.Histogram( 50, 0, 1000 ); //50 bins in the range [0,1000)
    std::for_each( bins.begin(), bins.end(), PrintBin() );
}
void test4() {
    short a[] = {1,
        2,2,
        3,3,3,
        4,4,4,4,4,
        5,5};
    Statistics stat1( a, a + sizeof(a)/sizeof(*a) );
    
    std::cout << "Bins:\n";
      // "+1" - so that 5 is the beginning of the 5th bin
    std::vector<int> bins = stat1.Histogram( 5, stat1.Minimum(), stat1.Maximum()+1 ); 
    std::for_each( bins.begin(), bins.end(), PrintBin() );
    
    std::cout << "Histogram:\n";
    stat1.DrawHistogramH( 5, stat1.Minimum(), stat1.Maximum()+1 );
}
void test5() {
    Statistics stat2;
    std::ifstream file( "data2" );
    file >> stat2;
    file.close();
    std::cout << "Histogram:\n";
    stat2.DrawHistogramH( 50, 0, 1000 );
}
void test6() {
    short a[] = {1,
        2,2,
        3,3,3,
        4,4,4,4,4,
        5,5};
    Statistics stat1( a, a + sizeof(a)/sizeof(*a) );
    
    std::cout << "Bins:\n";
    std::vector<int> bins = stat1.Histogram( 5, stat1.Minimum(), stat1.Maximum()+1 );
    std::for_each( bins.begin(), bins.end(), PrintBin() );
    
    std::cout << "Histogram:\n";
    stat1.DrawHistogramV( 5, stat1.Minimum(), stat1.Maximum()+1 );
}
void test7() {
    Statistics stat3;
    std::ifstream file3( "data3" ); //normally distributed data
    file3 >> stat3;
    file3.close();
    std::cout << "Histogram:\n";
    //stat3.DrawHistogramV( 50, stat3.Minimum(), stat3.Maximum()+1 );
}

void test8();

void (*pTests[])(void) = { 
	test0, test1, test2, test3, test4, test5, test6, test7, test8
};

#include <cstdio> /* sscanf */

void test8() {
	for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i)
		pTests[i]();
}

int main(int argc, char *argv[] ) {
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
