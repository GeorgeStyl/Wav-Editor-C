/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "myutils.h"
#include "wav_tools.h"
#include "crop.h"
#include "convert.h"
#include "reverse.h"


const int ISBEINT = 1;
#define is_bigendian() ( (*(char*)&ISBEINT) == 0 )

int main(int argc, char **argv) {

		
	printf("\n");
	printf("\n =======================================");
	printf("\n        WAV File Management app");
	printf("\n");
		
	if(argc < 3 ) {
		printf("\n ERROR *  Not enough command line parameters. Minimum 2. \n");
    		printf("\n Program usage:");
    		printf("\n <program> -list <input_file> ");
    		printf("\n     For listing ifromation of the <input_file> wav .\n");
	    	printf("\n <program> -reverse <input_file> <output_file> ");
    		printf("\n     For saving wav to a new file reversing the samples. \n");	    		
	    	printf("\n <program> -mono <input_file> <output_file> ");
	    	printf("\n     For saving wav to a new file with one channel only (mono). \n");
	    	printf("\n <program> -crop <input_file> <second_start> <second_end> <output_file> ");
	    	printf("\n     For cropping some seconds to a new wav file. \n");
	    	printf("\n Exiting...\n");
		return 1;
	}
	if(argc > 6) {
		printf("\n WARNING: Too many command line parameters, only the first 5 will be taken into acount...\n");
	}
	
	
	if( is_bigendian() ) {
		printf("\n System is using Big-Endian memory layout *");
	}
	else
	{
		printf("\n System is using Litle-Endian memory layout, Size of int is=%lu *", sizeof(int));
	}
	
	char *command = NULL;
	
	printf("\n command argument is :[%s], len=%lu", argv[1] , strlen(argv[1]))	;

	// int i;
	// for(i=2;i<argc;i++){
	//	printf("\n parameter %d (%d) argument is :[%s], len=%ld", i, i-1, argv[i] , strlen(argv[i]) );
	// }
	
	command = malloc( strlen(argv[1])+1 );
	strcpy(command, argv[1]);
	command[strlen(argv[1])] = 0;
	lower_case(command);	
	
	printf("\n command in lower case = [%s]", command);

	printf("\n\n"); 

	if( command[0] != '-') {
		printf("\n * Error * Bad command parameter (does not start with `-`), Exiting..." )	;		
	} 
	else 
	{
		// starting `-` confuses strcmp !!!
		// command[0]=' ';
		
	    if ( strcmp(command,"-list") == 0 )
	    {
	    	if(argc < 3) {
	    		printf("\n * ERROR *  Not enough command line parameters (<3) ) for listing file.\n");
	    		printf("\n Syntax is: <program> -list <input_file> \n");
	    		printf("\n Exiting...\n");
			} 
			else {

				byte *data_read;
				WavHeader *wavheader = read_wav(argv[2], &data_read);
				if (wavheader == NULL)
				{
					return 1;
				}
				if( data_read ==NULL )
				{
					return 1;	
				}

				if ( !is_valid_header(wavheader) )
				{
					printf(" -list: wav file corrupted\n");
					return 1;
				} 
				else
				{
					wav_list(wavheader);
				}

				if( data_read !=NULL )
					free(data_read);
				if( wavheader !=NULL )
					free(wavheader);

	    	}
		}
	    else if ( strcmp(command,"-reverse") == 0 )
	    {
	    	//  ./wavEditor -reverse sound.wav output.wav
	    	if(argc < 4) {
	    		printf("\n * ERROR *  Not enough command line parameters (<4) ) for reversing file.\n");
	    		printf("\n Syntax is: <program> -reverse <input_file> <output_file> \n");
	    		printf("\n Exiting...\n");
			} 
			else {
		    	reverse( argv[2],argv[3]);
			}
		}
	    else if ( strcmp(command,"-mono") == 0 )
	    {
	    	//  ./wavEditor -mono sound.wav output.wav
	    	if(argc < 4) {
	    		printf("\n * ERROR *  Not enough command line parameters (<4) for mono export file. Exiting...\n");
	    		printf("\n Syntax is: <program> -mono <input_file> <output_file> \n");
	    		printf("\n Exiting...\n");
			} 
			else {
		    	convert(argv[2],argv[3]);
			}
	    	
		}
	    else if ( strcmp(command,"-crop") == 0 )
	    {
	    	// ./wavEditor -crop sound.wav 2 4 output.wav
	    	if(argc < 6) {
	    		printf("\n * ERROR *  Not enough command line parameters (<6) for cropping file.\n");
	    		printf("\n Syntax is: <program> -crop <input_file> <second_start> <second_end> <output_file> \n");
	    		printf("\n Exiting...\n");
			} 
			else 
			{

				int secstart,  secend;

				int result = sscanf(argv[3], "%d", &secstart);
				if( result == EOF || result !=1 )
				{
					printf("\n -crop:: Bad start seconds given.");
				}
				else
				{
		    		result = sscanf(argv[4], "%d", &secend);
					if( result == EOF || result !=1 ) 
					{

						printf("\n -crop:: Bad end seconds given.");
					}	
					else 
					{

		    			crop(argv[2],secstart,secend,argv[5]);
					}
				}
			}
		}
		
		
		
	    else
	    {
		printf("\n * Error * Unkown command." )	;
    		printf("\n Program usage:\n");
    		printf("\n <program> -list <input_file> \n");
    		printf("\n     For listing ifromation of the <input_file> wav .\n");
	    	printf("\n <program> -reverse <input_file> <output_file> \n");
    		printf("\n     For saving wav to a new file reversing the samples. \n");	    		
	    	printf("\n <program> -mono <input_file> <output_file> \n");
	    	printf("\n     For saving wav to a new file with one channel only (mono). \n");
	    	printf("\n <program> -crop <input_file> <second_start> <second_end> <output_file> \n");
	    	printf("\n     For cropping some seconds to a new wav file. \n");
	    	printf("\n Exiting...\n");
		}
	}
    free(command);
   	
	printf("\n Exiting...\n");
	return 0;
}




























