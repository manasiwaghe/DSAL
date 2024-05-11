	//Delete a node AVL

    
	// Node* remove(Node *root, string key) {
	// 	if (root == NULL) {
	// 		return root;
	// 	}

	// 	if (key < root->key) {
	// 		root->left = remove(root->left, key);
	// 	} else if (key > root->key) {
	// 		root->right = remove(root->right, key);

	// 	} else {
	// 		if ((root->left == NULL) || (root->right == NULL)) {
	// 			Node *temp = root->left ? root->left : root->right;

	// 			if (temp == NULL) {
	// 				temp = root;
	// 				root = NULL;

	// 			} else {
	// 				*root = *temp;
	// 			}

	// 			free(temp);
	// 		} else {
	// 			Node *temp = minValueNode(root->right);
	// 			root->key = temp->key;
	// 			root->meaning = temp->meaning;
	// 			root->right = remove(root->right, temp->key);
	// 		}
	// 	}

	// 	if (root == NULL) {
	// 		return root;
	// 	}

	// 	root->height = 1 + max(height(root->left), height(root->right));

	// 	int balance = getBF(root);

	// 	//LL
	// 	if (balance > 1 && getBF(root->left) >= 0) {
	// 		return rotateRight(root);
	// 	}

	// 	//RR
	// 	if (balance < -1 && getBF(root->right) < 0) {
	// 		return rotateLeft(root);
	// 	}

	// 	//LR
	// 	if (balance > 1 && getBF(root->left) < 0) {
	// 		root->left = rotateLeft(root->left);
	// 		return rotateRight(root);
	// 	}

	// 	//RL
	// 	if (balance < -1 && getBF(root->right) > 0) {
	// 		root->right = rotateRight(root->right);
	// 		return rotateLeft(root);
	// 	}

	// 	return root;
	// }