/* Consider telephone book cbase of N clients. Make use of a hash table implementation
to quickly look up client‘s telephone number. Make use of two collision handling
techniques and compare them using number of comparisons required to find a set of
telephone numbers (Note: Use linear probing with replacement and without
replacement). Perform following operations
1) Insert
2) Display
3) Search (number of comparisons required to search)
Use Hash function as H(x) = (3*x + 5)%10*/

#include <iostream>
#include <cstring>
#define max 10
using namespace std;

class client
{
private:
    char clientname[20];
    long long phone;

public:
    friend class hashtable;
};

class hashtable
{
    client ht[max];

public:
    hashtable()
    {
        char str[20] = "---";
        for (int i = 0; i < max; i++)
        {
            ht[i].phone = 0;
            strcpy(ht[i].clientname, str);
        }
    }

    void create_HT1(); //without replacement
    void create_HT2(); //with replacement
    void display();
    int search_HT1(long long);
    int search_HT2(long long);
    int del(long long);
    int hash(long long);
};

int hashtable::hash(long long key){
    return ((3*key +5)%max);
}
void hashtable::create_HT1(){
    client c;
    int index;
    char ch;

    do{
        cout<<"\nclient name:";
        cin>>c.clientname;
        cout<<"\nphone number: ";
        cin>>c.phone;

        index = hash(c.phone);

        if(ht[index].phone == 0){
            ht[index] = c;
        }else{
            for(int i=index+1; i%max!= index; i++){
                ht[i]=c;
				break;
            }
        }
        cout<<"\n Add More(y/n):";
        cin>>ch;
    }while(ch=='y');
}

void hashtable::create_HT2(){
    client c;
    int index;
    char ch;

    do{
        cout<<"\nclient name:";
        cin>>c.clientname;
        cout<<"\nphone number: ";
        cin>>c.phone;

        index = hash(c.phone);

        if (ht[index].phone == 0)
            ht[index] = c;
        else //checking collisions
        {
            if ((hash(ht[index].phone)) == index)
            {
                while(ht[index].phone != 0)
                {
                    index = (index + 1) % max;
                }
                ht[index] = c;
            }
            else
            {
                client temp = ht[index];
                ht[index] = c;
                while(ht[index].phone!=0)
                {
                    index = (index + 1) % max;
                }
                ht[index] = temp;
            }
        }
        cout<<"\n Add More(y/n):";
        cin>>ch;
    }while(ch=='y');
}

void hashtable::display()
{
	cout<<"------------------------------------";
	cout<<"\nSrno\t Client Name \t   Phone number\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<max;i++)
	{
		cout<<i<<"\t"<< ht[i].clientname <<"\t" <<ht[i].phone<<endl;
	}
	cout<<"------------------------------------\n";
}


int main(){
    int y,iCh;
	hashtable h;
	do
	{
		cout<<"\n---------------LIST---------------\n";
		cout<<"\n1.INSERT\n2.DISPLAY\n3.SEARCH\n4.DELETE\n5.EXIT\n\n";
		cout<<"Enter your choice:";
		cin>>iCh;
		cout<<"\n";

		switch(iCh)
		{
			case 1://insert
				h.create_HT2();
				cout<<"\n";
				break;

			case 2://display
				h.display();
				cout<<"\n";
				break;

			case 3://search
				h.search_HT1(y);
				cout<<"\n";
				break;

			case 4://delete
                int s;
				h.del(s);
				cout<<"\n";
				break;

			case 5://exit
				break;
		}//end of switch
	}while(iCh!=5);//end of do
return 0;
}

