//    Final Project COMP 310
//    Your Name:
//    Your McGill ID:
//
//    You need to fill in this file for the third problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem3.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

char writebufferEXAM[50000];
char OFFSETS[MAX_FILES];


int seekEXAMFile(int fileID, int offset){
  int blocks = offset/currentPartition.block_size;
  printf("\n blocks in seek: %d \n", blocks);
  FILE *fileptr;
//  fileID = actindex;
  fileptr = active_file_table[fileID];
  if (fileID == MAX_OPENFILES) return -1;
//  int blockToRead = fat[fileID].blockPtrs[fat[fileID].current_location];
//  if (blockToRead == -1) return NULL;

  // Get fat index
  int FATindex = 0;
  for (; FATindex < MAX_FILES; FATindex++){
    //printf("%s", fat[FATindex].filename);
    if (fat[FATindex].filename == NULL) //|| strcmp(fat[FATindex].filename, name) == 0)
      break;
  }
  FATindex = FATindex -1;
  //printf("FATindex: %d", FATindex);
  if (active_file_table_owners[fileID] == FATindex)
      printf("fatindex: %d \n", FATindex);

  //printf(" %d ", (fat[FATindex].current_location + offset));
  //printf("\n fatINdex: %d", FATindex);
  //printf(" \n file lenght %d", fat[FATindex].file_length);

  if (((fat[FATindex].current_location-fat[FATindex].file_length)*5 + offset) >= (fat[FATindex].file_length*5)){
    printf("ERROR: Out of bounds. Stopped at end of file. \n");
    return 1;
  }

  if ((fat[FATindex].current_location*5 + offset) < 0){
    printf("ERROR: Out of bounds. Stopped at start of file. \n");
    return 1;
  }

  //printf("\n curr_loc: %d ", fat[FATindex].current_location);

  return FATindex;


}

void fseekToDataSectionEXAM(FILE *file){
  fseek(file, 0, SEEK_SET);
  for(int i = MAX_FILES*2 + 1; i > 0; i--)
    fgets(writebufferEXAM, 5000, file);
  return;
}

void fseekToBlockEXAM(FILE *file, int blockID, int offset){

  fseekToDataSectionEXAM(file);
  for (int i = blockID * currentPartition.block_size; i > 0 ; i--){
    char c = fgetc(file);
  }
  fseek(file, offset, SEEK_CUR);
  return;
}

void fseekToNextFreeBlockEXAM( FILE *file, int offset){
  fseekToBlockEXAM(file, currentPartition.last_free_block, 0);
  return;
}
