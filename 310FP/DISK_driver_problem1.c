//    Final Project COMP 310
//    Your Name:
//    Your McGill ID:
//
//    You need to fill in this file for the first problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "interpreter.h"
#include "DISK_driver_problem3.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>


//char filename[150];
//FILE *partitionFile;
//char writebuffer[50000];
//char writebuffer2[50000];

int openEXAMFile(int fileID, char *name){

  if (currentPartition.last_free_block > currentPartition.total_blocks)
    return -1;

  int FATindex = 0;
  for (; FATindex < MAX_FILES; FATindex++){
    //printf("%s", fat[FATindex].filename);
    if (fat[FATindex].filename == NULL || strcmp(fat[FATindex].filename, name) == 0)
      break;
  }
  //printf("FATindex: %d", FATindex);
  int i = 0;
  for (; i < MAX_OPENFILES; i++)
    if (active_file_table_owners[i] == FATindex)
      return FATindex;

  if(fileID == MAX_OPENFILES)
    return -1; // Too many files open at the same time

  if(active_file_table[fileID] != NULL){
    printf("ERROR: Index number in use.\n");
    return -1;
  }
  //printf("%s \n", filename);
  active_file_table[fileID] = fopen(filename, "r+");
  active_file_table_owners[fileID] = FATindex;
  //printf("check: %d", active_file_table_owners[fileID]);

  if (FATindex == MAX_FILES && fat[MAX_FILES-1].filename != NULL){
    fclose(active_file_table[fileID]);
    active_file_table[fileID] = NULL;
    active_file_table_owners[fileID] = -1;

    return -1;
  }
  else if(fat[FATindex].filename == NULL){
    fat[FATindex].filename = malloc(sizeof(500));
    strcpy(fat[FATindex].filename, name);
    //printf("Filename: %s \n", fat[FATindex].filename);
    fat[FATindex].current_location = 0;
    fat[FATindex].file_length = 0;
  }
  else{
    //fat[FATindex].current_location= 0;
  }

  return FATindex;
}

int writeEXAMFile(int file, char* data){
  //file = fatindex

  if(file < 0) return 0;

  if(fat[file].current_location >= MAX_BLOCKS) return 0;

  fat[file].current_location = fat[file].file_length;

  FILE *fileptr = NULL;
  int i = 0;
  for(; i < MAX_OPENFILES; i++){
    if(active_file_table_owners[i] == file){
      fileptr = active_file_table[i];
      break;
    }
  }
  if (i == MAX_OPENFILES)
    return 1;

  fseekToNextFreeBlock(fileptr);
  for(int i = 0; i < currentPartition.block_size; i++){
    char c = *(data+i);
    if (c == 0)
       c =  '0';

  //  printf("%c", c);
    fputc(c, fileptr);
  }
  fat[file].blockPtrs[fat[file].current_location] = currentPartition.last_free_block;

  currentPartition.last_free_block += 1;
  fat[file].current_location += 1;
  fat[file].file_length += 1;
  if(fat[file].current_location < MAX_BLOCKS)
    fat[file].blockPtrs[fat[file].current_location] = -1;

  partitionFile = fopen(filename, "r+");
  updateFATOnDisk();
  fclose(partitionFile);

  return 1;

}

char *readEXAMBlock(int file){

  if (file < 0) return NULL;
  if(fat[file].current_location >= MAX_BLOCKS) return NULL;

  printf("[currloc]: %d \n", fat[file].current_location);
  int blockToRead = fat[file].blockPtrs[fat[file].current_location- fat[file].file_length];

  printf("############blockptrs################");
  for(int i = 0; i < MAX_FILES; i++){
    printf(" %d ", fat[file].blockPtrs[i]);
  }
  printf("############################");

  printf("BLOCK TO READ: %d \n", blockToRead);
  if(blockToRead == -1) return NULL;

  FILE *fileptr = NULL;
  int i = 0;
  for(; i < MAX_OPENFILES; i++)
    if(active_file_table_owners[i] == file){
            fileptr = active_file_table[i];
          //  printf("File Index: %d \n", i);
      break;
    }

  if (i == MAX_OPENFILES) return NULL;

  int offset = OFFSETS[file];


  fseekToBlockEXAM(fileptr, blockToRead, offset);

  i = 0;

  for(; i < currentPartition.block_size; i++){
    char c = fgetc(fileptr);
    if(c == '0'){
      blockBuffer[i] = '\0';
      break;
    }
    blockBuffer[i] = c;
  }
  blockBuffer[i] = '\0';

  fat[file].current_location = fat[file].current_location + 1;
  printf("after curr loc: %d \n", fat[file].current_location);

  //printf("\n check block to read: %d \n", fat[file].current_location);
  return blockBuffer;

}
