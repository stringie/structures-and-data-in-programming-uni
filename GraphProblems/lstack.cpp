/*
 * lstack.cpp
 *
 *  Created on: 16.03.2017 г.
 *      Author: trifon
 */

#ifndef LSTACK_CPP_
#define LSTACK_CPP_

#include <iostream>
#include "abstract_stack.h"

template <typename T>
struct StackElement {
	T data;
	StackElement* next;
};

template <typename T>
class LinkedStack : public AbstractStack<T> {
protected:
	StackElement<T>* top;

private:

	void copy(StackElement<T>* toCopy);

	void eraseStack();

	void copyStack(LinkedStack const&);

public:

	// създаване на празен стек
	LinkedStack();

	// Конструктор за копиране
	LinkedStack(LinkedStack const&);

	// операция за присвояване
	LinkedStack& operator=(LinkedStack const&);

	// деструктор
	~LinkedStack();

	// проверка дали стек е празен
	bool empty() const;

	// включване на елемент
	void push(T const& x);

	// изключване на елемент
	T pop();

	// поглеждане на елемента на върха на стека
	T peek() const;

  	// поглеждане на елемента на върха на стека
        // с възможност за промяна
        T& peek();

	LinkedStack& operator+=(T const& x) {
		push(x);
		return *this;
	}
};

// O(1)
template <typename T>
LinkedStack<T>::LinkedStack() : top(nullptr) {}

// O(1)
template <typename T>
bool LinkedStack<T>::empty() const {
	return top == nullptr;
}

// O(1)
template <typename T>
void LinkedStack<T>::push(T const& x) {
	StackElement<T>* p = new StackElement<T>;
	p->data = x;
	p->next = top;
	top = p;
}

// O(1)
template <typename T>
T LinkedStack<T>::pop() {
	if (empty()) {
		// Стекът е празен
		std::cerr << "Опит за изключване на елемент от празен стек!\n";
		return T();
	}
	StackElement<T>* p = top;
	top = top->next;
	T x = p->data;
	delete p;
	return x;
}

// O(1)
template <typename T>
T LinkedStack<T>::peek() const {
	if (empty()) {
		// Стекът е празен
		std::cerr << "Опит за достъп до върха на празен стек!\n";
		return T();
	}
	return top->data;
}

// O(1)
template <typename T>
T& LinkedStack<T>::peek() {
  // TODO: проверка за празен стек!
  return top->data;
}

// O(n)
template <typename T>
void LinkedStack<T>::eraseStack() {
	// !!! delete top;
	// !!! delete[] top;
	while (!empty())
		pop();
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
	eraseStack();
}

/*
// O(n) по време, O(1) по памет
LinkedStack<T>::LinkedStack(LinkedStack const& ls) :
	top(nullptr) {

	// ако ls е празен, няма какво да правим повече
	if (ls.empty())
		return;

	// сигурни сме, че в ls има поне един елемент

	// копираме първия елемент
	StackElement* lastCopied = new StackElement;
	lastCopied->data = ls.top->data;

	// първият копиран елемент е върхът на стека
	top = lastCopied;

	// копираме останалите от втория елемент нататък
	for(StackElement* toCopy = ls.top->next;
			toCopy != nullptr;
			toCopy = toCopy -> next) {
		// правим копие на клетката, която сочи toCopy
		StackElement* copied = new StackElement;
		copied->data = toCopy->data;
		lastCopied->next = copied;
		lastCopied = copied;
	}

	// Последният елемент няма следващ
	lastCopied->next = nullptr;
}

*/

// O(n) и по време и по памет
template <typename T>
void LinkedStack<T>::copy(StackElement<T>* toCopy) {
	if (toCopy == nullptr)
		return;
	// сигурен съм, че има поне един елемент
	// Копирам стека от втория елемент нататък
	copy(toCopy->next);
	// добавям и първия елемент отгоре
	push(toCopy->data);
}

template <typename T>
void LinkedStack<T>::copyStack(LinkedStack const& ls) {
	top = nullptr;
	copy(ls.top);
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack const& ls) {
	copyStack(ls);
}

/*
 * template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack const& ls) :
		top(nullptr) {
	for(StackElement* toCopy = ls.top;
			toCopy != nullptr;
			toCopy = toCopy -> next) {
		push(toCopy->data);
	}
}
*/

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack const& ls) {
	if (this != &ls) {
		eraseStack();
		copyStack(ls);
	}
	return *this;
}

#endif /* LSTACK_CPP_ */