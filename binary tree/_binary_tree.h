#pragma once
#include <iostream>
using std::cout;
//struct for tree node
template <typename T>
struct treeNode
{
	treeNode* left;
	treeNode* right;
	treeNode* parent;
	T data;
	treeNode(const T& d,treeNode* l=nullptr,treeNode* r=nullptr,treeNode* p=nullptr):data(d),left(l),right(r),parent(p){ }
};
//tree class
template <typename T>
//using treeNode<T> = treeNode<T>;
class binaryTree
{
private:
	treeNode<T> *root;
	void delete_tree(treeNode<T> *rt);
	void show_node(treeNode<T> *rt) const;
	void transplant(treeNode<T>* u, treeNode<T>* v);
	treeNode<T>* min_node(treeNode<T> *rt) const;
	treeNode<T>* max_node(treeNode<T> *rt) const;
	treeNode<T>* find_node(const T& it,treeNode<T> *rt);
	void delete_node(treeNode<T> *u);
	int height_node(treeNode<T> *rt) const;
	int node_count(treeNode<T> *rt) const;
public:
	binaryTree() :root(nullptr) {}
	virtual ~binaryTree() { delete_tree(root); }
	void add_node(const T&);
	treeNode<T>* get_root() const { return root; }
	//treeNode<T>* find(const T& it);
	void delete_node(const T& key);
	void show() const;
	int size() const { return node_count(root); }
	int height() const { return height_node(root); }
	T min() const;
	T max() const;
};

template<typename T>
void binaryTree<T>::delete_tree(treeNode<T>* rt)
{
	if (rt)
	{
		delete_tree(rt->left);
		delete_tree(rt->right);
		delete rt;
	}
}

template<typename T>
void binaryTree<T>::show_node(treeNode<T> *rt) const
{
	if (rt)
	{
		cout << rt->data << ' ';
		show_node(rt->left);
		show_node(rt->right);
	}
}

template<typename T>
void binaryTree<T>::transplant(treeNode<T>* u, treeNode<T>* v)
{
	if (!u->parent)
		root = v;
	else if (u->parent->left == u)
		u->parent->left = v;
	else u->parent->right = v;
	if (v)
		v->parent = u->parent;
	delete u;
}

template<typename T>
treeNode<T> * binaryTree<T>::min_node(treeNode<T>* rt) const
{
	if (rt)
	{
		treeNode<T> *x = rt;
		while (x->left)
			x = x->left;
		return x;
	}
	return nullptr;
}

template<typename T>
treeNode<T> * binaryTree<T>::max_node(treeNode<T> * rt) const
{
	if (rt)
	{
		treeNode<T>* x = root;
		while (x->right)
			x = x->right;
		return x;
	}
	return nullptr;
}

template<typename T>
treeNode<T>* binaryTree<T>::find_node(const T & it, treeNode<T>* rt)
{
	if (rt)
	{
		if (rt->data == it)
			return rt;
		else if (rt->data > it)
			return find_node(it, rt->left);
		else
			return find_node(it, rt->right);
	}
	return nullptr;
}

template<typename T>
void binaryTree<T>::delete_node(treeNode<T>* u)
{
	if (!u)
		return;
	if (!u->left)
		transplant(u, u->right);
	else if (!u->right)
		transplant(u, u->left);
	else
	{
		treeNode<T> *y = min_node(u->right);
		T temp = y->data;
		//if (y->parent != u)
		//{
			transplant(y, y->right);
			u->data = temp;
			//y->right=u
		//}
	}
}

template<typename T>
int binaryTree<T>::height_node(treeNode<T>* rt) const
{
	if (rt)
	{
		int h1 = height_node(rt->left), h2 = height_node(rt->right);
		return (h1 > h2 ? h1 : h2) + 1;
	}
	return 0;
}

template<typename T>
int binaryTree<T>::node_count(treeNode<T>* rt) const
{
	if (rt)
	{
		return node_count(rt->left) + node_count(rt->right) + 1;
	}
	return 0;
}



template<typename T>
void binaryTree<T>::add_node(const T & d)
{
	if (root)
	{
		treeNode<T> *x = root, *t = new treeNode<T>(d);
		treeNode<T> *y = x;
		while (x)
		{
			y = x;
			if (x->data > d)
				x = x->left;
			else
				x = x->right;
		}
		t->parent = y;
		if (y->data > d)
			y->left = t;
		else
			y->right = t;
	}
	else
		root = new treeNode<T>(d);
}

//template<typename T>
//treeNode<T>* binaryTree<T>::find(const T & it)
//{
//	
//}

template<typename T>
void binaryTree<T>::delete_node(const T & key)
{
	treeNode<T> *u = find_node(key, root);
	delete_node(u);
}

template<typename T>
void binaryTree<T>::show() const
{
	show_node(root);
	cout << endl;
}

template<typename T>
T binaryTree<T>::min() const
{
	return min_node(root)->data;
}

template<typename T>
inline T binaryTree<T>::max() const
{
	return max_node(root)->data;
}
