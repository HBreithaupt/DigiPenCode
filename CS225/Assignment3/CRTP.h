#ifndef CRTP_H
#define CRTP_H
#include <cstdlib>
/*
 * Implements a templatized class for object counting (used in Curiously 
 * Recurring Template Pattern).
 *
 * Usage
 * class C1 : public ObjectCounter<C1> {....};
 * class C2 : public ObjectCounter<C2> {....};
 * now
 * C1::live() returns number of alive objects of type C1
 * C2::live() returns number of alive objects of type C2
 *
 * the key is that the base classes ObjectCounter<C1> and ObjectCounter<C2>
 * are 2 different classes, therefore each of them has 2 variables 
 * (total and alive) which are independent of the corresponding variables
 * from the other class.
 */
template <typename T> 
class ObjectCounter {
	protected:  
		ObjectCounter() {
			++ObjectCounter<T>::count;
			++ObjectCounter<T>::count_all;
		} 
		ObjectCounter (ObjectCounter<T> const&) {
			++ObjectCounter<T>::count;
			++ObjectCounter<T>::count_all;
		} 
		virtual ~ObjectCounter() { --ObjectCounter<T>::count; }
	public:
		static size_t live() { return ObjectCounter<T>::count; } 
		static size_t total() { return ObjectCounter<T>::count_all; } 
	private: 
		static int count; 
		static int count_all; 
}; 
template <typename T> 
int ObjectCounter<T>::count =0; 
template <typename T> 
int ObjectCounter<T>::count_all =0; 
#endif
