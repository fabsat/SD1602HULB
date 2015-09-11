/*-----------------------------------------------
 * char型(-127 ~ 127)の範囲を文字列に変換
 * 
 * Hirofumi Hamada
 *
 * ver.1.0
 * ---------------------------------------------*/
#include "number_to_string.h"


/* ASCIIコードの0の数値を定義 */
#define ASCII_NUMBER_0 (0x30)

/* 桁を分けるための境界値を定義 */
#define MAX_100        (127)
#define MIN_100        (100)
#define MAX_10         (99)
#define MIN_10         (10)
#define MAX_1          (0)
#define MIN_1          (9)

/* prototype */
static char *process_100(char num, int *flag, char *str);
static char *process_10(char num, int *flag, char *str);
static char *process_1(char num, int *flag, char *str);


/*-----------------------------------------
 * char型の数値を文字列へ変換
 *--------------------------------------*/
char *number_to_string(char num)
{
    static char str[8];
    int  flag = 0;
    char *error_message = "number size is over";
    
    if(num < 0) {
        str[flag] = '-';
        flag++;
        num *= (-1);
    }
    
    if(MIN_100 <= num && num < MAX_100)
        return process_100(num, &flag, str);
    else if(MIN_10 <= num && num <= MAX_10)
        return process_10(num, &flag, str);
    else if(MIN_1 <= num && num <= MAX_1)
        return process_1(num, &flag, str);
    else
        return error_message;
}


/*-----------------------------------------
 * 100の位を文字へ変換
 *--------------------------------------*/
static char *process_100(char num, int *flag, char *str)
{
    char remainder_100 = num % 100;
    
    str[*flag] = ASCII_NUMBER_0 + 1;
    (*flag)++;
    
    return process_10(remainder_100, flag, str);
}


/*-----------------------------------------
 * 10の位を文字へ変換
 *--------------------------------------*/
static char *process_10(char num, int *flag, char *str)
{
    int  divide_10    = (int)num / 10;
    char remainder_10 = num % 10;
    char val        = ASCII_NUMBER_0;
    int  i;
    
    for(i = 0; i < divide_10; i++) {
        val++;
    }
    
    str[*flag] = val;
    (*flag)++;
    
    return process_1(remainder_10, flag, str);
}


/*-----------------------------------------
 * 1の位を文字へ変換
 *--------------------------------------*/
static char *process_1(char num, int *flag, char *str)
{
    int  divide_1 = (int)num;
    char val      = ASCII_NUMBER_0;
    int  i;
    
    for(i = 0; i < divide_1; i++) {
        val++;
    }
    
    str[*flag] = val;
    (*flag)++;
    
    str[*flag] = '\0';
        
    return str;
}
