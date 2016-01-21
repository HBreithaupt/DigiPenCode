#include "array.h"
#include "element-factory.h"

#include <stdlib.h> /* atoi   */

void test0() { //basic test
	//client creates a factory to create elements
	//this way Array doesn't need to know about Element1 and Element2
	//this is yet another "programming to interfaces" example
	//or "old code calls new code"
	CS225::ElementFactory el_fact;

	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "modify myArray1\n";
	myArray1.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}
void test1() { //copy
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6,7,8};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "make a copy of first array\n";
	CS225::Array myArray2 (myArray1); //copy construct
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test2() { //copy 
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "modify myArray1\n";
	myArray1.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "Create copy myArray2(myArray1);\n";
	CS225::Array myArray2 (myArray1);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test3() { //assignment
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	int array2[] = {1,2,3,4,5,6,7,8,9};
	CS225::Array myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "Assign myArray2 = myArray1;\n";
	myArray2 = myArray1;
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test4() { //assignment 
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "Set myArray1.Set(2,3,33);\n";
	myArray1.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	int array2[] = {1,2,3,4,5,6,7,8,9};
	CS225::Array myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "Assign myArray2 = myArray1;\n";
	myArray2 = myArray1;
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test5() { //copy using Element, then modify the copy
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "Create copy myArray2(myArray1);\n";
	CS225::Array myArray2(myArray1);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "assign myArray2 = myArray1;\n";
	myArray2 = myArray1;
	std::cout << "Set myArray2.Set(2,3,33);\n";
	myArray2.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();

	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test6() { //copy using Element, then modify the original
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	CS225::Array myArray2(myArray1);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "Create copy myArray2(myArray1);\n";
	myArray2 = myArray1;
	std::cout << "Modify myArray1\n";
	myArray1.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test7() { //assignment using Element2 then modify the copy
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	int array2[] = {1,2,3,4,5,6,7,8,9};
	CS225::Array myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "Assign myArray2 = myArray1;\n";
	myArray2 = myArray1;
	std::cout << "Modify myArray2\n";
	myArray2.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test8() { //assignment using Element2 then modify the original
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	int array2[] = {1,2,3,4,5,6,7,8,9};
	CS225::Array myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "Assign myArray2 = myArray1;\n";
	myArray2 = myArray1;
	std::cout << "Modify myArray1\n";
	myArray1.Set(2,3,33);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

//function accepts by value
void foo(CS225::Array a) {
	std::cout << "in foo a = ";
	a.Print();
	std::cout << std::endl;
}

void test9() { //calling function that accepts by value
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	foo(myArray1);
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test10 () { //copy then delete the original
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array* p_myArray1 = new CS225::Array(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "p_myArray1-Print();   ";
	p_myArray1->Print();

	CS225::Array myArray2 = *p_myArray1;
	std::cout << "p_myArray1-Print();   ";
	p_myArray1->Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "delete p_myArray1;\n";
	delete p_myArray1;
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl;
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl;
}

void test11 () { //assign then delete the copy
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();

	{ //block
		int array2[] = {1,2,3,4,5,6,7,8,9};
		CS225::Array myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);
		std::cout << "myArray2.Print();   ";
		myArray2.Print();

		myArray2 = myArray1;
		std::cout << "myArray1.Print();   ";
		myArray1.Print();
		std::cout << "myArray2.Print();   ";
		myArray2.Print();
	} //myArray2 is deleted

	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl;
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl;
}

void test12 () { //chaining
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6,7,8,9};
	CS225::Array * pArray1 = new CS225::Array(array,sizeof(array)/sizeof(array[0]),&el_fact);
	std::cout << "pArray1-Print();   ";
	pArray1->Print();

	int a[] = {1};
	CS225::Array * pArray2=new CS225::Array(a,sizeof(a)/sizeof(a[0]),&el_fact);
	*pArray2=*pArray1;
	delete pArray1;

	CS225::Array * pArray3=new CS225::Array(a,sizeof(a)/sizeof(a[0]),&el_fact);
	*pArray3=*pArray2;
	delete pArray2;

	std::cout << "pArray3-Print();   ";
	pArray3->Print();
	delete pArray3;
	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl;
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl;
}

void test13() {
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,};
	CS225::Array  myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);

	int array2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	CS225::Array  myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);

	int array3[] = {1,2,3,4,5,6,7,8,9,10};
	CS225::Array  myArray3(array3,sizeof(array3)/sizeof(array3[0]),&el_fact);

	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "myArray3.Print();   ";
	myArray3.Print();

	std::cout << "Assign myArray3=myArray1;\n";
	myArray3=myArray1;

	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "myArray3.Print();   ";
	myArray3.Print();

	std::cout << "Assign myArray3=myArray2;\n";
	myArray3=myArray2;

	std::cout << "myArray1.Print();   ";
	myArray1.Print();
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "myArray3.Print();   ";
	myArray3.Print();

	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl;
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl;
}

//function returns by value
CS225::Array give_my_array(int * p, unsigned int size) {
	CS225::ElementFactory el_fact;
	CS225::Array result(p,size,&el_fact);
	for (unsigned int i=0;i<size;++i) {
		result.Set(2,i,2*result.Get(i)); //double them all and change type
	}
	std::cout << "int give_my_array(...) result.Print();   ";
	result.Print();
	return result;
}

void test14() {
	int array[] = {1,2,3,4,5,6,7,8,9};
	CS225::Array  myArray1 = give_my_array(array,sizeof(array)/sizeof(array[0]));
	std::cout << "in test result from give_my_array     ";
	myArray1.Print();

	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl;
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl;
}

/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
////test virtual constructor
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void test15() { //copy using Element, then modify the copy
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	myArray1.Set(2,3,44);
	myArray1.Set(2,4,55);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();

	std::cout << "Create copy myArray2(myArray1);\n";
	CS225::Array myArray2(myArray1);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();

	std::cout << "Modify myArray2\n";
	myArray2.Set(2,1,22);

	std::cout << "myArray1.Print();   ";
	myArray1.Print();

	std::cout << "myArray2.Print();   ";
	myArray2.Print();

	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl; 
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl; 
}

void test16() { //copy using Element, then modify the original
	CS225::ElementFactory el_fact;
	int array[] = {1,2,3,4,5,6};
	int array2[] = {1,2,3};
	CS225::Array myArray1(array,sizeof(array)/sizeof(array[0]),&el_fact);
	myArray1.Set(2,3,44);
	myArray1.Set(2,4,55);
	std::cout << "myArray1.Print();   ";
	myArray1.Print();

	CS225::Array myArray2(array2,sizeof(array2)/sizeof(array2[0]),&el_fact);
	std::cout << "myArray2.Print();   ";
	myArray2.Print();
	std::cout << "Assign myArray2 = myArray1;\n";
	myArray2 = myArray1;
	std::cout << "myArray2.Print();   ";
	myArray2.Print();

	std::cout << "Modify myArray2\n";
	myArray2.Set(2,1,22);

	std::cout << "myArray1.Print();   ";
	myArray1.Print();

	std::cout << "myArray2.Print();   ";
	myArray2.Print();

	std::cout << "live  nodes  " << CS225::AbstractElement::live()  << std::endl;
	std::cout << "total nodes  " << CS225::AbstractElement::total() << std::endl;
}

void test17();

void (*pTests[])() = { test0,test1,test2,test3,test4,test5,test6,test7,
	test8,test9,test10,test11,test12,test13,test14,test15,test16
	,test17
}; 

void test17() {
	for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i) 
		pTests[i]();
}

int main (int argc, char ** argv) {
	if (argc >1) {
		pTests[atoi( argv[1] )]();
	}
	return 0;
}
