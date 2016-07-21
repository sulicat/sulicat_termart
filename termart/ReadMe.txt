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
