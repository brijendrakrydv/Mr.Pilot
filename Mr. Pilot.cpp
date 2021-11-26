// This is simple game built using C++ by Brijendra Kumar Yadav

// Header Files
#include<iostream>       
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int birdY[3];
int birdX[3];
int birdFlag[3];
char plane[4][4] = { ' ','/','\\',' ', 
			     	'/','^','^','\\',
					'_','|','|','_',
		            ' ','\\','/',' ',
                       
                    
                    };
     
int planePos = WIN_WIDTH/2;
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	} 
}
void genbird(int ind){
	birdX[ind] = 17 + rand()%(33);  
}
void drawbird(int ind){
	if( birdFlag[ind] == true ){
		gotoxy(birdX[ind], birdY[ind]);   cout<< " __ ";  
		gotoxy(birdX[ind], birdY[ind]+1); cout<<"( o>"; 
		gotoxy(birdX[ind], birdY[ind]+2); cout<<"///\\"; 
		gotoxy(birdX[ind], birdY[ind]+3); cout<< "\\V_/";  
	} 
}
void erasebird(int ind){
	if( birdFlag[ind] == true ){
		gotoxy(birdX[ind], birdY[ind]);   cout<<"    ";  
		gotoxy(birdX[ind], birdY[ind]+1); cout<<"    "; 
		gotoxy(birdX[ind], birdY[ind]+2); cout<<"    "; 
		gotoxy(birdX[ind], birdY[ind]+3); cout<<"    "; 
	} 
}
void resetbird(int ind){
	erasebird(ind);
	birdY[ind] = 1;
	genbird(ind);
}

void drawPlane(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+planePos, i+22); cout<<plane[i][j];
		}
	}
}
void erasePlane(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+planePos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( birdY[0]+4 >= 23 ){
		if( birdX[0] + 4 - planePos >= 0 && birdX[0] + 4 - planePos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
    cout<<"\t\t------------Do You Know?------------"<<endl<<endl;
    cout<<"\t70000+ birds have died in New York since 2009 because of plane hits."<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Birds by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play(){
	planePos = -1 + WIN_WIDTH/2;
	score = 0;
	birdFlag[0] = 1;
	birdFlag[1] = 0;
	birdY[0] = birdY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	genbird(0);
	genbird(1);
	
	gotoxy(WIN_WIDTH + 7, 2);cout<<"Mr. Pilot";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Controls ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( planePos > 18 )
					planePos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( planePos < 50 )
					planePos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawPlane(); 
		drawbird(0); 
		drawbird(1); 
		if( collision() == 1  ){
			gameover();
			return;
		} 
		Sleep(50);
		erasePlane();
		erasebird(0);
		erasebird(1);   
		
		if( birdY[0] == 10 )
			if( birdFlag[1] == 0 )
				birdFlag[1] = 1;
		
		if( birdFlag[0] == 1 )
			birdY[0] += 1;
		
		if( birdFlag[1] == 1 )
			birdY[1] += 1;
		 
		if( birdY[0] > SCREEN_HEIGHT-4 ){
			resetbird(0);
			score++;
			updateScore();
		}
		if( birdY[1] > SCREEN_HEIGHT-4 ){
			resetbird(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		cout<<"\n\n";
		cout<<"You are flying a plane and thousands of migratory birds are heading towards you."<<endl;
        cout<<" Show your flying skills and save the Birds.\n\n\n"<<endl;
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        Mr.Pilot        | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}

//Contributed By Brijendra Kumar Yadav