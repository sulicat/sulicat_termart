this is the documentation for the sulicat_termart library
made by suli, 2016

Goal of termart:
	- ability to seperate text areas and draw them at different colors aswell as modes
	- to allow for drawing boxes, vertical and horizontal lines
	- to allow text hilighting and easy making of menus. 
	- any other usefull features where thought of on the go....

architecture:
	ARRAY of domain objects
	loop through array for every line to figure out what to draw.
	send appropriate ansi escape codes to do what each domain specifies





basic eg:-


	struct domain * screen_obj = termart_init();

	termart_add( screen_obj, "obj_two" );
	termart_add( screen_obj, "obj_one" );

	termart_set_pos( screen_obj, "obj_two", 10, 10 );
	termart_change_color( screen_obj, "obj_two", "black" );
	termart_set_size( screen_obj, "obj_two", 30, 10 );
	termart_add_text( screen_obj, "obj_two", "aasdasdadadasd" );
	termart_change_bg( screen_obj, "obj_two", "blue" );
	termart_fill_domain( screen_obj, "obj_two" );

	termart_set_pos( screen_obj, "obj_one", 40, 10 );
	termart_change_color( screen_obj, "obj_one", "black" );
	termart_set_size( screen_obj, "obj_one", 5, 5 );
	termart_add_text( screen_obj, "obj_one", "hello worldsssss" );
	termart_change_bg( screen_obj, "obj_one", "green" );
	termart_fill_domain( screen_obj, "obj_one" );

	termart_draw( screen_obj );






USE:
	
	-	initiate termart, this will return an array of malloc 0
	-	add ALL needed domains
	-	now change domain settings by using their names
	-	to draw call the draw function with given domain array from init




METHODS
	name								return
		
	termart_init()							----	struct domain *	
	termart_add( struct domain *, char * )				----	struct domain *
	termart_to_string( struct domain * )				----	VOID
	termart_change_color( struct domain *, char *, char * )		---- 	VOID
	termart_change_bg( struct domain *, char *, char * )		----	VOID
	termart_add_text( struct domain *, char *, char * )		----	VOID
	termart_set_pos( struct domain *, char *, int, int )		----	VOID
	termart_set_size( struct domain *, char *. int, int )		----	VOID
	termart_toggle_bold( struct domain *, char * )			----	VOID
	termart_toggle_underline( struct domain *, char * )		----	VOID
	termart_toggle_blink( struct domain *, char * )			----	VOID
	termart_get_height( struct domain *, char * )			----	VOID
	termart_set_cursor( struct domain *, char *, int, int )		----	VOID
	set_main_bg_color( struct domain *, char *, char * )		----	VOID
	termart_add_border( struct domain *, char *, char * )		----	VOID
	termart_fill_domain( struct domain *, char * )			----	VOID
	termart_draw( struct domain * )					----	VOID

