//============================================================================
//Dictionary stores keywords & its meanings. Provide facility for
//Adding new keywords. Provide facility to display whole data sorted in ascending or
//descending order. Also find how many maximum comparisons may
//require for finding any keyword. Use Height balance tree and find the
//complexity for finding a keyword.
//============================================================================

#include <iostream>
using namespace std;
int cnt = 0;

class Node {
	string key;
	string meaning;
	Node *left;
	Node *right;
	int height;
public:
	Node() {
		key = "";
		meaning = "";
		left = NULL;
		right = NULL;
		height = 0;
	}

	Node(string key, string meaning) {
		this->key = key;
		this->meaning = meaning;
		left = right = NULL;
		height = 1;
	}

	friend class AVL;
};

class AVL {
	Node *root;
public:

	AVL() {
		root = NULL;
	}

	void insert(string key, string meaning) {
		this->root = insert(root, key, meaning);
	}

	void printInorder() {
		inorder(root);
	}

	void printPreorder() {
		preorder(root);
	}
    
	string search(string key) {
    return searchUtil(root, key);
	}

private:
	int height(Node *node) {
		if (node == NULL) {
			return 0;
		}
		return node->height;
	}

	int getBF(Node *node) {
		if (node == NULL) {
			return 0;
		}
		return height(node->left) - height(node->right);
	}

	int max(int a, int b) {
		return (a > b ? a : b);
	}

	Node* rotateRight(Node *p) {
		Node *pl = p->left;
		Node *plrc = pl->right;

		//rotate
		pl->right = p;
		p->left = plrc;

		//update height
		p->height = max(height(p->left), height(p->right));
		pl->height = max(height(pl->left), height(pl->right));

		return pl;
	}

	Node* rotateLeft(Node *p) {
		Node *pr = p->right;
		Node *prlc = pr->left;

		//rotate
		pr->left = p;
		p->right = prlc;

		//update height

		p->height = max(height(p->left), height(p->right));
		pr->height = max(height(pr->left), height(pr->right));

		return pr;
	}

	//Insert a Node
	Node* insert(Node *node, string key, string meaning) {
		Node *new_node = new Node(key, meaning);

		if (node == NULL) {
			return new_node;
		}

		if (key < node->key) {
			node->left = insert(node->left, key, meaning);
		} else if (key > node->key) {
			node->right = insert(node->right, key, meaning);
		} else {
			return node;
		}

		//update height
		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getBF(node);

		//LL
		if (balance > 1 && key < node->left->key) {
			cout << "LL" << endl;
			return rotateRight(node);
		}

		if (balance < -1 && key > node->right->key) {
			cout << "RR" << endl;
			return rotateLeft(node);
		}

		//LR
		if (balance > 1 && key > node->left->key) {
			cout << "LR" << endl;
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		//RL
		if (balance < -1 && key < node->right->key) {
			cout << "RL" << endl;
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;

	}

	// Get min value from node
	Node* minValueNode(Node *node) {
		Node *current = node;
		while (current->left != NULL) {
			current = current->left;
		}

		return current;
	}

	//Inorder Traversal
	void inorder(Node *node) {

		if (node != NULL) {

			inorder(node->left);
			cout << node->key << " \t "<<node->meaning <<" - "<< getBF(node) <<endl;
			inorder(node->right);

		}
	}

	//Preorder Traversal
	void preorder(Node *node) {

		if (node != NULL) {

			cout << node->key << "" << getBF(node) << " | ";
			preorder(node->left);
			preorder(node->right);

		}
	}
    
	string searchUtil(Node* node, string key) {
		cnt++;
    	if (node == NULL) {
        	return "Word not found in the dictionary.";
    	}

    	if (key == node->key) {
       	 	return node->meaning;
    	} else if (key < node->key) {
        	return searchUtil(node->left, key);
    	} else {
        	return searchUtil(node->right, key);
    	}
	}
};

int main() {

	AVL avl;

	bool flag = true;
	int ch;
	string key, meaning,skey;

	while(flag){
		cout<<"\n======== AVL Dictionary ========="<<endl;
		cout<<"1. Add Words to Dictionary "<<endl;
		cout<<"2. Display Words( Ascending order) "<<endl;
		cout<<"3. Search a word "<<endl;
		cout<<"4. Exit.."<<endl;
		cout<<"\n Enter Your Choice: ";
		cin>>ch;

		switch(ch){
		case 1:
			cout<<"Enter word: ";
			cin>>key;
			cout<<"Enter Meaning: ";
			cin>>meaning;

			avl.insert(key, meaning);
			break;
		case 2:
			cout<<"Words in Ascending Order: "<<endl;
			cout<<"Word\tMeaning\tBF"<<endl;
			avl.printInorder();
			cout<<endl;
			break;

		case 3:
			cout<<"Enter the string to search "<<endl;
			cin>>skey;

			cout<<"meaning is: "<<avl.search(skey);
			cout<<"number of comparisons required: "<<cnt;
			cout<<endl;
			break;

		case 4:
			cout<<"ThankYou:)"<<endl;
			flag =false;
			break;

		default:
			cout<<"Invalid Input!!"<<endl;
			break;
		}


	}
	return 0;
}