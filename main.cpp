//
// <<Stefan Mijalkov>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
#include <stdbool.h>

using namespace std;


	struct MovieData
	{
	//to keep track of the year
	int PubYear;
	
	//rating portion counter:
	int Num5Stars;
	int Num4Stars;
	int Num3Stars;
	int Num2Stars;
	int Num1Stars;
	
	//added part
	int ID;
	string Name;
	int NumReviews=0;
	double AvgRating=0.0;
	double totalScore=0.0;
	
	};
	

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//



int InputMovies(string moviesFilename, binarysearchtree<string, MovieData>& nameSearchTree, binarysearchtree<int, MovieData>& idSearchTree)
{
  ifstream moviesFile(moviesFilename);
  int id, pubYear;
  int numMovies=0;
  string   name;
  MovieData movieData;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return -1;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
    //cout << id << "," << pubYear << "," << name << endl;
    
	//MY WORK STARTS HERE:
	
	movieData.ID=id;
	movieData.Name= name;
	movieData.PubYear = pubYear;
    
    nameSearchTree.insert(name, movieData);
    idSearchTree.insert(id, movieData);


    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
    numMovies++;
    
  }
  
  
  return numMovies;
  
}

//needs InputRating file:

int InputRating(string reviewsFilename, binarysearchtree<string, MovieData>& nameSearchTree, binarysearchtree<int, MovieData>& idSearchTree){
	
	ifstream reviewsFile(reviewsFilename);
	int reviewID, movieID, rating;
	int numRatings=0;
	
		if(!reviewsFile.good()){
		cout<<"**Error: unable to open reviews file '" <<reviewsFilename<<"', exiting"<<endl;
		return -1;
	}

	MovieData* ptIDSearchValue;
	MovieData* ptNameSearchValue;
	
	reviewsFile>>reviewID;
	
	while(!reviewsFile.eof()){
		
		reviewsFile>>movieID;
		reviewsFile>>rating;
		
		
		
		ptIDSearchValue=idSearchTree.search(movieID);
		ptNameSearchValue=nameSearchTree.search(ptIDSearchValue->Name);
		
		ptIDSearchValue->NumReviews++;
		ptNameSearchValue->NumReviews++;
		
		switch(rating){
			case 1: ptIDSearchValue->Num1Stars++;
					ptNameSearchValue->Num1Stars++;
					break;
			
			case 2: ptIDSearchValue->Num2Stars++;
					ptNameSearchValue->Num2Stars++;
					break;
			
			case 3: ptIDSearchValue->Num3Stars++;
					ptNameSearchValue->Num3Stars++;
					break;
			
			case 4: ptIDSearchValue->Num4Stars++;
					ptNameSearchValue->Num4Stars++;
					break;
			
			case 5: ptIDSearchValue->Num5Stars++;
					ptNameSearchValue->Num5Stars++;
					break;
			
		}
		
		ptNameSearchValue->totalScore+=(double)rating;
		ptNameSearchValue->AvgRating=(ptNameSearchValue->totalScore) / (ptNameSearchValue->NumReviews);
		
		
		ptIDSearchValue->totalScore+=(double)rating;
		ptIDSearchValue->AvgRating=(ptIDSearchValue->totalScore) / (ptIDSearchValue->NumReviews);
	
	
	
		reviewsFile>>reviewID;
		numRatings++;
		
	}
	
	return numRatings;
	
}

//
// main
//
int main()
{
	
	int numMovies;
	int numReviews;
	string moviesFilename; // = "movies1.txt";
	string reviewsFilename; // = "reviews1.txt";
	string input;
	size_t counter=0;
	bool idSearch=false;
	bool nameSearch=false;
	
	
	binarysearchtree<int, MovieData> idSearchTree; //searches by ID
	binarysearchtree<string, MovieData>  nameSearchTree; //searches by name

  	cout << "movies file?> ";
  	cin >> moviesFilename;

	cout << "reviews file?> ";
	cin >> reviewsFilename;

	string junk;
	getline(cin, junk);  // discard EOL following last input:

  	numMovies=InputMovies(moviesFilename, nameSearchTree, idSearchTree);
	numReviews=InputRating(reviewsFilename, nameSearchTree, idSearchTree);
	
	if(numMovies==-1 || numReviews==-1){
		return 0;
	}
	
	cout<<"Num movies: "<<numMovies<<endl;
	cout<<"Num reviews: "<<numReviews<<endl;
	cout<<endl;
	
	cout<<"Tree by movie id: size="<<idSearchTree.size()<<", height="<<idSearchTree.height()<<endl;
	cout<<"Tree by movie name: size="<<nameSearchTree.size()<<", height="<<nameSearchTree.height()<<endl;
	cout<<endl;
	
	MovieData* ptIdSearch=nullptr;
	MovieData* ptNameSearch=nullptr;
	MovieData* temp;
	
	
	
	while(true){
		
		cout << "Enter a movie id or name (or # to quit)>";
		getline(cin, input);
		
		if(input=="#")
		break;
		
		
		while(counter!=input.size()){
			if(isdigit(input[counter])){
				counter++;
			}
			else
			{
				break;
			}
		}
		
		if(counter==input.size()){
			idSearch=true;
			int idKey = stoi(input);
			ptIdSearch=idSearchTree.search(idKey);
			temp=ptIdSearch;
		}
		else
		{	
			nameSearch=true;
			ptNameSearch=nameSearchTree.search(input);
			temp=ptNameSearch;
		}
		
		if((nameSearch && ptNameSearch==nullptr) || (idSearch && ptIdSearch==nullptr)) {
			cout<<"not found...";
		}
		else{
			cout<<"Movie ID: "<<temp->ID<<endl;
			cout<<"Movie name: "<<temp->Name<<endl;
			cout<<"Avg rating: "<<temp->AvgRating<<endl;
			cout<<"5 stars: "<<temp->Num5Stars<<endl;
			cout<<"4 stars: "<<temp->Num4Stars<<endl;
			cout<<"3 stars: "<<temp->Num3Stars<<endl;
			cout<<"2 stars: "<<temp->Num2Stars<<endl;
			cout<<"1 star: "<<temp->Num1Stars<<endl;
			}
			
			
			idSearch=false;
			nameSearch=false;
			counter=0;
		
			cout<<endl;
			
		}
		
		return 0;
		
	}	
	