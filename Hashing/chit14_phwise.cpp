/* Consider telephone book database of N clients. Make use of a hash table implementation 
to quickly look up client‘s telephone number. Make use of two collision handling 
techniques and compare them using number of comparisons required to find a set of 
telephone numbers (Note: Use linear probing with replacement and without 
replacement). Perform following operations 
1) Insert
2) Display
3) Search (number of comparisons required to search)
Use Hash function as H(x) = (3*x + 5)%10*/

#include<iostream>
#include<cstring>
#define max 10
using namespace std;


struct client
{
	char clientName[20];
	long int iPhno;
};//end of structure

class hashtable
{
	client ht[max];

	public:
		hashtable()	//constructor
		{	char str[20]="---";
			for(int i=0;i<max;i++)
			{
				ht[i].iPhno=0;
				strcpy(ht[i].clientName,str);
			}
		}

		void create_HT1();
//		void create_HT2();
		void display();
		int search_HT1(int);
//		int search_HT2(int);
		int del(int);
		int hash(long int);
};//end of class

void hashtable::create_HT1()
{
	client c;
	int Pos;
	char check;
	do
	{
		cout<<"\n Enter client name: ";
		cin>>c.clientName;
		cout<<"\n Enter Phone Number:";
		cin>>c.iPhno;
		Pos=hash(c.iPhno);

		if(ht[Pos].iPhno==0)
		{
			ht[Pos]=c;
		}
		else
		{
			for(int i=Pos+1;i%max!=Pos;i++)
			{
				ht[i]=c;
				break;
			}
		}
		cout<<"\n Add More(y/n):";
		cin>>check;
	}while(check=='y' || check=='Y');
}//end  of insert

int hashtable::hash(long int key)
{
    int hashval = (3*key+5);
    cout<< key<<" : "<<hashval;
	return(hashval%max);
}//end of hash

void hashtable::display()
{
	cout<<"------------------------------------";
	cout<<"\nSrno\t Client Name \t   Phone number\n";
	cout<<"------------------------------------\n";
	for(int i=0;i<max;i++)
	{
		cout<<i<<"\t"<< ht[i].clientName <<"\t" <<ht[i].iPhno<<endl;
	}
	cout<<"------------------------------------\n";
}//end of display 

int hashtable::search_HT1(int x)
{
	int iFlag=0;
	cout<<"Enter Phone number to be searched:";
	cin>>x;
	for(int i=0;i<max;i++)
	{
		if(ht[i].iPhno==x)
		{
			cout<<"\n Phone Number Found at position "<<i+1;
            cout<<"\nClient name: "<<ht[i].clientName;
			iFlag=1;
		}
	}
	if(iFlag==0)
	cout<<"\n Phone Number Not Found";
}//end of search

int hashtable::del(int s)
{
	int iF=0;
	cout<<"\n Enter phone number to be deleted:";
	cin>>s;
	for(int i=0;i<max;i++)
	{
		if(ht[i].iPhno==s)
		{

			ht[i].iPhno=0;
			cout<<"\n Phone number found and deleted";
			iF=1;
		}
	}
	if(iF==0)
	cout<<"\n Phone number not found";

}//end of del

int main()
{
	int iCh;
	long long y;
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
				h.create_HT1();
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
                long long s;
				h.del(s);
				cout<<"\n";
				break;

			case 5://exit
				break;
		}//end of switch
	}while(iCh!=5);//end of do
return 0;
}