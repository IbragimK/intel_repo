#ifndef _TREE_H_
#define _TREE_H_

typedef char* value_t;

typedef struct node {
	value_t value;
	struct node* left, right;
} node_t;

/* Сreates new tree node with a set value and
 * pointers to the left and right
 * subtrees.
 * Returns created node.
 */
node_t* new_node(value_t value, node_t* left, node_t* right) {
	node_t* node;
	
	if (node) {
		node->value = value;
		node->left = left;
		node->right = right;
	}

	return node;
}

/* Inserts new node with value to the tree end */
void tree_insert(tree_t** root, value_t value) {
	if (*root) {
		if (value < (*root)->value) {
			tree_insert(&((*root)->left), value);
		} else {
			tree_insert(&((*root)->right), value);
		}
	} else {
		*root = new_node(value, NULL, NULL);
	}
}

/* Deletes tree */
void delete_tree(node_t* tree) {
	if (tree) {
		free(tree);
		delete_tree(tree->left);
		delete_tree(tree->right);
	}
}

/* Find tree node with with a set root and value. 
 * Returns node if found or NULL otherwise
 */
node_t* find(node_t* root, value_t value) {
	if (root) {
		if (root->value == value) {
			return root->value;
		} else if (root->value > value) {
			return find(root->left, value);
		} else if (root->value < value) {
			return find(root->right, value);
		}
	} else {
		return NULL;
	}
}

#endif
