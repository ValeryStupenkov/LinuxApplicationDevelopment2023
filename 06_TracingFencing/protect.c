#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <fcntl.h>

int remove(char *fname) {
	char* name = basename(fname);
	if (!strstr(name, "PROTECT")) {
		return remove(fname);
	}
	return 0;
}
