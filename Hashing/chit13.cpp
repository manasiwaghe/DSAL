/* Implement all the functions of a dictionary (ADT) using open hashing technique: separate 
chaining using linked list Data: Set of (key, value) pairs, Keys are mapped to values, Keys 
must be comparable, and Keys must be unique. Standard Operations: Insert (key, value), 
Find(key), Delete(key). Use hash function as H(x) = (3x+5) %10 
*/

#include <iostream>
#define tableSize 10
using namespace std;

class SLLNode{
private:
	int key;
	char value[20];
	SLLNode *next;

public:
    friend class openHash;
} *HashTable[10];

class openHash{
public:
	void insert_key(SLLNode *head);
	void displayHT();
	void search(int key);
    void del(int key,SLLNode *head);
};

void openHash::insert_key(SLLNode *head){
	SLLNode *newnode = new SLLNode;
	SLLNode *temp;
	cout << "Enter key for the new node: ";
	cin >> newnode->key;
	cout << "Enter value for the new node: ";
	cin >> newnode->value;

	newnode->next = NULL;

	if(head == NULL){
		head = newnode;
	}
	else{
		temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newnode;
	}

	int key = newnode->key;

	int index = (3*key + 5)% tableSize;

	if(HashTable[index] == NULL){
		HashTable[index] = newnode;
	}
	else{
		temp = HashTable[index];
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newnode;
	}
}

void openHash::displayHT(){
	for(int i=0;i<tableSize; i++){
		SLLNode *temp = HashTable[i];
		while(temp!= NULL){
            cout<< i <<"-> ";
			cout << temp->key << "  ";
			cout << temp->value << endl;
			temp = temp->next;
		}
	}
}

void openHash::search(int key){
	bool flag = false;
	int cmp = 0;
	for(int i=0;i<tableSize; i++){
		SLLNode *temp = HashTable[i];
		while(temp != NULL){
			if(temp->key == key){
				cout << "The value for the given key is: " << temp->value;
				cout << "\nThe number of comparisons required are: " << cmp;
				flag = true;
				break;
			}
			else{
				temp = temp->next;
			}
			cmp++;
		}
	}
	if(flag==false){
		cout << "The key doesn't exist!";
		cout << "\nThe number of comparisons required are: " << cmp;
	}
}

void openHash::del(int key,SLLNode *head){
    SLLNode *curr = head,*prev =head;
    for(int i=0;i<tableSize; i++){
		prev = HashTable[i];
		while(prev != NULL){
			if(prev->next->key == key){
                curr = prev->next;
				break;
			}
			else{
				prev = prev->next;
			}
		}
	}
    prev->next = curr->next;
    delete curr;
    cout<<"Key deleted successfully!";
}

int main() {
	SLLNode *head=NULL;
	openHash t;

	int n;
	cout<< "Enter the number of values you want to insert: ";
	cin >> n;

	for(int i=0;i<n;i++){
		t.insert_key(head);
	}

	t.displayHT();

	int key;
	cout << "Enter the key you want to search";
	cin >> key;
	t.search(key);

    int delkey;
    cout<<"Enter the key you want to delete: ";
    cin>>delkey;
    t.del(delkey,head);

    cout<<"Hash Table after deletion"<<endl;
    t.displayHT();

	return 0;
}