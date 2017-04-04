// binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include <vld.h>
#include "_binary_tree.h"

int main()
{
	srand(time(0));
	binaryTree<int> tr;
	/*for (int i = 0; i < 5; i++)
	{
		int a = rand() % 50;
		cout << a << ' ';
		tr.add_node(a);
	}*/
	tr.add_node(12);
	tr.add_node(5);
	tr.add_node(2);
	tr.add_node(9);
	tr.add_node(18);
	tr.add_node(19);
	tr.add_node(15);
	tr.add_node(17);
	tr.add_node(13);
	cout << endl;
	tr.show();
	int n;
	cin >> n;
	tr.delete_node(n);
	tr.show();
	//cout << tr.min() << ' '<<tr.max()<<endl;
	system("pause");
    return 0;
}

