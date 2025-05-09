
/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/
#include <stdio.h>
#include <string.h>

#include "wav_tools.h"
// #include "reverse.h"


int reverse( char *in_filename, char *out_filename) {

	byte *data = NULL;
	WavHeader *wavheader = read_wav(in_filename, &data);
	if (wavheader == NULL)
	{
		printf("-reverse: failed to read wav header\n");
		return 0;
	}

	if(data==NULL)
	{
		printf("-reverse: failed to read data. \n");
		free(wavheader);
		return 0;
	}


	FILE *fpout = fopen(out_filename, "w+b");
	if (fpout == NULL)
	{
		printf("-reverse: Failed to open file [%s] for write.\n",out_filename);
		free(data);
		free(wavheader);
		return 0;
	}

	// no changes to wav header. write it as it is
	size_t element_wrote = fwrite(wavheader, sizeof(WavHeader), 1, fpout);

	if (element_wrote != 1)
	{
		printf("-reverse: System could not write new wavheader\n");
		free(data);
		free(wavheader);
		fclose(fpout);
		return 0;
	}
	printf("-reverse: wav header wrote in file %s\n", out_filename);
	fflush(stdout);


	int datasize = wavheader->Subchunk2Size; 

	printf("-reverse: writing data %d bytes [in %d bytes block]...\n",datasize,wavheader->BlockAlign);
	int i;
	int buflen = wavheader->BlockAlign; 		// numChannels * BytesPerSample ;	
	int startsize = datasize - wavheader->BlockAlign;
	for(i=startsize; i>=0; i -= buflen) 
	{		
		byte buf[buflen];
		int k;
		for(k=0; k<buflen; k++ ) {			
			buf[k] = data[i+k];	
		}
		if( fwrite(&buf,sizeof(byte),buflen,fpout) != buflen )
		{
			printf("\n -reverse: * ERROR * Writing #%d block of wav Data !",i);
			free(data);
			free(wavheader);
			fclose(fpout);
			return 0;				
		} 

	}
	free(data);
	free(wavheader);
	fclose(fpout);
	printf("-reverse: Finished reversing wav. New file is %s",out_filename);
	fflush(stdout);
	return 1;
}