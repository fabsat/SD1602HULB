/******************************************************************************************
 * char_number_to_string.h
 * ver2.00
 * Hirofumi Hamada
 *=========================================================================================
 * char型(-128 ~ 127)の数値を文字列へ変換
 * char_number_to_string.cのヘッダファイル
 *
 *=========================================================================================
 * ・ver1.00 || 初版 || 2015/09/14 || Hirofumi Hamada
 *   初版
 * ・ver2.00 || マクロを追加 || 2015/12/15 || Hirofumi Hamada
 *   ソースファイルからマクロを移動
 *   ファイル名・関数名の先頭にchar_を追加
 *=========================================================================================
 * PIC16F886
 * MPLAB X IDE
 * XC8 Compiler 
 *=========================================================================================
 * Created by fabsat Project(Tokai university Satellite Project[TSP])
 *****************************************************************************************/
#ifndef _CHAR_NUMBER_TO_STRING_H_
#define _CHAR_NUMBER_TO_STRING_H_


/* define  Macro */
#define ASCII_NUMBER_0 (0x30)
#define MAX_100        (127)
#define MIN_100        (100)
#define MAX_10         (99)
#define MIN_10         (10)
#define MAX_1          (9)
#define MIN_1          (0)
#define INT8_T_MINIMUM (-128)
#define INT8_T_MAXIMUM (127)

/* Prototype of function */
char *char_number_to_string(char num);

#endif
