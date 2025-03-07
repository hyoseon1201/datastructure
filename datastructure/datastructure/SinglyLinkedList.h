#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{

	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		Node* current = list.first_;
		while (current)
		{
			this->PushBack(current->item);
			current = current->next;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear()
	{
		while (first_)
			PopFront();
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		Node* currentNode = first_;

		while (currentNode)
		{
			currentNode = currentNode->next;
			size++;
		}

		return size;
	}

	T Front()
	{
		assert(first_);

		return first_->item;
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;
		while (current->next)
			current = current->next;
		return current->item;
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
		Node* current = first_;

		while (current)
		{
			if (current->item == item)
				return current;

			current = current->next;
		}

		return current;
	}

	void InsertBack(Node* node, T item)
	{
		// TODO:
		Node* temp = new Node;
		temp->item = item;
		temp->next = node->next;
		node->next = temp;
	}

	void Remove(Node* n)
	{
		assert(first_);

		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
		if (first_ == n)
		{
			first_ = first_->next;
			delete n;
			return;
		}

		Node* prev = first_;
		while (prev->next)
		{
			if (prev->next == n)
				break;
			prev = prev->next;
		}
		prev->next = n->next;
		delete n;
	}


	void PushFront(T item)
	{
		Node* newNode = new Node;
		newNode->item = item;

		newNode->next = first_;
		first_ = newNode;
	}

	void PushBack(T item)
	{
		if (first_ == nullptr)
		{
			PushFront(item);
		}
		else
		{
			Node* current = first_;
			while (current->next)
				current = current->next;
			Node* newNode = new Node;
			newNode->item = item;
			current->next = newNode;
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// TODO: 메모리 삭제
		Node* temp = first_;
		first_ = first_->next;
		delete temp;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		if (first_->next == nullptr)
		{
			delete first_;
			first_ = nullptr;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(first_);

		// TODO: 메모리 삭제

		Node* secondLast = first_;

		while (secondLast->next->next)
			secondLast = secondLast->next;

		Node* temp = secondLast->next;
		secondLast->next = secondLast->next->next;

		delete temp;
	}

	void Reverse()
	{
		Node* current = first_;
		Node* previous = nullptr;

		while (current)
		{
			Node* temp = previous;
			previous = current;
			current = current->next;
			previous->next = temp;
		}

		first_ = previous;
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;
	
	bool print_debug_ = false;
};