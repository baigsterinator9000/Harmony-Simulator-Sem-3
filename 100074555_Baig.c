/* File: 100074555_Baig.c									  *
 * Mirza Tauheed Shah Baig, 100074555						  *
 * This program generates a game based on Harmony puzzle game *
 * in which the user has to rearrange tiles in order to win.  *	   
 * Last Modified : 28/5/2017,  3:16 AM	  	  	  	  	  	 */
 
#include <stdio.h>
#include <windows.h> 
#include <time.h>
#include <stdlib.h>

#define row 5
#define col 4

struct GAME /*contains 3 main array types for gameboard*/
{
	char l_array;
	int n_array;
	char c_array;
};

void intro(); /*Prints Introduction Header*/
void instructions(); /*Prints Instructions for the game*/
void game(char name[20]); /*Main Game happens in this function*/
void autoplay(); /*This function contains the extra featured(autoplay)*/
void letter_sort(struct GAME brd[row][col]); /*Sorts letters for the autoplay feature*/
void random_letter(char *l,int *A,int *B,int *C,int *D,int *E); /*	Generates Random letters for main game*/
void letter_array(struct GAME brd[row][col]); /*Assigns generated letters to the gameboard(array)*/
void num_gen(int *n,int *one,int *two,int *three,int *four); /*Generates random numbers*/
void num_array(int array[]); /*Assigns generated numbers to array*/
void num_compare(struct GAME brd[row][col]); /*Compares numbers with already generated numebrs to avoid repition*/
void disp_array(struct GAME brd[row][col]); /*Displays the main gameboard array*/
void disp_autoplay(struct GAME brd[row][col]); /*Array display for the autoplay function(no colors)*/
void swap(struct GAME brd[row][col],int *select,int *a1,int *b1,int *a2,int *b2,int *N); /*Swaps two selected tiles*/
void win(struct GAME brd[row][col],int n,char name[20]); /*Determines if user has won or not*/
void storescore(char name[20],int score); /*Stores user's name and score into a file*/
void prevscore(); /*Displays previous scores of players from a file*/
void record(char name[20]); /*Stores user's name for later use*/

int main(void)
{
	char mode,name[20];
	int score = 0;
	
	intro();
	record(name); /*prompts name from user*/
	system("cls");
	instructions(); /*shows instructions to user*/
		
	while(1)
	{
		system("cls"); /*clears screen*/
		prevscore(); /*shows scores of previous players*/
		printf("\nSelect game mode: \nA - Play the game \nB - Autoplay(Extra Feature)[NO COLORS]\nQ to Quit\n");
		mode = getch(); /*prompts input to select game mode*/
		if(mode=='a'||mode=='A') 
		{
			game(name); /*goes to main game*/
			break;
		}
		else if(mode=='b'||mode=='B')
		{
			autoplay(); /*goes to autoplay feature*/
			break;
		}
		else if(mode=='q'||mode=='Q')
		{
			break; /*quits the game*/
		}
		else 
			printf("Invalid input, Please enter one of the options given");
		Sleep(1500);
	}
	
	printf("\n\n Thanks for playing");
		
	return 0;
}

void intro() /*Game Header*/
{	 
	printf("*******************************************************************************");
	printf("\n********************************** Hi *****************************************");
	printf("\n*******************************************************************************");
	Sleep(1000);
	printf("\n\n	Welcome to Harmony\n\n");
	Sleep(1000);
	printf("\n\n This is a tile swapping puzzle game");
	Sleep(1000);
}

void record(char name[20]) /*Gets name*/
{	 
	printf("\n\nPlease Enter your name: ");
	scanf("%s",name); /*name is stored as a string for later use*/
	Sleep(1000);
	printf("\n*** Hello %s! Let's get started! ***",name);
	Sleep(2000);
}

