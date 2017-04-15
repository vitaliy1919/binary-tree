#pragma once
#include <iostream>
#include <fstream>
using namespace std;
template <typename T>
class RedBlackTree
{
public:
	struct Node
	{
		enum {Red,Black};
		Node	*left = nullptr;
		Node	*right = nullptr;
		Node	*parent = nullptr;
		T		data;
		int		number = 0;
		short	color = Black;
		Node():data(){}
		Node(const T& d, int c=Black, Node* l=nullptr, Node* r=nullptr, Node* p=nullptr):data(d),color(c),left(l),right(r),parent(p) {}
	};
	RedBlackTree() { nil_ = new Node(); root_ = nil_; }
	void insertElement(const T& element);
	void showTree() { showTree(root_, 0); cout << endl; }
	int getNumberOfLeaves() const { return getNumberOfLeaves(root_); }
	int getTreeHeight() const { return getTreeHeight(root_); }
	void deleteElement(const T& key);
	void writeTreeForVisualisation() const;
	~RedBlackTree();
private:
	Node *root_, *nil_;
	void deleteRedBlackTree(Node *start_node);
	RedBlackTree& operator=(const RedBlackTree& tr) { return *this; }
	RedBlackTree(const RedBlackTree& tr) { return *this; }
	int getNumberOfLeaves(Node *start_node) const;
	int getTreeHeight(Node *start_node) const;
	Node *minNode(Node *start_node);
	Node *maxNode(Node *start_node);
	void transplantRB(Node *u, Node *v);
	void leftRotate(Node *x);
	void rightRotate(Node *y);
	void fixAfterInsert(Node *x);
	void fixAfterDelete(Node *x);
	Node* search(Node* start_node, const T& key) const;
	void showTree(Node *start_node, int level);
	void writeTreeNodeInformation(ostream& os,Node* start_node) const;
	void writeTreeNodeLink(ostream& os, Node* start_node) const;
	void deleteNodeFromRBTree(Node *node_to_delete);
};

template<typename T>
void RedBlackTree<T>::deleteRedBlackTree(Node * start_node)
{
	if (start_node!=nil_)
	{
		deleteRedBlackTree(start_node->left);
		deleteRedBlackTree(start_node->right);
		delete start_node;
	}
}
template<typename T>
int RedBlackTree<T>::getNumberOfLeaves(Node * start_node) const
{
	if (start_node)
	{
		if (start_node->right == nil_ && start_node->left == nil_)
			return 1;
		int left_leaves = 0, right_leaves = 0;
		if (start_node->left != nil_)
			left_leaves = getNumberOfLeaves(start_node->left);
		if (start_node->right != nil_)
			right_leaves = getNumberOfLeaves(start_node->right);
		return left_leaves + right_leaves;
	}
	return 0;
}
template<typename T>
int RedBlackTree<T>::getTreeHeight(Node * start_node) const
{
	if (start_node != nil_)
	{
		int left_height = 0, right_height = 0;
		if (start_node->left != nil_)
			left_height = getTreeHeight(start_node->left);
		if (start_node->right != nil_)
			right_height = getTreeHeight(start_node->right);
		return (left_height > right_height ? left_height : right_height) + 1;
	}
	return 0;
}
//
template<typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::minNode(Node * start_node)
{
	if (start_node != nil_)
	{
		while (start_node->left != nil_)
			start_node = start_node->left;
	}
	return start_node;
}

template<typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::maxNode(Node * start_node)
{
	if (start_node != nil_)
	{
		while (start_node->right != nil_)
			start_node = start_node->right;
	}
	return start_node;
}

template<typename T>
void RedBlackTree<T>::transplantRB(Node * u, Node * v)
{
	if (u->parent == nil_)
		root_ = v;
	else if (u->parent->left == u)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
	delete u;
}

template<typename T>
void RedBlackTree<T>::leftRotate(Node * x)
{
	Node *y = x->right;
	if (x->parent == nil_)
		root_ = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;
	x->right = y->left;
	if (y->left != nil_)
		y->left->parent = x;
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
}

