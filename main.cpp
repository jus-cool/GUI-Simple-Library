#include <windows.h>
#include "FILE_HANDLER.h"
#include <iostream>
#include <string>
using namespace std;

int button_add_id[10]={100,101,102,103,104,105,106,107,108,109};
int button_remove_id[10]={200,201,202,203,204,205,206,207,208,209};

static HWND book_name_text;
static HWND book_author_text;
static HWND book_id_text;
static HWND book_submit;

static HWND book_author_display[20];
static HWND book_name_display[20];
static HWND book_id_display[20];

static HWND book_add_button[10];
static HWND book_remove_button[10];
static HWND book_view_button[10];

BOOK* a=new BOOK[20];
int i=0, y_axis=200, y_axis_2=65;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	
	
	
	switch(Message) {
		
		//Create Stuff here
		case WM_CREATE:{
			
			//Text-fields fot search operations
			CreateWindow(TEXT("STATIC"), TEXT("Enter Book Name here"), WS_VISIBLE | WS_CHILD , 10 , 5,200,20, hwnd , (HMENU)NULL , NULL , NULL);	
			book_name_text = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER , 10 , 30,200,20, hwnd , (HMENU)1 , NULL , NULL);	
			//book_author_text = CreateWindow(TEXT("EDIT"), TEXT("Enter Author Name here"), WS_VISIBLE | WS_CHILD | WS_BORDER , 10 , 40,200,20, hwnd , (HMENU)2 , NULL , NULL);
			CreateWindow(TEXT("STATIC"), TEXT("Enter Id Here"), WS_VISIBLE | WS_CHILD  , 250 , 5,200,20, hwnd , (HMENU)NULL , NULL , NULL);
			book_id_text = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER , 250 , 30,200,20, hwnd , (HMENU)3 , NULL , NULL);
			
			
			//Buttoon for submit operation
			CreateWindow(TEXT("STATIC"), TEXT("Submit"), WS_VISIBLE | WS_CHILD  , 470 , 5,80,20, hwnd , (HMENU)NULL , NULL , NULL);
			book_submit= CreateWindow(TEXT("Button"), TEXT("Submit"), WS_VISIBLE | WS_CHILD  , 470 , 30,80,20, hwnd , (HMENU)2 , NULL , NULL);
			
			
			//Button for search operation
			CreateWindow(TEXT("BUTTON"), TEXT("Search"), WS_VISIBLE | WS_CHILD  , 10 , 70,50,20, hwnd , (HMENU)4 , NULL , NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("Search"), WS_VISIBLE | WS_CHILD  , 350 , 70,50,20, hwnd , (HMENU)5 , NULL , NULL);
			
			//Display Searched books
			CreateWindow(TEXT("STATIC"), TEXT("BOOK NAME"), WS_VISIBLE | WS_CHILD  , 10 , 150,170,20, hwnd , (HMENU)NULL , NULL , NULL);
			CreateWindow(TEXT("STATIC"), TEXT("BOOK AUTHOR"), WS_VISIBLE | WS_CHILD  , 190 , 150,170,20, hwnd , (HMENU)NULL , NULL , NULL);
			CreateWindow(TEXT("STATIC"), TEXT("ID"), WS_VISIBLE | WS_CHILD  , 370 , 150,40,20, hwnd , (HMENU)NULL , NULL , NULL);
			
			//Final Lent Static text
			CreateWindow(TEXT("STATIC"), TEXT("The Books you have decided to lend"), WS_VISIBLE | WS_CHILD  , 650 , 40,400,20, hwnd , (HMENU)NULL , NULL , NULL);
			break;
		}
		
		
		//Action is here
		case WM_COMMAND:{
			static char temp_name[100], temp_author[100],temp_id[10];
			
			
			if(LOWORD(wParam)==2 && i != 0){
				
				for(int count = 0; count <=i ; count++){
					
					if(a[count].add_value == 0){
						CreateWindow(TEXT("STATIC"),TEXT(a[0].book_name.c_str()), WS_VISIBLE | WS_CHILD, 650, y_axis_2, 400,20, hwnd, (HMENU)NULL,NULL,NULL);
						y_axis_2 +=30;
					}
				}
				CreateWindow(TEXT("STATIC"),TEXT("Ability to lend the books for different user to be added soon"), WS_VISIBLE | WS_CHILD, 650, y_axis_2, 400,20, hwnd, (HMENU)NULL,NULL,NULL);
			}
			
			if(LOWORD(wParam)== 4){
				if (i >9){
					MessageBox(NULL,"Can't load more than 10 books", "Too many books!!", MB_OK | MB_ICONEXCLAMATION );
					return 0;
					
				}
				
				int len1 = GetWindowTextLength(book_name_text)+1;
				//int len2 = GetWindowTextLength(book_author_text)+1;
				
				GetWindowText(book_name_text,temp_name,len1);
				//GetWindowText(book_author_text,temp_author,len2);
				a[i]=BOOK(temp_name);
				if (a[i].confirm==1){
					
					book_name_display[i] = CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD  , 10 , y_axis,170,20, hwnd , (HMENU)NULL , NULL , NULL);
					book_author_display[i] = CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD  , 190 , y_axis,170,20, hwnd , (HMENU)NULL , NULL , NULL);
					book_id_display[i] = CreateWindow(TEXT("STATIC"),TEXT(""),WS_VISIBLE | WS_CHILD , 370 , y_axis,40,20,hwnd ,(HMENU)NULL ,NULL,NULL );
					
					book_add_button[i] = CreateWindow(TEXT("Button"),TEXT("Add"),WS_VISIBLE | WS_CHILD , 420 , y_axis,60,20,hwnd ,(HMENU)button_add_id[i] ,NULL,NULL );	
					book_remove_button[i] = CreateWindow(TEXT("Button"),TEXT("Remove"),WS_VISIBLE | WS_CHILD , 490 , y_axis,60,20,hwnd ,(HMENU)button_remove_id[i] ,NULL,NULL );	
					book_view_button[i] = CreateWindow(TEXT("STATIC"),TEXT(""),WS_VISIBLE | WS_CHILD , 560 , y_axis,60,20,hwnd ,(HMENU)NULL ,NULL,NULL );	
					
					SetWindowText(book_name_display[i],a[i].book_name.c_str());
					SetWindowText(book_author_display[i],a[i].book_author.c_str());
					
					string temp_id_display = to_string(a[i].book_id);
					SetWindowText(book_id_display[i], temp_id_display.c_str());
					y_axis=y_axis +30;
					i++;
				}
				else {
					
					MessageBox(NULL, "No records found","No book in entry",MB_ICONEXCLAMATION|MB_OK);
				}
				
				
				
			}
			
			if(LOWORD(wParam)==100){
				
				switch(a[0].add_value){
						case 1:{
							SetWindowText(book_view_button[0],"Added");
							a[0].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==200){
				SetWindowText(book_view_button[0],"");
				a[0].add_value=1;					
			}
			
			if(LOWORD(wParam)==101){
				
				switch(a[1].add_value){
						case 1:{
							SetWindowText(book_view_button[1],"Added");
							a[1].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==201){
				SetWindowText(book_view_button[1],"");
				a[1].add_value=1;					
			}
			
			if(LOWORD(wParam)==102){
				
				switch(a[2].add_value){
						case 1:{
							SetWindowText(book_view_button[2],"Added");
							a[2].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==202){
				SetWindowText(book_view_button[2],"");
				a[2].add_value=1;					
			}
			
			if(LOWORD(wParam)==103){
				
				switch(a[3].add_value){
						case 1:{
							SetWindowText(book_view_button[3],"Added");
							a[3].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==203){
				SetWindowText(book_view_button[3],"");
				a[3].add_value=1;					
			}
			
			if(LOWORD(wParam)==104){
				
				switch(a[4].add_value){
						case 1:{
							SetWindowText(book_view_button[4],"Added");
							a[4].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==204){
				SetWindowText(book_view_button[4],"");
				a[4].add_value=1;					
			}
			
			if(LOWORD(wParam)==105){
				
				switch(a[5].add_value){
						case 1:{
							SetWindowText(book_view_button[5],"Added");
							a[5].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==205){
				SetWindowText(book_view_button[5],"");
				a[5].add_value=1;					
			}
			
			if(LOWORD(wParam)==106){
				
				switch(a[6].add_value){
						case 1:{
							SetWindowText(book_view_button[6],"Added");
							a[6].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==206){
				SetWindowText(book_view_button[6],"");
				a[6].add_value=1;					
			}
			
			if(LOWORD(wParam)==107){
				
				switch(a[7].add_value){
						case 1:{
							SetWindowText(book_view_button[7],"Added");
							a[7].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==207){
				SetWindowText(book_view_button[7],"");
				a[7].add_value=1;					
			}
			
			
			if(LOWORD(wParam)==108){
				
				switch(a[8].add_value){
						case 1:{
							SetWindowText(book_view_button[8],"Added");
							a[8].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==208){
				SetWindowText(book_view_button[8],"");
				a[8].add_value=1;					
			}
			
			
			if(LOWORD(wParam)==109){
				
				switch(a[9].add_value){
						case 1:{
							SetWindowText(book_view_button[9],"Added");
							a[9].add_value=0;	
							break;							
							}
						}						
			}
			
			
			if(LOWORD(wParam)==209){
				SetWindowText(book_view_button[9],"");
				a[9].add_value=1;					
			}
			
			
			
			// Button for id search
			if(LOWORD(wParam)==5){
				if (i >9){
					MessageBox(NULL,"Can't load more than 10 books", "Too many books!!", MB_OK | MB_ICONEXCLAMATION );
					return 0;
					
				}
				
				int len3= GetWindowTextLength(book_id_text)+1;
					
				GetWindowText(book_id_text,temp_id,len3);
				a[i]=BOOK(stoi(temp_id));
					
				if (a[i].confirm ==1 ){
					book_name_display[i] = CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD  , 10 , y_axis,170,20, hwnd , (HMENU)NULL , NULL , NULL);
					book_author_display[i] = CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD  , 190 , y_axis,170,20, hwnd , (HMENU)NULL , NULL , NULL);
					book_id_display[i] = CreateWindow(TEXT("STATIC"),TEXT(""),WS_VISIBLE | WS_CHILD , 370 , y_axis,40,20,hwnd ,(HMENU)NULL ,NULL,NULL );
					book_add_button[i] = CreateWindow(TEXT("Button"),TEXT("Add"),WS_VISIBLE | WS_CHILD , 420 , y_axis,60,20,hwnd ,(HMENU)button_add_id[i] ,NULL,NULL );	
					book_remove_button[i] = CreateWindow(TEXT("Button"),TEXT("Remove"),WS_VISIBLE | WS_CHILD , 490 , y_axis,60,20,hwnd ,(HMENU)button_remove_id[i] ,NULL,NULL );	
					book_view_button[i] = CreateWindow(TEXT("STATIC"),TEXT(""),WS_VISIBLE | WS_CHILD , 560 , y_axis,60,20,hwnd ,(HMENU)NULL ,NULL,NULL );
					
					
					SetWindowText(book_name_display[i],a[i].book_name.c_str());
					SetWindowText(book_author_display[i],a[i].book_author.c_str());
					
					string temp_id_display = to_string(a[i].book_id);
					SetWindowText(book_id_display[i], temp_id_display.c_str());
					y_axis=y_axis +30;
					i++;
				}
			
				else {
					MessageBox(NULL, "No records found","No book in entry",MB_ICONEXCLAMATION|MB_OK);
				}
					
			}
		
		
			
			break;
		}
		
		
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}

	
	
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Welcome To My Library",WS_VISIBLE|WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		1000, /* width */
		600, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

