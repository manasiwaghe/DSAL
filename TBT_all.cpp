/* Create an inordered threaded binary search tree for integer value. Perform preorder and inorder 
traversals and deletion of a node. Display smallest and largest value in it.
Note: Display lbit, rbit for every node*/

#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    Node *left, *right;
    int info;
    bool lthread;
    bool rthread;

public:
    friend class tbt;
};

class tbt
{
public:
    Node* insert(Node *root, int ikey)
    {
        // Searching for a Node with given value
        Node *ptr = root;
        Node *par = NULL; // Parent of key to be inserted
        while (ptr != NULL)
        {
            // If key already exists, return
            if (ikey == (ptr->info))
            
            {
                printf("Duplicate Key !\n");
                return root;
            }

            par = ptr; // Update parent pointer

            // Moving on left subtree.
            if (ikey < ptr->info)
            {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            }

            // Moving on right subtree.
            else
            {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        // Create a new node
        Node *tmp = new Node;
        tmp->info = ikey;
        tmp->lthread = true;
        tmp->rthread = true;
 
        if (par == NULL)
        {
            root = tmp;
            tmp->left = NULL;
            tmp->right = NULL;
        }
        else if (ikey < (par->info))
        {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        }
        else
        {
            tmp->left = par;
            tmp->right = par->right;
            par->rthread = false;
            par->right = tmp;
        }

        return root;
    }

    // Returns inorder successor using rthread
    Node *inorderSuccessor(Node *ptr)
    {
        // If rthread is set, we can quickly find
        if (ptr->rthread == true)
            return ptr->right;

        // Else return leftmost child of right subtree
        ptr = ptr->right;
        while (ptr->lthread == false)
            ptr = ptr->left;
        return ptr;
    }

    // Printing the threaded tree
    void inorder(Node *root)
    {
        if (root == NULL)
            cout<<"Tree is empty";

        // Reach leftmost node
        Node *ptr = root;
        while (ptr->lthread == false)
            ptr = ptr->left;

        // One by one print successors
        while (ptr != NULL)
        {
            cout<<"  ||"<<ptr->lthread<<"| "<< ptr->info<<" |"<<ptr->rthread<<"||  ";
            ptr = inorderSuccessor(ptr);
        }
    }

    void preorder(Node *root)
    {
        Node *ptr;
        if (root == NULL)
        {
            cout<<"Tree is empty";
            return;
        }
        ptr = root;
        while (ptr != NULL)
        {
            cout<<"  ||"<<ptr->lthread<<"| "<< ptr->info<<" |"<<ptr->rthread<<"||  ";
            if (ptr->lthread == false)
                ptr = ptr->left;
            else if (ptr->rthread == false)
                ptr = ptr->right;
            else
            {
                while (ptr != NULL && ptr->rthread == true)
                    ptr = ptr->right;
                if (ptr != NULL)
                    ptr = ptr->right;
            }
        }
    }

    Node* inPred(Node* ptr)
{
    if (ptr->lthread == true)
        return ptr->left;
 
    ptr = ptr->left;
    while (ptr->rthread == false)
        ptr = ptr->right;
    return ptr;
}
 
// Here 'par' is pointer to parent Node and 'ptr' is pointer to current Node.

//deleting leaf node
Node* caseA(Node* root, Node* par,
                   Node* ptr)
{
    // If Node to be deleted is root
    if (par == NULL)
        root = NULL;
 
    // If Node to be deleted is left
    // of its parent
    else if (ptr == par->left) {
        par->lthread = true;
        par->left = ptr->left;
    }
    else {
        par->rthread = true;
        par->right = ptr->right;
    }
 
    // Free memory and return new root
    free(ptr);
    return root;
}
 
//deleting node with 1 child
Node* caseB(Node* root, Node* par,
                   Node* ptr)
{
    Node* child;
 
    // Initialize child Node to be deleted has
    // left child.
    if (ptr->lthread == false)
        child = ptr->left;
 
    // Node to be deleted has right child.
    else
        child = ptr->right;
 
    // Node to be deleted is root Node.
    if (par == NULL)
        root = child;
 
    // Node is left child of its parent.
    else if (ptr == par->left)
        par->left = child;
    else
        par->right = child;
 
    // Find successor and predecessor
    Node* s = inorderSuccessor(ptr);
    Node* p = inPred(ptr);
 
    // If ptr has left subtree.
    if (ptr->lthread == false)
        p->right = s;
 
    // If ptr has right subtree.
    else {
        if (ptr->rthread == false)
            s->left = p;
    }
 
    free(ptr);
    return root;
}
 
// Here 'par' is pointer to parent Node and 'ptr' is
// pointer to current Node.
Node* caseC(Node* root, Node* par,
                   Node* ptr)
{
    // Find inorder successor and its parent.
    Node* parsucc = ptr;
    Node* succ = ptr->right;
 
    // Find leftmost child of successor
    while (succ->lthread==false) {
        parsucc = succ;
        succ = succ->left;
    }
 
    ptr->info = succ->info;
 
    if (succ->lthread == true && succ->rthread == true)
        root = caseA(root, parsucc, succ);
    else
        root = caseB(root, parsucc, succ);

    return root;
}
 
// Deletes a key from threaded BST with given root and
// returns new root of BST.
Node* delThreadedBST(Node* root, int dkey)
{
    // Initialize parent as NULL and ptrent
    // Node as root.
    Node *par = NULL, *ptr = root;
 
    // Set true if key is found
    int found = 0;
 
    // Search key in BST : find Node and its
    // parent.
    while (ptr != NULL) {
        if (dkey == ptr->info) {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->info) {
            if (ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }
        else {
            if (ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }
 
    if (found == 0)
        printf("dkey not present in tree\n");
 
    // Two Children
    else if (ptr->lthread == false && ptr->rthread == false)
        root = caseC(root, par, ptr);
 
    // Only Left Child
    else if (ptr->lthread == false)
        root = caseB(root, par, ptr);
 
    // Only Right Child
    else if (ptr->rthread == false)
        root = caseB(root, par, ptr);
 
    // No child
    else
        root = caseA(root, par, ptr);
 
    return root;
}

void minelement(Node* root){
    if(root == NULL){
        return;
    }
    while(root->lthread!= true){
        root = root->left;
    }
    cout<<"\nMinimum element is: "<<root->info;
}

void maxelement(Node* root){
    if(root == NULL){
        return;
    }
    while(root->rthread!= true){
        root = root->right;
    }
    cout<<"\nMaximum element is: "<<root->info;
}
};

// Driver Program
int main()
{
    tbt t;
    Node *root = NULL;

    int n;
    cout << "how many nodes do you want to insert? ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int key;
        cout << "enter the data of node: ";
        cin >> key;
        root = t.insert(root, key);
    }
    cout<<"\nInorder traversal: ";
    t.inorder(root);
    cout<<"\nPreorder traversal: ";
    t.preorder(root);

    t.maxelement(root);
    t.minelement(root);

    int i=2;
    while(i>0){
        int delkey;
        cout<<"Enter the key you want to delete: ";
        cin>>delkey;
        t.delThreadedBST(root,delkey);
        t.inorder(root);

        i--;
    }

    

    return 0;
}
