#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*

This is a collection of functions to make the terminal more visualy apealing. THe goal is to be able to import and use with other programs withing the suite.

It includes the following functionality

	- create domains within the terminal
	- write within the domains, while having a wrap function
	- draw borders the domains
	- be able to change the color of the text within the domain
	- align text (optional)
	
	- have the ability to make buttons 
	- get mouse location
	- get keyboard input

	-hover effects, and color changes

	- import black and white pictures

*/	


#define MAX_CHAR_LENGTH 500

#define BLACK "\e[30m"
#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define CYAN "\e[36m"	
#define PURPLE "\e[35m"
#define BROWN "\e[33m"
#define GREY "\e[37m"
#define YELLOW "\e[33m"
#define WHITE "\e[37m"

#define BLACK_BG "\e[40m"	
#define RED_BG "\e[41m"
#define BLUE_BG "\e[44m"
#define GREEN_BG "\e[42m"
#define CYAN_BG "\e[46m"	
#define PURPLE_BG "\e[45m"
#define BROWN_BG "\e[43m"
#define GREY_BG "\e[47m"
#define YELLOW_BG "\e[43m"
#define WHITE_BG "\e[47m"

#define BOLD "\e[1m"
#define UNDELINE "\e[1m"
#define DIM "\e[2m"
#define BLINK "\e[5m"

#define CLEAR_LINE "\e[2K"	



/* the structs */
struct domain {

	char * name;
	char * text;
	char * color;
	char * color_bg;
	int x;
	int y;
	int width;
	int height;
	int id;
	int length_of_array;

	int is_crossed;
	int is_underlined;
	int is_blinking;
	int is_bold;

} domain;

int terminal_height;
int terminal_width;


// -----------------------------------------------------------------------------------------------

// initialise function, 
// make an apointer to an array of size 1 domain
struct domain * termart_init() {
 
 	struct domain * array_domain = malloc( sizeof(struct domain) );
 	array_domain[0].name = "length_of_array"; array_domain[0].id = 0;
 	array_domain[0].length_of_array = 1;
 	array_domain[0].color_bg = WHITE_BG;
 	printf("%s", WHITE );

	return array_domain;
}


// create domain function
// make a new domain, add to domain array
// change memory given to dominma array using realloc
struct domain * termart_add( struct domain * arr, char * name ) {

	int length_of_array = arr[0].length_of_array;
	arr = realloc( arr, sizeof(struct domain) * (length_of_array + 1) );

	arr[ length_of_array ].name = name;
	arr[ length_of_array ].id = length_of_array;
	//arr[ length_of_array ].text = malloc( sizeof(char) * 2 );
	arr[ length_of_array ].text = " ";
	arr[ length_of_array ].color = BLACK;
	arr[ length_of_array ].color_bg = BLACK;
	arr[ length_of_array ].x = 0;
	arr[ length_of_array ].y = 0;
	arr[ length_of_array ].width = 0;
	arr[ length_of_array ].height = 0;
	
	arr[ length_of_array ].is_underlined = 0;
	arr[ length_of_array ].is_blinking = 0;
	arr[ length_of_array ].is_crossed = 0;
	arr[ length_of_array ].is_bold = 0;
	
	arr[0].length_of_array = length_of_array + 1;

	return arr;
}






// the output finction of the array.
// given an array of domain structs, will output the array values in the format of:
//		------
//		NAME: 	_____
//		COLOR: 	_____
//		ETC: 	_____
//		------

void termart_to_string( struct domain * arr ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;
	
	for( i = 0; i < length_of_array; i++ ){		
		printf( "------------------------------------------------------------------\n" );
		
		if(arr[i].name != NULL)
			printf("NAME: \t\t%s\n", arr[i].name );
		if(arr[i].text != NULL)
			printf("TEXT: \t\t%s \n", arr[i].text );
		if(arr[i].color != NULL)
			printf("%sCOLOR: \t\t\n", arr[i].color );
		if(arr[i].color_bg != NULL)
			printf("%sCOLOR BG: \t\t\n", arr[i].color_bg );

		printf("X: \t\t%d \n", arr[i].x );		
		printf("Y: \t\t%d \n", arr[i].y );
		printf("WIDTH: \t\t%d \n", arr[i].width );
		printf("HEIGHT: \t%d \n", arr[i].height );

		printf("BLINKING: \t%d\n", arr[i].is_blinking );
		printf("CROSSED: \t%d\n", arr[i].is_crossed);
		printf("UNDERLINED: \t%d\n", arr[i].is_underlined );
		printf("BOLD: \t%d\n", arr[i].is_bold );

		printf( "------------------------------------------------------------------\n" );	
	}
}





