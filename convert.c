/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wav_tools.h"
// #include "convert.h"

//#define fname "piano2.wav"
 
int convert(char *in_filename, char *out_filename)
{

	
	printf("-mono: converting to mono...\n");

	fflush(stdout);
	byte *data = NULL;
	WavHeader *wavheader = read_wav(in_filename, &data);
	if (wavheader == NULL)
	{
		printf("-mono: Failed to read header. Conversion failed.\n");
		free(data);
		free(wavheader);
		return 0;
	}
	printf("-mono: header read.\n");

	FILE *fpout = NULL;
	fpout = fopen(out_filename, "w+b");
	if (fpout == NULL)
	{
		printf("-mono: Failed to open file [%s] for write.\n",out_filename);
		free(data);
		free(wavheader);
		return 0;
	}

	// dword _ChunkSize = wavheader->ChunkSize;

	word _NumChannels = wavheader->NumChannels;

	// dword _ByteRate = wavheader->ByteRate;

	word _BlockAlign = wavheader->BlockAlign;
	
	word _BitsPerSample = wavheader->BitsPerSample;

	int bytesPerSample = (int) _BitsPerSample / 8;

	dword _Subchunk2Size = wavheader->Subchunk2Size;


	wavheader->Subchunk2Size = _Subchunk2Size / _NumChannels;
	wavheader->ChunkSize = wavheader->Subchunk2Size + 36;
	wavheader->NumChannels = 1;
	wavheader->BlockAlign = bytesPerSample * 1;
	wavheader->ByteRate = wavheader->SampleRate  * 1 * bytesPerSample;
	
	size_t element_wrote = fwrite(wavheader, sizeof(WavHeader), 1, fpout);

	if( element_wrote != 1) {
		printf("-mono: Failed to write header to file.\n");
		fclose(fpout);
		free(data);
		free(wavheader);
		return 0;		
	}
	printf("-mono: header was written to file,...\n");


	int i,j;

	for (i=0;i<_Subchunk2Size;i += _BlockAlign) //skip next channels bytes for this sample
	{
		for (j=0;j<bytesPerSample;j++) //all bytes for channel 1 for this sample
		{
			element_wrote = fwrite(&data[i+j], sizeof(byte), 1,fpout);
			if (element_wrote == 0)
			{
				printf("-mono: Failed to write data element to file\n");
				
				fclose(fpout);
				free(data);
				free(wavheader);
				return 0;
			}

		}
	}
	free(data);
	free(wavheader);
	
	fclose(fpout);
	printf("-mono: file succesfuly converted to mono\n");
	return 1;

}
