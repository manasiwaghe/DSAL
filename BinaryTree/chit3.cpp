/*Beginning with an empty binary tree, construct binary tree by inserting the values in the 
order given. After constructing a binary tree perform following operations on it-
• Perform inorder, recursive traversal 
• Preorder, post-order non-recursive traversal
• Find mirror image of a tree*/

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
    void mirror(node*);
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
    if(root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void bt::preorder(node *root)
{
    
    if (root == NULL)
        return;
 
    stack s;
    s.push(root);
 
    while (s.isempty() == false) {
        node* curr = s.Top();
        cout<<curr->data<<" ";
        s.pop();
 
        // Push right and left children of the popped node to stack
        if (curr->right)
            s.push(curr->right);
        if (curr->left)
            s.push(curr->left);
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

void bt::mirror(node* root){
	if(root){
		node* temp=root->left;
		root->left=root->right;
		root->right=temp;

		mirror(root->left);
		mirror(root->right);
	}
}

int main()
{
	bt b;
	int ch;
	do
	{
		cout<<"\n1.create\n2.insert\n3.inorder\n4.preorder\n5.postorder\n6.find mirror image of tree";
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
			       b.mirror(b.root);
                   cout<<"preorder for mirrored tree is: ";
                   b.preorder(b.root);
			       break;
		}
	}while(ch!=0);
	return 0;
}