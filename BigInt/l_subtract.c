#include "l_subtract.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int dig_w(const char* num, int len, int index) {
    if (len - index >= 0)
    {   
        int exp = num[len - index];
        if (exp >= 48 && exp <= 57) 
            return exp - 48; 
    }   
    return 0;
}

void subtract(const char *a, const char *b) { // a - b
    char result_s[MAX_SIZE]; for (int i = 0; i < MAX_SIZE; i++) result_s[i] = '0';
    int sign = 0, max_len = 0; // sign: 0 for negative, 1 for positive
    char *top = malloc(MAX_SIZE * sizeof(char));
    char *bottom = malloc(MAX_SIZE * sizeof(char));
    int top_len = 0, bot_len = 0;
    if (strlen(a) > strlen(b)) { 
	sign = 1; 
	top_len = max_len = strlen(a); 
	strcpy(top, a); 
	strcpy(bottom, b);
	bot_len = strlen(b);
    }
    else { 
	top_len = max_len = strlen(b); 
	strcpy(top, b);
	strcpy(bottom, a);
	bot_len = strlen(a); }
    for (int i = 1; i <= max_len; i++) {
	int borrow = 0;
	if (dig_w(top, top_len, i) < dig_w(bottom, bot_len, i)) // Bottom diggest is larger - borrow
	{
	    int j = i + 1;
	    while (dig_w(top, top_len, j) == 0) {
		top[top_len - j] = '9';
		j++;
	    }
	    top[top_len - j] -= 1;
	    borrow += 10;
	}
	result_s[MAX_SIZE - i] = dig_w(top, top_len, i) + borrow - dig_w(bottom, bot_len, i) + '0';
    }
    printf("%s", result_s); // ADD SIGN
}

int main() {
    subtract("134126784012364192346129684", "12893412340612834612683419634");
    return 0; 
}

		
