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
    int index = 5;

	int len_dir;
    const char* dir = fast_basename(&len_dir);
    memcpy(BufTotal+5, dir, len_dir);
    index += len_dir;

    const char* status_str = argv[1];
    if (status_str && status_str[0] != '0') {
        char buf[10] = {'\x1b', '[', '3', '1', 'm', ' ', ' ', ' ', ' ', ' '};
        int len = strlen(status_str);
        memcpy(buf + (9 - len), status_str, len);
        memcpy(BufTotal+index, buf, 10);
        index += 10;
    } else {
        // const char* arrow = "   \x1b[33m> ";
        // memcpy(BufTotal+index, arrow, 11);
        char* bufindex = BufTotal+index; // "   \x1b[33m> " copy below;
		bufindex[0] = ' '; bufindex[1] = ' '; bufindex[2] = ' '; bufindex[3] = '\x1b'; bufindex[4] = '['; bufindex[5] = '3'; bufindex[6] = '3'; bufindex[7] = 'm'; bufindex[8] = '>'; bufindex[9] = ' '; bufindex[10] = '\0';
        index += 11;
    }
    write(STDOUT_FILENO, BufTotal, index);

}
