#include <iostream>

template <typename T>
template <typename Container, typename NodeType, typename ReferenceType>
typename CircularList<T>::template Iterator<Container, NodeType, ReferenceType>& CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator++()
{
	this->position = this->position->next;
	if (this->position == owner->sentinel)
	{
		this->position = this->position->next;
	}

	return *this;
}

template<typename T>
template <typename Container, typename NodeType, typename ReferenceType>
typename CircularList<T>::template Iterator<Container, NodeType, ReferenceType> CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator++(int)
{
	Iterator old = *this;
	++(*this);
	return old;
}

template<typename T>
template <typename Container, typename NodeType, typename ReferenceType>
ReferenceType CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator*()
{
	if (this->position == owner->sentinel)
		throw "Invalid position!";

	return this->position->data;
}

template<typename T>
template <typename Container, typename NodeType, typename ReferenceType>
bool CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator==(const Iterator& iter) const
{
	return this->owner == iter.owner && this->position == iter.position;
}

template<typename T>
template <typename Container, typename NodeType, typename ReferenceType>
bool CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator!=(const Iterator& iter) const
{
	return !(*this == iter);
}

template<typename T>
template <typename Container, typename NodeType, typename ReferenceType>
NodeType* CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator->()
{
	return this->position;
}

template<typename T>
template <typename Container, typename NodeType, typename ReferenceType>
CircularList<T>::Iterator<Container, NodeType, ReferenceType>::operator bool() const
{
	return this->position != NULL;
}

template<typename T>
CircularList<T>::CircularList()
	:count(0)
{
	this->sentinel = new Node();
	this->sentinel->next = this->sentinel;
}

template<typename T>
CircularList<T>::CircularList(const CircularList<T>& list)
	: CircularList()
{	
	copy(list);
}

template<typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList<T>& list)
{
	if (this != &list)
	{
		clear();
		copy(list);
	}
	
	return *this;
}

template<typename T>
CircularList<T>::~CircularList()
{
	clear();
	delete this->sentinel;
}

template <typename T>
typename CircularList<T>::Node* CircularList<T>::getPrevious(typename CircularList<T>::Node* position)
{
	Node* current = position;
	while (current->next != position)
	{
		current = current->next;
	}

	return current;
}

template<typename T>
void CircularList<T>::push_back(const T& elem)
{
	this->insert(iterator(this, this->sentinel), elem);
}

template<typename T>
void CircularList<T>::insert(const iterator& iter, const T& elem)
{
	if (this != iter.owner)
		throw "Invalid iterator: different owner!";

	Node* previous = this->getPrevious(iter.position);
	
	Node* newElem = new Node(elem, iter.position);
	previous->next = newElem;

	++this->count;
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::erase(typename CircularList<T>::iterator& iter)
{
	if (this != iter.owner)
		throw "Invalid iterator: different owner!";

	if (!iter)
		throw "Invalid iterator: null pointer!";

	// ���� � �������� ���� ��� ������ ������?
	if(iter.position == this->sentinel)
		return iter;

	iterator next = iter;
	++next;

	Node* previous = this->getPrevious(iter.position);
	previous->next = iter->next;

	delete iter.position;
	iter.position = NULL;

	--this->count;

	return next;
}

template <typename T>
typename CircularList<T>::iterator CircularList<T>::begin()
{
	return iterator(this, this->sentinel->next);
}

template <typename T>
typename CircularList<T>::const_iterator CircularList<T>::begin() const
{
	return const_iterator(this, this->sentinel->next);
}

template <typename T>
size_t CircularList<T>::size() const
{
	return this->count;
}

template <typename T>
bool CircularList<T>::empty() const
{
	return this->sentinel == this->sentinel->next;
}

template <typename T>
void CircularList<T>::copy(const CircularList<T>& list)
{
	if (list.empty())
		return;

	// O(n^2) ������ ���������� � push_back
	const_iterator iter = list.begin(), end = iter;
	do
	{
		this->push_back(*iter);
		++iter;
	} 
	while (iter != end);
}

template <typename T>
void CircularList<T>::clear()
{
	iterator iter = this->begin();
	while (!this->empty())
	{
		iter = this->erase(iter);
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const CircularList<T>& list)
{
	if(list.empty())
		return out;

	typename CircularList<T>::const_iterator iter = list.begin(), end = iter;
	do
	{
		out << *iter << ' ';
		++iter;
	} 
	while (iter != end);

	return out;
}

template <typename T>
bool find(const CircularList<T>& list, const T& x)
{
	if (list.empty()) return false;

	typename CircularList<T>::const_iterator iter = list.begin(), end = iter;
	do
	{
		if (*iter == x)
			return true;
		
		++iter;
	} 
	while (iter != end);

	return false;
}

template <typename T>
void eraseAllEqualTo(CircularList<T>& list, const T& x)
{
	if (list.empty()) return;

	typename CircularList<T>::iterator iter = list.begin();
	
	size_t initial_size = list.size();
	for (size_t i = 1; i <= initial_size; ++i)
	{
		if (*iter == x)
			iter = list.erase(iter);
		else
			++iter;
	} 
}