#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define ESC 27

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Error: no file name!\n");
		return 1;
	}
	
	FILE *f = fopen(argv[1], "r");
	
	if (f == NULL) {
		printf("Error while opening file!\n");
		return 1;
	}
	
	initscr();
        noecho();
        cbreak();
        printw("File: %s", argv[1]);
        refresh();
        
        int win_lines = LINES-4;
        int win_cols = COLS-4;

	WINDOW *win = newwin(win_lines, win_cols, 2, 2);
    	
    	keypad(win, TRUE);
        scrollok(win, TRUE);
        box(win, 0, 0);
        wmove(win, 1, 0);
        
        int c = 0;
	char buf[win_cols];
	char **lines;
	int i, s_cnt, count = 0;
	
	while(fgets(buf, win_cols, f)){
		lines = realloc(lines, sizeof(*lines)*(count+1));
		lines[count] = strdup(buf);
		count++;
	}
	
	for(i=0; i<win_lines-3; i++){
		wprintw(win,"\t%s", lines[i]);
	}
	
	s_cnt = 2;
	while((c = wgetch(win)) != ESC) {
		if (c == ' ') {
			werase(win);
			wprintw(win, "\t\n");
			while(i<(s_cnt*(win_lines-3)) && i<count){
				wprintw(win, "\t%s", lines[i]);
				i++;
			}
			s_cnt++;
		}

                box(win, 0, 0);
                wrefresh(win);
        }
        
	for (i=0; i<count; i++) {
		free(lines[i]);
	}
	free(lines);
        
	fclose(f);
        endwin();
        
	return 0;
}
