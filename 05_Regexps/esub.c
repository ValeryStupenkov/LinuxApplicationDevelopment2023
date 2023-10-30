#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

#define MAXBAGS 10

int main(int argc, char *argv[]) {
	int i;
	regex_t regex;
	int rc;
	char errbuf[100];
	regmatch_t bags[MAXBAGS];
	int num_bags = 0;

	if (argc != 4) {
		printf("Error: Must be exactly three parameters \n");
		exit(1);
	}
		
	char* subst = argv[2];
	char* str = argv[3];
	
	if ((rc = regcomp(&regex, argv[1], REG_EXTENDED))) {
		regerror(rc, &regex, errbuf, 100);
		printf("Error: regcomp() failed with %s \n", errbuf);
		exit(EXIT_FAILURE);
	}
	
        if ((rc = regexec(&regex, str, MAXBAGS, bags, REG_EXTENDED)) == 0) {
        	for(i = 0; i<MAXBAGS && bags[i].rm_so>=0; i++) {
                	int b = bags[i].rm_so, e = bags[i].rm_eo;
                        printf("%d %d/%d\t%.*s\n", i, b, e, e - b, str + b);
                        num_bags++;
                }
	}
	else {
		regerror(rc, &regex, errbuf, 100);
		printf("Error: regexec() failed with %s \n", errbuf);
		exit(EXIT_FAILURE);
	}
	
	char *result = calloc(strlen(str) + strlen(subst), sizeof(char));
	int offset = bags[0].rm_so;
	strncpy(result, str, offset);
	
	int len_subst = strlen(subst);
	int j = 0;
	for (i = 0; i < len_subst; i++) {
		if (subst[i] == '\\' && i < len_subst-1) {
			if (isdigit(subst[i+1])){
				if (num_bags == 0 || j >= num_bags || subst[i+1]-'0' >= num_bags) {
					printf("Error: bag does not exist! \n");
					free(result);
					regfree(&regex);
					exit(1);
				}
				int reg_len = bags[j].rm_eo - bags[j].rm_so;
				strncpy(result + offset, str + bags[j].rm_so, reg_len);
				offset += reg_len;
				i++;
				j++;
			}
			else if (subst[i+1] == '\\') {
				result[offset] = subst[i];
				offset++;
				i++;
			}
			
		}
		else {
			result[offset] = subst[i];
			offset++;
		}
	}
	
	strncpy(result  + offset, str + bags[num_bags-1].rm_eo, strlen(str) - bags[num_bags-1].rm_eo);
	printf("%s\n", result);
	
	regfree(&regex);
	free(result);
	return 0;
}
