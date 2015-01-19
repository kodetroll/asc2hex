// asc2hex - A program that takes a string of the form 'ABCDE' and converts
// it to the form of '4142434445' (hex)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inbuf[120];
char outbuf[120];

int main(int argc, char * argv[])
{
	int i,j,k;
	char c;
	char tmp[4];

	if (argc < 2)
	{
		printf("Please enter string ('abcde'): ");
		scanf("%79s",inbuf);
	} else {
		strcpy(inbuf,argv[1]);
	}

	memset(outbuf,0x00,sizeof(outbuf));
	i = 0;
	j = 0;
	do
	{
		sprintf(tmp,"%02x",inbuf[i++]);
		strncat(outbuf,tmp,strlen(tmp));
	} while(i<strlen(inbuf));

	printf("%s",outbuf);

	exit(0);
}
