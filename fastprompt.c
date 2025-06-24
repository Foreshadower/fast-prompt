#include <unistd.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

const char* fast_basename(int* length) {
    char* path = getenv("PWD");
    const char* end = path + strlen(path) - 1;
    const char* start = end;
    // const char* start = path + strlen(path) - 1;
    while (start > path && start[-1] != '/') start--;
    *length = (end - start) + 1;
    return start;
}

int main(int argc, char** argv) { // TODO likely much better method
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    char BufTotal[30] = "\x1b[32m"; // TODO Boldly assumes basename is <18 chars
    int len_dir;
    const char* dir = fast_basename(&len_dir);
    memcpy(BufTotal+5, dir, len_dir);
    int index = 5 + len_dir;

    // const char* status_str = argv[1];

    char* bufindex = BufTotal+index;
    if (argv[1] && argv[1][0] != '0') {
        // char buf[10] = {'\x1b', '[', '3', '1', 'm', ' ', ' ', ' ', ' ', ' '};
        char buf[10] = {'\x1b', '[', '3', '1', 'm', ' ', ' ', ' ', argv[1][0], ' '};
        // int len = strlen(status_str);
        // instead just check indexes 1 2 and 3 directly, only place for em!
		if (argv[1][2] == '\0') { // second
			buf[8] = argv[1][1];
			buf[7] = argv[1][0];
		} else if (argv[1][3] == '\0') { // third
			buf[8] = argv[1][2];
            buf[7] = argv[1][1];
            buf[6] = argv[1][0];
		}
        memcpy(bufindex, buf, 10);

    } else { // const char* arrow = "   \x1b[33m> ";
		bufindex[0] = ' '; bufindex[1] = ' '; bufindex[2] = ' '; bufindex[3] = '\x1b'; bufindex[4] = '['; bufindex[5] = '3'; bufindex[6] = '3'; bufindex[7] = 'm'; bufindex[8] = '>'; bufindex[9] = ' ';
    }
    write(STDOUT_FILENO, BufTotal, index+10);

}
