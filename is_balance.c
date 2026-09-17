#include <stdio.h>
#include <string.h>

int main(void)
{
    char text[100];
    int cur_open = 0;
    int cur_close = 0;

    scanf("%99s", text);

    for (int i = 0; text[i] != '\0'; i++) {

        if (text[i] == '(') {
            cur_open++;
        }

        else if (text[i] == ')') {
            cur_close++;

            if (cur_close > cur_open) {
                printf("False cur_close > cur_open");
                return 0;
            }
        }
    }

    if (cur_open == cur_close) {
        printf("Ok");
    }
    else if (cur_open > cur_close) {
        printf("cur_open_high_false");
    }
    else {
        printf("cur_close_high_problem");
    }

    return 0;
}


