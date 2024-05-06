/* Consider telephone book database of N clients. Make use of a hash table implementation 
to quickly look up client‘s telephone number. Make use of two collision handling 
techniques and compare them using number of comparisons required to find a set of 
telephone numbers (Note: Use linear probing with replacement and without 
replacement). Perform following operations 
1) Insert
2) Display
3) Search (number of comparisons required to search)
Use Hash function as H(x) = (3*x + 5)%10
*/

#include<iostream>
#include<cstring>
#define max 10
using namespace std;


class client
{
	private:
		string clientName;
		long int iPhno;

	public:
		friend class hashtable;

};

class hashtable
{
	client ht[max];

	public:
		hashtable()	
		{	string str = "------";
			for(int i=0;i<max;i++)
			{
				ht[i].iPhno=0;
				ht[i].clientName=str;
			}
		}

		void create_HT1(); //without replacement
//		void create_HT2(); //with replacement
		void display();
		int search_HT1(string);
//		int search_HT2(string);
		int getHash(string);
		int del(string);
};

void hashtable::create_HT1()
{
	client c;
	int Pos;
	char check;
	do{
		cout<<"\n Enter client name: ";
		cin>>c.clientName;
		cout<<"\n Enter Phone Number:";
		cin>>c.iPhno;
		Pos=getHash(c.clientName);

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
}

int hashtable::getHash(string key)
{
	int hash = 0;
	for (char ch : key){
		hash += (int)ch;
	}

	cout<< key <<" : "<<hash;

	return((3*hash + 5)%max);
}

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
}

int hashtable::search_HT1(string name)
{
	int iFlag=0;
	for(int i=0;i<max;i++)
	{
		if(ht[i].clientName==name)
		{
			cout<<"\n Client found at position "<<i;
			cout<<"\nClient name : "<<ht[i].clientName;
			cout<<"\nContact number : "<<ht[i].iPhno;
			iFlag=1;
		}
	}
	if(iFlag==0)
	cout<<"\n client Not Found";
}

int hashtable::del(string name)
{
	int iF=0;
	for(int i=0;i<max;i++)
	{
		if(ht[i].clientName==name)
		{
			string str = "-----";
			ht[i].clientName=str;
			ht[i].iPhno = 0;
			cout<<"\n client found and deleted";
			iF=1;
		}
	}
	if(iF==0)
	cout<<"\n client not found";

}//end of del


int main()
{
	int iCh;
	string name;
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
				cout<<"Enter the client name you want to search : ";
				cin>>name;
				h.search_HT1(name);
				cout<<"\n";
				break;

			case 4://delete
				cout<<"Enter the client name you want to delete : ";
				cin>>name;
				h.del(name);
				cout<<"\n";
				break;

			case 5://exit
				break;
		}//end of switch
	}while(iCh!=5);//end of do
return 0;
}