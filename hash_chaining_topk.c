#include <stdio.h>
#include <stdlib.h>
#include "massdal/prng.h"

uint64_t top_item[10]={0};
uint64_t top_item_cnt[10]={0};

typedef struct node{
    unsigned long int flow_value;
    unsigned long int flow_count;
    struct node *next;
}node;

int main(int argc, char **argv){
    FILE *ifp1;
    unsigned long int flow_value, weighting;
    unsigned long int hash_key;
    unsigned long int distinct_count;
    unsigned long int tmp_flow_value, tmp_flow_cnt;

    node *hash_table = (node*)malloc(1000*sizeof(node));
    memset(hash_table, 0, sizeof(hash_table));

    if (argc!=2){
        printf("Usage: hash_chaining trace1.txt\n");
        exit(0);
       }

    if((ifp1=fopen(argv[1],"r"))==NULL){
        printf("Error!! Can't open pattern file: %s !!!\n",argv[2]);
        exit(0);
    }



    while (fscanf(ifp1, "%ld",&flow_value)==1){

        hash_key=hash31(3721,917,flow_value)%1000;

        //if collision happend
        if(hash_table[hash_key].flow_value!=0 && flow_value!=hash_table[hash_key].flow_value){
            node *tmp = &hash_table[hash_key]; 

            //if the slot doesn't have any linked node
            if(tmp->next == NULL){
                //creat new node
                node *new_node = (node*)malloc(sizeof(node));
                new_node->flow_value = flow_value;
                new_node->flow_count = 1;
                new_node->next = NULL;

                //insert new node 
                tmp->next = new_node;
            }
            // if the slot have alreadly linked node
            else{
                while(tmp){
                    //if already in the linked list
                    if(tmp->flow_value==flow_value){
                        tmp->flow_count +=1;
                        break;
                    }
                    //if reach the end and didn't find it 
                    else if(tmp->next==NULL){
                        //creat new node
                        node *new_node = (node*)malloc(sizeof(node));
                        new_node->flow_value = flow_value;
                        new_node->flow_count = 1;
                        new_node->next = NULL;

                        //insert new node 
                        tmp->next = new_node;
                        break;
                    }
                    tmp = tmp->next;                   
                }
            }  
        }
        // if collision doesn't happened
        else{
            hash_table[hash_key].flow_value = flow_value;
            hash_table[hash_key].flow_count += 1;            
        }


    }

    fclose(ifp1);
    

    for(int i=0; i<1000; i++){
        if(hash_table[i].flow_count!=0){
            distinct_count++;
            // printf("[item %d] %ld :  %d\n", i+1, hash_table[i].flow_value, hash_table[i].flow_count);

            node *tmp = (node*)malloc(sizeof(node));
            tmp = &hash_table[i];

            for(int j=9; j>=0; j--)
            {
                if(top_item_cnt[j]<tmp->flow_count)
                {
                    tmp_flow_cnt=top_item_cnt[j];
                    top_item_cnt[j]=tmp->flow_count;

                    tmp_flow_value=top_item[j];
                    top_item[j]=tmp->flow_value;
                    if(j<9)
                    {
                        top_item_cnt[j+1]=tmp_flow_cnt;
                        top_item[j+1]=tmp_flow_value;
                    }
                }
            }


            //go into the linked slot(which had collision happened)
            while(tmp->next){
                distinct_count++;
                tmp = tmp->next;

                for(int j=9; j>=0; j--)
                {
                    if(top_item_cnt[j]<tmp->flow_count)
                    {
                        tmp_flow_cnt=top_item_cnt[j];
                        top_item_cnt[j]=tmp->flow_count;

                        tmp_flow_value=top_item[j];
                        top_item[j]=tmp->flow_value;
                        if(j<9)
                        {
                            top_item_cnt[j+1]=tmp_flow_cnt;
                            top_item[j+1]=tmp_flow_value;
                        }
                    }
                }                
            }
        }
    }

    for(int i=0; i<10; i++){
        printf("[No.%d] %ld :  %d\n", i+1, top_item[i], top_item_cnt[i]);
    }
    // printf("Other item has 0 frequency!\n");
    printf("distinct %d\n", distinct_count);
    return 0;
}