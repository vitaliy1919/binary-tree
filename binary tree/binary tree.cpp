// binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "_binary_tree.h"

int main()
{
	srand(time(0));
	binaryTree<int> tr;
	for (int i = 0; i < 5; i++)
	{
		int a = rand() % 5;
		cout << a << ' ';
		tr.addNode(a);
	}
	cout << endl;
	tr.show();
	system("pause");
    return 0;
}

