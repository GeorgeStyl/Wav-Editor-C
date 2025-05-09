/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/

#ifndef WAV_TOOLS_H
	#define WAV_TOOLS_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	typedef unsigned char byte;

	typedef unsigned short int word;

	typedef unsigned int dword;

	typedef struct wav_Header
	{

		/*dword = 4 bytes
		  word = 2 bytes
		*/

		byte ChunkID00;

		byte ChunkID01;

		byte ChunkID02;

		byte ChunkID03;

		dword ChunkSize;

		byte Format00;

		byte Format01;

		byte Format02;

		byte Format03;

		byte Subchunk1ID00;

		byte Subchunk1ID01;

		byte Subchunk1ID02;

		byte Subchunk1ID03;

		dword Subchunk1Size ;

		word AudioFormat;

		word NumChannels;

		dword SampleRate; 

		dword ByteRate;

		word BlockAlign;
		
		word BitsPerSample; 

		byte Subchunk2ID00;

		byte Subchunk2ID01;

		byte Subchunk2ID02;

		byte Subchunk2ID03;

		dword Subchunk2Size;  // holds the nuber of bytes in data
	}WavHeader;


/*read_wav_header_data returns all file's information  until the data section in the variable 'wavheader'
  and informs via call by reference the cariable 'data_read'.Which is the data information from data section until EOF
*/

	WavHeader* read_wav(char *fname, byte** data_read);

	void wav_list(WavHeader* header);

	int is_valid_header(WavHeader* header);

#endif