#pragma once

#include <string>

#include "Stack.h"
#include "Queue.h"

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* left = nullptr;
		Node* right = nullptr;
	};

	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
			cout << endl;
		}
	};

	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		root_ = root;
	}

	~BinaryTree()
	{
		DeleteTree(root_);
	}

	bool IsEmpty()
	{
		return root_ == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;
		cout << node->item << " ";
	}

	int Sum()
	{
		return Sum(root_);
	}

	int Sum(Node* node)
	{
		if (!node)
			return 0;
		return node->item + Sum(node->left) + Sum(node->right);
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		if (!node)
			return 0;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	void DeleteTree(Node* node)
	{
		if (node)
		{
			DeleteTree(node->left);
			DeleteTree(node->right);
			delete node;
		}
	}

	void Preorder()
	{
		Preorder(root_);
	}

	void Preorder(Node* node)
	{
		if (node)
		{
			Visit(node);
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder()
	{
		Inorder(root_);
	}

	void Inorder(Node* node)
	{
		if (node)
		{
			Inorder(node->left);
			Visit(node);
			Inorder(node->right);
		}
	}

	void Postorder()
	{
		Postorder(root_);
	}

	void Postorder(Node* node)
	{
		if (node)
		{
			Postorder(node->left);
			Postorder(node->right);
			Visit(node);
		}
	}

	void Levelorder()
	{
		using namespace std;

		MyQueue q;
		Node* current = root_;
		while (current)
		{
			Visit(current);
			if (current->left)
				q.Enqueue(current->left);
			if (current->right)
				q.Enqueue(current->right);
			if (q.IsEmpty())
				return;

			cout << endl;
			cout << "Queue: ";
			q.Print();

			current = q.Front();
			q.Dequeue();
		}
	}

	void IterPreorder()
	{
		using namespace std;

		if (!root) return;

		MyStack s;
		s.Push(root_);

		while (!s.IsEmpty())
		{
			Node* current = s.Top();
			s.Pop();

			Visit(current);

			if (current->right)
				s.Push(current->right);
			if (current->left)
				s.Push(current->left);

			cout << "Stack: ";
			s.Print();
		}
	}

	void IterInorder()
	{
		if (!root_) return;

		Stack<Node*> s;
	}

	void IterPostorder()
	{

	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}