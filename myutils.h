/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/

#ifndef MY_UTILS_H

	#define MY_UTILS_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <errno.h>
	#include <ctype.h>	// for white space characters and for the fanction: "isspace"
	#include <time.h>	// for mktime

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__WINDOWS__)
	//define something for Windows (32-bit and 64-bit, this part is common)
	   #ifdef _WIN64
	      //define something for Windows (64-bit only)
	   #else
	      //define something for Windows (32-bit only)
	   #endif
	
	   #define NEWLINE '\n'
	
	#elif __APPLE__
	
	#define NEWLINE '\r'
	
	#elif __MACH__
	
	#define NEWLINE '\r'
	
	#elif __linux__
	#define NEWLINE '\n'
	
	#elif linux
	#define NEWLINE '\n'
	
	#elif __linux
	   #define NEWLINE '\n'
	
	#elif __unix__ // all unices not caught above
	    // Unix
	   #define NEWLINE '\n'
	
	#elif__unix // all unices not caught above
	    // Unix
	   #define NEWLINE '\n'
	
	#elif defined(_POSIX_VERSION)
	    // POSIX
	   #define NEWLINE '\n'
	#else
		//  "Unknown compiler"
	   #define NEWLINE '\n'
	
	#endif
	
	
	void mypause() ;
	
	//~~~~~~~~~~~~~~ left trims white space characters ~~~~~~~~~~~~~~~
	void l_trim(char *instr) ;
	//~~~~~~~~~~~~~~~ right trims white space characters~~~~~~~~~~~~~~~~
	char* r_trim(char *instr) ;
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONVERTING THE STRING TO LOWER CASE~~~~~~~~~~~~~~~~~~~~~~~~
	void lower_case(char *instr) ;
	
	//~~~~~~~~~~~~~~~returns a new string converted to lower case~~~~~~~~~~~~~~~~~~~~~~~
	char *str_lower_case(char *instr) ;
	

	
	
#endif