template<typename T>
void RedBlackTree<T>::rightRotate(Node *y)
{
	Node *x = y->left;
	if (y->parent == nil_)
		root_ = x;
	else if (y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;
	y->left = x->right;
	if (x->right != nil_)
		x->right->parent = y;
	x->right = y;
	x->parent = y->parent;
	y->parent = x;
}

template<typename T>
void RedBlackTree<T>::fixAfterInsert(Node * x)
{
	while (x->parent->color == Node::Red)
	{
		Node *grand_parent = x->parent->parent;
		if (x->parent == grand_parent->left)
		{
			Node *y = grand_parent->right;
			if (y->color == Node::Red) //case 1 - uncle grand_parent->right is Red
			{
				x->parent->color = Node::Black; //repaint nodes and change x
				y->color = Node::Black;			// up to 2 levels
				grand_parent->color = Node::Red;
				x = grand_parent;
			}
			else // case 2 or 3 - uncle grand_parent->right is Black
			{ 
				if (x == x->parent->right)// case 2: if x - right child
				{
					x = x->parent;
					leftRotate(x);
				}
				x->parent->color = Node::Black;
				grand_parent->color = Node::Red;
				rightRotate(grand_parent);
			}
		}
		else //the same, but left is now right, right is left 
		{
			Node *y = grand_parent->left;
			if (y->color == Node::Red)
			{
				x->parent->color = Node::Black; 
				y->color = Node::Black;			
				grand_parent->color = Node::Red;
				x = grand_parent;
			}
			else // case 2 or 3 - uncle grand_parent->right is Black
			{
				if (x == x->parent->left)
				{
					x = x->parent;
					rightRotate(x);
				}
				x->parent->color = Node::Black;
				grand_parent->color = Node::Red;
				leftRotate(grand_parent);
			}
		}
	}
	root_->color = Node::Black;
}

template<typename T>
void RedBlackTree<T>::fixAfterDelete(Node * x)
{
	while (x != root_ && x->color == Node::Black)
	{
		if (x == x->parent->left)
		{
			Node *brother = x->parent->right;
			if (brother->color == Node::Red)
			{
				brother->color = Node::Black;
				x->parent->color = Node::Red;
				leftRotate(x->parent);
				brother = x->parent->right;
			}
			if (brother->left->color == Node::Black && 
				brother->right->color == Node::Black)
			{
				brother->color = Node::Red;
				x = x->parent;
			}
			else {
				if (brother->right->color == Node::Black)
				{
					brother->left->color = Node::Black;
					brother->color = Node::Red;
					rightRotate(brother);
					brother = x->parent->right;
				}
				brother->color = x->parent->color;
				x->parent->color = Node::Black;
				brother->right->color = Node::Black;
				leftRotate(x->parent);
				x = root_;
			}
		}
		else
		{
			Node *brother = x->parent->left;
			if (brother->color == Node::Red)
			{
				brother->color = Node::Black;
				x->parent->color = Node::Red;
				rightRotate(x->parent);
				brother = x->parent->left;
			}
			if (brother->left->color == Node::Black &&
				brother->right->color == Node::Black)
			{
				brother->color = Node::Red;
				x = x->parent;
			}
			else {
				if (brother->left->color == Node::Black)
				{
					brother->right->color = Node::Black;
					brother->color = Node::Red;
					leftRotate(brother);
					brother = x->parent->left;
				}
				brother->color = x->parent->color;
				x->parent->color = Node::Black;
				brother->left->color = Node::Black;
				rightRotate(x->parent);
				x = root_;
			}
		}
	}
	x->color = Node::Black;
}

template<typename T>
typename RedBlackTree<T>::Node * RedBlackTree<T>::search(Node * start_node, const T & key) const
{
	while (start_node != nil_ && start_node->data != key)
	{
		if (start_node->data > key)
			start_node = start_node->left;
		else
			start_node = start_node->right;
	}
	return start_node;
}

template<typename T>
void RedBlackTree<T>::showTree(Node * start_node, int level)
{
	if (start_node != nil_)
	{
		cout << "(" << start_node->data << "," << level << (start_node->color == Node::Red ? ",Red)" : ",Black)") << ' ';
		showTree(start_node->left, level + 1);
		showTree(start_node->right, level + 1);
	}
}

template<typename T>
void RedBlackTree<T>::writeTreeNodeInformation(ostream & os,Node* start_node) const
{
	static int node_number = 0;
	if (start_node != nil_)
	{
		/*os << "node" << node_number << " [shape=circle,fontsize=20,label=\"" << start_node->data << "\",style=filled" <<
			(start_node->color == Node::Black ? ",fillcolor=Black,fontcolor=red]" : ",fillcolor=Red]") << endl;*/
		os << "node" << node_number << " [shape=circle,fontsize=20,fontname=\"Calibri\",label=< <B>" << start_node->data << "</B> >,style=filled";
		if (start_node->left == nil_ && start_node->right == nil_)
			os << ",color=green,penwidth=5";
		os<<(start_node->color == Node::Black ? ",fillcolor=Black,fontcolor=white]" : ",fillcolor=Red]") << endl;
		start_node->number = node_number;
		if (start_node->left != nil_)
		{
			node_number++;
			writeTreeNodeInformation(os, start_node->left);
		}
		if (start_node->right != nil_)
		{
			node_number++;
			writeTreeNodeInformation(os, start_node->right);
		}
	}
}

template<typename T>
void RedBlackTree<T>::writeTreeNodeLink(ostream & os, Node * start_node) const
{
	static int node_number = 0;
	if (start_node != nil_)
	{
		if (start_node->left != nil_)
		{
			os << "node" << start_node->number << "->";
			os << "node" << start_node->left->number << endl;
		}
		if (start_node->right != nil_)
		{
			os << "node" << start_node->number << "->";
			os << "node" << start_node->right->number << endl;
		}
		if (start_node->left != nil_)
			writeTreeNodeLink(os, start_node->left);
		if (start_node->right != nil_)
			writeTreeNodeLink(os, start_node->right);
	}
}

template<typename T>
void RedBlackTree<T>::deleteNodeFromRBTree(Node * node_to_delete)
{
	Node *y = node_to_delete, *x = nullptr;
	short original_color = y->color;
	if (node_to_delete->left == nil_)
	{
		x = node_to_delete->right;
		transplantRB(node_to_delete, node_to_delete->right);
	}
	else if (node_to_delete->right == nil_)
	{
		x = node_to_delete->left;
		transplantRB(node_to_delete, node_to_delete->left);
	}
	else
	{
		y = minNode(node_to_delete->right);
		x = y->right;
		original_color = y->color;
		T min_data = y->data;
		transplantRB(y, y->right);
		node_to_delete->data = min_data;
	}
	if (original_color== Node::Black)
		fixAfterDelete(x);
}

template<typename T>
void RedBlackTree<T>::insertElement(const T &element)
{
	Node *insert_node = new Node(element,Node::Black,nil_,nil_);
	Node *x = root_, *y = nil_;
	while (x != nil_)
	{
		y = x;
		if (x->data > element)
			x = x->left;
		else
			x = x->right;
	}
	insert_node->parent = y;
	if (y == nil_)
	{
		root_ = insert_node;
		return; //-V773
	}
	else if (y->data > element)
		y->left = insert_node;
	else
		y->right = insert_node;
	insert_node->color = Node::Red;
	fixAfterInsert(insert_node);
}

template<typename T>13
void RedBlackTree<T>::deleteElement(const T & key)
{
	Node *node_to_delete = search(root_, key);
	if (node_to_delete != nil_)
		deleteNodeFromRBTree(node_to_delete);
}

template<typename T>
void RedBlackTree<T>::writeTreeForVisualisation() const
{
	ofstream f("graph1.gv");
	f << "digraph structs{\n";
	writeTreeNodeInformation(f, root_);
	writeTreeNodeLink(f, root_);
	f << "}";
	f.close();
}

template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
	deleteRedBlackTree(root_);
	delete nil_;
}
