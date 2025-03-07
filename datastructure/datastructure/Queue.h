#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class Queue
{
public:
	Queue(int capacity = 2)
	{
		capacity_ = capacity;
		queue_ = new T[capacity_];
		front_ = rear_ = 0;
	}

	~Queue()
	{
		if (queue_)
			delete[] queue_;
	}

	bool IsEmpty() const
	{
		if (front_ == rear_)
			return true;

		return false;
	}

	bool IsFull() const
	{
		return (rear_ + 1) % capacity_ == front_;
	}

	T& Front() const
	{
		return queue_[(front_ + 1) % capacity_];
	}

	T& Rear() const
	{
		return queue_[rear_];
	}

	int Size() const
	{
		if (front_ < rear_)
			return rear_ - front_;
		else if (front_ > rear_)
			return capacity_ - front_ + rear_;
		else
			return 0;
	}

	void Resize()
	{
		T* new_queue = new T[2 * capacity_];
		
		int count = 1;
		for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
		{
			new_queue[count] = queue_[i];
			count++;
		}

		front_ = 0;
		rear_ = capacity_ - 1;
		capacity_ *= 2;
		delete[] queue_;
		queue_ = new_queue;
	}

	void Enqueue(const T& item)
	{
		if (IsFull())
			Resize();

		rear_ = (rear_ + 1) % capacity_;
		queue_[rear_] = item;
	}

	void Dequeue()
	{
		front_ = (front_ + 1) % capacity_;
	}

	void Print()
	{
		using namespace std;

		for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
			cout << queue_[i] << " ";
		cout << endl;

		if (print_debug_)
			PrintDebug();
	}

	void PrintDebug()
	{
		using namespace std;

		cout << "Cap = " << capacity_ << ", Size = " << Size();
		cout << endl;

		// front와 rear 위치 표시
		for (int i = 0; i < capacity_; i++) {
			if (i == front_) cout << " F ";
			else if (i == rear_) cout << " R ";
			else cout << "   ";
		}
		cout << endl;

		// 0 based index
		for (int i = 0; i < capacity_; i++)
			cout << setw(2) << i << " ";
		cout << endl;

		if (front_ < rear_)
		{
			// front 앞 사용하지 않은 공간
			for (int i = 0; i < front_ + 1; i++)
				cout << " - ";

			// 저장된 내용물
			for (int i = front_ + 1; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear 뒤 사용하지 않은 공간
			for (int i = rear_ + 1; i < capacity_; i++)
				cout << " * ";

			cout << endl << endl;
		}
		else if (front_ > rear_)
		{
			// rear 이전에 저장된 내용물
			for (int i = 0; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear와 front 사이 사용하지 않은 공간
			for (int i = rear_ + 1; i <= front_; i++)
				cout << " * ";

			// front 뒤 내용물
			for (int i = front_ + 1; i < capacity_; i++)
				cout << setw(2) << queue_[i] << " ";

			cout << endl << endl;
		}
		else // 비었을 경우
		{
			for (int i = 0; i < capacity_; i++)
				cout << " - ";
			cout << endl << endl;
		}
	}

	void SetDebugFlag(bool flag)
	{
		print_debug_ = flag;
	}

protected:
	T* queue_;
	int front_ = 0;
	int rear_ = 0;
	int capacity_;
	bool print_debug_ = false;
};