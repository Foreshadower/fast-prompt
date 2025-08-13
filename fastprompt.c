#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* note: the unrolled char assignment annoys me too. */

int len_dir;
const char* dir;
char BufTotal[70] = "\x1b[32m"; // TODO max basename check

const char* basename() {
    char* path = getenv("PWD");
    const char* end = path + strlen(path) - 1;
    const char* start = end;
    while (start > path && start[-1] != '/') start--;
    len_dir = (end - start) + 1;
    return start;
}

int main(int argc, char** argv) {

    dir = basename();
    memcpy(BufTotal+5, dir, len_dir);

    char* colour_reset = BufTotal+5+len_dir;
    colour_reset[0] = '\x1b'; colour_reset[1] = '['; colour_reset[2] = '0';
    colour_reset[3] = 'm'; colour_reset[4] = ' ';

    int index = 10 + len_dir;

    char* bufindex = BufTotal+index;

    if (argv[1] && argv[1][0] != '0') {

        char buf[15] = {'\x1b', '[', '3', '1', 'm', ' ', ' ', ' ', argv[1][0],
                        ' ', '\x1b', '[', '0', 'm', '\0'};

        if (argv[1][2] == '\0') { /* two digit status into buf */
            buf[7] = argv[1][0]; buf[8] = argv[1][1];
        }
        else if (argv[1][3] == '\0') { /* three digit status into buf */
            buf[6] = argv[1][0]; buf[7] = argv[1][1]; buf[8] = argv[1][2];
        }

        memcpy(bufindex, buf, 15);

    }
    else { // const char* arrow = " \x1b[33m> ";
        bufindex[0] = ' '; bufindex[1] = ' '; bufindex[2] = ' ';
        bufindex[3] = '\x1b'; bufindex[4] = '['; bufindex[5] = '3';
        bufindex[6] = '3'; bufindex[7] = 'm'; bufindex[8] = '>';

        bufindex[9] = ' '; bufindex[10] = '\x1b'; bufindex[11] = '[';
        bufindex[12] = '0'; bufindex[13] = 'm'; bufindex[14] = '\0';
    }

    write(STDOUT_FILENO, BufTotal, index+20);
}
