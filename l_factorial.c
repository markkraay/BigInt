#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
typedef unsigned long long big_int;
void  multiply_strings(char** top, char** bottom, int t_or_b, int *main_l, int temp_l){ // Multiply the strings, reassign the return string to main's memory, clear temp_n's memory
    char result[MAX_SIZE];
    for (int i= 0; i < MAX_SIZE; i++) result[i] = '0';
    
    int offset = 0;
    int carry = 0;
    int b_i = (t_or_b == 0) ? temp_l - 1: (*main_l) - 1;  
    int t_i = (t_or_b == 0) ? (*main_l) - 1: temp_l - 1;
    for (b_i; b_i >= 0; b_i--)
    {
        offset += 1;
        carry = 0;
        int t_offset = 0;
        if ((*bottom)[b_i] != '0')
        {
          for (int ti = t_i; ti >= 0; ti--)
          {
              int mult = ((*bottom)[b_i] - 48) * ((*top)[ti] - 48) + carry;
              carry = 0;
              int added_r_mult = ((char)result[MAX_SIZE - t_offset - offset] - 48) + mult;
              carry = added_r_mult / 10; 
              int mod = added_r_mult % 10; 
              result[MAX_SIZE - t_offset - offset] = mod + '0';
              t_offset++;
          }
          if (carry > 0) {
              int carry_o = carry / 10;
              int carry_mod = carry % 10;
              result[MAX_SIZE - t_offset - offset] = carry_mod + '0';
              result[MAX_SIZE - t_offset - offset - 1] = carry_o + '0';
          }
        }
    }
    int len = MAX_SIZE;
    int i = 0;
    if (t_or_b == 0) // t_or_b == 0; assign memory to top because top is main
    {
        while (1){ if (result[i] == '0') { len--; i++;} else { break; } }
        *main_l = len;
        memset(*top, '0', len);
        for (i = 0; i < len; i++)
	{
            (*top)[len-i-1] = result[MAX_SIZE-1-i];
        }
        memset(*bottom, '0', MAX_SIZE);
    }
    else
    {   
        while (1){ if (result[i] == '0') { len--; i++;} else { break; } }
        *main_l = len;
        memset(*bottom, '0', len);
        for (i = 0; i < len; i++)
	{
            (*bottom)[len-i-1] = result[MAX_SIZE-1-i];
        }
        memset(*top, '0', MAX_SIZE);
    } 
    return;
}

char* factorial(int n) {
    big_int hold_n[2] = {1, 1}; // [0] = previous; [1] = current
    int main_l = 0;  
    int temp_l = 0;
    char* main_n = calloc(MAX_SIZE, sizeof(char));
    char* temp_n = calloc(MAX_SIZE, sizeof(char)); // Max number of digits for ull
    for (big_int i = 1; i <= n; i++)
    {   
        big_int x = hold_n[1] * i;
        if (hold_n[1] != 0 && x / hold_n[1] != i) // Overflow
        {
            // if first time, put the number in main; otherwise put the number in temp, multiply the two numbers and return the values to main
            if (main_l == 0) { sprintf(main_n, "%llu", hold_n[1]); hold_n[1] = i; main_l = strlen(main_n); }
            else {
                sprintf(temp_n, "%llu", hold_n[0]);
                hold_n[1] = i;    
                temp_l = strlen(temp_n);
                if (main_l > temp_l)
                    multiply_strings(&main_n, &temp_n, 0, &main_l, temp_l);
                else    
                    multiply_strings(&temp_n, &main_n, 1, &main_l, temp_l); 
	    }
        }
        else
        {
            hold_n[1] *= i;
            hold_n[0] = hold_n[1];
        }
    }   
    // Multiply hold_n[1]s remnants with main if there is any value in main_n, if there isnt a value in main_n, we can just assign the digit to its memory
    if (strlen(main_n) == 0) { sprintf(main_n, "%llu", hold_n[1]); }
    else {
        sprintf(temp_n, "%llu", hold_n[0]);
        temp_l = strlen(temp_n);
        if (main_l > temp_l) 
            multiply_strings(&main_n, &temp_n, 0, &main_l, temp_l);
        else    
            multiply_strings(&temp_n, &main_n, 1, &main_l, temp_l);
    }
   // main_n[MAX_SIZE - main_l] = '\0';
    return main_n;
}

int main(){
//   char *main = calloc(MAX_SIZE, sizeof(char));
//   char *k = calloc(MAX_SIZE, sizeof(char));
//   int main_l = 19;
//   sprintf(main, "%s", "2432902008176640000");
//   sprintf(k, "%s", "3569119343741952000");
//   multiply_strings(&main, &k, 0, &main_l, 19);
//   printf("%s", main);
//   return 0;

      printf("%s", factorial(50));
      return 0;
}

