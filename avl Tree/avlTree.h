#pragma once

struct node {
	int value;
	node* left;
	node* right;
	int height;

	node() {
		left = right = 0;
		height = 1;
	}
	node(int new_value) {
		left = right = 0;
		value = new_value;
		height = 1;
	}
};
class AVL_tree {
	node* root;
	void right_rotation(node* &);
	void left_rotation(node* &);
	void left_right_rotation(node* &);
	void right_left_rotation(node* &);
	int get_height(node* &);
	void change_height(node* &);
	int get_delta(node* &);
public:
	AVL_tree() : root(0) {}
	AVL_tree(int root_value) {
		root = new node(root_value);
	}

	node* add(node* current_node, int value);
	void add(int value);
	node* min_value(node*);
	node* delete_node(node*, int&);
	void delete_node(int);
	void postorder(node*, int);
	void print_tree();
};
