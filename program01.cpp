/* Author: Jorge Moreno
   Instructor: Professor Ryan Michaels
   Date: 1/30/18
   Description: This program reads in multiple files for hands of cards as well as a deck. Once each hand/deck is in their own hash table i have created a menu to perform operations.
	 These operations include set Union, Intersection, and Difference.*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

const int SIZE = 52; 

class Hash //class to hold all information for a card
{
  private:
    string suite;
    string face;
    int hashN;  
		int hashF;
  
  public:
    Hash(int hnum,int hash,string fface,string fsuite) //puts in the information for each card and stores it
    {
      this->hashN = hnum;
			this->hashF = hash;
			this->face = fface;
			this->suite = fsuite;
    }
    int getValue()  //returns the unique number for a card
    {
      return hashN;
    }
		int getValueF()  //returns the hash number for a card
		{
			return hashF;
		}
	string getsuite()  //returns the card's suite
	{
		return this->suite;
	}
	string getface()  //returns the card's face
	{
		return this->face;
	}
};

class Hashmap  //This class holds all the functions used for operations.
{ 
  private:
    Hash **hTable; //pointer to the class Hash that will be used to pass card information
  
  public:
    Hashmap() //initializing all the buckets in hash table to null
    {
      hTable = new Hash*[SIZE];
      for(int i=0; i<SIZE; i++)
      {
        hTable[i] = NULL;
      }
    }
    int hashFunction(int add) //hash function generated for the table
    {
      return(add % SIZE);
      //return(SIZE % card);
    }
    void insertValue(string fface,string fsuite) //inserts a value into the hash table when an empty spot is found
    {
			int hnum = convert(fface,fsuite);
			int hash = hashFunction(hnum);
      int count = 0;

			while(hTable[hash]!=NULL && hTable[hash]->getValue() != hnum  && count < SIZE) //if the table is full and there is no dupes
      {
       hash = hashFunction(hash+1);
       count++;
      }
			hTable[hash] = new Hash(hnum,hash,fface,fsuite); //insert the card into the hash table
		}
	int convert(string fface, string fsuite)  //function converts the info for a card into a unique number
	{
			int fnum;
			int snum;
			if(fface == "Ace")
			{
				fnum = 1;
			}
			else if(fface == "Two")
			{
				fnum = 2;
			}
			else if(fface == "Three")
			{
				fnum = 3;
			}
			else if(fface == "Four")
			{
				fnum = 4;
			}
			else if(fface == "Five")
			{
				fnum = 5;
			}
			else if(fface == "Six")
			{
				fnum = 6;
			}
			else if(fface == "Seven")
			{
				fnum = 7;
			}
			else if(fface == "Eight")
			{
				fnum = 8;
			}
			else if(fface == "Nine")
			{
				fnum = 9;
			}
			else if(fface == "Ten")
			{
				fnum = 10;
			}
			else if(fface == "Jack")
			{
				fnum = 11;
			}
			else if(fface == "Queen")
			{
				fnum = 12;
			}
			else if(fface == "King")
			{
				fnum = 13;
			}
			if(fsuite == "Diamonds")
			{
				snum = 100;
			}
			else if(fsuite == "Hearts")
			{
				snum =200;
			}
			else if(fsuite == "Spades")
			{
				snum =300;
			}
			else if(fsuite == "Clubs")
			{
				snum =400;
			}
			int cnum = fnum+snum; //unique number
			return(cnum);
	}
	 int Search(int hnum)  //function used to search for a card and return if it is found
	{
	    int hash = hashFunction(hnum);
	    int count = 0;
	    
		 	while (hTable[hash] != NULL && hTable[hash]->getValue() != hnum && count < SIZE)
	    {
	        hash = hashFunction(hash + 1);
		      count++;
	    }
	    if (hTable[hash] == NULL || hTable[hash]->getValue() != hnum)
			{
	        return -1;
			}
			else
			{
				return hash;
			}
	 }
	string handFace(int a) //function used to go into the hash class and return the face
	{
		if(hTable[a] != NULL)
		{
		return hTable[a]->getface();
		}
		else
		{
		return "EMPTY";
		}
	}
	string handSuite(int a)  //function used to go into the hash class and return the suite
	{
		if(hTable[a] != NULL)
		{
		return hTable[a]->getsuite();
		}
		else
		{
			return "EMPTY";
		}
	}
		 void printTable() //Function prints out a hand table
      {
        for(int i=0; i<SIZE; i++)
        {
          if(hTable[i] != NULL)
          {
            cout << "The Data found in slot " << i << " is int number: " << hTable[i]->getValueF() << " "<< hTable[i]->getface() << " of " <<hTable[i]->getsuite() << endl;
          }
        }
      }
     void printUniverse()  //functon is the same as print but edited for the universe table
      {
			 int count=0;
        for(int i=0; i<SIZE; i++)
        {
          if(hTable[i] != NULL)
          {
            cout << "The Data found in slot " << i << " is int number: " << hTable[i]->getValueF() << " "<< hTable[i]->getface() << " of " <<hTable[i]->getsuite() << endl;
						count++;
          }
					if(count == 52) //if the number of cards in the table reached 52 we acheived the universal set
					{
						cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
						cout << "The Universal set was acheived using all hand sets!" << endl;
						cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-" << endl;
					}
        }
      }
  /*void Remove(int hnum)
	{
	    int hash = hashFunction(hnum);
	    int count = 0;
	    while (hTable[hash] != NULL && count < SIZE)
	    {
	        if (hTable[hash]->getValue() == hnum)
	            break;
	        hash = hashFunction(hash + 1);
		count++;
	    }
		if (hTable[hash] == NULL || hTable[hash]->getValue() != hnum)
		{
			cout<<hnum<< " not found in our Hash Table.\n";
			return;
		}
		else
		{
			hTable[hash] = NULL;
		}
		cout<<"Element Deleted\n";
	}*/
      ~Hashmap()  //deconstructor
      {
        for(int i=0;i<SIZE;i++)
        {
          if(hTable[i] != NULL)
          {
            delete hTable[i];
          }
        }
        delete[] hTable;
      }
};

