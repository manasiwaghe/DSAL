/*
Beginning with an empty binary tree, construct binary tree by inserting the values in the 
order given. After constructing a binary tree perform following operations on it-
  Perform postorder, Inorder, Preorder recursive traversal 
  postorder, Inorder, Preorder non-recursive traversal 
  Find the height of tree 
  Count number of leaves, number of internal nodes.
  Find mirror image of a tree
  Level wise printing */

#include<iostream>
using namespace std;
#define size 20

static int intN=0,extN=0;
int arr[10];

class node{
	private:
     	int data;
     	node *left;
     	node *right;
	public:
		friend class bt;
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
		friend class bt;
	
};

class bt{
public:
	node *root;

	bt(){
		root=NULL;
	}

	node* create(node*);
	void insert(node*);
	void postorder_rec(node*);
	void inorder_rec(node*);
    void preorder_rec(node*);
    void postorder_nonrec(node*);
	void inorder_nonrec(node*);
    void preorder_nonrec(node*);
    void count_nodes(node*);
    int height(node*);
    void mirror(node*);
    void level_print(node*, int);
};

node* bt::create(node *root)
{
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

void bt::insert(node *root)
{
	int i,flag,cnt,front,rear;
	node *q[size],*newnode;

	rear=front=0;

	q[rear++]=root;

	cout<<"How many nodes? ";
	cin>>cnt;

	i=0;
	flag=1;

	while(i<cnt){

		if(flag==1){
			newnode= new node;
			cout<<"\nEnter data of node: ";
			cin>>newnode->data;
			newnode->left=NULL;
			newnode->right=NULL;
		}
		if(root->left==NULL){
			root->left=newnode;
			q[rear++]=root->left;
			i++;
			flag=1; //node is assigned
		}
		else if(root->right==NULL){
			root->right=newnode;
			q[rear++]=root->right;
			i++;
			flag=1; //node is assigned
		}
		else{
			front++;
			root=q[front];
			flag=0;
		}
		cout<<"Node inserted :"<<newnode->data;
	}
}

void bt::inorder_nonrec(node *root)
{
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

void bt::inorder_rec(node *root)
{
    if(root == NULL)
        return;
    inorder_rec(root->left);
    cout << root->data << " ";
    inorder_rec(root->right);
}

void bt::preorder_nonrec(node *root)
{
	if (root == NULL)
        return;
 
    stack s;
    s.push(root);
 
    while (s.isempty() == false) {
        node* curr = s.Top();
        cout<<curr->data;
        s.pop();
 
        // Push right and left children of the popped node to stack
        if (curr->right)
            s.push(curr->right);
        if (curr->left)
            s.push(curr->left);
    }
}

void bt::preorder_rec(node *root)
{
    if(root == NULL)
        return;
    
    cout << root->data << " ";
    preorder_rec(root->left);
    preorder_rec(root->right);
}

void bt::postorder_nonrec(node *root){
	if (root == NULL) 
        return; 

    stack s1, s2; 
  
    // push root to first stack 
    s1.push(root); 
    node* curr; 
  
    // Run while first stack is not empty 
    while (!s1.isempty()) { 
        // Pop an item from s1 and push it to s2 
        curr = s1.Top(); 
        s1.pop(); 
        s2.push(curr); 
		if (curr->left) 
            s1.push(curr->left); 
        if (curr->right) 
            s1.push(curr->right); 
    } 

    // Print all elements of second stack 
    while (!s2.isempty()) { 
        curr = s2.Top(); 
        s2.pop(); 
        cout << curr->data << " "; 
    }  
}

void bt::postorder_rec(node *root){
    if(root!=NULL){
        postorder_rec(root->left);
        postorder_rec(root->right);
        cout<<" "<<root->data;
    }  
}

int bt::height(node* root){
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

void bt::count_nodes(node* root){
	if(root){
		if(root->left || root->right){
			intN++;
		}
		else{
			extN++;
		}
		count_nodes(root->left);
		count_nodes(root->right);
	}
}

void bt::mirror(node* root){
	if(root){
		node* temp=root->left;
		root->left=root->right;
		root->right=temp;

		mirror(root->left);
		mirror(root->right);
	}
}

void bt::level_print(node* root, int level){
    if (root == NULL)
        return;
    if (level == 1)
        cout<<root->data<<" ";
    else if (level > 1) {
        level_print(root->left, level - 1);
        level_print(root->right, level - 1);
    }
}

int main()
{
	bt b;
	node *root = NULL;
	int ch;
	do
	{
		cout<<"\n1.create\n2.insert\n3.inorder\n4.preorder\n5.postorder\n6.height of tree\n7.count internal and external nodes\n8.Level wise printing\n9.mirror image of tree";
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:
                    root = b.create(root);
				    break;
			case 2:
                    b.insert(root);
				    break;
			case 3:
                    cout<<"\ninorder recursive traversal is";
					b.inorder_rec(root);
                    cout<<"\ninorder non-recursive traversal is";
                    b.inorder_nonrec(root);
					break;
			case 4:
                    cout<<"\npreorder recursive traversal is";
					b.preorder_rec(root);
                    cout<<"\npreorder non-recursive traversal is";
					b.preorder_nonrec(root);
					break;
			case 5:
                    cout<<"\npostorder recursive traversal is";
					b.postorder_rec(root);
                    cout<<"\npostorder non-recursive traversal is";
					b.postorder_nonrec(root);
					break;
			case 6:
                    cout<<"height of the tree is: "<<b.height(root);
                    break;
            case 7:
                    b.count_nodes(root);
                    cout<<"Number of internal nodes: "<<intN;
			   	    cout<<"\nNumber of external nodes: "<<extN<<endl;
                    break;
            case 8:
			  		{
					int h = b.height(root);
                    int i;
                    for (i = 1; i <= h; i++) {
                        b.level_print(root, i);
                        cout<<endl;
                    }
                    break;
					}

            case 9:
                    cout<<"Inorder before mirroring: ";
                    b.inorder_rec(root);
                    b.mirror(root);
                    cout<<"Inorder after mirroring: ";
                    b.inorder_rec(root);
                    break;
		}
	}while(ch!=0);
	return 0;
}