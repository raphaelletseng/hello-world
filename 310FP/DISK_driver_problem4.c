//    Final Project COMP 310
//    Your Name:
//    Your McGill ID:
//
//    You need to fill in this file for the fourth random problem



//	  Fill in the name of the command that you are implementing here
//    ------------------>COMMAND NAME<-----------------------------

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem3.h"
#include "DISK_driver_problem4.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *readpipeCommand(int file){

  if (file < 0) return NULL;
  if (fat[file].current_location >= MAX_BLOCKS) return NULL;

  int blockToRead = fat[file].blockPtrs[fat[file].current_location - fat[file].file_length];
  if(blockToRead == -1) return NULL;
  FILE *fileptr = NULL;
  int i = 0;
  for(; i < MAX_OPENFILES; i++){
    if(active_file_table_owners[i] == file){
      fileptr = active_file_table[i];
      break;
    }
  }
  if (i == MAX_OPENFILES) return NULL;

  fseekToBlock(fileptr, blockToRead);

  pipeBuffer = malloc(500);
  i=0;
  for(; i < currentPartition.block_size; i++){
    char c = fgetc(fileptr);
    if(c=='0'){
      pipeBuffer[i] = '\0';
      break;
    }
    pipeBuffer[i] = c;
  }
  pipeBuffer[i] = '\0';
  fat[file].current_location = fat[file].current_location +1;

  return pipeBuffer;

}
