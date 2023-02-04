#include	"utils.h"		/* Header file */

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {

	if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		
	Fputs(recvline, stdout);
	
	Writen(sockfd, sendline, strlen(sendline));		
		
	}
}
