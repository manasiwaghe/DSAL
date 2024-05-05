/*Beginning with an empty binary tree, construct binary tree by inserting the values in the 
order given. After constructing a binary tree perform following operations on it-
• Perform preorder recursive traversal 
• Postorder, Inorder non-recursive traversal
• Count number of leaves, number of internal nodes.*/

#include<iostream>
#define size 20
using namespace std;

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

	void create();
	void insert(node*);
	void postorder(node*);
	void inorder(node*);
    void preorder(node*);
    void count_nodes(node*);
    // void swap(node*);
    // void copy_tree(node*);
};

void bt::create()
{
	node *curr,*temp;
	curr=new node;
    
    cout<<"enter data:";
	cin>>curr->data;
	curr->left=curr->right=NULL;
		if(root==NULL){
			root=curr;
		}
		else{
			temp=root;
			while(1)
			{
					if(temp->left==NULL)
					{
						temp->left=curr;
						break;
					}
					else if(temp->right==NULL)
					{
						temp->right=curr;
						break;
					}
					else
					{
						temp=temp->left;
					}
			}
		}
		cout<<"Node created :"<<curr->data;
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

void bt::inorder(node *root)
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

void bt::preorder(node *root)
{
	if(root!=NULL)
	{
		cout<<"  "<<root->data;
		preorder(root->left);
		preorder(root->right);
	}
}

void bt::postorder(node *root){
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

// void bt::swap(node* root){
// 	if(root){
// 		node* temp=root->left;
// 		root->left=root->right;
// 		root->right=temp;

// 		swap(root->left);
// 		swap(root->right);
// 	}
// }

// void bt::copy_tree(node* root){
// 	node* root1;
// 	if(root){
// 		root1=root;
// 		root1->left=root->left;
// 		root1->right=root->right;

// 		copy_tree(root->left);
// 		copy_tree(root->right);
// 	}
// 	preorder(root1);
// }

int main()
{
	bt b;
	int ch;
	do
	{
		cout<<"\n1.create\n2.insert\n3.inorder\n4.preorder\n5.postorder\n6.count number of internal and external nodes";
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:
                    b.create();
				    break;
			case 2:
                    b.insert(b.root);
				    break;
			case 3:
                    cout<<"inorder traversal is\n";
					b.inorder(b.root);
					break;
			case 4:
                    cout<<"preorder traversal is\n";
					b.preorder(b.root);
					break;
			case 5:
                    cout<<"postorder traversal is\n";
					b.postorder(b.root);
					break;
			case 6:
			       b.count_nodes(b.root);
			   	   cout<<"Number of internal nodes: "<<intN;
			   	   cout<<"\nNumber of external nodes: "<<extN<<endl;
			       break;
		}
	}while(ch!=0);
	return 0;
}