// this will change the color of a given domain.
// it takes in the domain array, the name of the domain you want to change and the color to change it
// basic colors can be typed, caps and non-caps
void termart_change_color( struct domain * arr, char * name, char * color){

	int length_of_array = arr[0].length_of_array;
	int i = 0;

	// loop through to look for the correct name
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			
			//check the different colors
			if( color == "red" || color == "RED" || color == RED )
				arr[i].color = RED;
			else if( color == "blue" || color == "BLUE" || color == BLUE )
				arr[i].color = BLUE;
			else if( color == "green" || color == "GREEN" || color == GREEN )
				arr[i].color = GREEN;
			else if( color == "purple" || color == "PURPLE" || color == PURPLE )
				arr[i].color = PURPLE;
			else if( color == "yellow" || color == "YELLOW" || color == YELLOW )
				arr[i].color = YELLOW;
			else if( color == "white" || color == "WHITE" || color == WHITE )
				arr[i].color = WHITE;
			else if( color == "black" || color == "BLACK" || color == BLACK )
				arr[i].color = BLACK;
			else{
				arr[i].color = color;
			}
		}
	}
}




// function to allow us to change the backgound color of a domain
void termart_change_bg( struct domain * arr, char * name, char * color ){
	
	int length_of_array = arr[0].length_of_array;
	int i = 0;

	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			//check the different colors
			if( color == "red" || color == "RED" || color == RED )
				arr[i].color_bg = RED_BG;
			else if( color == "blue" || color == "BLUE" || color == BLUE )
				arr[i].color_bg = BLUE_BG;
			else if( color == "green" || color == "GREEN" || color == GREEN )
				arr[i].color_bg = GREEN_BG;
			else if( color == "purple" || color == "PURPLE" || color == PURPLE )
				arr[i].color_bg = PURPLE_BG;
			else if( color == "yellow" || color == "YELLOW" || color == YELLOW )
				arr[i].color_bg = YELLOW_BG;
			else if( color == "white" || color == "WHITE" || color == WHITE )
				arr[i].color_bg = WHITE_BG;
			else if( color == "black" || color == "BLACK" || color == BLACK )
				arr[i].color_bg = BLACK_BG;
			else{
				arr[i].color_bg = color;
			}	
		}
	}
}



// this will add text to a given domain
// use: 
//		termart_add_text( struct domain obj, "domain_name", "text_to_add" )
void termart_add_text( struct domain * arr, char * name, char * text ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;


	// loop through to look for the correct name
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			arr[i].text = malloc( sizeof(char) * strlen(text) );
			//arr[i].text = realloc( arr[i].text, sizeof(char) * strlen(text) );
			strcpy(arr[i].text, text); // add the text
		}
	}
}




// this will change the x and y position of the 
void termart_set_pos( struct domain * arr, char * name, int x, int y ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			arr[i].x = x;
			arr[i].y = y;
		}
	}
}


// function to change the size of a domain
void termart_set_size( struct domain * arr, char * name, int width, int height ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			arr[i].width = width;
			arr[i].height = height;
		}
	}
}


// toggle bold attribute
void termart_toggle_bold( struct domain * arr, char * name  ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			if (arr[i].is_bold != 0){
				arr[i].is_bold = 0;
			}else{
				arr[i].is_bold = 1;
			}
		}
	}
}



// toggle underline attribute
void termart_toggle_underline( struct domain * arr, char * name  ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			if (arr[i].is_underlined != 0){
				arr[i].is_underlined = 0;
			}else{
				arr[i].is_underlined = 1;
			}
		}
	}
}


/*
char * termart_get_text_full( struct domain * arr, char * name ){
	char * temp = malloc( sizeof(char) * termart_get_width(arr) * termart_get_height( arr ) );
	int i;
	for( i = 1; i < arr[0].length_of_array; i++){
		if( arr[i].name == name ){

			int x;
			for( x = 0; x < strlen(arr[i].text); x++ ){
				temp[x] = arr[i].text[x];
				printf("%s\n", "a" );
			}



		}
	}

	return temp;

}
*/

// toggle blinking attribute
void termart_toggle_blink( struct domain * arr, char * name  ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			if (arr[i].is_blinking != 0){
				arr[i].is_blinking = 0;
			}else{
				arr[i].is_blinking = 1;
			}
		}
	}
}


// get terminal width
int termart_get_width( struct domain * arr ){

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (int)(w.ws_col);
}


// get terminal height
int termart_get_height( struct domain * arr ){

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (int)(w.ws_row);
}



void termart_set_cursor( struct domain * arr, int x, int y ){
	printf("\e[%d;%dH", x, y );
}


void set_main_bg_color( struct domain * arr, char * color ){

	if( color == "red" || color == "RED" || color == RED )
		arr[0].color_bg = RED_BG;
	else if( color == "blue" || color == "BLUE" || color == BLUE )
		arr[0].color_bg = BLUE_BG;
	else if( color == "green" || color == "GREEN" || color == GREEN )
		arr[0].color_bg = GREEN_BG;
	else if( color == "purple" || color == "PURPLE" || color == PURPLE )
		arr[0].color_bg = PURPLE_BG;
	else if( color == "yellow" || color == "YELLOW" || color == YELLOW )
		arr[0].color_bg = YELLOW_BG;
	else if( color == "white" || color == "WHITE" || color == WHITE )
		arr[0].color_bg = WHITE_BG;
	else if( color == "black" || color == "BLACK" || color == BLACK )
		arr[0].color_bg = BLACK_BG;
	else{
		arr[0].color_bg = color;
	}

}