void instructions() /*Game Instructions*/
{	 
	int i,j;
	
	/*Old color attribute of screen is stored*/
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE ); 
	WORD wOldColorAttrs; 
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	GetConsoleScreenBufferInfo(h, &csbiInfo); 
	wOldColorAttrs = csbiInfo.wAttributes;
	
	printf("\nGoal: to arrange all tiles in an order so that they are in");
	printf("\nalphabetical order vertically and in numerical(ascending) order horizontally.");
	printf("\n\nYou use the 8,6,4,2 keys on the numpad to control the cursor '^' and the 5 key ");
	printf("\nto select a tile. After two tiles have been selected they will get swapped.");
	printf("\n\n Complete the goal in order to finish the game\n");
	system("pause");
	printf("\n\n***This is what the board should look like at the end.***\n");
	Sleep(1500);
	
	/*For loops display a 5x4 gameboard with letters from A to E which are also numbered from 1-4*/
	for(i=0;i<row;i++)
	{	
		printf("\n -----------------------\n");
		printf("|");
		for(j=0;j<col;j++)
		{
			/*If statements determine color of tile*/
			if(i==0)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); /*cyan color*/
			if(i==1)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); /*yellow color*/
			if(i==2)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_INTENSITY); /*green color*/
			if(i==3)
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_INTENSITY); /*red color*/
			if(i==4)
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY); /*magenta color*/
			printf("%3c  ",'A'+i); /*A is incremented for each value of i*/
			SetConsoleTextAttribute ( h, wOldColorAttrs); /*old color attribute is returned*/
			printf("|");
		}
		printf("\n");
		printf("|");
		for(j=0;j<col;j++)
		{
			if(i==0)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			if(i==1)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(i==2)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			if(i==3)
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(i==4)
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			printf("%3i  ",j+1); /*Displays values 1-4 for each row*/
			SetConsoleTextAttribute ( h, wOldColorAttrs);
			printf("|");
		}
		printf("\n");
		printf("|");
		for(j=0;j<col;j++)
		{
			if(i==0)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			if(i==1)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(i==2)
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			if(i==3)
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(i==4)
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			printf("     ");
			SetConsoleTextAttribute ( h, wOldColorAttrs);
			printf("|");
		}	 	 
	}
	printf("\n -----------------------\n");
	printf("(Scroll up for instructions)\n");
	system("pause"); /*pauses screen and prompts for key press*/	   	   
}

void prevscore() /*Reads previous scores from file*/
{
	char name[20];
	int score;

	/*This function takes previous scores stored in a file and displays them on the screen
	for the user to see*/	 
	FILE *f;
	f = fopen("scores.txt", "r"); /*file is opened for reading*/
	if (f == NULL)
	{
		printf("No previous scores available"); /*Displays when no score file is found*/
	}
	else 
	{
		printf("\nPrevious Player scores: \n\n");
		while(fscanf(f,"%s %i",&name,&score)==2) /*Name and score of each previous player is scanned from file*/
		{
			printf("%s - %i\n",name,score); /*name and score are printed*/
		}
	}
	fclose(f);/*closes file*/
}

void storescore(char name[20],int score) /*Stores score of user*/
{
	/*This function takes the name of the user and the score and stores it into the file of previous scores*/
	FILE *f;
	f = fopen("scores.txt", "a"); /*file is opened for appending*/
	if (f == NULL)
	{
		printf("Error opening file\n\n"); /*Displays when file not found*/
	}
	else 
	{
		fprintf(f,"%s %i\n",name,score); /*Prints name and score into file*/
	}
	fclose(f);
}

