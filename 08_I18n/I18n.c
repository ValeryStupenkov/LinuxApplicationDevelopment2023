#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <libintl.h>

#define _(STRING) gettext(STRING)

int get_answer() {
	char *buf = NULL;
	size_t size = 0;
	
	if (getline(&buf, &size, stdin) < 0) { 
		printf(_("Error! String expected\n"));
		exit(1);
	}
	
	int len = strlen(buf);
	if (len > 0 && buf[len-1] == '\n')
		buf[len-1] = '\0';
	int ans = strcmp(buf, _("Yes"));
	return ans == 0;
}

int main() {
	setlocale(LC_ALL, "");
	bindtextdomain("I18n", getenv("PWD"));
	textdomain("I18n");
	
	int a = 1;
	int b = 100;
	int mid;
	
	printf(_("Think of a number between 1 and 100\n"));
	
	while (a != b) {
		mid = (a + b) / 2;
		printf(_("Is your number greater than %d?\nPrint Yes or No\n"), mid);
		
		int is_greater = get_answer();
		if (is_greater) {
			a = mid + 1;
		}
		else {
			b = mid;
		}
	}
	
	printf(_("Your number is %d!\n"), a);
	
	return 0;
}
