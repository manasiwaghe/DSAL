/* Create an inordered threaded binary search tree for integer value. Perform preorder and inorder 
traversals and deletion of a node. Display smallest and largest value in it.
Note: Display lbit, rbit for every node*/

#include <iostream>
using namespace std;

class TBST;

class treenode
{
    int data;
    bool lbit, rbit;
    treenode *llink;
    treenode *rlink;

public:
    treenode()
    {
        data = 0;
        lbit = 0;
        rbit = 0;
        llink = NULL;
        rlink = NULL;
    }

    treenode(int d)
    {
        this->data = d;
        llink = NULL;
        rlink = NULL;
        lbit = 0;
        rbit = 0;
    }

    friend class TBST;
};

class TBST
{
    treenode *root = NULL;
    treenode *head = NULL;

public:
    void insert(int val)
    {
        // if tree is empty
        if (root == NULL)
        {
            head = new treenode(-9999);
            // pointing rlink to itself
            head->rlink = head;
            // create root
            root = new treenode(val);
            // attach root to head
            head->llink = root;
            head->lbit = 1;
            root->llink = head;
            root->rlink = head;
            return;
        }
        // if tree is not empty
        else
        {
            treenode *parent = root;
            treenode *temp = new treenode(val);
            while (true)
            {
                // check if inserted data is same as existing data
                if (parent->data == val)
                {
                    delete temp;
                    return;
                }
                // Insert in left subtree
                else if (val < parent->data)
                {
                    // check if left subtree exists
                    if (parent->lbit == 1)
                        parent = parent->llink;
                    else
                    {
                        // add node
                        temp->llink = parent->llink;
                        temp->rlink = parent;
                        parent->llink = temp;
                        parent->lbit = 1;
                        return;
                    }
                }
                // Insert in right subtree i.e. val > parent->data
                else
                {
                    // check if right subtree exists
                    if (parent->rbit == 1)
                        parent = parent->rlink;
                    else
                    {
                       // add node
                        temp->llink = parent;
                        temp->rlink = parent->rlink;
                        parent->rlink = temp;
                        parent->rbit = 1;
                        return;
                    }
                }
            }
        }
    }

    void inorder()
    {
        treenode *temp = root;
        if (temp == NULL)
            cout << "Tree Empty" << endl;
        else
        {
            // find extreme left node
            while (temp->lbit == 1)
            {
                temp = temp->llink;
            }
            while (temp != head)
            {
                // print node
                cout << temp->data << " ";
                // check if it has right child
                if (temp->rbit == 1)
                {
                    // traverse to right child
                    temp = temp->rlink;
                    // again traverse to its left most bit
                    while (temp->lbit == 1)
                    {
                        temp = temp->llink;
                    }
                }
                else
                {
                    temp = temp->rlink;
                    // rlink point to inorder successor i.e which will be root
                }
            }
            cout << endl;
        }
    }

    void preorder()
    {
        bool flag = 0;
        treenode *temp = root;
        while (temp != head)
        {
            if (flag == 0)
            {
                cout << temp->data << " ";
            }
            if (flag == 0 && temp->lbit == 1)
            {
                temp = temp->llink;
            }
            else
            {
                flag = (temp->rbit == 1) ? (0) : (1);
                temp = temp->rlink;
            }
        }
        cout << endl;
    }

    // search for element
    bool search(int ele, treenode *&parent, treenode *&current)
    {
        while (current != head)
        {
            if (current->data == ele)
            {
                return true;
            }
            else
            {
                parent = current;
                if (ele < current->data)
                {
                    current = current->llink;
                }
                else
                {
                    current = current->rlink;
                }
            }
        }
        return false;
    }

    void del(int ele)
    {
        treenode *parent = NULL;
        treenode *current = root;
        if (search(ele, parent, current))
        {
            delnode(ele, parent, current);
            cout << ele << " Deleted" << endl;
        }
        else
        {
            cout << "Element not found" << endl;
        }
    }

    void delnode(int ele, treenode *&parent, treenode *&current)
    {
        // Deleting Process
        cout << "Delete process" << endl;
        // Node having 2 links
        if (current->lbit == 1 && current->rbit == 1)
        {
            treenode *curr_succ = current->rlink;
            parent = current;
            while (curr_succ->lbit == 1)
            {
                parent = curr_succ;
                curr_succ = curr_succ->llink;
            }
            current->data = curr_succ->data;
            current = curr_succ;
            cout << "Deleted Node having left and right links" << endl;
        }
        // Leaf Node
        if (current->lbit == 0 && current->rbit == 0)
        {
            if (parent->llink == current)
            {
                cout << "Deleted node (left child)" << endl;
                parent->llink = current->llink;
                parent->lbit = 0;
            }
            else
            {
                cout << "Deleted node (rght child)" << endl;
                parent->rlink = current->rlink;
                parent->rbit = 0;
            }
            delete current;
        }
        // Only one child process
        // 1. left link and right thread
        if (current->lbit == 1 && current->rbit == 0)
        {
            treenode *temp = current->llink;
            if (parent->llink == current)
            {
                parent->llink = temp;
            }
            else
            {
                parent->rlink = temp;
            }
            while (temp->rbit == 1)
            {
                temp = temp->rlink;
            }
            temp->rlink = current->rlink;
            cout << "Deleting Node with left link" << endl;
            delete current;
        }
        // 2. right link, left thread
        if (current->lbit == 0 && current->rbit == 1)
        {
            treenode *temp = current->rlink;
            if (parent->llink == current)
            {
                parent->llink = temp;
            }
            else
            {
                parent->rlink = temp;
            }
            while (temp->lbit == 1)
            {
                temp = temp->llink;
            }
            temp->llink = current->llink;
            cout << "Deleting Node with right link" << endl;
            delete current;
        }
    }
};

int main()
{
    TBST t1;
    cout << "Creating Threaded Binary Search..." << endl;
    int n;
    cout << "Enter no. of elements:" << endl;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int y;
        cout << "Data :";
        cin >> y;
        t1.insert(y);
    }
    int ch = 0;
    while (ch != 4)
    {
        cout << "1.Inorder Traversal" << endl;
        cout << "2.Preorder Traversal" << endl;
        cout << "3.Delete Node" << endl;
        cout << "4.Exit" << endl;
        cout << "Your choice : " << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            cout << "Inorder Taversal : " << endl;
            t1.inorder();
            break;
        }
        case 2:
        {
            cout << "Preorder Traversal: " << endl;
            t1.preorder();
            break;
        }
        case 3:
        {
            int x;
            cout << "Enter node to delete: " << endl;
            cin >> x;
            t1.del(x);
            break;
        }
        default:
        {
            cout << "Invalid choice" << endl;
        }
        }
    }

    return 0;
}