void termart_fill_domain( struct domain * arr, char * name ){

	int i = 1;

	for( i = 1; i < arr[0].length_of_array; i++ ){
		if(arr[i].name == name){

			arr[i].text = realloc(arr[i].text, sizeof(char) * arr[i].width * arr[i].height);
			
			//printf("%d\n", (int)strlen(arr[i].text) );
			int x;
			for( x = strlen(arr[i].text); x < (arr[i].width * arr[i].height); x++ ){

					strcat(arr[i].text, " ");
			}

		}
	}

}


// -----------------------------------------------------------------------------------------------


// this is the draw function
// it works as follows
// - clear screen
// - get the size of the terminal window
// - print all the colors and atributes
// - start drawing from the first line, by moving the cursor to a certain domain 
//	 then looping through all the text set by it

void termart_draw( struct domain * arr ){

	// set the color to the main background color
	printf("%s", arr[0].color_bg );

	//	loop through all the rows and delete them
	// clear the terminal
	int i = 0;
	int row = 0;
	int col = 0;
	for( i = 0; i < termart_get_height( arr ); i++){
		// to row position
		printf("\e[%d;%dH", row, col );
		// clear the row
		printf( CLEAR_LINE );
		row += 1;
	}

	// now terminal is clear. 
	// we will move to the top left
	row = 0;
	col = 0;
	printf("\e[%d;%dH", row, col );
	// now cycle through the domain array
	
	int num_of_filled_lines = 0;
	for( i = 1; i < arr[0].length_of_array; i++ ){

		// find how many rows will be needed to write all the text. 
		// int text_length / int domain width 
		int num_of_rows_needed = 0;
		int text_length = strlen( arr[i].text );
		num_of_rows_needed = text_length / arr[i].width;
		// cycle through every letter
		// print it in the correct spot
		int x = 0;
		row = arr[i].y;
		col = arr[i].x;
		printf("\e[%d;%dH", row, col );


		// change foreground color
		printf("%s", arr[i].color );
		// change background color
		printf("%s", arr[i].color_bg );

	

		for( x = 0; x <= text_length ; x++ ){
			// go to row and col
			printf("\e[%d;%dH", row, col );
			// print current letter
			printf("%c" , arr[i].text[x] );
			//increment col by 1
			col = col + 1;
			if( col % arr[i].width == 0  ){
				printf(" ");
				row = row + 1;
				col = arr[i].x;
			}


		}	

	}

	// following is an inclomplete fix 

	printf("%s", arr[0].color_bg );
	printf("\e[%d;%dH ", termart_get_width( arr ), termart_get_height( arr ));



}











// -----------------------------------------------------------------------------------------------



 
int main( int argc, char ** argv){

	/*

	struct domain * screen_obj = termart_init();
	termart_add( screen_obj, "hello" );
	termart_add( screen_obj, "cat" );
	termart_add( screen_obj, "three" );
	
	termart_add( screen_obj, "four" );
	termart_set_size( screen_obj, "four", 20, 20 );
	termart_set_pos( screen_obj, "four", 50,50 );
	termart_add_text( screen_obj, "four", "this is the fourth texxt" );
	termart_fill_domain( screen_obj, "four" );

	
	termart_change_color( screen_obj, "cat", "purple");
	termart_add_text( screen_obj, "cat", "this is the text to be addasdasded to the domain " );
	termart_add_text( screen_obj, "hello", "123456789101112" );
	termart_add_text( screen_obj, "three", "123456789101112" );
	termart_set_pos( screen_obj, "cat", 10, 10 );
	termart_set_pos( screen_obj, "three", 50, 10 );
	termart_set_size( screen_obj, "hello", 10,10 );
	termart_set_size( screen_obj, "three", 10,10 );
	termart_change_bg( screen_obj, "hello", "green" );
	termart_change_bg( screen_obj, "cat", "green" );
	termart_change_bg( screen_obj, "cat", "red" );
	termart_set_size( screen_obj, "cat", 10, 10);
	termart_change_color( screen_obj, "hello", "white" );
	termart_set_pos( screen_obj, "hello", 10,50 );

	termart_add( screen_obj, "four" );
	



//	termart_get_text_full( screen_obj, "hello" );
	termart_fill_domain( screen_obj, "hello" );
	termart_fill_domain( screen_obj, "cat" );
	termart_set_cursor( screen_obj, 10,10 );
	termart_draw( screen_obj );
*/


	struct domain * screen_obj = termart_init();

	termart_add( screen_obj, "obj_one" );

	termart_set_pos( screen_obj, "obj_one", 10, 10 );
	termart_change_color( screen_obj, "obj_one", "black" );
	termart_set_size( screen_obj, "obj_one", 5, 5 );
	termart_add_text( screen_obj, "obj_one", "hello worldsssss" );
	termart_change_bg( screen_obj, "obj_one", "green" );
	termart_fill_domain( screen_obj, "obj_one" );

	termart_draw( screen_obj );

	return 0;

}
