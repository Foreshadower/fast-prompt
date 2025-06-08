#include <unistd.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

const char* fast_basename() {
    char* path = getenv("PWD");
    const char* start = path + strlen(path) - 1;
    while (start > path && start[-1] != '/') --start;
    return start;
}

int main(int argc, char** argv) { // TODO likely much better method
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    char BufTotal[30]; // TODO Boldly assumes basename is <18 chars
    int index = 5;

    memcpy(BufTotal, "\x1b[32m", 5);

    const char* dir = fast_basename();

    memcpy(BufTotal+5, dir, strlen(dir));
    index += strlen(dir);

    const char* status_str = argv[1];
    if (status_str && status_str[0] != '0') {
        char buf[10] = {'\x1b', '[', '3', '1', 'm', ' ', ' ', ' ', ' ', ' '};
        int len = strlen(status_str);
        memcpy(buf + (9 - len), status_str, len);
        memcpy(BufTotal+index, buf, 10);
        index += 10;
    } else {
        char* arrow = "   \x1b[33m➜ ";
        memcpy(BufTotal+index, arrow, 12);
        index += 12;
    }
    write(STDOUT_FILENO, BufTotal, index);

}
