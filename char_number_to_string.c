/******************************************************************************************
 * char_number_to_string.c
 * ver2.00
 * Hirofumi Hamada
 *=========================================================================================
 * char型(-128 ~ 127)の数値を文字列へ変換
 *
 *=========================================================================================
 * ・ver1.00 || 初版 || 2015/09/14 || Hirofumi Hamada
 *   初版
 * ・ver2.00 || 境界値のバグを修正 || 2015/12/15 || Hirofumi Hamada
 *   境界値のバグを修正
 *   ファイル名・関数名の先頭にchar_を追加
 *=========================================================================================
 * PIC16F886
 * MPLAB X IDE
 * XC8 Compiler 
 *=========================================================================================
 * Created by fabsat Project(Tokai university Satellite Project[TSP])
 *****************************************************************************************/
#include "char_number_to_string.h"


/* prototype of function */
static char *process_100(char num, int *p_flag, char *p_str);
static char *process_10(char num, int *p_flag, char *p_str);
static char *process_1(char num, int *p_flag, char *p_str);



/*=====================================================
 * @brief
 *     char型の数値を文字列へ変換
 * @param
 *     num:変換したい数値
 * @return
 *     str:変換した文字列を格納した配列へのポインタ
 * @note
 *     -128 ~ 127の数値
 *===================================================*/
char *char_number_to_string(char num)
{
    static char str[5];
    int  flag = 0;
    char *p_error_message = "size of number is over";

    /* num == -128 process */
    if(num == INT8_T_MINIMUM)
    {
        str[0] = '-';
        str[1] = '1';
        str[2] = '2';
        str[3] = '8';
        str[4] = '\0';
        
        return str;
    }
   
    /* For negetive number process */
    if(num < 0)
    {
        str[flag] = '-';
        flag++;
        num *= (-1);
    }

    /* converting process */
    if(MIN_100 <= num && num <= MAX_100)
    {
        return process_100(num, &flag, str);
    }
    else if(MIN_10 <= num && num <= MAX_10)
    {
        return process_10(num, &flag, str);
    }
    else if(MIN_1 <= num && num <= MAX_1)
    {
        return process_1(num, &flag, str);
    }
    else
    {
        return p_error_message;
    }

}


/*-----------------------------------------
 * 100の位を文字へ変換
 *--------------------------------------*/
static char *process_100(char num, int *p_flag, char *p_str)
{
    char remainder_100 = num % 100;
    
    p_str[*p_flag] = ASCII_CODE_0 + 1;
    (*p_flag)++;
    
    return process_10(remainder_100, p_flag, p_str);
}


/*-----------------------------------------
 * 10の位を文字へ変換
 *--------------------------------------*/
static char *process_10(char num, int *p_flag, char *p_str)
{
    int  divide_10    = (int)(num / 10);
    char remainder_10 = num % 10;
    char val          = ASCII_CODE_0;
    int  i;
    
    for(i = 0; i < divide_10; i++)
    {
        val++;
    }
    
    p_str[*p_flag] = val;
    (*p_flag)++;
    
    return process_1(remainder_10, p_flag, p_str);
}


/*-----------------------------------------
 * 1の位を文字へ変換
 *--------------------------------------*/
static char *process_1(char num, int *p_flag, char *p_str)
{
    int  divide_1 = (int)num;
    char val      = ASCII_CODE_0;
    int  i;
    
    for(i = 0; i < divide_1; i++)
    {
        val++;
    }
    
    p_str[*p_flag] = val;
    (*p_flag)++;
    
    p_str[*p_flag] = '\0';
        
    return p_str;
}
