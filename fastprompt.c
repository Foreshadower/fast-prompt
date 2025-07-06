#include <unistd.h>
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

int main(int argc, char** argv) {
    char BufTotal[70] = "\x1b[90m"; // TODO max basename check
    int len_dir;
    const char* dir = fast_basename(&len_dir);
    memcpy(BufTotal+5, dir, len_dir);
    char* escapetemp = BufTotal+5+len_dir;
    escapetemp[0] = '\x1b'; escapetemp[1] = '['; escapetemp[2] = '0'; escapetemp[3] = 'm'; escapetemp[4] = ' ';

    int index = 10 + len_dir;

    char* bufindex = BufTotal+index;
    if (argv[1] && argv[1][0] != '0') {
        char buf[15] = {'\x1b', '[', '3', '1', 'm', ' ', ' ', ' ', argv[1][0], ' ', '\x1b', '[', '0', 'm', '\0'};
        if (argv[1][2] == '\0') { // second
			buf[8] = argv[1][1];
			buf[7] = argv[1][0];
		} else if (argv[1][3] == '\0') { // third
			buf[8] = argv[1][2];
            buf[7] = argv[1][1];
            buf[6] = argv[1][0];
		}
        memcpy(bufindex, buf, 15);

    } else { // const char* arrow = "   \x1b[33m> ";
		bufindex[0] = ' '; bufindex[1] = ' '; bufindex[2] = ' '; bufindex[3] = '\x1b'; bufindex[4] = '['; bufindex[5] = '3'; bufindex[6] = '3'; bufindex[7] = 'm'; bufindex[8] = '>'; bufindex[9] = ' '; bufindex[10] = '\x1b'; bufindex[11] = '['; bufindex[12] = '0'; bufindex[13] = 'm'; bufindex[14] = '\0';
    }
    write(STDOUT_FILENO, BufTotal, index+20);

}
