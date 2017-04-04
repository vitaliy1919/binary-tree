#pragma once
#include <iostream>
using std::cout;
//struct for tree node
template <typename T>
struct treeNode
{
	treeNode* left;
	treeNode* right;
	T data;
	treeNode(const T& d,treeNode* l=nullptr,treeNode* r=nullptr):data(d),left(l),right(r){ }
};

//tree class
template <typename T>
class binaryTree
{
private:
	treeNode<T> root;
	void show_from_node(treeNode<T> *rt) const;
public:
	binaryTree() :root() {}
	void addNode(const T&);
	void show() const;
};

template<typename T>
void binaryTree<T>::show_from_node(treeNode<T> *rt) const
{
	if (rt)
	{
		cout << rt->data << ' ';
		show_from_node(root->left);
		show_from_node(root->right);
	}
}

template<typename T>
void binaryTree<T>::addNode(const T & d)
{
	if (root)
	{
		treeNode<T> *x = root, *t = new Node(d);
		treeNode<T> *y = x;
		while (x)
		{
			y = x;
			if (x->data > d)
				x = x->left;
			else
				x = x->right;
		}
		if (y->data > d)
			y->left = t;
		else
			y->right = t;
	}
	else
		root = new treeNode(d);
}

template<typename T>
void binaryTree<T>::show() const
{
	show_from_node(root);
	cout << endl;
}
