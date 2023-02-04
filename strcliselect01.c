#include	"utils.h"		/* Header file */
//Edited
void
str_cli(FILE *fp, int sockfd)
{
	int		maxfdp1;
	fd_set		rset; //file discriptor set (we are worring about reading perpouse so only read set is enough)
	char		sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);
	for ( ; ; ) 
    {
        //Replace x with the correct parameter values
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd , &rset); //first param: -name of the client's socket
        
		maxfdp1 = max(fileno(fp), sockfd) + 1; //arrays are starting with 0, thats why we do this
        // Complete the select() function
		select(maxfdp1,&rset,NULL,NULL,NULL); //wait forver until we type something

        //Replace x with the correct file descriptor value
		if (FD_ISSET(sockfd , &rset)) //check for socket file discriptor got data
        	{	
			/* socket is readable */
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			Fputs(recvline, stdout);
		}

		//Replace x with the correct file descriptor value
		if (FD_ISSET(fileno(fp) , &rset)) //this is good rather than using if-else
        	{  
			/* input is readable */
			if (Fgets(sendline, MAXLINE, fp) == NULL)
				return;		/* all done */
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}