void game(char name[20]) /*Main Game*/
{
	/*This function contains the main gameplay of the game, it takes input from the user and 
	performs actions according to it.Tiles are swapped,when the user when selects 2 of them.
	Once the board is alligned accordingly,the user wins the game */
	
	struct GAME board[row][col] = {0}; /*Gameboard declaration an a structure*/
			
	char arrow = '^'; /*cursor*/
	int a=0,b=0;
	char move; /*input for navigating*/
	char select= '~'; /*symbol when selected*/
	int sel = 0; /*no.of selected tiles*/
	int a1=0,a2=0,b1=0,b2=0;
	int no_of_moves=0; /*no.of moves*/
	
	srand((unsigned)time(NULL)); /*random seed*/
	 
	board[a][b].c_array = arrow; /*cursor is set to first tile*/
			
	letter_array(board); /*recevies letter array for game*/
	num_compare(board); /*receives numbers for game*/
	disp_array(board); /*displays the gameboard*/
	
	while(1)
	{
		system("cls"); 
		disp_array(board);
		win(board,no_of_moves,name); /*checks to see if win conditon has been met*/
		printf("   No.of Moves = %i",no_of_moves); /*shows no.of moves to user*/
		move=0; 	  
		printf("\n\n(Numpad 8,6,4,2 to move, 5 to select. 'Q' to quit, 'I' for instructions)\n  Enter input: ");
		fflush(stdin);
		move = getch(); /*receives input*/
		
		if(move == '8') /*for moving up on the gameboard*/
		{
			if(a==0) /*upper limit of board*/
			{
				printf("Cant move outside the board!");
				Sleep(500);
				continue;
			}
			if(board[a][b].c_array!=select) /*if tile has not been selected*/
				board[a][b].c_array = ' '; /*display empty space*/
			if(board[a-1][b].c_array!=select) 
				board[a-1][b].c_array = '^'; /*new position displays cursor*/
			a--; /*position of cursor is changed*/
		}	 
		else if(move == '2') /*for moving down on the gameboard*/
		{	
			if(a==4) /*lower limit of board*/
			{
				printf("Cant move outside the board!");
				Sleep(500);
				continue;
			}
			if(board[a][b].c_array!=select)
				board[a][b].c_array = ' ';
			if(board[a+1][b].c_array!=select)
				board[a+1][b].c_array = '^';
			a++;
		}	 
		else if(move == '4') /*for moving left on the gameboard*/
		{
			if(b==0) /*left limit of board*/
			{
				printf("Cant move outside the board!");
				Sleep(500);
				continue;
			}	 	 	 
			if(board[a][b].c_array!=select)
				board[a][b].c_array = ' ';
			if(board[a][b-1].c_array!=select)	  	  	  
				board[a][b-1].c_array = '^';
			b--;
		}	 
		else if(move == '6') /*for moving right on the gameboard*/
		{	
			if(b==3) /*right limit of board*/
			{
				printf("Cant move outside the board!");
				Sleep(500);
				continue;
			}	 	 
			if(board[a][b].c_array!=select)
				board[a][b].c_array = ' '; 
			if(board[a][b+1].c_array!=select)
				board[a][b+1].c_array = '^';
			b++;			
		}
		else if(move == '5') /*for selecting a tile*/ 
		{
			if(board[a][b].c_array!=select)	/*if tile has not previously been selected*/   	   
			{
				board[a][b].c_array = select; /*displays select symbol*/
				sel++; /*selection is incremented*/
				if(sel==1) /*first selection coordinated stored*/
				{
					a1=a;
					b1=b;
				}
				if(sel==2)/*secon selection coordinates stored*/
				{
					a2=a;
					b2=b;
					
					board[a1][b1].c_array = ' '; /*symbol is reset to empty space*/
					board[a2][b2].c_array = '^'; /*cursor displayed at last selected tile*/
				}
				swap(board,&sel,&a1,&b1,&a2,&b2,&no_of_moves);/*uses stored coordinates to perform swap*/     	  	  	  
			}
			else  /*if tile is already selected, unselects it*/
			{
				board[a][b].c_array = '^'; /*displays cursor*/
				sel = 0; /*resets select count to zero*/
			}	 	 	 	 
		}
		else if(move == 'q'||move == 'Q') /*for quitting the game*/
		{
			printf("\nQuitting...");
			Sleep(1500);
			break;
		}
		else if(move == 'i'||move == 'I') /*for displaying instructions*/
		{
			system("cls");
			instructions();
			
		}
		else /*else it does nothing*/
		{
			printf("Invalid input");
			Sleep(1000);
			continue;	 
		}	  
	}	 
}

