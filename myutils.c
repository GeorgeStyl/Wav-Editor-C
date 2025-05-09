/* Gewrgios Stylianopoulos
   A.M.: 2022201219
   email:dit19219@uop.gr

   Nikolaos Perdikoulis
   A.M.: 2022201900180
   email:dit19180@uop.gr
*/


#include "myutils.h" 

/* =================== functions =========================================== */

void mypause() {
    printf("\n Press ENTER to continue...");
    // char dummy;
    //dummy =
    getchar( );
}


//~~~~~~~~~~~~~~ left trims white space characters ~~~~~~~~~~~~~~~
void l_trim(char *instr)
{

    if (instr == NULL)
        return ;
    //if (instr[0] == 0)
    //	return instr;// empty string

    size_t l = strlen(instr);
    size_t pos = 0;

    while ( pos<l && instr[pos] !=0 && isspace(instr[pos])  )
    {
        pos++;
    }

    if(pos==l) {
        // all white spaces ?
        instr[0] = 0;
        return ;
    } else {

        int i;
        for(i=pos;i<l;i++){
            instr[i-pos]=instr[i];
        }
        instr[i-pos]=0;
        return ;
    }
}

//~~~~~~~~~~~~~~~ right trims white space characters~~~~~~~~~~~~~~~~
char* r_trim(char *instr)
{

    if (instr == NULL)
        return NULL;
    if (instr[0] == 0)
        return instr;// empty string

    size_t  l =  strlen(instr)-1;

    while( *instr !=0 && isspace( instr[l]) && l >=0 )
    {
        instr[l]=0;
        l--;
    }

    return instr;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONCERTING THE STRING TO LOWER CASE~~~~~~~~~~~~~~~~~~~~~~~~
void lower_case(char *instr)
{
    int next = -1;
    while ( next+1 <= strlen(instr) )
    {
        next++;
        instr[next] = tolower( instr[next] );
    }
}

//~~~~~~~~~~~~~~~returns a new string converted to lower case~~~~~~~~~~~~~~~~~~~~~~~
char *str_lower_case(char *instr)
{
    if(instr==NULL) return NULL;

    size_t l = strlen(instr);
    char * lstr = (char *) malloc( l +1 );

    strcpy(lstr, instr);
    int next = -1;
    while ( next+1 <= strlen(lstr) )
    {
        next++;
        lstr[next] = tolower( lstr[next] );
    }
    lstr[l] = 0 ;
    return lstr;
}



