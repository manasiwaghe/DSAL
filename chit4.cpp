/*Beginning with an empty binary tree, construct binary tree by inserting the values in the 
order given. After constructing a binary tree perform following operations on it-
• Perform non-recursive inorder traversal, recursive postorder
• Level wise printing
• Display and count leaf nodes
• Display and count internal nodes*/

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
    int height(node*);
    void level_print(node*, int);
    void count_nodes(node*);
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

void bt::postorder(node *root){
	if (root == NULL) 
        return; 
    
	postorder(root->left);
	postorder(root->right);
    cout<<"  "<<root->data;

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
	int ch;
	do
	{
		cout<<"\n1.create\n2.insert\n3.inorder\n4.postorder\n5.count number of internal and external nodes\n6.print level-wise";
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
                    cout<<"postorder traversal is\n";
					b.postorder(b.root);
					break;
			case 5:
			       b.count_nodes(b.root);
			   	   cout<<"Number of internal nodes: "<<intN;
			   	   cout<<"\nNumber of external nodes: "<<extN<<endl;
			       break;
            case 6:
                    int h = b.height(b.root);
                    int i;
                    for (i = 1; i <= h; i++) {
                        b.level_print(b.root, i);
                        cout<<endl;
                    }
    }

	}while(ch!=0);
	return 0;
}