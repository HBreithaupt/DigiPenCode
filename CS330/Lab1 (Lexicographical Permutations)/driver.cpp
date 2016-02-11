#include "perm-lexicographical.h"
#include <iterator> //ostream_iterator
#include <algorithm>
#include <iostream>

struct Print
{
	void operator() ( std::vector<int> const& v) const
	{
		std::copy( v.begin(), v.end(),
				std::ostream_iterator<int>(std::cout, " ") );
		std::cout << std::endl;
	}
};

int main() {
	std::vector<int> v;
	for(int i = 1; i<6; ++i) v.push_back(i);

	Print printer;

	do
	{
		printer( v );
	}
	while ( nextPermLexicographical(v) );
}
