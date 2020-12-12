#include "l_add.h"

#include <string.h>
#include <stdio.h>

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

void add(const char *a, const char *b) {
    char return_s[MAX_SIZE]; for (int i = 0; i < MAX_SIZE; i++) return_s[i] = '0';
    int len_a = strlen(a), len_b = strlen(b);
    int add_len = len_a > len_b ? len_a : len_b;
    int carry = 0, index = 1;
    for (int i = 1; i <= add_len; i++) {
	int tot = dig_w(a, len_a, i) + dig_w(b, len_b, i) + carry;
	int down = tot % 10;
	carry = tot / 10;
	return_s[MAX_SIZE - index] = down + '0';
	index++;
    }
    return_s[MAX_SIZE - index] = carry + '0';
    printf("%s", return_s);
}


int main() {
    add("12893412340612834612683419634", "134126784012364192346129684");

    return 0;
}

