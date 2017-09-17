#include <iostream>
#include "avlTree.h"

using namespace std;


int main() {
	AVL_tree tree;
	for (int i = 0; i < 100; i+=5) {
        tree.add(i);
	}
    tree.delete_node(5);
    tree.delete_node(10);
    tree.delete_node(20);
    tree.delete_node(30);
	tree.print_tree();
	system("pause");
	return 0;
}
