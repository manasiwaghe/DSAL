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
    client ht1[max];
    client ht2[max];

public:
    hashtable()
    {
        char str[20] = "---";
        for (int i = 0; i < max; i++)
        {
            ht1[i].phone = 0;
            strcpy(ht1[i].clientname, str);
            ht2[i].phone = 0;
            strcpy(ht2[i].clientname, str);
        }
    }

    void create_HT1(); //without replacement
    void create_HT2(); //with replacement
    void display1();
    void display2();
    int search_HT1(long long);
    int search_HT2(long long);
    int del(long long);
    int hash(long long);
};

int hashtable::hash(long long key){
    return ((3*key + 5)%max);
}

void hashtable::create_HT1(){
    client c1;
    int index;
    char ch;

    do{
        cout<<"\nclient name:";
        cin>>c1.clientname;
        cout<<"\nphone number: ";
        cin>>c1.phone;

        index = hash(c1.phone);

        if(ht1[index].phone == 0){
            ht1[index] = c1;
        }else{
            for(int i=index+1; i%max!= index; i++){
                ht1[i]=c1;
				break;
            }
        }
        cout<<"\n Add More(y/n):";
        cin>>ch;
    }while(ch=='y');
}

void hashtable::create_HT2(){
    client c2;
    int index;
    char ch;

    do{
        cout<<"\nclient name:";
        cin>>c2.clientname;
        cout<<"\nphone number: ";
        cin>>c2.phone;

        index = hash(c2.phone);

        if (ht2[index].phone == 0)
            ht2[index] = c2;
        else //checking collisions
        {
            if ((hash(ht2[index].phone)) == index)
            {
                while(ht2[index].phone != 0)
                {
                    index = (index + 1) % max;
                }
                ht2[index] = c2;
            }
            else
            {
                client temp = ht2[index];
                ht2[index] = c2;
                while(ht2[index].phone!=0)
                {
                    index = (index + 1) % max;
                }
                ht2[index] = temp;
            }
        }
        cout<<"\n Add More(y/n):";
        cin>>ch;
    }while(ch=='y');
}

int hashtable::search_HT1(long long x)
{
	int iFlag=0;
	cout<<"Enter Phone number to be searched:";
	cin>>x;
	for(int i=0;i<max;i++)
	{
		if(ht1[i].phone==x)
		{
			cout<<"\n Phone Number Found at position "<<i+1;
            cout<<"\nClient name: "<<ht1[i].clientname;
			iFlag=1;
		}
	}
	if(iFlag==0)
	cout<<"\n Phone Number Not Found";
}//end of search

int hashtable::search_HT2(long long x)
{
	int iFlag=0;
	cout<<"Enter Phone number to be searched:";
	cin>>x;
	for(int i=0;i<max;i++)
	{
		if(ht2[i].phone==x)
		{
			cout<<"\n Phone Number Found at position "<<i+1;
            cout<<"\nClient name: "<<ht2[i].clientname;
			iFlag=1;
		}
	}
	if(iFlag==0)
	cout<<"\n Phone Number Not Found";
}//end of search

// int hashtable::del(long long s)
// {
// 	int iF=0;
// 	cout<<"\n Enter phone number to be deleted:";
// 	cin>>s;
// 	for(int i=0;i<max;i++)
// 	{
// 		if(ht1[i].phone==s)
// 		{

// 			ht1[i].phone=0;
// 			cout<<"\n Phone number found and deleted";
// 			iF=1;
// 		}
// 	}
// 	if(iF==0)
// 	cout<<"\n Phone number not found";

// }

void hashtable::display1()
{
	cout<<"------------------------------------";
	cout<<"\nSrno\t Client Name \t   Phone number\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<max;i++)
	{
		cout<<i<<"\t"<< ht1[i].clientname <<"\t" <<ht1[i].phone<<endl;
	}
	cout<<"------------------------------------\n";
}

void hashtable::display2()
{
	cout<<"------------------------------------";
	cout<<"\nSrno\t Client Name \t   Phone number\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<max;i++)
	{
		cout<<i<<"\t"<< ht2[i].clientname <<"\t" <<ht2[i].phone<<endl;
	}
	cout<<"------------------------------------\n";
}

int main(){
    int y,iCh;
	hashtable h;
	do
	{
		cout<<"\n---------------LIST---------------\n";
		cout<<"\n1.INSERT(without replacement) \n2.INSERT(with replacement) \n3.DISPLAY(without replacement)\n4.DISPLAY(with replacement) \n5.SEARCH \n6.DELETE \n7.EXIT\n\n";
		cout<<"Enter your choice:";
		cin>>iCh;
		cout<<"\n";

		switch(iCh)
		{
			case 1://insert
				h.create_HT1();
				cout<<"\n";
				break;

            case 2://insert
				h.create_HT2();
				cout<<"\n";
				break;

			case 3://display
				h.display1();
				cout<<"\n";
				break;

            case 4://display
				h.display2();
				cout<<"\n";
				break;

			case 5://search
				h.search_HT1(y);
				cout<<"\n";
				break;

			case 6://delete
                int s;
				// h.del(s);
				cout<<"\n";
				break;

			case 7://exit
				break;
		}//end of switch
	}while(iCh!=8);//end of do
return 0;
}

