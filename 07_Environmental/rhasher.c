#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rhash.h"
#include <errno.h>
#include <ctype.h>

#ifdef READLINE
#include "readline/readline.h"
#endif

unsigned get_hash_type(const char *hash_fun) {
    	if (!strcasecmp(hash_fun, "md5")) {
        	return RHASH_MD5;
    	} 
    	else if (!strcasecmp(hash_fun, "sha1")) {
        	return RHASH_SHA1;
    	} 
    	else if (!strcasecmp(hash_fun, "tth")) {
        	return RHASH_TTH;
    	}
}


int main() {
	rhash_library_init();
	
    	unsigned char hashed_string[64];
    	char output[150];
    	
	char *cmd = NULL;
	size_t cmd_size = 0;
    
#ifdef READLINE
    	while (cmd = readline(NULL)) {
        	cmd_size = strlen(cmd);
#else
    	while (getline(&cmd, &cmd_size, stdin) > 0) {
#endif
        	char *hash_fun = strtok(cmd, " ");
		if (hash_fun == NULL) {
            		fprintf(stderr, "Error: Wrong number of arguments!\n");
            		continue;
        	}
        		
        	char *arg = strtok(NULL, "\n ");
        	if (arg == NULL) {
            		fprintf(stderr, "Error: Wrong number of arguments!\n");
            		continue;
        	}	
        	
        	if (strcasecmp(hash_fun, "md5") && strcasecmp(hash_fun, "sha1") && strcasecmp(hash_fun, "tth")) {
            		fprintf(stderr, "Error: Unrecognized hash function.\n");
            		continue;
        	}	
        	
        	unsigned hash_type = get_hash_type(hash_fun);
        	
        	int hash_flags = isupper(hash_fun[0]) ? RHPR_HEX : RHPR_BASE64;
        	
        	if (arg[0] != '"') {
            		int res = rhash_file(hash_type, arg, hashed_string);
            		if (res == -1) {
                		fprintf(stderr, "Error: %s, %s\n", arg, strerror(errno));
                		continue;
            		}
        	} 	
        	else {
            		int res = rhash_msg(hash_type, &arg[1], strlen(&arg[1]), hashed_string);
            		if (res == -1) {
                		fprintf(stderr, "Error: %s, %s\n", arg, strerror(errno));
                		continue;
            		}
        	}
        	
        	rhash_print_bytes(output, hashed_string, rhash_get_digest_size(hash_type), hash_flags);
        	printf("%s\n", output);

        	free(cmd);
        	cmd = NULL;
    	}

    	free(cmd);
    
    	return 0;
}