void autoplay() /*plays the game for the user*/
{
	/*This Function autoplays the game by letter sorting using letter_sort() function
	and then the numbers are sorted in similar way.When the array is sorted accordingly
	the game ends.*/
	
	struct GAME board[row][col] = {0}; 
				
	int i,j,k,l,a=0,b=0;
	int n_swap;
	char l_swap;
	int A=0,B=0,C=0,D=0,E=0;
	
	srand((unsigned)time(NULL));
					  	  
	letter_array(board);
	num_compare(board);
	system("cls");
	disp_autoplay(board);
	printf("\nSorry,colors are not available in this mode\n");
	Sleep(2000);
	printf("\n");
		
	letter_sort(board); /*sorts the letters on the board accordingly*/
	system("cls");
	disp_autoplay(board);
	
	/*Bubble Sorting of numbers*/	 	 	   	   
	for(i=0;i<row;i++) /*for each row*/
	{
		for(j=0;j<col-1;j++)/*compares 3 elements one by one*/
		{
			for(k=0;k<(col-1)-j;k++) /*with the elements behind it*/
			{	 	 	 	 	 
				if(board[i][k].n_array>board[i][k+1].n_array) /*if value is greater*/
				{	 	 	 	 	 	 	 	 	 	 	 	 
					printf("\nNow to arrange these in numerical order\nJust a moment please :)");
					
					n_swap = board[i][k].n_array;
					board[i][k].n_array = board[i][k+1].n_array; /*Greater value is swapped to the right*/
					board[i][k+1].n_array = n_swap; /*Lesser value is swapped to the left*/
					
					/*letters are swapped along with numbers*/
					l_swap = board[i][k].l_array;
					board[i][k].l_array = board[i][k+1].l_array;
					board[i][k+1].l_array = l_swap;
											
					Sleep(500);
					system("cls");
					disp_autoplay(board);
				}
			}	 	 	 
		}	 	   	   
	}
	printf("\nDONE!!!:D");	  
}

void letter_sort(struct GAME brd[row][col]) /*Sorts letter for autoplay*/
{
	/*This function sorts the letters by assigning them to a 1D array and then using 
	BubbleSort algorithm to swap them and arrage them in ascending order.Afterwards the 
	array is coverted back to 2D*/
	
	int n_1d[20];
	char l_1d[20];
	char c_1d[20];
	int n_temp,i,j,k=0,n,m,a;
	char l_temp;
	
	/*whole array is converted to 1D array*/
	for(i=0;i<row;i++) 
	{
       for(j=0;j<col;j++)
	   {  
         l_1d[k]=brd[i][j].l_array; 
		 n_1d[k]=brd[i][j].n_array;
		 c_1d[k]= ' ';
		 k++;
       } 
    }
	
	for(i=0;i<20;i++)
	{	 	 	 	 
		for(a=0;a<col;a++)
	  	{ 
			c_1d[a]= ' '; /*all characters are assigned empty space*/
		}
		for(j=0;j<19;j++)
		{
			
			if(l_1d[j]>l_1d[j+1]) /*Bubble sorting letters(ASCII values are compared)*/
			{
	        	c_1d[j+1] = ' ';
				c_1d[j] = '^'; /*arrow is displayed on lesser value*/
				
				l_temp = l_1d[j];
	        	l_1d[j] = l_1d[j+1];
	         	l_1d[j+1] = l_temp;
				
				n_temp = n_1d[j];
	        	n_1d[j] = n_1d[j+1];
	         	n_1d[j+1] = n_temp;
				
				Sleep(500);
				system("cls");
					
				for(i=0;i<row;i++) /*displays 1D array as a 2D array*/
				{	
					n=4*i; /*n selects the row based on a 1D array(element 4 of 1D = element 1 of 2D 2nd row.*/
					m=n+4; /*m selects the limit for the row(4 elements each row)*/
					
					printf("\n -----------------------\n");
					printf("|");
					for(j=n;j<m;j++)
					{
						printf("%3c  |",l_1d[j]); /*displays the letters*/
					}
					printf("\n");
					printf("|");
					for(j=n;j<m;j++)
					{
						printf("%3i  |",n_1d[j]); /*displays the numbers*/
					}
					printf("\n");
					printf("|");
					for(j=n;j<m;j++)
					{
						printf("%3c  |",c_1d[j]); /*displays empty space/arrow*/
					}	 	 
				}
				printf("\n -----------------------");
				printf("\n Hello! Since i am a computer program i cannot make intelligent decisions.I");
				printf("\n will be using a sorting algorithm, \n So sit back and relax, while i sort this out :)");
			}
        }
	}
	
	i=0;
	k=0;
	while(i<20) /*coverts 1D array back to 2D array*/
	{
		for(j=0;j<col;j++)
		{
			brd[k][j].l_array=l_1d[i];
			brd[k][j].n_array=n_1d[i];
			i++;
		}
		k++;
	}
	printf("\n i did it!");
	Sleep(2500);
	 
}

