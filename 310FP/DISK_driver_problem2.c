//    Final Project COMP 310
//    Your Name: Raphaelle Tseng
//    Your McGill ID: 260767650
//
//    You need to fill in this file for the second problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem4.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void closeEXAMFile (int fileID){


  int i = 0;
  for(; i < MAX_OPENFILES; i++){
    if (active_file_table_owners[i] == fileID)
      break;
  }
  if (i == MAX_OPENFILES) return;

  fclose(active_file_table[i]);
  active_file_table[i] = NULL;
  active_file_table_owners[i] = -1;
  printf("CLOSE_EXAM curr loc: %d \n", fat[fileID].current_location);
  free(pipeBuffer);


  return;

}
