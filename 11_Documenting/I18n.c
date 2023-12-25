#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <libintl.h>

#define _(STRING) gettext(STRING)

/** Convert @p n into roman number.
 *
 * @param n integer to convert
 * @return string representation of @p n converted to roman number
 */
const char *to_roman(int n) {
	char *roman_numbers[] = {
            "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
            "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII","XVIII", "XIX", "XX",
            "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
            "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
            "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
            "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
            "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
            "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
            "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
            "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C",};

	return roman_numbers[n-1];
}

/** Prints help message
 */
void help() {
	printf(_("Number game\n"));
	printf(_("Usage: ./I18n [OPTIONS]\n"));
    	printf(_("Guesses a number between 1 and 100\n\n"));
    	printf(_("Options:\n"));
    	printf(_("  -r        Use roman number system\n"));
    	printf(_("  --help    Show help message\n\n"));
}


/** Get Yes or No from input
 */
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


/** @mainpage Number game
 *  Number game
 *  @section SYNOPSIS
 *  I18n [\a --help] [\a -r]
 *  @section DESCRIPTION
 *  Program guesses number between 1 and 100.
 *  It asks you questions about the number you chose and waits for Yes or No.
 *  If you print anything but Yes, it is considered as No.
 *  The number that you have chosen will be printed in the end. 
 *
 * @section OPTIONS
 * - *help* - show help message
 * - *r* - use roman number system
 */
int main(int argc, char **argv) {
	setlocale(LC_ALL, "");
	bindtextdomain("I18n", getenv("PWD"));
	textdomain("I18n");
	
	int a = 1;
	int b = 100;
	int mid;
	int is_roman = 0;
	
	if (argc > 1 && !strcmp(argv[1], "-r")) 
		is_roman = 1;
	else if (argc > 1 && !strcmp(argv[1], "--help")) {
		help();
		return 0;
	}
	
	if (is_roman){
		printf(_("Think of a number between %s and %s\n"), to_roman(1), to_roman(100));
	}
	else
		printf(_("Think of a number between 1 and 100\n"));
	
	while (a != b) {
		mid = (a + b) / 2;
		if (is_roman)
			printf(_("Is your number greater than %s?\nPrint Yes or No\n"), to_roman(mid));
		else
			printf(_("Is your number greater than %d?\nPrint Yes or No\n"), mid);
		
		int is_greater = get_answer();
		if (is_greater) {
			a = mid + 1;
		}
		else {
			b = mid;
		}
	}
	
	if (is_roman) 
		printf(_("Your number is %s!\n"), to_roman(a));
	else
		printf(_("Your number is %d!\n"), a);
	
	return 0;
}