void random_letter(char *l,int *A,int *B,int *C,int *D,int *E) /*generates random letters*/
{
	int exit=0;
	int r; 
	
	
	/*The loop generates letters A,B,C,D and E and keeps a count of how many of them
	are generated, so once 4 of one letter are generated,it will regenerate till another
	letter is is made*/
	do 
	{
		r = rand()%5 +65;/*generates a random number between 65-69*/
		
		if(r==65)
		{
			if(*A<4)/*checks if 'A' limit is reached*/
			{
				*l='A'; /*generates A*/
				(*A)++; /*'A' count is incremented*/
				exit=1; /*loop exits*/
		 	}
		} 
		
		if(r==66) /*similarly for all 5 letters*/
		{
			if(*B<4)
			{
				*l='B';
				(*B)++;
				exit=1;
		 	}
		} 
		
		if(r==67)
		{
			if(*C<4)
			{
				*l='C';
				(*C)++;
				exit=1;
		 	}
		}
		
		if(r==68)
		{
			if(*D<4)
			{
				*l='D';
				(*D)++;
				exit=1;
		 	}
		}
		
		if(r==69)
		{
			if(*E<4) 
			{
				*l='E';
				(*E)++;
				exit=1;
		 	}
		}
		
	}while(exit!=1);/*loops breaks when exit=1*/			
}

void letter_array(struct GAME brd[row][col])/*assigns generated random letters to array*/
{
	int i,j;
	int A=0,B=0,C=0,D=0,E=0;
	char a; /*letter to receive letter from random_letter() function*/
			
	for(i=0;i<row;i++)/*20 letters are generated*/
	{
		for(j=0;j<col;j++)
		{
			random_letter(&a,&A,&B,&C,&D,&E); /*letter is obtained from the random_letter() function*/
			brd[i][j].l_array = a; /*element is assigned to that letter*/
		}
	}	 
}

void num_gen(int *n,int *one,int *two,int *three,int *four) /*generates random numbers*/
{
	/*generates random numbers in a similar way to random_letter() function*/
	
	int i,j,exit=0;
	
	do 
	{
		*n = rand()%4 + 1; /*numbers are generated from 1-4*/
		if(*n==1 && *one<1) /*checks number generated and checks count*/
		{	 
			(*one)++;/*count incremented*/
			exit=1;
		} 
		if(*n==2 && *two<1)
		{	 
			(*two)++;
			exit=1;
		} 
		if(*n==3 && *three<1)
		{	 
			(*three)++;
			exit=1;
		} 
		if(*n==4 && *four<1)
		{	 
			(*four)++;
			exit=1;
		} 
		
	}while(exit!=1);			
	
}

