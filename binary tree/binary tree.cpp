// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "_binary_tree.h"
#include "red_black_tree.h"
//#include <vld.h>
double timeLapsed(clock_t start_time)
{
	return double(clock() - start_time) / CLOCKS_PER_SEC;
}
template <typename T>
void visualize(const RedBlackTree<T>& rb_tree)
{
	sf::VideoMode vm;
	vm = vm.getDesktopMode();
	clock_t start_rendering = clock();
	rb_tree.writeTreeForVisualisation();
	system("gvgen -dh3 | dot  -Tpng -Gsize=16,9\! -Gdpi=120 -Gratio=fill -otree.png graph1.gv");
	double time_for_render = timeLapsed(start_rendering);
	cout << "Image generated in " << time_for_render / CLOCKS_PER_SEC << endl;
	start_rendering = clock();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Red Black Tree Visualisation", sf::Style::Default, settings);

	time_for_render = timeLapsed(start_rendering);
	cout << "Window opened in " << time_for_render << endl;
	start_rendering = clock();
	sf::Texture tree_image;
	tree_image.setSmooth(true);
	tree_image.loadFromFile("tree.png");
	time_for_render = timeLapsed(start_rendering);
	cout << "Image opened in " << time_for_render << endl;
	sf::Sprite tree_;
	int n;
	tree_.setTexture(tree_image);
	double wd = tree_.getLocalBounds().width, hg = tree_.getLocalBounds().height;
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
		}
		window.clear(sf::Color::Black);
		;
		tree_.setScale(window.getSize().x / wd, window.getSize().y / hg);
		window.draw(tree_);
		window.display();
	}
}
int main()
{
	RedBlackTree<int> RBtree;
	vector<int> numbers_in_tree;
	char input = 0;
	do
	{
		system("cls");
		if (!numbers_in_tree.empty())
		{
			for (auto x : numbers_in_tree)
				cout << x << ' ';
			cout << endl;
		}
		cout << "Input a to add element, d to delete, v - to visualize tree (q to quit): ";
		cin >> input;
		input = tolower(input);
		switch (input)
		{
		case 'a':
		{
			int number_for_insert, number_of_numbers = 1;
			cout << "Input number of numbers: ";
			cin >> number_of_numbers;
			cout << "Input "<<number_of_numbers<<" numbers to insert:\n";
			for (int i = 0; i < number_of_numbers; i++)
			{
				cin >> number_for_insert;
				if (!cin)
				{
					cin.clear();
					while (cin.get() != '\n');
				}
				RBtree.insertElement(number_for_insert);
			/*	if (number_for_insert == 62)
					visualize(RBtree);*/
				numbers_in_tree.push_back(number_for_insert);
			}
			break;
		}
		case 'd':
		{
			int number_to_delete;
			cout << "Input number to delete: ";
			cin >> number_to_delete;
			RBtree.deleteElement(number_to_delete);
			auto find_el = find(numbers_in_tree.begin(), numbers_in_tree.end(), number_to_delete);
			if (find_el!=numbers_in_tree.end())
				numbers_in_tree.erase(find(numbers_in_tree.begin(), numbers_in_tree.end(), number_to_delete));
			break;
		}
		case 'v':
		{
			cout <<"Number of leaves: "<< RBtree.getNumberOfLeaves() << endl;
			cout << "Tree height: " << RBtree.getTreeHeight() << endl;
			visualize(RBtree);
			break;
		}
		default:
			break;
		}
	} while (input != 'q');
	system("pause");
	return 0;
}

