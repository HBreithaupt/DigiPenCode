#include "element-factory.h"

//this is a concrete factory, so it has to know about all element classes
#include "element1.h"
#include "element2.h"

//for grading I'll use a different factory that supports 
//3d element types.

//#include "element3.h"

CS225::AbstractElement* CS225::ElementFactory::MakeElement(int id,int value) const {
	AbstractElement* p_element = NULL;
	switch (id) {
		case 1: p_element = new Element1(value); break;
		case 2: p_element = new Element2(value); break;
		//case 3: p_element = new Element3(value); break;
	}
	return p_element;
}