void num_array(int array[])
{
	/*each generated number is assiged to an array for later use*/
	
	int num,i,one=0,two=0,three=0,four=0;
	
	for(i=0;i<4;i++)
	{
		num_gen(&num,&one,&two,&three,&four);
		array[i] = num;
	}
}

void num_compare(struct GAME brd[row][col])
{
	/*This function gets the numbers from the num_array() function and assigns each of them randomly
	to each letter from A-E, it also makes sure each letter only has numbers assigned from 1-4 by keeping the count
	of the elements.*/
	
	int i,j;
	int num;
	int A[4],B[4],C[4],D[4],E[4]; /*5 arrays take reading from 1-4 5 times from num_array() function*/
	int a=0,b=0,c=0,d=0,e=0;
	
	num_array(A);/*an array generated is called and stored which has randomly assigned numbers from 1-4 in it*/
	num_array(B);
	num_array(C);
	num_array(D);
	num_array(E);

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(brd[i][j].l_array=='A')/*if element of letter array is 'A'*/
			{
				brd[i][j].n_array = A[a];/*assigns a number to it*/
				a++; /*increases position of elements by one(goes to next number)*/	   	   	   	   
			}
			if(brd[i][j].l_array=='B')
			{
				brd[i][j].n_array = B[b];
				b++;				  	   	   	   	    	   	   	   
			}
			if(brd[i][j].l_array=='C')
			{
				brd[i][j].n_array = C[c];
				c++;					   	   	   	   	    	   	   	   
			}
			if(brd[i][j].l_array=='D')
			{
				brd[i][j].n_array = D[d];
				d++;				;	   	   	   	   	    	   	   	   
			}
			if(brd[i][j].l_array=='E')
			{	
				brd[i][j].n_array = E[e];
				e++;					   	   	   	   ;
			}
		}
	}
}

void disp_array(struct GAME brd[row][col])
{
	/*This function displays the gameboard to the user.This does it by printing the 3 different arrays
	,one for letter, one for numbers and one for characters(arrow/select/empty).It also assigns colors 
	to the tiles of the board by assigning each letter A-E with a specific set of color(all A's are cyan)
	and assigned the same color of that letter position to the position of the number and character*/
	
	int i,j;
	
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
				
	for(i=0;i<row;i++)
	{	
		printf("\n -----------------------\n");
		printf("|");
		for(j=0;j<col;j++)
		{
			if(brd[i][j].l_array == 'A')/*if letter is 'A'*/
				SetConsoleTextAttribute ( h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);/*Assigns cyan*/
			if(brd[i][j].l_array == 'B')
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'C')
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'D')
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'E')
				SetConsoleTextAttribute ( h, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
			printf("%3c  ",brd[i][j].l_array);
			SetConsoleTextAttribute ( h, wOldColorAttrs);
			printf("|");
		}
		printf("\n");
		printf("|");
		for(j=0;j<col;j++)
		{
			if(brd[i][j].l_array == 'A')/*If letter is A*/
				SetConsoleTextAttribute ( h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);/*assigns cyan*/
			if(brd[i][j].l_array == 'B')
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'C')
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'D')
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'E')
				SetConsoleTextAttribute ( h, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
			printf("%3i  ",brd[i][j].n_array);
			SetConsoleTextAttribute ( h, wOldColorAttrs);
			printf("|");
		}
		printf("\n");
		printf("|");
		for(j=0;j<col;j++)
		{
			if(brd[i][j].l_array == 'A')/*if letter is A*/
				SetConsoleTextAttribute ( h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);/*assigns cyan*/
			if(brd[i][j].l_array == 'B')
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'C')
				SetConsoleTextAttribute ( h, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'D')
				SetConsoleTextAttribute ( h, BACKGROUND_RED | BACKGROUND_INTENSITY);
			if(brd[i][j].l_array == 'E')
				SetConsoleTextAttribute ( h, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
			printf("%3c  ",brd[i][j].c_array);
			SetConsoleTextAttribute ( h, wOldColorAttrs);
			printf("|");
		}
	}
	printf("\n -----------------------");
}

