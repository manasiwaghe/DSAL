
#include <iostream>
#define size 10
using namespace std;

class DictNode
{
    string key;
    string value;
    DictNode *next;

public:
    DictNode()
    {
        key = "-";
        value = "-";
        next = NULL;
    }

    DictNode(string word, string meaning)
    {
        key = word;
        value = meaning;
        next = NULL;
    }

    friend class HashList;
};

class HashList
{
    DictNode *list[size];

public:
    HashList()
    {
        for (int i = 0; i < size; i++)
        {
            list[i] = NULL;
        }
    }

    int hashFunc(string word)
    {
        return ((int)word[0] % 10);
    }

    void insert(DictNode *n)
    {
        int index = hashFunc(n->key);

        if (list[index] == NULL)
        {
            list[index] = n;
        }
        else
        {
            DictNode *q = list[index];
            while (q->next != NULL)
            {
                q = q->next;
            }
            q->next = n;
        }
    }

    int search(string word)
    {
        int hashNo = hashFunc(word);
        DictNode *q = list[hashNo];
        while (q != NULL)
        {
            if (q->key == word)
            {
                cout << "\nMeaning of " << word << " is " << q->value;
                return 1;
            }
            q = q->next;
        }
        return 0;
    }

    void del(string word)
    {
        int hashNo = hashFunc(word);
        DictNode *q = list[hashNo];
        DictNode *par = NULL;
        while (q != NULL)
        {
            if (q->key == word)
            {
                if(par == NULL)
                {
                    list[hashNo] = q->next;
                    break;
                }
                else
                {
                    par->next = q->next;
                    break;
                }
            }
            par = q;
            q = q->next;
        }
        if (q == NULL)
        {
            cout << "\nWord does not exist in dictionary.";
        }
    }

    void display()
    {
        cout << "\nIndex\tKey-Value pairs";
        for (int i = 0; i < size; i++)
        {
            DictNode *q = list[i];
            cout << "\n"
                 << i << "\t";
            while (q != NULL)
            {
                cout << q->key << "->" << q->value << "----";
                q = q->next;
            }
        }
    }
};

int main()
{

    HashList HL;

    int ch;
    do
    {
        cout << "\n\n\t\tMenu:\n\t1.Insert Word\n\t2.Search a word\n\t3.Delete word\n\t4.Exit";
        cout << "\nEnter your choice : ";
        cin >> ch;
        string w;

        switch (ch)
        {
        case 1:
            int cont;
            do
            {
                string word, meaning;
                cout << "\nEnter the word to be inserted : ";
                cin >> word;
                cout << "\nEnter its meaning : ";
                cin >> meaning;
                DictNode *N1 = new DictNode(word, meaning);
                HL.insert(N1);
                cout << "\nContinue adding words?(1:yes,2:no)";
                cin >> cont;
            } while (cont == 1);
            HL.display();
            break;

        case 2:
            cout << "\nEnter word to be searched : ";
            cin >> w;
            if (HL.search(w) == 1)
            {
                cout << "\nWord is present in the list.";
            }
            else
            {
                cout << "\nWord is not present in the list.";
            }
            break;

        case 3:
            cout << "\nEnter word to be deleted : ";
            cin >> w;
            HL.del(w);
            HL.display();
            break;

        case 4:
            cout << "\nExiting program.";
            break;

        default:
            cout << "\nWrong choice";
        }
    } while (ch != 4);
    return 0;
}