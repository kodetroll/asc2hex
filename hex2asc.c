// hex2asc - A program that takes a string in the form of '4142434445' (hex)
// and converts it to the binary represented by the hex digits. e.g.
// 'abcde'.
//
// (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
// Author: Kodetroll
// Date: January 2015
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inbuf[120];
char outbuf[120];

int hex2int(char c);

int hex2int(char c)
{
	switch(c)
	{
		case '0':
			return(0);
			break;
		case '1':
			return(1);
			break;
		case '2':
			return(2);
			break;
		case '3':
			return(3);
			break;
		case '4':
			return(4);
			break;
		case '5':
			return(5);
			break;
		case '6':
			return(6);
			break;
		case '7':
			return(7);
			break;
		case '8':
			return(8);
			break;
		case '9':
			return(9);
			break;
		case 'a':
			return(10);
			break;
		case 'b':
			return(11);
			break;
		case 'c':
			return(12);
			break;
		case 'd':
			return(13);
			break;
		case 'e':
			return(14);
			break;
		case 'f':
			return(15);
			break;
		case 'A':
			return(10);
			break;
		case 'B':
			return(11);
			break;
		case 'C':
			return(12);
			break;
		case 'D':
			return(13);
			break;
		case 'E':
			return(14);
			break;
		case 'F':
			return(15);
			break;
		default:
			return(0);
			break;
	}
}

int main(int argc, char * argv[])
{
	int i,j,k;
	char c;

	if (argc < 2)
	{
		printf("Enter hex string (e.g. '424f54'): ");
		scanf("%78s",inbuf);
	} else {
		strcpy(inbuf,argv[1]);
	}

	memset(outbuf,0x00,sizeof(outbuf));
	i = 0;
	j = 0;
	do
	{
		c = hex2int(inbuf[i++]) * 16;
		c += hex2int(inbuf[i++]);
		outbuf[j++] = c;
	} while(i<strlen(inbuf));

	printf("%s",outbuf);

	exit(0);
}
