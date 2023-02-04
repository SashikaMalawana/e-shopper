#include	"utils.h"		/* Header file */
#include <stdio.h>
#include <stdlib.h>

//[Refered link]https://www.geeksforgeeks.org/bool-in-c/
typedef enum boolean {false, true} bool;

/*This function only searches for a string part which is in the first part of the content
	you need to find. and it will stop searching when it find the delimeter.
 
 *@param key[] -> key you are looking for
 *@param str_from[] -> where you need to find if your string part exists
 *@param delimeter -> only upto this point it will search
 *@return bool -> if string part matches return true , otherwise false
 */
bool search_doc_id(char key[],char str_from[], char delimeter)
{
	int i = 0;
	for(i = 0; key[i] != '\0'; i++)
	{
		if(str_from[i] == key[i])
			continue;
		else
			return false;
	}

	if(str_from[i] == delimeter)
		return true;
	else
		return false;
}

void str_echo(int sockfd)
{
	int selected_quantity= 1;
	int Tab_count = 0;
	int line_no = 0;
	int count;
	int time_c;

	char selected_item_Id[5];
	char selected_categ[10];
	char item_id_c[3];
	char confirmation[3];
	char confirmation_a[3];
	char buy_status[3];
	char pay_status[3];
	double totalPrice = 0;

	ssize_t	n;
	char line[MAXLINE];

	bool is_available = false;
	bool is_atleast_one = false;

	char item_list[300];
	char buff_temp[255];
	char res[256];
	char res_out[1000];
	char buff[1000];
	char buffer[255];
	char text_line[255];
	char newline[255];

	char pid[3];
	int pqt;

	char sid[3];
	char stype[20];
	char sbrand[20];
	int sqt;
	double sprice;

	char aid[3];
	char atype[20];
	char abrand[20];
	int  aqt;
	double aprice;

	char strTotalPrice[20];
	char strprice[20];
	int fqt;
	

	char *ret;
	char *ret1;


	FILE * fPtr;
	FILE * fTemp;
	FILE *fp;
	FILE *fp_spec;

	
	FILE *fp3 = fopen("welcome_message.txt", "r");
	if(fp3==NULL)
	{
		snprintf(res_out, sizeof(res_out),"cant open file");
		return 1;
	}
	while(!feof(fp3))
	{
	fgets(res, sizeof(res), fp3);
	//To determine the end of the file in the middle of the loop
	//otherwise it may print last line twice
	//[Reference Link ]https://stackoverflow.com/questions/29143338/c-program-prints-the-last-line-twice-file-i-o
	if (feof(fp3))
		break;
		snprintf(line, sizeof(line), res);
		n = strlen(line);
		Writen(sockfd, line, n);
	}
	fclose(fp3);

	for ( ; ; )
	{
		if ((n = Readline(sockfd, line, MAXLINE)) == 0)
		return;		/* connection closed by other end */

		//https://regex101.com/
	
		//Checking for specialization code format.
		if (sscanf(line, "%s", & selected_categ) == 1)
		{
		//Checking for specialization length entered
		if (strlen(selected_categ) == 4)
		{
			fp_spec = fopen("database.txt", "r");
			//Display table title fields Id and Name
			snprintf(line, sizeof(line), "PID Product type	Brandname Available quantity Unitprice\n");
			n = strlen(line);
			Writen(sockfd, line, n);
			while(!feof(fp_spec))
			{
			fgets(item_list,600,fp_spec);
			//To determine the end of the file in the middle of the loop
			//otherwise it may print last line twice
			//[Reference Link ]https://stackoverflow.com/questions/29143338/c-program-prints-the-last-line-twice-file-i-o
			if (feof(fp_spec))
					break;

			ret = strstr(item_list, selected_categ);
			if (ret != NULL)
			{
			//is_atleast_one gets true if there is the item exists
			is_atleast_one = true;
			int i;
			for (i = 0; item_list[i] != '\0'; i++)
			{
			if ((item_list[i] == '	') && (Tab_count < 5))
			{
				Tab_count++;
				if (Tab_count < 5)
				{
					 buff_temp[i] = ' ';
					 continue;
				}
				if (Tab_count == 5)
				{
					 buff_temp[i] = '\0';
					 break;
				}
			}
			buff_temp[i] = item_list[i];
			}
			Tab_count = 0;
						
				//buff_temp -> store Item PID and Name only
				 snprintf(line, sizeof(line), "%s\n", buff_temp);
				 n = strlen(line);
				 Writen(sockfd, line, n); //write line
			}
			}
			fclose(fp_spec);
			//If not found error generates and exit
			if(!is_atleast_one) {
			snprintf(line, sizeof(line), "Sorry item not found!\n");
			n = strlen(line);
			Writen(sockfd, line, n);
			exit(0);
			}
			for ( ; ; ) {
			if ((n = Readline(sockfd, line, MAXLINE)) == 0)
				return;		/* connection closed by other end */

			//[Reference Link ]https://regex101.com/
			
			//
			if (sscanf(line, "%s %s %d", &buy_status, &selected_item_Id, &selected_quantity) == 3)
			{
				//accept code further validation
				if((selected_quantity > 0) && (buy_status[0] == 'b'))
				{
					//start to read the file line by line, buff is a line of the text file
					fp = fopen("database.txt", "r");
					while(!feof(fp))
					{
					fgets(buff,255,fp);
					 if (feof(fp))
									break;
								

								ret1 = strstr(buff, selected_item_Id);
								
								
								if(ret1 != NULL)
								{
									
			if(sscanf(buff, "%s	%s	%s	%d	%lf", &aid , &atype, &abrand, & aqt, & aprice) == 5)
						{
										
					if(sqt >= selected_quantity)
						{
								//printf("%d %d",sqt , selected_quantity);
								//toPayment = true;
											
									totalPrice = selected_quantity*sprice;
								
									fqt = sqt-selected_quantity;
									printf("%d", fqt);
									strcat(line1, "Total cost : ");
									sprintf(strTotalPrice, "%.2lf", totalPrice);
									strcat(line1, strTotalPrice);
									snprintf(line1, sizeof(line1),  " press p to confirm the payment");
											
											n = strlen(line1);
											Writen(sockfd, line1, n); //write line
											delay(1);
											
											break;
						}
							else
									{
										snprintf(line, sizeof(line), "accept code error!\n");
										n = strlen(line);printf("swrite line");
										Writen(sockfd, line, n); //write line
									}
						}
								
									

							}
							
							fclose(fp);
							
							//if(toPayment)
							//{
								
								for( ; ; )
								{
									
									
									if ((n = Readline(sockfd, line, MAXLINE)) == 0)
										return;		/* connection closed by other end */
												
									if (sscanf(line, "%s %s %d", &pay_status , &pid, &pqt) == 3)
				{
					if((selected_quantity == pqt) && (pay_status[0] == 'p')&&(strcmp(selected_item_Id, pid) == 0))
					{
							snprintf(line, sizeof(line), "Your appointment process successfully!\n\n");
											
											fflush(stdin);
											
											fPtr  = fopen("Stock.txt", "r");
											fTemp = fopen("replace.tmp", "w");
											
											 if (fPtr == NULL || fTemp == NULL)
							{
							//Unable to open file hence exit
						       snprintf(line, sizeof(line), "File access error! Try little while.\n");
												n = strlen(line);
												Writen(sockfd, line, n);
												exit(0);
											}
											
											strcat(text_line, sid);
											strcat(text_line, "	");
											strcat(text_line, stype);
											strcat(text_line, "	");
											strcat(text_line, sbrand);
											strcat(text_line, "	");
											strcat(text_line, fqt);
											strcat(text_line, "	");
											sprintf(strprice, "%.2lf", sprice);
											strcat(text_line, strprice);
											
											while ((fgets(buffer, 255, fPtr)) != NULL)
								{
			if(sscanf(buff, "%s	%s	%s	%d	%lf", &aid , &atype, &abrand, &aqt, &aprice) == 5)
									{
										if(strcmp(sqt, aqt) == 0)
										fputs(text_line, fTemp);
												else
										fputs(buffer, fTemp);
											}		
								}
											
											fclose(fPtr);
											fclose(fTemp);
											
											remove("database.txt");
											
											rename("replace.tmp", "database.txt");

											
											n = strlen(line);
											Writen(sockfd, line, n);
											exit(0);
						}
					else
						snprintf(line, sizeof(line), "Accept Payment code does not meet the correct format!\n");
											n = strlen(line);
											Writen(sockfd, line, n); //write line
										
							}
					else
						snprintf(line, sizeof(line), "Accept Payment code does not meet the correct format!\n");
										n = strlen(line);
										Writen(sockfd, line, n); //write line
									
								}											
										
											
											
									
			snprintf(line, sizeof(line), "Accept code does not meet the correct format!\n");
			}
			else
			snprintf(line, sizeof(line), "accept code error!\n");
			n = strlen(line);
			Writen(sockfd, line, n); //write line
			}
		}
		else
		snprintf(line, sizeof(line), "Specialization code error!\n");
		}
		else
		snprintf(line, sizeof(line), "Specialization code error!\n");

		n = strlen(line);
		Writen(sockfd, line, n); //write line
		}
	}
}