/*
int main(int argc, char** argv)
{


	if (argc < 2)
	{
		printf("ERROR: Expected file name as first argument.\n");
		return 1;
	}

	
	byte *data_read;

// read_wav_header_data returns all file's information  until the data section in the variable 'wavheader'
//  and informs via call by reference the cariable 'data_read'.Which is the data information from data section until EOF



	printf("\n argv[1]=%s....%lu \n", argv[1], strlen(argv[1]));

	if(strcmp(argv[1],"-list")==0) 
	{
		// WavHeader *wavheader = read_wav(argv[2], &data_read);
		WavHeader *wavheader = read_wav(argv[2], &data_read);
		if (wavheader == NULL)
		{
			return 1;
		}
		int i;
		printf("DATA_READ: \n");
		for (i=0;i<sizeof(data_read);i++)
			printf("data_read\n");


		if ( !is_valid_header(wavheader) )
		{
			printf(" -list: wav file corrupted\n");
		//FOR DEBUG!!!!!!!!!!!!!!!!!!!!!!!!	
		//return 1;
		}


		wav_list(wavheader);

	}
	else if (strcmp(argv[1],"-crop")==0) 
	{

		int start_sec = 2, end_sec = 4; //na ta allaksw
		if (start_sec >=0 && end_sec >0 && end_sec > start_sec )
		{
				
				if (!crop(argv[2], start_sec, end_sec, argv[5]) )
				{
					printf("\n -crop: The file could not be cropped");
				}
		}
		else
		{
			printf(" -crop: You gave invalid seconds to crop\n");
		}
	}
	else if (strcmp(argv[1],"-mono")==0) 
	{
		printf("mpainei stin convert\n");
		convert(argv[2], argv[3]  );

	}


//convert(argv[2], argv[3]  );


	free(wavheader);
	free(data_read);

	//return 0;
//}

*/
