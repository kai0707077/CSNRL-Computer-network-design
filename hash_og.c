#include <stdio.h>
#include <stdlib.h>
#include "massdal/prng.h"

uint64_t hash_table[10000]={0};
uint64_t item_name_table[10000]={0};
uint64_t hash_key;
uint64_t distinct_count;

int main(int argc, char **argv)
{
    FILE *ifp1;
    unsigned long int key,score,weighting;
    // char cool;
    unsigned int sum=0, i=0;
    float average=0.0;

    if (argc!=3) {
        printf("\n\nUsage... \n");
        printf("program file_name\n");
        printf("EX.\n");
        printf("a.exe weighting trace1.txt\n");
        exit(0);
       }

//atoi transfer str to int
 weighting=atoi(argv[1]);
  if((ifp1=fopen(argv[2],"r"))==NULL)
  {
      printf("Error!! Can't open pattern file: %s !!!\n",argv[2]);
      exit(0);
  }

  while (fscanf(ifp1, "%ld",&key)==1)
  {
    // i++;
    hash_key=hash31(3721,917,key)%10000;
    // printf("%d\n", hash_key);
    
    hash_table[hash_key]++;
    item_name_table[hash_key]=key;

    //printf("%llu\n", hash_key);
  }
	// printf("the last key=%ld\n",key);
  fclose(ifp1);


  for(int i=0; i<10000; i++)
  {

    
    if(hash_table[i]!=0)
    {
      distinct_count++;
      printf("[item %d] %ld :  %d\n", i+1, item_name_table[i], hash_table[i]);
    }
  }
  printf("Other item has 0 frequency!\n");
  printf("The number of distinct items: %d \n", distinct_count);

  return 0;
}
