#include <iostream>
using namespace std;

class test{
	public:
		int x;
		
		void call(){
			
		}
};



int main(){
	test obj;
	
	while (true){
	
	switch(obj.x){
		case 1:{
			obj.x=0;
			break;
		}
		case 0:{
			obj.x=1;
			break;
		}
	}
	cout << obj.x;
	
}
}
