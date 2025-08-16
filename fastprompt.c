#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// TODO max basename check

           /* my ( https://github.com/foreshadower ) shell prompt */
              /* takes either no args, or 1 for last exit code */

            /* note: the unrolled char assignment annoys me too. */

#define DIRCOLOR "\x1b[32m"
#define DIRCOLORLEN 5
#define BUFMAX 44
#define RESETLEN 4
#define STATUSLEN 15

#define NONDIRLEN (DIRCOLORLEN + RESETLEN + STATUSLEN)
#define DIRLENMAX BUFMAX - NONDIRLEN

inline static const char*
basename(int* len)
{
    const char* path  = getenv("PWD");
    const char* end   = path + strlen(path) - 1;
    const char* start = end;
    
    while (start > path && start[-1] != '/') start--;

    *len = (int)(end - start) + 1;
    if ((int)(end - start) > DIRLENMAX) *len = DIRLENMAX;
    return start;
}

int
main(int argc, char** argv)
{
    int         dir_len;
    const char* dir_name              = basename(&dir_len);
    char        buffer_prompt[BUFMAX] = DIRCOLOR;
    char*       buffer_reset          = buffer_prompt + DIRCOLORLEN + dir_len;
    char*       buffer_status         = buffer_reset + RESETLEN;

    memcpy(buffer_prompt + DIRCOLORLEN, dir_name, dir_len);

    buffer_reset[0] = '\x1b';
    buffer_reset[1] = '[';
    buffer_reset[2] = '0';
    buffer_reset[3] = 'm';


    if (argc > 1 && argv[1][0] != '0') {        /* !0, so "\x1b[31m" for red */

        char status_arr[15] = {'\x1b', '[', '3', '1', 'm',
                               ' ', ' ', ' ', argv[1][0],  /* 1 digit status */
                               ' ', '\x1b', '[', '0', 'm',
                               '\0'};

        if (argv[1][2] == '\0') {                          /* 2 digit status */
            status_arr[7] = argv[1][0];
            status_arr[8] = argv[1][1];
        }
        else if (argv[1][3] == '\0') {                     /* 3 digit status */
            status_arr[6] = argv[1][0];
            status_arr[7] = argv[1][1];
            status_arr[8] = argv[1][2];
        }

        memcpy(buffer_status, status_arr, STATUSLEN);

    } else {      /* add arrow " \x1b[33m>" then reset escape code "\x1b[0m" */

        buffer_status[0] = ' ';
        buffer_status[1] = ' ';
        buffer_status[2] = ' ';
        buffer_status[3] = '\x1b';
        buffer_status[4] = '[';
        buffer_status[5] = '3';
        buffer_status[6] = '3';
        buffer_status[7] = 'm';
        buffer_status[8] = '>'; 

        buffer_status[9] =  ' ';
        buffer_status[10] = '\x1b';
        buffer_status[11] = '[';
        buffer_status[12] = '0';
        buffer_status[13] = 'm';
        buffer_status[14] = '\0';

    }

    write(STDOUT_FILENO, buffer_prompt, dir_len + NONDIRLEN);

}
