/* Construct binary search tree. Provide facility for adding new entries, deleting any 
element. Provide facility to display whole data sorted in ascending order using non-recursive traversal. Search an element present in a tree and display number of 
comparisons required to search.*/

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
    // void minElement(node* root);
    // void maxElement(node* root);
    void searchNode(node* root, int key);
    // void swap(node* root);
    int height(node* root);
    node* deleteNode(node* root, int key);
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

node* maxValue(node *root){
    if(root==NULL){
        return 0;
    }
    node *temp =root;
    while(temp->right!=NULL){
        temp= temp->right;
    }
    return temp;
}

node* BSTree::deleteNode(node* root, int key){
    if(root==NULL)
            return root;
        
        if(root->data ==key){
            // for 0 child
            if(root->left==NULL && root->right ==NULL){
                delete root;
                return NULL;
            }
            // for 1 child
            if(root->left!=NULL && root->right ==NULL){
                node *temp = root->left;
                delete root;
                return temp;
            }
             if(root->left==NULL && root->right !=NULL){
                node *temp = root->right;
                delete root;
                return temp;
            }
            // for 2 child
            if(root->left!=NULL && root->right!=NULL){
            int maxi = maxValue(root->left)->data;
              root->data = maxi;
              root->left = deleteNode(root->left,maxi);
              return root;
            }
        }
        else if(root->data >key){
            root->left= deleteNode(root->left,key);
            return root;
        }
        else{
            root->right = deleteNode(root->right,key);
            return root;
        }
        return root;
}

int main() {
    BSTree b;
    node* newnode;
    node* root = NULL;
    int ch, n;
    do {
        cout << "\nOperations: \n1.create \n2.insert \n3.inorder \n4.search node \n5.delete node ";
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
        	int key;
        	cout<<"Enter the node you want to search: ";
        	cin>>key;
        	b.searchNode(root,key);
        	break;
        case 5:
            int del;
            cout<<"Enter the node you want to delete: ";
            cin>>del;
            b.deleteNode(root, del);
            break;
        }

    } while (ch < 12);

    return 0;
}