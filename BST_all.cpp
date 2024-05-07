/* Construct binary search tree. Provide facility for adding new entries, deleting any 
element. 
Provide facility to display whole data sorted in ascending and descending order using non-recursive traversal.
Search an element present in a tree and display number of comparisons required to search.
Change a tree so that the roles of the left and right pointers are swapped at every node.
Display in level order
Find Minimum and maximum data value in tree.*/

#include <iostream>
#define size 20
using namespace std;

class node {
public:
    int data;
    node* left, * right;
};

class stack{
	private:
		int top;
		node* st[size];

		stack(){
			top=-1;
		}

		node* Top(){
			return st[top];
		}

		bool isempty(){
			if(top==-1){
				return 1;
			}
			return 0;
		}

		bool isfull(){
			if(top == size-1){
				return 1;
			}
			return 0;
		}
		 
		node* pop(){
			if(top == -1){
				cout<<"stack is empty!";
			}
			else{
				node* popped = st[top];
				top--;
				return popped;
			}
		}

		void push(node* k){
			if(top == size-1){
				cout<<"stack is full!";
			}
			else{
				top++;
				st[top] = k;
			}
		}

	public:
		friend class BSTree;
	
};

class BSTree {
public:
    node* Node;

    BSTree() {
        Node = NULL;
    }
    node* create_BST(node* root);
    void insertnodes(node* root, node* newnode);
    void inorder(node* root);
    void minElement(node* root);
    void maxElement(node* root);
    void searchNode(node* root, int key);
    void swap(node* root);
    int height(node* root);
    node* deleteNode(node* root, int key);
    void descending(node* root);
    void level_print(node* root, int level);
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

void BSTree::inorder(node* root) {
    stack s;
	node *curr = root;
	while(curr!=NULL || s.isempty()==false){
		while(curr!= NULL){
			s.push(curr);
			curr = curr->left;
		}
		curr = s.Top();
		s.pop();
		cout<<curr->data<<" ";
		curr = curr->right;
	}
}

void BSTree::descending(node* root) {
    stack s;
	node *curr = root;
	while(curr!=NULL || s.isempty()==false){
		while(curr!= NULL){
			s.push(curr);
			curr = curr->right;
		}
		curr = s.Top();
		s.pop();
		cout<<curr->data<<" ";
		curr = curr->left;
	}
}

void BSTree::searchNode(node* root, int key){
	bool flag=false;
    int cmp = 0;
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
        cmp++;
	}
	if(flag==true){
		cout<<"Node is present!";
        cout<<"\nNumber of comparisons required : "<<cmp;
	}
	else{
		cout<<"Node is not present!";
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

node* BSTree::deleteNode(node* root, int k){
    // Base case
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in the left subtree
    if (k < root->data) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in the right subtree
    else if (k > root->data) {
        root->right = deleteNode(root->right, k);
        return root;
    }

    // If key is same as root's key, then this is the node to be deleted
    // Node with only one child or no child
    if (root->left == NULL) {
        node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        node* temp = root->left;
        delete root;
        return temp;
    }

    // Node with two children: Get the inorder successor (smallest
    // in the right subtree)
    node* succParent = root;
    node* succ = root->right;
    while (succ->left != NULL) {
        succParent = succ;
        succ = succ->left;
    }

    // Copy the inorder successor's content to this node
    root->data = succ->data;

    // Delete the inorder successor
    if (succParent->left == succ)
        succParent->left = succ->right;
    else
        succParent->right = succ->right;
    
    delete succ;
    return root;
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

int main() {
    BSTree b;
    node* newnode;
    node* root = NULL;
    int ch, n;
    do {
        cout << "\nOperations: \n1.create \n2.insert \n3.ascending order \n4.descending order \n5.search node \n6. delete node \n7.swap the nodes \n8.display in level order \n9.minimum and maxmimum value ";
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
            b.inorder(root);
            break;

        case 4:
            b.descending(root);
            break;

        case 5:
        	int key;
        	cout<<"Enter the node you want to search: ";
        	cin>>key;
        	b.searchNode(root,key);
        	break;

        case 6:
            int del;
            cout<<"Enter the node you want to delete: ";
            cin>>del;
            b.deleteNode(root, del);
            break;

        case 7:
            cout<<"before swapping: ";
            b.inorder(root);
            b.swap(root);
            cout<<"\nafter swapping: ";
            b.inorder(root);
            break;

        case 8:
            int h = b.height(root);
            int i;
            for (i = 1; i <= h; i++) {
                b.level_print(root, i);
                cout<<endl;
            }
            break;

        case 9:
            b.minElement(root);
            b.maxElement(root);
            break;
        }

    } while (ch < 12);

    return 0;
}