void disp_autoplay(struct GAME brd[row][col])
{
	/*This function displays the gameboard for autoplay function.This one does not have colors*/
	
	int i,j;
	
	for(i=0;i<row;i++)
	{	
		printf("\n -----------------------\n");
		printf("|");
		for(j=0;j<col;j++)/*This loop prints letter array*/
		{
			printf("%3c  ",brd[i][j].l_array);
			printf("|");
		}
		printf("\n");
		printf("|");
		for(j=0;j<col;j++)/*This loop prints number array*/
		{
			printf("%3i  ",brd[i][j].n_array);
			printf("|");
		}
		printf("\n");
		printf("|");
		for(j=0;j<col;j++)/*This loop prints character array*/
		{
			printf("%3c  ",brd[i][j].c_array);
			printf("|");
		}
	}
	printf("\n -----------------------");
}

void swap(struct GAME brd[row][col],int *select,int *a1,int *b1,int *a2,int *b2,int *N)
{
	/*This function gets the coordinates of two elements in the array and then swaps their content.
	this is done by assigning the 1st value to a temporary variable, followed by assigning the 2nd value
	to the 1st location and then assigning the 2nd location to the temporary variables content*/
	
	int n_temp = 0;
	char l_temp = ' ';
		
	if(*select ==2) /*once two elements are selected*/
	{
		/*content of two locations is swapped*/
		l_temp = brd[*a1][*b1].l_array;
		brd[*a1][*b1].l_array = brd[*a2][*b2].l_array;
		brd[*a2][*b2].l_array = l_temp;
		
		/*the numbers are also swapped*/	
		n_temp = brd[*a1][*b1].n_array;
		brd[*a1][*b1].n_array = brd[*a2][*b2].n_array;
		brd[*a2][*b2].n_array = n_temp;
		
		/*everything is reset to zero*/
		*a1=0;
		*b1=0;
		*a2=0;
		*b2=0;
		*select=0;
		(*N)++; /*count for the swaps is increased(no.of moves)*/
	}
}	

void win(struct GAME brd[row][col],int n,char name[20])
{
	/*This function determines if the user has won the game, by generating gameboard that should
	display the final positions of the tiles and compares that gameboard with the original gameboard
	of game() function, once all of the numbers and letters are in position, the user wins.*/
	
	char l_win[row][col];
	int n_win[row][col];
	int i,j,win=0;
	
	for(i=0;i<row;i++)/*letters A-E is assigned to each row*/
	{
		for(j=0;j<col;j++)/*the columns will have the same letter for one row*/
		{
			if(i==0)
				l_win[i][j] = 'A';
			if(i==1)
				l_win[i][j] = 'B';
			if(i==2)
				l_win[i][j] = 'C';
			if(i==3)
				l_win[i][j] = 'D';
			if(i==4)
				l_win[i][j] = 'E';
		}
	}
		
	for(i=0;i<row;i++)/*each row contains numbers 1-4*/
	{
		for(j=0;j<col;j++)/*the whole column will have the same number from top to bottom*/
		{
			if(j==0)
				n_win[i][j] = 1;
			if(j==1)
				n_win[i][j] = 2;
			if(j==2)
				n_win[i][j] = 3;
			if(j==3)
				n_win[i][j] = 4;
		}
	}
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(brd[i][j].l_array == l_win[i][j] && brd[i][j].n_array == n_win[i][j])/*compares each main game element with win array(letters and numbers)*/
				win++;/*count is increased for win*/				
		}
	}
	
	if(win==20)/*once win reaches 20(all 20 elements are in their respective position)*/
	{
		printf("\nYOU WON!!!");
		Sleep(2000);
		printf("\nNo.of Swaps = %i",n);
		Sleep(1000);
		printf("\n Thanks for Playing, %s",name);
		storescore(name,n);/*stores final score and name in record file*/
		exit(0);/*exits the program*/
	}	 	 
}

