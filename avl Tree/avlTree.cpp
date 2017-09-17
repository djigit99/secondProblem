#pragma once
#include "avlTree.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

void AVL_tree::right_rotation(node* &currect_node) {
	if (currect_node == NULL) {
		return;
	}
	node* new_right_tree = currect_node;
	node* new_root = currect_node->left;
	new_right_tree->left = currect_node->left ? currect_node->left->right : NULL;
	new_root->right = new_right_tree;
	change_height(new_right_tree);
	change_height(new_root);
	currect_node = new_root;
}
void AVL_tree::left_rotation(node* &currect_node) {
	if (currect_node == NULL) {
		return;
	}
	node* new_left_tree = currect_node;
	node* new_root = currect_node->right;
	new_left_tree->right = currect_node->right ? currect_node->right->left : NULL;
	new_root->left = new_left_tree;
	change_height(new_left_tree);
	change_height(new_root);
	currect_node = new_root;
}
void AVL_tree::left_right_rotation(node* &current_node) {
	left_rotation(current_node->left);
	right_rotation(current_node);
}
void AVL_tree::right_left_rotation(node* &current_node) {
	right_rotation(current_node->right);
	left_rotation(current_node);
}
int AVL_tree::get_height(node* &current_node) {
	if (current_node == NULL)
		return 0;
	return current_node->height;
}
void AVL_tree::change_height(node* &current_node) {
	current_node->height = std::max(get_height(current_node->left),
		get_height(current_node->right)) + 1;
}
int AVL_tree::get_delta(node* &current_node) {
	if (current_node == NULL)
		return 0;
	return get_height(current_node->left) - get_height(current_node->right);
}
node* AVL_tree::add(node* current_node, int value) {
	if (current_node == NULL) {
		return new node(value);
	}

	/*	Find the correct path (left, right, NAN) :
	when the current value more than node's value then go to right son,
	when the value less then go to left son
	otherwise break the route */
	if (current_node->value > value) {
		current_node->left = add(current_node->left, value);
	}
	else if (current_node->value < value) {
		current_node->right = add(current_node->right, value);
	}
	else
		return current_node;

	/* Change the height of current node */
	change_height(current_node);

	/* Check out delta of sons' height and do the appropriate rotation */
	int delta = get_delta(current_node);

	// Left Left Case
	if (delta > 1 && value < current_node->left->value)
		right_rotation(current_node);

	// Right Right Case
	if (delta < -1 && value > current_node->right->value)
		left_rotation(current_node);

	// Left Right Case
	if (delta > 1 && value > current_node->left->value) {
		left_right_rotation(current_node);
	}

	// Right Left Case
	if (delta < -1 && value < current_node->right->value) {
		right_left_rotation(current_node);
	}
	return current_node;
}
void AVL_tree::add(int value) {
	root = add(root, value);
}
node* AVL_tree::min_value(node* current_node) {
    if (current_node == NULL) {
        return NULL;
    }
    while (current_node->left != NULL) {
        current_node = current_node->left;
    }
    return current_node;
}
node* AVL_tree::delete_node(node* current_node, int &value) {
    if (current_node == NULL)
        return NULL;

	/*	Find the correct path (left, right, NAN) :
	when the current value more than node's value then go to right son,
	when the value less then go to left son
	otherwise break the route */
    if (current_node->value > value) {
        current_node->left = delete_node(current_node->left, value);
    }
    else if (current_node->value < value) {
        current_node->right = delete_node(current_node->right, value);
    }
    else {
        if (current_node->left == NULL) {
            node* tmp = current_node->right;
            delete current_node;
            current_node = tmp;
        }
        else if (current_node->right == NULL) {
            node* tmp = current_node->left;
            delete current_node;
            current_node = tmp;
        }
        else {
            node* tmp = min_value(current_node->right);
            current_node->value = tmp->value;
            current_node->right = delete_node(current_node->right, tmp->value);
        }
    }

    if (current_node == NULL)
      return NULL;

    /* Change the height of current node */
	change_height(current_node);

	/* Check out delta of sons' height and do the appropriate rotation */
	int delta = get_delta(current_node);

	// Left Left Case
	if (delta > 1 && get_delta(current_node->left) >= 0)
		right_rotation(current_node);

	// Right Right Case
	if (delta < -1 && get_delta(current_node->right) <= 0)
		left_rotation(current_node);

	// Left Right Case
	if (delta > 1 && get_delta(current_node->left) < 0) {
		left_right_rotation(current_node);
	}

	// Right Left Case
	if (delta < -1 && get_delta(current_node->right) > 0) {
		right_left_rotation(current_node);
	}

	return current_node;

}
void AVL_tree::delete_node(int value) {
    root = delete_node(root, value);
}
/* Functions for testing */
void AVL_tree::postorder(node* p, int indent = 0)
{
    if(p != NULL) {
        if(p->right) {
            postorder(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->value << "\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            postorder(p->left, indent+4);
        }
    }
}

void AVL_tree::print_tree() {
    postorder(root);
}




