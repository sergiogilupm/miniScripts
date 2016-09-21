

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: ./sqlCopy SQL_keyword\n");
		exit(1);
	}

	char* inputFileName = concat (argv[1], "input.txt"); 
	char* outputFilname = concat (argv[1], "output.txt"); 
	char* keyword = argv[1]; 
	FILE *fpIn;
	FILE *fpOut;
	ssize_t read;
	char * line = NULL;
	char * bid = NULL;
	size_t len = 0;
	int count = 0;



	fpIn = fopen(inputFileName, "r");
	fpOut = fopen(outputFilname, "w+");

	if (fpIn == NULL)
	{
		fprintf(stderr, "Input file %s could not be opened\n", inputFileName);
		exit(1);
	}

	if (fpOut == NULL)
	{
		fprintf(stderr, "Output file %s could not be opened\n", outputFilname);
		exit(1);
	}

	fprintf (fpOut, "UPDATE eicache.brokers SET FAULTCATEGORY = '%s' WHERE \n", keyword);

 	while ((read = getline(&line, &len, fpIn)) != -1) {
        printf("Retrieved line of length %zu : ", read);
        printf("%s", line);
        bid = strtok( line, "\n");
        fprintf (fpOut, "BID = %s OR \n", bid);
        count++;
    }

	fclose(fpIn);
	fclose(fpOut);
	fprintf(stdout, "Processed %d lines\n", count);
	fprintf(stdout, "\n+SUCCESS\n");

	return 0;
}



