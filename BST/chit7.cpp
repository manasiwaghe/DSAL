/*Beginning with an empty binary search tree. Construct the binary search tree by inserting 
the values in given order. After constructing binary search tree perform following 
operations 1) Find numbers of node in longest path 2) Minimum and maximum data value 
found in tree 3) Change a tree so that the roles of the left and right pointers are swapped at 
every node. 4) Display in level order*/

#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    int data;
    node* left, * right;
};

class BSTree {
public:
    node* Node;

    BSTree() {
        Node = NULL;
    }
    node* create_BST(node* root);
    void insertnodes(node* root, node* newnode);
    void minElement(node* root);
    void maxElement(node* root);
    void swap(node* root);
    int height(node*);
    void level_print(node* root, int level);
    void inorder(node*);

};

node* BSTree::create_BST(node* root) {
    node* newnode = new node;
    cout << "Enter data for root: ";
    cin >> newnode->data;
    newnode->left = NULL;
    newnode->right = NULL;

    if (root == NULL) {
        root = newnode;
        cout << "Root created successfully\n";
    }
    else {
        cout << "Root already exists\n";
    }

    return root;
}

void BSTree::insertnodes(node* root, node* newnode) {
    if (newnode->data < root->data) {
        if (root->left == NULL) {
            root->left = newnode;
        }
        else {
            root=root->left;
            insertnodes(root,newnode);
        }
    }
    else {
        if (root->right == NULL) {
            root->right = newnode;
        }
        else {
            root=root->right;
            insertnodes(root,newnode);
        }
    }
}

void BSTree::minElement(node* root){
	int mini;
	while(root->left!= NULL){
		root=root->left;
		mini=root->data;
	}
	cout<<"Minimum value is: "<<mini;
}

void BSTree::maxElement(node* root){
	int maxi;
	while(root->right!= NULL){
		root=root->right;
		maxi=root->data;
	}
	cout<<"\nMaximum value is: "<<maxi;
}

void BSTree::swap(node* root){
	if(root){
		node* temp;
		temp=root->left;
		root->left=root->right;
		root->right=temp;
		swap(root->left);
		swap(root->right);
	}
}

int BSTree::height(node* root){
    if (root == NULL)
        return 0;
    else {
        int lDepth = height(root->left);
        int rDepth = height(root->right);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void BSTree::level_print(node* root, int level){
    if (root == NULL)
        return;
    if (level == 1)
        cout<<root->data<<" ";
    else if (level > 1) {
        level_print(root->left, level - 1);
        level_print(root->right, level - 1);
    }
}

void BSTree::inorder(node* root) {
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main() {
    BSTree b;
    node* newnode;
    node* root = NULL;
    int ch, n;
    do {
        cout << "\nOperations: \n1.create \n2.insert \n3.numbers of node in longest path \n4.minimum value \n5.maximum value \n6.display in level order \n7.swap left-right nodes";
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            root = b.create_BST(root);
            break;
        case 2:
            cout << "How many nodes do you want to insert? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                newnode = new node;

                cout << "Enter data: ";
                cin >> newnode->data;
                newnode->left = NULL;
                newnode->right = NULL;

                b.insertnodes(root, newnode);
            }
            break;
        case 3:
            cout<<"the maximum numbers of node in longest path: "<<b.height(root);
            break;
        case 4:
        	b.minElement(root);
        	break;
        case 5:
        	b.maxElement(root);
        	break;
        case 6:
            int h = b.height(root);
            int i;
            for (i = 1; i <= h; i++) {
                b.level_print(root, i);
                cout<<endl;
            }
            break;
        case 7:
            cout<<"before swapping: ";
            b.inorder(root);
            b.swap(root);
            cout<<"\nafter swapping: ";
            b.inorder(root);
            break;
        }

    } while (ch < 12);

    return 0;
}