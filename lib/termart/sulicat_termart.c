#include <stdio.h>
#include <stdlib.h>


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



/* the structs */
struct domain {

	char * name;
	char * text;
	char * color;
	int x;
	int y;
	int width;
	int height;
	int id;
	int length_of_array;


} domain;




// -----------------------------------------------------------------------------------------------

// initialise function, 
// make an apointer to an array of size 1 domain
struct domain * termart_init() {
 
 	struct domain * array_domain = malloc( sizeof(struct domain) );
 	array_domain[0].name = "length_of_array"; array_domain[0].id = 0;
 	array_domain[0].length_of_array = 1;

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
	arr[ length_of_array ].text = "";
	arr[ length_of_array ].color = RED;
	arr[ length_of_array ].x = 0;
	arr[ length_of_array ].y = 0;
	arr[ length_of_array ].width = 0;
	arr[ length_of_array ].height = 0;
	
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
		printf( "------\n" );
		
		if(arr[i].name != NULL)
			printf("NAME: %s\n", arr[i].name );
		if(arr[i].text != NULL)
			printf("TEXT: %s \n", arr[i].text );
		if(arr[i].color != NULL)
			printf("%sCOLOR: \n", arr[i].color );

		printf("X: %d \n", arr[i].x );		
		printf("Y: %d \n", arr[i].y );
		printf("WIDTH: %d \n", arr[i].width );
		printf("HEIGHT: %d \n", arr[i].height );


		printf( "------\n" );	
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




// this will add text to a given domain
// use: 
//		termart_add_text( struct domain obj, "domain_name", "text_to_add" )
void termart_add_text( struct domain * arr, char * name, char * text ){

	int length_of_array = arr[0].length_of_array;
	int i = 0;

	// loop through to look for the correct name
	for( i = 1; i < length_of_array; i++){
		if( arr[i].name == name ){
			arr[i].text = text; // add the text
		}
	}
}




// -----------------------------------------------------------------------------------------------




int main( int argc, char ** argv){

	struct domain * screen_obj = termart_init();
	termart_add( screen_obj, "hello" );
	termart_add( screen_obj, "cat" );
	termart_change_color( screen_obj, "cat", "black");
	termart_add_text( screen_obj, "cat", "this is the text to be added to the domain " );
	termart_to_string( screen_obj );

	return 0;

}