int main()
{
	ifstream din;  //to read the deck file
	ifstream hin;  //to read the first hand file
	ifstream hin2;  //to read the second hand file
	ifstream hin3;  //to read the third hand file
	ifstream hin4;  //to read the fourth hand file
	
	Hashmap deckhash;  //hashmap variable for the deck
  Hashmap hash;  //hashmap variable for the first hand
	Hashmap hash2;  //hashmap variable for the second hand
	Hashmap hash3;  //handmap variable for the third hand
	Hashmap hash4;  //handmap variable for the fourth hand
	
	int uCount=0;  //universe counter
  int cardnum;  //used to hold the unique number for a card
	int i;  //counter variable
  int choice;  //variable to hold the users first choice
	int choice2;  //variable to hold the users second choice
	string fface;  //variable to read in the face from a file
	string fsuite;  //variable to read in the suite from a file
	
	cout << "=========================================================" << endl;
	
	din.open("Deck.txt");  //open the deck file
  if(din.fail())
  {
    cout << "Unable to open the Deck file." << endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    cout << "Deck file opened, ready to insert values into a hash table." << endl;
  }
  hin.open("Hand1.txt");  //open the first file
  if(hin.fail())
  {
    cout << "Unable to open hand1 file." << endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    cout << "Hand 1 file opened, ready to insert values into a hash table." << endl;
  }
	hin2.open("Hand2.txt");  //open the second file
  if(hin2.fail())
  {
    cout << "Unable to open hand2 file." << endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    cout << "Hand 2 file opened, ready to insert values into a hash table." << endl;
  }
	hin3.open("Hand3.txt");  //open the third file
  if(hin3.fail())
  {
    cout << "Unable to open hand3 file." << endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    cout << "Hand 3 file opened, ready to insert values into a hash table." << endl;
  }
	hin4.open("Hand4.txt");  //open the fourth file
  if(hin4.fail())
  {
    cout << "Unable to open hand4 file." << endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    cout << "Hand 4 file opened, ready to insert values into a hash table." << endl;
  }
	while(!din.eof())  //insert each card into a table with no dupes
  {
    din >> fface >> fsuite;
		deckhash.insertValue(fface,fsuite);		
	}
	while(!hin.eof())  //insert each card into a table with no dupes
	{
		hin >> fface >> fsuite;
		hash.insertValue(fface,fsuite);
	}
	while(!hin2.eof())  //insert each card into a table with no dupes
	{
		hin2 >> fface >> fsuite;
		hash2.insertValue(fface,fsuite);
	}	
	while(!hin3.eof())  //insert each card into a table with no dupes
	{
		hin3 >> fface >> fsuite;
		hash3.insertValue(fface,fsuite);
	}	
	while(!hin4.eof())  //insert each card into a table with no dupes
	{
		hin4 >> fface >> fsuite;
		hash4.insertValue(fface,fsuite);
	}
	cout << endl;
	cout << "The Deck and all 4 hands are now in their individual Sets." << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "Now performing operations on those sets." << endl;
	cout << "---------------------------------------------------------" << endl;
	while(1)
	{
		cout << "=========================================================" << endl;  //Menu
		cout << "Pick an operation in this menu." << endl;
		cout <<"1. Insert an element into a hand's set." << endl;
		cout <<"2. Search for an element in a hand's set." << endl;
		cout <<"3. Print the contents of a hand's set." << endl;
		cout <<"4. Check if the hand sets acheived the universal set." << endl;
		cout <<"5. Find the union between two sets." << endl;
		cout <<"6. Find the intersection between two sets." << endl;
		cout <<"7. Find the difference between two sets." << endl;
		cout <<"8. Find the unique cards in each set." << endl;
		cout <<"9. Find the most common card between all sets." << endl;
		cout <<"10. Exit the program." << endl;
	 	cout <<"           ======= Enter a number =======" << endl;
		cout <<"=========================================================" << endl;
  	cin >> choice;
		
		switch(choice)
		{
			case 1:
				cout << "Enter the face then suite of the card to be inserted." << endl;
				cout << "Face options: [Ace] [Two] [Three] [Four] [Five] [Six] [Seven] [Eight] [Nine]" << endl;
				cout << "              [Ten] [Jack] [Queen] [King]" << endl;
				cin >> fface;
				cout << "Suite: [Diamonds] [Spades] [Hearts] [Clubs]" << endl;
				cin >> fsuite;
				cout << "Choose the hand number you want this card to be inserted into." << endl;
				cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
				cin >> choice2;
				if(choice2 == 1)
				{
				hash.insertValue(fface,fsuite);
				cout << "Your card has been inserted into the correct hand set." << endl;
				}
				else if(choice2 == 2)
				{
				hash2.insertValue(fface,fsuite);
				cout << "Your card has been inserted into the correct hand set." << endl;
				}
				else if(choice2 == 3)
				{
				hash3.insertValue(fface,fsuite);
				cout << "Your card has been inserted into the correct hand set." << endl;
				}
				else if(choice2 == 4)
				{
				hash4.insertValue(fface,fsuite);
				cout << "Your card has been inserted into the correct hand set." << endl;
				}
				else
				{
					cout << "What you entered is not a hand that is available." << endl;
				}
				break;
			case 2:
				cout << "Enter the face then suite of the card you want to search." << endl;
				cout << "Face options: [Ace] [Two] [Three] [Four] [Five] [Six] [Seven] [Eight] [Nine]" << endl;
				cout << "              [Ten] [Jack] [Queen] [King]" << endl;
				cin >> fface;
				cout << "Suite: [Diamonds] [Spades] [Hearts] [Clubs]" << endl;
				cin >> fsuite;
				cout << "Choose the hand number you want to search for this card." << endl;
				cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
				cin >> choice2;
				if(choice2 == 1)
				{
					cardnum = hash.convert(fface,fsuite);
					int found = hash.Search(cardnum);
					if(found == -1)
					{
						cout << "The card you were looking for in the chosen hand is not in the set." << endl;
					}
					else
					{
						cout << "Your card " << fface << " of " << fsuite << " was found in slot " << found << " of the hand's set." << endl;
					}
				}
				else if(choice2 == 2)
				{
					cardnum = hash2.convert(fface,fsuite);
					int found = hash2.Search(cardnum);
					if(found == -1)
					{
						cout << "The card you were looking for in the chosen hand is not in the set." << endl;
					}
					else
					{
						cout << "Your card " << fface << " of " << fsuite << " was found in slot " << found << " of the hand's set." << endl;
					}
				}
				else if(choice2 == 3)
				{
					cardnum = hash3.convert(fface,fsuite);
					int found = hash3.Search(cardnum);
					if(found == -1)
					{
						cout << "The card you were looking for in the chosen hand is not in the set." << endl;
					}
					else
					{
						cout << "Your card " << fface << " of " << fsuite << " was found in slot " << found << " of the hand's set." << endl;
					}
				}
				else if(choice2 == 4)
				{
					cardnum = hash4.convert(fface,fsuite);
					int found = hash4.Search(cardnum);
					if(found == -1)
					{
						cout << "The card you were looking for in the chosen hand is not in the set." << endl;
					}
					else
					{
						cout << "Your card " << fface << " of " << fsuite << " was found in slot " << found << " of the hand's set." << endl;
					}
				}
				else
				{
					cout << "What you entered is not a correct hand set." << endl;
				}
				break;
			case 3:
				cout << "Choose a hand or the deck to print out the cards in it's set." << endl;
				cout << "(0) Deck " << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
				cin >> choice2;
				if(choice2 == 0)
				{
			  cout << endl;
				cout << "=============================================" << endl;
				cout << "Printing the deck set." << endl;
				cout << "=============================================" << endl;
				deckhash.printTable();
				cout << endl;
				}
				else if(choice2 == 1)
				{
				cout << endl;
				cout << "=============================================" << endl;
				cout << "Printing the hash 1 set." << endl;
				cout << "=============================================" << endl;
					hash.printTable();
					cout << endl;
				}
				else if(choice2 == 2)
				{
					cout << endl;
				cout << "=============================================" << endl;
				cout << "Printing the hand 2 set." << endl;
				cout << "=============================================" << endl;
					hash2.printTable();
					cout << endl;
				}
				else if(choice2 == 3)
				{
					cout << endl;
				cout << "=============================================" << endl;
				cout << "Printing the hand 3 set." << endl;
				cout << "=============================================" << endl;
					hash3.printTable();
					cout << endl;
				}
				else if(choice2 == 4)
				{
					cout << endl;
				cout << "=============================================" << endl;
				cout << "Printing the hand 4 set." << endl;
				cout << "=============================================" << endl;
					hash4.printTable();
					cout << endl;
				}
				else
				{
					cout << "That set does not exist." << endl;
				}
				break;
			case 4:
				{
					
			
				cout << "Checking if the union of all hands created the universal set." << endl;
				
		 	 Hashmap *universe = new Hashmap();
				hin.seekg(0);
				hin2.seekg(0);
				hin3.seekg(0);
				hin4.seekg(0);
				hin.seekg(0);
				while(!hin.eof())
				{
				hin >> fface >> fsuite;
				universe->insertValue(fface,fsuite);
				}
				while(!hin2.eof())
				{
				hin2 >> fface >> fsuite;
				universe->insertValue(fface,fsuite);
				}
				while(!hin3.eof())
				{
				hin3 >> fface >> fsuite;
				universe->insertValue(fface,fsuite);
				}
				while(!hin4.eof())
				{
				hin4 >> fface >> fsuite;
				universe->insertValue(fface,fsuite);
				}
				universe->printUniverse();
				delete universe;
				}		
				break;
			case 5:
			{
			 Hashmap *unionSet = new Hashmap();
			
				int a;
				int pick;
				int pick2;
				string tempface;
				string tempsuite;
			
				cout << "Pick the first set you want to union." << endl;
				cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
				cin >> pick;
				cout << "Pick the second set you want to union." << endl;
				cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
				cin >> pick2;
				if(pick == 1 && pick2 == 2 || pick == 2 && pick2 == 1)
				{
					hin.seekg(0);
					while(!hin.eof())
					{
					hin >> fface >> fsuite;
					unionSet->insertValue(fface,fsuite);
					}
					//unionSet->printTable();
					//cout << endl;
					hin2.seekg(0);
					while(!hin2.eof())
					{
						hin2 >> fface >> fsuite;
						unionSet->insertValue(fface,fsuite);
					}
					cout << "The Union of Hand 1 and Hand 2 is : " << endl;
					unionSet->printTable();
					delete unionSet;
				}
				else if(pick == 1 && pick2 == 3 || pick == 3 && pick2 == 1)
				{
					hin.seekg(0);
					while(!hin.eof())
					{
					hin >> fface >> fsuite;
					unionSet->insertValue(fface,fsuite);
					}
					hin3.seekg(0);
					while(!hin3.eof())
					{
						hin3 >> fface >> fsuite;
						unionSet->insertValue(fface,fsuite);
					}
					cout << "The Union of Hand 1 and Hand 3 is : " << endl;
					unionSet->printTable();
					delete unionSet;
				}
				else if(pick == 1 && pick == 4 || pick == 4 && pick2 == 1)
				{
					hin.seekg(0);
					while(!hin.eof())
					{
					hin >> fface >> fsuite;
					unionSet->insertValue(fface,fsuite);
					}
					hin4.seekg(0);
					while(!hin4.eof())
					{
						hin4 >> fface >> fsuite;
						unionSet->insertValue(fface,fsuite);
					}
					cout << "The Union of Hand 1 and Hand 4 is : " << endl;
					unionSet->printTable();
					delete unionSet;
				}
				else if(pick == 2 && pick2 == 3 || pick == 3 && pick2 == 2) 
				{
					hin2.seekg(0);
					while(!hin2.eof())
					{
					hin2 >> fface >> fsuite;
					unionSet->insertValue(fface,fsuite);
					}
					hin3.seekg(0);
					while(!hin3.eof())
					{
						hin3 >> fface >> fsuite;
						unionSet->insertValue(fface,fsuite);
					}
					cout << "The Union of Hand 2 and Hand 3 is : " << endl;
					unionSet->printTable();
					delete unionSet;
				}	
				else if(pick == 2 && pick2 == 4 || pick == 4 && pick2 == 2)
				{
					hin2.seekg(0);
					while(!hin2.eof())
					{
					hin2 >> fface >> fsuite;
					unionSet->insertValue(fface,fsuite);
					}
					hin4.seekg(0);
					while(!hin4.eof())
					{
						hin4 >> fface >> fsuite;
						unionSet->insertValue(fface,fsuite);
					}
					cout << "The Union of Hand 2 and Hand 4 is : " << endl;
					unionSet->printTable();
					delete unionSet;
				}
				else if(pick == 3 && pick2 == 4 || pick == 4 && pick2 == 3)	
				{
					hin3.seekg(0);
					while(!hin3.eof())
					{
					hin3 >> fface >> fsuite;
					unionSet->insertValue(fface,fsuite);
					}
					hin4.seekg(0);
					while(!hin4.eof())
					{
						hin4 >> fface >> fsuite;
						unionSet->insertValue(fface,fsuite);
					}
					cout << "The Union of Hand 3 and Hand 4 is : " << endl;
					unionSet->printTable();
					delete unionSet;
				}	
				else
				{
					cout << "Either you are trying to union the same set together or you have entered sets numbers that do not exist." << endl;
				}
		    }
				break;
			case 6:
				{
					Hashmap *intSet = new Hashmap();
			
					int pick;
					int pick2;
					string tempface;
					string tempsuite;
					cout << "Pick the first set you want to intersect." << endl;
					cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
					cin >> pick;
					cout << "Pick the second set you want to intersect." << endl;
					cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
					cin >> pick2;
					if(pick == 1 && pick2 == 2 || pick == 2 && pick2 == 1)
					{
						hin.seekg(0);
						hin2.seekg(0);
						while(!hin.eof())
						{
							hin >> fface >> fsuite;
							while(!hin2.eof())
							{
								hin2 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									intSet->insertValue(fface,fsuite);
								}
							}
							hin2.seekg(0);
						}
						cout << "The intersect of hand 1 and hand 2 is: " << endl;
						intSet->printTable();
						delete intSet;
					}
					else if(pick == 1 && pick2 == 3 || pick == 3 && pick2 == 1)
					{
						hin.seekg(0);
						hin3.seekg(0);
						while(!hin.eof())
						{
							hin >> fface >> fsuite;
							while(!hin3.eof())
							{
								hin3 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									intSet->insertValue(fface,fsuite);
								}
							}
							hin3.seekg(0);
						}
						cout << "The intersect of hand 1 and hand 3 is: " << endl;
						intSet->printTable();
						delete intSet;
					}
					else if(pick == 1 && pick2 == 4 || pick == 4 && pick2 == 1)
					{
						hin.seekg(0);
						hin4.seekg(0);
						while(!hin.eof())
						{
							hin >> fface >> fsuite;
							while(!hin4.eof())
							{
								hin4 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									intSet->insertValue(fface,fsuite);
								}
							}
							hin4.seekg(0);
						}
						cout << "The intersect of hand 1 and hand 4 is: " << endl;
						intSet->printTable();
						delete intSet;
					}
					else if(pick == 2 && pick2 == 3 || pick == 3 && pick2 == 2)
					{
						hin2.seekg(0);
						hin3.seekg(0);
						while(!hin2.eof())
						{
							hin2 >> fface >> fsuite;
							while(!hin3.eof())
							{
								hin3 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									intSet->insertValue(fface,fsuite);
								}
							}
							hin3.seekg(0);
						}
						cout << "The intersect of hand 2 and hand 3 is: " << endl;
						intSet->printTable();
						delete intSet;
					}
					else if(pick == 2 && pick2 == 4 || pick == 4 && pick2 == 2)
					{
						hin2.seekg(0);
						hin4.seekg(0);
						while(!hin2.eof())
						{
							hin2 >> fface >> fsuite;
							while(!hin4.eof())
							{
								hin4 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									intSet->insertValue(fface,fsuite);
								}
							}
							hin4.seekg(0);
						}
						cout << "The intersect of hand 2 and hand 4 is: " << endl;
						intSet->printTable();
						delete intSet;
					}
					else if(pick == 3 && pick2 == 4 || pick == 4 && pick2 == 3)
					{
						hin3.seekg(0);
						hin4.seekg(0);
						while(!hin3.eof())
						{
							hin3 >> fface >> fsuite;
							while(!hin4.eof())
							{
								hin4 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									intSet->insertValue(fface,fsuite);
								}
							}
							hin4.seekg(0);
						}
						cout << "The intersect of hand 3 and hand 4 is: " << endl;
						intSet->printTable();
						delete intSet;
					}
					else
				{
					cout << "Either you are trying to intersect the same set together or you have entered sets numbers that do not exist." << endl;
				}
				}
				break;
			case 7:
				{
				 Hashmap *difSet = new Hashmap();
				
					
					int pick;
					int pick2;
					string tempface;
					string tempsuite;
			
					cout << "Pick the first set you want to take the difference of." << endl;
					cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
					cin >> pick;
					cout << "Pick the second set you want to tkae the difference of." << endl;
					cout << "(1) Hand 1" << " " << "(2) Hand 2" << " " << "(3) Hand 3" << " " << "(4) Hand 4" << endl;
					cin >> pick2;
					cout << "Finding the set of " << pick << " - " << pick2 << endl;
					if(pick ==1 && pick2 ==2)
					{
						hin.seekg(0);
						hin2.seekg(0);
						while(!hin.eof())
						{
							int count = 0;
							hin >> fface >> fsuite;
							while(!hin2.eof())
							{
								hin2 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin2.seekg(0);
						}
						cout << "The difference of hand 1 and hand 2 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 1 && pick2 == 3)
					{
						hin.seekg(0);
						hin3.seekg(0);
						while(!hin.eof())
						{
							int count = 0;
							hin >> fface >> fsuite;
							while(!hin3.eof())
							{
								hin3 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin3.seekg(0);
						}
						cout << "The difference of hand 1 and hand 3 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 1 && pick2 == 4)
					{
						hin.seekg(0);
						hin4.seekg(0);
						while(!hin.eof())
						{
							int count = 0;
							hin >> fface >> fsuite;
							while(!hin4.eof())
							{
								hin4 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin4.seekg(0);
						}
						cout << "The difference of hand 1 and hand 4 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 2 && pick2 == 1)
					{
						hin2.seekg(0);
						hin.seekg(0);
						while(!hin2.eof())
						{
							int count = 0;
							hin2 >> fface >> fsuite;
							while(!hin.eof())
							{
								hin >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin.seekg(0);
						}
						cout << "The difference of hand 2 and hand 1 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 3 && pick2 == 1)
					{
						hin3.seekg(0);
						hin.seekg(0);
						while(!hin3.eof())
						{
							int count = 0;
							hin3 >> fface >> fsuite;
							while(!hin.eof())
							{
								hin >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin.seekg(0);
						}
						cout << "The difference of hand 3 and hand 1 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 4 && pick2 == 1)
					{
						hin4.seekg(0);
						hin.seekg(0);
						while(!hin4.eof())
						{
							int count = 0;
							hin4 >> fface >> fsuite;
							while(!hin.eof())
							{
								hin >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin.seekg(0);
						}
						cout << "The difference of hand 4 and hand 1 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 2 && pick2 == 3)
					{
						hin2.seekg(0);
						hin3.seekg(0);
						while(!hin2.eof())
						{
							int count = 0;
							hin2 >> fface >> fsuite;
							while(!hin3.eof())
							{
								hin3 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin3.seekg(0);
						}
						cout << "The difference of hand 2 and hand 3 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 2 && pick2 == 4)
					{
					hin2.seekg(0);
						hin4.seekg(0);
						while(!hin2.eof())
						{
							int count = 0;
							hin2 >> fface >> fsuite;
							while(!hin4.eof())
							{
								hin4 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin4.seekg(0);
						}
						cout << "The difference of hand 2 and hand 4 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
				  else if(pick == 3 && pick2 == 2)
					{
						hin3.seekg(0);
						hin2.seekg(0);
						while(!hin3.eof())
						{
							int count = 0;
							hin3 >> fface >> fsuite;
							while(!hin2.eof())
							{
								hin2 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin2.seekg(0);
						}
						cout << "The difference of hand 3 and hand 2 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 4 && pick2 == 2)
					{
						hin4.seekg(0);
						hin2.seekg(0);
						while(!hin4.eof())
						{
							int count = 0;
							hin4 >> fface >> fsuite;
							while(!hin2.eof())
							{
								hin2 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin2.seekg(0);
						}
						cout << "The difference of hand 4 and hand 2 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 3 && pick2 == 4)
					{
						hin3.seekg(0);
						hin4.seekg(0);
						while(!hin3.eof())
						{
							int count = 0;
							hin3 >> fface >> fsuite;
							while(!hin4.eof())
							{
								hin4 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin4.seekg(0);
						}
						cout << "The difference of hand 3 and hand 4 is: " << endl;
						difSet->printTable();
						delete difSet;
					}
					else if(pick == 4 && pick2 == 3)
					{
						hin4.seekg(0);
						hin3.seekg(0);
						while(!hin4.eof())
						{
							int count = 0;
							hin4 >> fface >> fsuite;
							while(!hin3.eof())
							{
								hin3 >> tempface >> tempsuite;
								if(fface == tempface && fsuite == tempsuite)
								{
									count++;
								}
							}
							if(count==0)
							{
								difSet->insertValue(fface,fsuite);
							}
							hin3.seekg(0);
						}
						cout << "The difference of hand 4 and hand 3 is: " << endl;
						difSet->printTable();
						delete difSet;
					}	
				}
				break;
			case 8:
			{
				cout << endl;
				Hashmap *unique = new Hashmap();
				int a;
				int c1=0;
				int c2=0;
				int c3=0;
				int c4=0;
				
				for(i=0;i<SIZE;i++)
				{
					int count=0;
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash.handFace(a))
						{
							if(deckhash.handSuite(i) == hash.handSuite(a))
							{
								count++;
								c1++;
							}
						}
					}
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash2.handFace(a))
						{
							if(deckhash.handSuite(i) == hash2.handSuite(a))
							{
								count++;
								c2++;
							}
						}
					}
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash3.handFace(a))
						{
							if(deckhash.handSuite(i) == hash3.handSuite(a))
							{
								count++;
								c3++;
							}
						}
					}
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash4.handFace(a))
						{
							if(deckhash.handSuite(i) == hash4.handSuite(a))
							{
								count++;
								c4++;
							}
						}
					}
					if(deckhash.handFace(i) != "EMPTY" && deckhash.handSuite(i) != "EMPTY" && count ==1)
					{
						if(c1 == 1)
						{
							cout << "Unique card in hand 1 : " << deckhash.handFace(i) << " of " << deckhash.handSuite(i) << endl;
						}
						else if(c2 == 1)
						{
							cout << "Unique card in hand 2 : " << deckhash.handFace(i) << " of " << deckhash.handSuite(i) << endl;
						}
						else if(c3 == 1)
						{
							cout << "Unique card in hand 3 : " << deckhash.handFace(i) << " of " << deckhash.handSuite(i) << endl;
						}
						else if(c4 == 1)
						{
							cout << "Unique card in hand 4 : " << deckhash.handFace(i) << " of " << deckhash.handSuite(i) << endl;
						}
				    unique->insertValue(deckhash.handFace(i),deckhash.handSuite(i));
					}
					count=0;
					c1=0;
					c2=0;
					c3=0;
					c4=0;		
				}	
			}
				break;
			case 9:
				{
				cout << endl;
				cout << "The number of times a card has been found between all sets : " << endl;
				cout << "=========================================================" << endl;
				Hashmap *common = new Hashmap();
				int a;
				int com=0;
				string tempFace;
	      string tempSuite;
				
				for(i=0;i<SIZE;i++)
				{
					int count=0;
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash.handFace(a))
						{
							if(deckhash.handSuite(i) == hash.handSuite(a))
							{
							count++;
							}
						}
					}
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash2.handFace(a))
						{
							if(deckhash.handSuite(i) == hash2.handSuite(a))
							{
							count++;
							}
						}
					}
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash3.handFace(a))
						{
							if(deckhash.handSuite(i) == hash3.handSuite(a))
							{
							count++;
							}
						}
					}
					for(a=0;a<SIZE;a++)
					{
						if(deckhash.handFace(i) == hash4.handFace(a))
						{
							if(deckhash.handSuite(i) == hash4.handSuite(a))
							{
							count++;
							}
						}
					}
					
					if(deckhash.handFace(i) != "EMPTY" && deckhash.handSuite(i) != "EMPTY" && count !=0)
					{
						cout << "- " << deckhash.handFace(i) << " of " << deckhash.handSuite(i) << " : " << count << " times." << endl;
						common->insertValue(deckhash.handFace(i),deckhash.handSuite(i));
					}
					if(count > com)
					{
						com = count;
						tempFace = deckhash.handFace(i);
						tempSuite = deckhash.handSuite(i);
					}
					count =0;
				}
				cout << "The most common card present is : " << tempFace << " of " << tempSuite << endl;
				
				
				
				}
				break;
			case 10:
				{
				exit(1);
				}
			default:
				cout << endl << "What you entered is not an option." << endl;
				break;
		}
	}

	din.close();  //close each file
	hin.close();
	hin2.close();
	hin3.close();
	hin4.close();
  return 0;
}

