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

int main(int argc, char** argv) {
    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8);

    const char* dir = fast_basename();
    write(STDOUT_FILENO, "\x1b[32m", 5); // green directory
    write(STDOUT_FILENO, dir, strlen(dir));
    const char* status_str = argv[1];
    if (status_str && status_str[0] != '0') {
        char buf[4] = {' ', ' ', ' ', ' '};
        int len = strlen(status_str);
        memcpy(buf + (3 - len), status_str, len);

        write(STDOUT_FILENO, "\x1b[31m ", 6); // red error
        write(STDOUT_FILENO, buf, 4);
    } else {
        write(STDOUT_FILENO, "   \x1b[33m➜ ", 12); // yellow arrow
    }


    // buffered version
    // make buffer, size n
    // add green, size 5
    // add dir, size ?
    // add either orange arrow, size 12, or:
    // red, size 6, and buf, size 4
    // so either 5+?+{12 or 10}, 15+? or 17+?
}
