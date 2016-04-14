#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h> // because of access()

#define DEF_FILE 1 // if file that return 1
#define DEF_DIR  3 // if dir return 3
#define DEF_NONE 5 // else return 5

#define DEF_FILE_NOT_EXIST 7 // if not exist file return 7

int isFILEDIR( char *flag)
{
	struct stat myResult;

	char *ptr;
	int return_val = -1;

	if(access(flag, F_OK) != -1)
	{
		// file exist
	}else {
		// file not exist
		return_val = DEF_FILE_NOT_EXIST;
		return return_val;
	}

	if(lstat(flag, &myResult) < 0)
	{
		printf("Error of lstat\n");
		exit(0);
	}

	if(S_ISREG(myResult.st_mode) )
	{
		ptr = "regular file";
		return_val = DEF_FILE;
	}
	else if(S_ISDIR(myResult.st_mode))
	{
		ptr = "directory";
		return_val = DEF_DIR;
	} else
	{
		ptr = "unknown mode";
		return_val = DEF_NONE;
	}
	return return_val;
}

int main(int arg, char *argv[])
{
	if(arg != 3)
		exit(1);

	int val1 = (int)isFILEDIR(argv[1]); // type casting
	int val2 = (int)isFILEDIR(argv[2]); // type casting
	int sum = val1 + val2;

	char *pstr1 = argv[1];
	char *pstr2 = argv[2];

	switch(sum)
	{
		case 2:
		{
			if(strcmp(pstr1, pstr2) == 0 )
			{
				printf("Error same filename! \n");
			}
		} break;

		case 4:// move from src to dst
		{
			char fullName[256] = {0, }; // array initializing
			sprintf(fullName, "%s/%s", pstr2, pstr1); // step of dir/file
			if(rename(pstr1, fullName))
			{
				printf("Completed move from %s to %s\n", pstr1, pstr2);
			}
		} break;

		case 8:// rename
		{
			if(rename(pstr1, pstr2) == 0)
			{
				printf("Completed rename from %s to %s\n", pstr1, pstr2);
			}
		}break;
	}
	return 0;
}
