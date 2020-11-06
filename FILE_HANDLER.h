#include <iostream>
using namespace std;

#include <string>
#include <fstream>

class BOOK{
	public:
		string book_name, book_author;
		int book_id,confirm, add_value=1;
	
	public:
		BOOK(){
			book_name="No name";
			book_author="No author";
		}
		BOOK(string x_name ,int check=0){
			string use_name=input_parser(x_name);
			confirm=check_in_list(use_name,check);
		}
		BOOK(int x_id, int check= 0){
			//Checking if id exists in the data base
			if (check == 0){
				confirm= check_id_list(x_id);
				//if id exists return book_name and file_name
			}
		}
		
		int check_id_list(int);
		
		string input_parser(string);
		string output_parser(string);
		
		int check_in_list(string,int);
		
};


int BOOK::check_id_list(int x_id){
	ifstream id_file;
	int x;
	string name, author;
	
	id_file.open("data/id.txt");
	if (!id_file){
		cout <<"File Failed to open"<<endl;
	}	
	while(id_file>>x>>name>>author){
		if(x_id == x){
		
			book_name=output_parser(name);
			book_author=output_parser(author);
			book_id = x_id;
			id_file.close();
			return 1;
		}
		
	}
	id_file.close();
	return 0;	
}


string BOOK::input_parser(string x){
	int len=x.length();
	for(int i =0 ; i< x.length();i++){
		if (x[i]==' '){
			x[i]='_';
		
		}
		if(x[i+1]<='Z' && x[i+1] >= 'A' ){
				
				x[i]= x[i]+32;
	
			
		}
		
	}
	
	return x;	
}
string BOOK::output_parser(string x){
	int len=x.length();
	for(int i =0 ; i< x.length();i++){
		if (x[i]=='_'){
			x[i]=' ';
		}
	}
	return x;	
}

int BOOK::check_in_list(string name_passed, int check =0){
	ifstream id_file;
	int x;
	string name, author;
	
	id_file.open("data/id.txt");
	if (!id_file){
		cout <<"File Failed to open"<<endl;
	}	
	while(id_file>>x>>name>>author){
		if( name== name_passed && check ==0){
			book_name=output_parser(name);
			book_author=output_parser(author);
			book_id=x;
			id_file.close();
			return 1;
		}
		if( author== name_passed && check !=0){
			book_name=output_parser(name);
			book_author=output_parser(author);
			book_id=x;
			id_file.close();
			return 1;
		}	
	}
	id_file.close();
	return 0;	
}

