
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
// #include "crop.h"



int crop(char *in_filename, int start_sec, int end_sec, char *out_filename)
{


	if( start_sec<0)
	{
		printf("-crop: Start Second if less than 0.\n");
		return 0;
	}
	if(  end_sec <= start_sec )
	{
		printf("-crop: End Second if less or equal to Start Second.\n");
		return 0;
	}

	byte *data = NULL;
	WavHeader *wavheader = read_wav(in_filename, &data);
	if (wavheader == NULL)
	{
		printf("-crop: failed to read wav header\n");
		return 0;
	}
	if(data==NULL)
	{
		printf("-crop: failed to read data. \n");
		free(wavheader);
		return 0;
	}

	int bytes_per_sample = wavheader->BitsPerSample / 8 ;

	int one_sec_bytes = wavheader->SampleRate * wavheader->NumChannels * bytes_per_sample ; // one secnd in bytes

	float total_duration_secs = 0;

	total_duration_secs = (float) wavheader->Subchunk2Size / (float) one_sec_bytes;
	
	if (total_duration_secs < start_sec || total_duration_secs < end_sec)
	{
		printf("-crop: Error: The seconds you gave for crop are greater than the file's total duration\n");
		free(data);
		free(wavheader);
		return 0;
	}

	int crop_secs = end_sec - start_sec;

	int new_data_size = one_sec_bytes * crop_secs;	

	int new_chunk_size = 36 + new_data_size;

	FILE *fpout = fopen(out_filename, "w+b");
	if (fpout == NULL)
	{
		printf("-crop: Failed to open file [%s] for write.\n",out_filename);
		free(data);
		free(wavheader);
		return 0;
	}
	wavheader->ChunkSize = new_chunk_size;
	wavheader->Subchunk2Size = new_data_size;

	size_t element_wrote = fwrite(wavheader, sizeof(WavHeader), 1, fpout);

	if (element_wrote != 1)
	{
		printf("-crop: System could not write new wavheader\n");
		free(data);
		free(wavheader);
		fclose(fpout);
		return 0;
	}
	printf("-crop: wav header wrote in file %s\n", out_filename);
	fflush(stdout);

//~~~~~~~~~~~~~~~~~~~~~~~~~CROP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	printf("-crop: wrtiting data...\n");
	fflush(stdout);

	int i;

	for (i = (start_sec * one_sec_bytes); i < (end_sec * one_sec_bytes) ; i++)
	{
		// printf("%u|",data[i]);
		// fflush(stdout);
		if (fwrite(&data[i],sizeof(byte), 1, fpout) != 1)
		{
			fclose(fpout);
			printf("-crop : System could not write all data bytes\n");
			fflush(stdout);
			free(data);
			free(wavheader);
			return 0;
		}
	}
	printf("\n");
	fclose(fpout);
	free(data);
	free(wavheader);

	printf("-crop:: Finished writing cropped file %s\n",out_filename);
	fflush(stdout);
	return 1;

}
