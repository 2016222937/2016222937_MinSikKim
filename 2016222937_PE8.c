#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main()
{
	FILE *fp;
	char buf[BUFSIZ];
/*	char buf[100];
	int i = 0;*/

	fp = popen("ls", "r");
//	fp = popen("ls", "r");

	while(fgets(buf, BUFSIZ, fp) != NULL)
		fputs(buf, stdout);
/*	while(fgets(buf, 100, fp) != NULL)
		printf("%3d %s", i++, buf);*/
	pclose(fp);
	return 0;
}
/*
FILE *popen2(const char *command, const char *mode)
{
		
}*/
