#include <stdio.h>
#include <stdlib.h>
#include "massdal/prng.h"

uint64_t hash_table[10000]={0};
uint64_t item_name_table[10000]={0};
uint64_t top_item[10]={0};
uint64_t top_item_cnt[10]={0};
uint64_t hash_key;
uint64_t distinct_count;

int main(int argc, char **argv)
{
    FILE *ifp1;
    unsigned long int key;
    // char cool;
    // unsigned int sum=0, i=0;
    float average=0.0;
    uint64_t tmp1, tmp2;

    if (argc!=2) {
        printf("\n\nUsage... \n");
        printf("program file_name\n");
        printf("EX.\n");
        printf("a.exe weighting trace1.txt\n");
        exit(0);
       }


  if((ifp1=fopen(argv[1],"r"))==NULL)
  {
      printf("Error!! Can't open pattern file: %s !!!\n",argv[1]);
      exit(0);
  }

  while (fscanf(ifp1, "%ld",&key)==1)
  {
    // i++;

    hash_key=hash31(3721,917,key)%10000; 

    //doing linear probing, put collision item to next slot
    while(item_name_table[hash_key]!=0 && item_name_table[hash_key]!=key)
    {
        hash_key++;
        if(hash_key >= 10000)
        {
            hash_key=0;
        } 
    }
    hash_table[hash_key]++;
    item_name_table[hash_key]=key;

  }

  fclose(ifp1);

  //caculate top 10 item
  for(int i=0; i<10000; i++)
  {

    if(hash_table[i]!=0)
    {
        distinct_count++;
    //   printf("[item %d] %ld :  %d\n", i+1, item_name_table[i], hash_table[i]);
        for(int j=9; j>=0; j--)
        {
            if(top_item_cnt[j]<hash_table[i])
            {
                tmp1=top_item_cnt[j];
                top_item_cnt[j]=hash_table[i];

                tmp2=top_item[j];
                top_item[j]=item_name_table[i];
                if(j<9)
                {
                    top_item_cnt[j+1]=tmp1;
                    top_item[j+1]=tmp2;
                }
            }
        }
    }
  }

  //print top 10 item 
  for(int i=0; i<10; i++)
  {
      printf("[No.%d] %ld :  %d\n", i+1, top_item[i], top_item_cnt[i]);
  }

//   printf("Other item has 0 frequency!\n");
  printf("The number of distinct items: %d \n", distinct_count);

  return 0;
}
