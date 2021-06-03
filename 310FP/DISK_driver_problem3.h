//    Final Project COMP 310
//    Your Name:
//    Your McGill ID:
//
//    DISK_driver_problem3.h
//
char OFFSETS[MAX_FILES];

int seekEXAMFile(int fileID, int offset);
void fseekToBlockEXAM(FILE *file, int blockID, int offset);
