#include <stdio.h>
#include <stdlib.h>
#include "massdal/prng.h"

uint64_t hash_table1[10000]={0};
uint64_t hash_table2[10000]={0};
uint64_t hash_table3[10000]={0};

uint64_t item_name_table[10000]={0};

uint64_t top_item[10]={0};
uint64_t top_item_mean[10]={0};
uint64_t top_item_median[10]={0};

uint64_t hash_key1;
uint64_t hash_key2;
uint64_t hash_key3;

uint64_t distinct_count;

int main(int argc, char **argv)
{
    FILE *ifp1;
    unsigned long int key;
    unsigned long int tmp1, tmp2, tmp3;
    // unsigned int sum=0;
    float average=0.0;
    int mean, median;

    if (argc!=2) {
        printf("\n\nUsage... \n");
        printf("program file_name\n");
        printf("EX.\n");
        printf("a.exe trace1.txt\n");
        exit(0);
       }

  if((ifp1=fopen(argv[1],"r"))==NULL)
  {
      printf("Error!! Can't open pattern file: %s !!!\n",argv[1]);
      exit(0);
  }

  while (fscanf(ifp1, "%ld",&key)==1)
  {
    //hsah H(x) for slot position
    hash_key1=hash31(3721,917,key)%10000;
    hash_key2=hash31(3167,911,key)%10000;
    hash_key3=hash31(3907,127,key)%10000;

    //store input value
    item_name_table[hash_key1]=key;

    //hash S(x) for {+, -}
    if(hash31(2069,233,key)%2 == 0){
      hash_table1[hash_key1]++;
    }
    else{
      hash_table1[hash_key1]--;
    }
    if(hash31(3467,503,key)%2 == 0){
      hash_table2[hash_key2]++;
    }
    else{
      hash_table2[hash_key2]--;
    }
    if(hash31(1999,859,key)%2 == 0){
      hash_table3[hash_key3]++;
    }
    else{
      hash_table3[hash_key3]--;
    }

  }

  fclose(ifp1);


  for(int i=0; i<10000; i++)
  {

    if(item_name_table[i]!=0)
    {
      distinct_count++;

      //get hash key
      hash_key1=hash31(3721,917,item_name_table[i])%10000;
      hash_key2=hash31(3167,911,item_name_table[i])%10000;
      hash_key3=hash31(3907,127,item_name_table[i])%10000;

      //caculate mean
      mean = (abs(hash_table1[hash_key1])+abs(hash_table2[hash_key2])+abs(hash_table3[hash_key3]))/3;
      
      //caculeate median
      if(abs(hash_table1[hash_key1])>=abs(hash_table3[hash_key3]) && abs(hash_table1[hash_key1])<=abs(hash_table2[hash_key2]))
      {
        median=abs(hash_table1[hash_key1]);
      }
      else if(abs(hash_table1[hash_key1])>=abs(hash_table2[hash_key2]) && abs(hash_table1[hash_key1])<=abs(hash_table3[hash_key3]))
      {
        median=abs(hash_table1[hash_key1]);
      }      
      else if(abs(hash_table2[hash_key2])>=abs(hash_table1[hash_key1]) && abs(hash_table2[hash_key2])<=abs(hash_table3[hash_key3]))
      {
        median=abs(hash_table2[hash_key2]);
      }
      else if(abs(hash_table2[hash_key2])>=abs(hash_table3[hash_key3]) && abs(hash_table2[hash_key2])<=abs(hash_table1[hash_key1]))
      {
        median=abs(hash_table2[hash_key2]);
      }      
      else if(abs(hash_table3[hash_key3])>=abs(hash_table2[hash_key2]) && abs(hash_table3[hash_key3])<=abs(hash_table1[hash_key1]))
      {
        median=abs(hash_table3[hash_key3]);
      }
      else if(abs(hash_table3[hash_key3])>=abs(hash_table1[hash_key1]) && abs(hash_table3[hash_key3])<=abs(hash_table2[hash_key2]))
      {
        median=abs(hash_table3[hash_key3]);
      }      
      // printf("%d, %d, %d\n", hash_table1[hash_key1], hash_table2[hash_key2], hash_table3[hash_key3]);
      
      for(int j=9; j>=0; --j)
      {
          if(top_item_median[j]<median)
          {
              tmp1=top_item_median[j];
              top_item_median[j]=median;

              tmp2=top_item[j];
              top_item[j]=item_name_table[i];

              tmp3=top_item_mean[j];
              top_item_mean[j]=mean;

              if(j<9)
              {
                  top_item_median[j+1]=tmp1;
                  top_item[j+1]=tmp2;
                  top_item_mean[j+1]=tmp3;
              }
          }
      }

      // for(int j=9; j>=0; j--)
      // {
      //     if(top_item_mean[j]<mean)
      //     {
      //         tmp1=top_item_median[j];
      //         top_item_median[j]=median;

      //         tmp2=top_item[j];
      //         top_item[j]=item_name_table[i];

      //         tmp3=top_item_mean[j];
      //         top_item_mean[j]=mean;

      //         if(j<9)
      //         {
      //             top_item_median[j+1]=tmp1;
      //             top_item[j+1]=tmp2;
      //             top_item_mean[j+1]=tmp3;
      //         }
      //     }
      // }

    }
  }

  for(int i=0; i<10; i++)
  {
    printf("[No.%d] %ld :  %d(median)  %d(mean)\n", i+1, top_item[i], top_item_median[i], top_item_mean[i]);
  }
  // printf("Other item has 0 frequency!\n");
  printf("The number of distinct items: %d \n", distinct_count);
  
  // printf("%d, %d, %d\n", hash_table1[hash31(3721,917,2757310440)%10000], hash_table2[hash31(3167,911,2757310440)%10000], hash_table3[hash31(3907,127,2757310440)%10000]);
  return 0;
}
