/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/

#include <stdio.h>
#include "wav_tools.h"
/*read_wav_header_data returns all file's information  until the data section in the variable 'wavheader'
  and informs via call by reference the cariable 'data_read'.Which is the data information from data section until EOF
*/

WavHeader* read_wav(char *fname, byte** data_read)
{

	WavHeader *wavheader = NULL;

	wavheader = malloc( sizeof(WavHeader) );
	if (wavheader == NULL)
	{
		printf("\n -readwav: System could not allocate memmory");
		return NULL;
	}

	FILE *fp = NULL;

	fp = fopen(fname, "rb");

	if (fp == NULL)
	{
		printf("\n -readwav: Failed to open the file [%s]",fname);
		return NULL;
	}
	/* fread returns the number of elements it read. If this number differs from the nmemb parameter, then either an error had occurred or the End Of File was reached. */
	size_t elements_read = fread(wavheader,sizeof(WavHeader), 1, fp);

	if (elements_read != 1)
	{
		printf("\n -readwav: fread could not read wav header");
		fclose(fp);
		return NULL;
	}
	
	*data_read = malloc( wavheader->Subchunk2Size );
	if(*data_read == NULL)
	{
		printf("\n -readwav: could not allocate mem for data size %u", wavheader->Subchunk2Size);
		fclose(fp);
		return NULL;
		
	}
	//fread read from the last position of the fp pointer 
	// elements_read = fread(*data_read, wavheader->Subchunk2Size, 1, fp);
	// if (elements_read != 1)
	elements_read = fread(*data_read, sizeof(byte), wavheader->Subchunk2Size, fp);
	if (elements_read != wavheader->Subchunk2Size)
	{
		printf("\n -readwav: fread could not read wav data (all bytes)");
		fclose(fp);
		*data_read = NULL;
		return NULL;
	}
	fclose(fp);
	return wavheader; 
}

int is_valid_header(WavHeader* header)
{
	if ( !(header->ChunkID00 == 'R' && header->ChunkID01 == 'I' && header->ChunkID02 == 'F' && header->ChunkID03 == 'F') )
	{
		printf("-headerValidation: ERROR. Chunk ID did not match `RIFF` chars.\n");
		return 0;
	}
	if (!(header->Format00 == 'W' && header->Format01 == 'A' && header->Format02 == 'V' && header->Format03 == 'E') )
	{
		printf("-headerValidation: ERROR. Format did not match `WAVE`\n");
		return 0;
	}
	if (!(header->Subchunk1ID00 == 'f' && header->Subchunk1ID01 == 'm' && header->Subchunk1ID02 == 't') )
	{
		printf("-headerValidation: ERROR. Subchunk1ID did not match `fmt `\n");
		return 0;
	}
	if (!(header->Subchunk2ID00 == 'd' && header->Subchunk2ID01 == 'a' && header->Subchunk2ID02 == 't' && header->Subchunk2ID03 == 'a')  )
	{
		printf("-headerValidation: ERROR. Subchunk2ID did not match `data`\n");
		return 0;
	}

	if(header->ChunkSize<=36)
	{
		printf("-headerValidation: ERROR. Subchunk1Size too small (<=36) \n");
		return 0;
		
	}
	if(header->Subchunk2Size<1)
	{
		printf("-headerValidation: ERROR. Subchunk2Size too small (<1)\n");
		return 0;
	}
	if(header->ChunkSize< header->Subchunk2Size+36)
	{
		printf("-headerValidation: ERROR. Subchunk1Size < Subchunk2Size + 36 \n");
		return 0;
	}
	if(header->Subchunk1Size!=16)
	{
		printf("-headerValidation: WARNING. Subchunk1Size != 16\n");
	}	
	if(header->AudioFormat < 1 )
	{
		printf("-headerValidation: ERROR. AudioFormat < 1\n");
		return 0;
	}
	if(header->NumChannels < 1 )
	{
		printf("-headerValidation: ERROR. NumChannels < 1\n");
		return 0;
	}
	if(header->SampleRate <1)
	{
		printf("-headerValidation: ERROR. SampleRate < 1\n");
		return 0;
	} 
	if(header->ByteRate <1)
	{
		printf("-headerValidation: ERROR. ByteRate < 1\n");
		return 0;
	}
	if(header->BlockAlign <1)
	{
		printf("-headerValidation: ERROR. BlockAlign < 1\n");
		return 0;
	}	
	if(header->BitsPerSample <1)
	{
		printf("-headerValidation: ERROR. BitsPerSample < 1\n");
		return 0;
	}	
	if(header->BlockAlign != (header->NumChannels * header->BitsPerSample / 8 )) 
	{
		printf("-headerValidation: ERROR. BlockAlign != NumChannels * BitsPerSample / 8 \n");
		return 0;
	}	
	
	return 1;

}

void wav_list(WavHeader* header)
{
	printf("RIFF_CHUNK_HEADER\n");
	printf("=================\n");
	printf("chunkID      : %c%c%c%c\n",header->ChunkID00, header->ChunkID01, header->ChunkID02, header->ChunkID03);
	printf("chunkSize    : %u (bytes)\n", header->ChunkSize);
	printf("format       : %c%c%c%c\n",header->Format00, header->Format01, header->Format02, header->Format03);
	printf("\n");
	printf("FMT_SUBCHUNK_HEADER\n");
	printf("===================\n");
	printf("subChunk1ID  : %c%c%c\n",header->Subchunk1ID00, header->Subchunk1ID01 ,header->Subchunk1ID02); 
	printf("subChunk1Size: %d (bytes)\n", header->Subchunk1Size);
	printf("audioFormat  : %u\n",header->AudioFormat);
	printf("numChannels  : %u (1=mono, 2=stereo)\n", header->NumChannels);
	printf("sampleRate   : %u (Hz)\n", header->SampleRate);
	printf("byteRate     : %u (bytes-per-second, Bps)\n", header->ByteRate);
	printf("blockAlign   : %u (bytes)\n", header->BlockAlign);
	printf("bitsPerSample: %u (bits)\n", header->BitsPerSample);
	printf("\n");
	printf("DATA_SUBCHUNK_HEADER\n");
	printf("====================\n");
	printf("subChunk2ID  : %c%c%c%c\n",header->Subchunk2ID00, header->Subchunk2ID01, header->Subchunk2ID02, header->Subchunk2ID03);
	printf("subChunk2Size: %u (bytes)\n",header->Subchunk2Size);
}
