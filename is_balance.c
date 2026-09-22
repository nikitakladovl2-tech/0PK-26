#include <stdio.h>
#include <string.h>
#include <assert.h>


int is_balance(char text[]){
    int cur_open = 0;
    int cur_close = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '(') {
            cur_open++;
        }
        else if (text[i] == ')') {
            cur_close++;
            if (cur_close > cur_open) {
                return 0;
            }
        }
    }

    if (cur_open == cur_close) {
        return 1;
    }
    return 0;
}

int tests(){
    assert(is_balance("()") == 1);
    assert(is_balance(")") == 0);
    assert(is_balance("") == 1);
    assert(is_balance(")()") == 0);
    assert(is_balance(")(") == 0);
    assert(is_balance("(()())") == 1);
    printf("All test passed");
    return 0;
}

int main(void){
    char text[100];

    scanf("%99s", text);

    tests();
    return 0;
}



