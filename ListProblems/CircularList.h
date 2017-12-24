#ifndef CIRCULARLIST_H_INCLUDED
#define CIRCULARLIST_H_INCLUDED

#include <cstdlib>

template <typename T>
class CircularList
{
	public:
		struct Node
		{
			T data;
			Node* next;

			Node(const T& elem, Node* pos = NULL)
				: data(elem), next(pos)
			{}

			Node(Node* pos = NULL): next(pos)
			{}
		};

		template <typename Container = CircularList<T>, typename NodeType = Node, typename ReferenceType = T&>
		class Iterator
		{
			friend class CircularList<T>;

			public:
				Iterator& operator++();
				Iterator operator++(int);

				ReferenceType operator*();

				bool operator==(const Iterator&) const;
				bool operator!=(const Iterator&) const;

				operator bool() const;

			private:
				Container* owner;
				NodeType* position;

				Iterator(Container* list, NodeType* pos)
					: owner(list), position(pos)
				{}

				NodeType* operator->();
		};

		typedef Iterator<CircularList<T>, Node, T&> iterator;
		typedef Iterator<const CircularList<T>, const Node, const T&> const_iterator;

	public:
		CircularList();
		CircularList(const CircularList<T>&);
		CircularList<T>& operator=(const CircularList<T>&);
		~CircularList();

		void push_back(const T&);
		void insert(const iterator&, const T&);

		iterator erase(iterator&);

		iterator begin();
		const_iterator begin() const;

		size_t size() const;

		bool empty() const;

	private:
		Node* sentinel;
		size_t count;

		void copy(const CircularList<T>&);
		void clear();
		Node* getPrevious(Node*);
};

#include "CircularList.hpp"

#endif // !CIRCULARLIST_H_INCLUDED

