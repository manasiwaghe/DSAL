/*Construct binary search tree. Provide facility for adding new entries. Provide facility to 
display whole data sorted in descending order using non-recursive traversal.
Find Minimum and maximum data value in tree. Also find how many maximum 
comparisons may require for finding any keyword.*/

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
    void descending(node* root);
    void minElement(node* root);
    void maxElement(node* root);
    void searchNode(node* root, int key);
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

void BSTree::descending(node* root) {
    stack<node*> s;
    node* curr = root;

    while (curr != NULL || !s.empty()) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr->right;
        }

        curr = s.top();
        s.pop();

        cout << curr->data << " ";

        curr = curr->left;
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

void BSTree::searchNode(node* root, int key){
	bool flag=false;
	while(root!=NULL){
		if(root->data==key){
			flag=true;
			break;
		}
		else if(root->data<key){
			root=root->right;
		}
		else{
			root=root->left;
		}
	}
	if(flag==true){
		cout<<"Node is present!";
	}
	else{
		cout<<"Node is not present!";
	}
}

int main() {
    BSTree b;
    node* newnode;
    node* root = NULL;
    int ch, n;
    do {
        cout << "\nOperations: \n1.create \n2.insert \n3.descending order \n6.minimum value \n7.maximum value \n8.search node";
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
            b.descending(root);
            break;
        case 6:
        	b.minElement(root);
        	break;
        case 7:
        	b.maxElement(root);
        	break;
        case 8:
        	int key;
        	cout<<"Enter the node you want to search: ";
        	cin>>key;
        	b.searchNode(root,key);
        	break;
        }

    } while (ch < 12);

    return 0;
}