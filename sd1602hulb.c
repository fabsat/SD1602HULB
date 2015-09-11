/*-----------------------------------------------
 * For SD1602HULB
 * Using PIC16F886
 * 
 * Hirofumi Hamada
 *
 * RS、R/W、Enabla 全て使用
 * 4bitモード
 * 色合いが若干おかしいので修正が必要
 * ver.3.0
 * ---------------------------------------------*/

/*------------------------------------------------
 * 動作時のコンフィギュレーション設定
 * FOSC  = INTRC_NOCLKOUT
 * WDTE  = OFF
 * PWRTE = OFF
 * MCLRE = ON
 * CP    = OFF
 * CPD   = OFF
 * BOREN = ON
 * IESO  = OFF
 * FCMEN = OFF
 * LVP   = OFF
 * BOR4V = BOR40V
 * WRT   = OFF
 *-----------------------------------------------*/

#include <xc.h>
#include <stdio.h>
#include "sd1602hulb.h"


/*-----------------------------------------------
 * LCDにコマンドを発行
 * 上位4bitモードでの書き込み
 *---------------------------------------------*/
void lcd_set_command_4bit(rs_mode_t mode, uint8_t data)
{
  LCD_RW = 0;
  LCD_RS = 0;
     
  if(mode == RS_MODE_DATA)
       LCD_RS = 1;
     
  LCD_D4 = ((data) & 0x01);
  LCD_D5 = ((data >> 1) & 0x01);
  LCD_D6 = ((data >> 2) & 0x01);
  LCD_D7 = ((data >> 3) & 0x01);
  ENABLE_PULSE;

  return;
}


/*-----------------------------------------------
 * LCDにコマンドを発行
 * 8bitでの記述用
 *---------------------------------------------*/
void lcd_set_command(rs_mode_t mode, uint8_t data)
{
  lcd_set_command_4bit(mode, (data >> 4));
  lcd_set_command_4bit(mode, data);

  return;
}


/*-----------------------------------------------
 * PICの初期化
 *---------------------------------------------*/
static void pic_init(void)
{
  OSCCON  = 0x75;  //0b01110101
  TRISB   = 0x00;  //PORTBを出力設定
  TRISC   = 0x00;  //PORTCを出力設定
  PORTB   = 0x00;  //PORTBをLow
  PORTC   = 0x00;  //PORTCをLow

  return;
}


/*-----------------------------------------------
 * LCDの初期化処理
 *---------------------------------------------*/
void lcd_init()
{
  /* PICの初期化 */
  pic_init();

  /* 信号をLowにする */
  LCD_RS = 0;
  LCD_RW = 0;
  LCD_EN = 0;

  __delay_ms(15);    // 電源ON後15msまで待ってから初期化

  /* 初期イニシャライズシーケンス */
  lcd_set_command_4bit(RS_MODE_COMMAND, 0x03);
  __delay_ms(5);       //4.1ms以上待ち
  lcd_set_command_4bit(RS_MODE_COMMAND, 0x03);
  __delay_ms(1);       //100us以上待ち
  lcd_set_command_4bit(RS_MODE_COMMAND, 0x03);
  __delay_ms(1);       //39us以上待ち

  /* 初期化シーケンス　ファンクションセット */
  lcd_set_command_4bit(RS_MODE_COMMAND, 0x02);
  __delay_ms(1);       //39us以上待ち
     
  /* ここから4bitモード動作 (4bit * 2 -> 8bit命令) */
  lcd_set_command(RS_MODE_COMMAND, 0x28);
  __delay_ms(1);

  lcd_set_command(RS_MODE_COMMAND, 0x0F);
  __delay_ms(1);

  lcd_set_command(RS_MODE_COMMAND, 0x01);
  __delay_ms(2);

  lcd_set_command(RS_MODE_COMMAND, 0x06);
  __delay_ms(1);

  return;  
}

/*-----------------------------------------------
 * Busyチェック関数
 *    Busyフラグが立っている間ループで回り続ける
 *---------------------------------------------*/
void lcd_busywait(void)
{
  /* busy flagの初期化 */
  uint8_t busy_flag = 1;

  LCD_RS = 0;
  LCD_RW = 1;

  /* データビットを入力 */
  TRISB  = 0xFF;
  ANSELH = 0x00;	// 入力はdigital

  /* busy_flagのstatus調査 */
  while(busy_flag){
    LCD_EN = 1;

    busy_flag = RB7;

    LCD_EN = 0;

    ENABLE_PULSE;
  }

  /* データビットを出力 */
  TRISB = 0x00;

  return;
}


/*-----------------------------------------------
 * LCDにデータを1バイト出力する処理
 *    data : 出力する文字データ
 *---------------------------------------------*/
void lcd_putc(int8_t data)
{
  lcd_set_command(RS_MODE_DATA, data);
  lcd_busywait();

  return;
}


/*-----------------------------------------------
 * LCDに文字列データを出力する処理
 * (文字列をNULL(0x00)まで繰返し出力)
 *     str : 出力する文字列のデータ
 *---------------------------------------------*/
void lcd_puts(const int8_t *str)
{
  while(*str){
    lcd_putc(*str);
    str++;
  }

  return;
}


/*-----------------------------------------------
 * int型をchar型に変換
 * 
 *---------------------------------------------*/
int8_t *convert_int_into_string(const int value)
{
  int8_t *str_p;
  static int8_t str[25] = {'\0'};
  sprintf(str, "%d", value);

  str_p = &str[0];

  return str_p;
}



/*-----------------------------------------------
 * 表示位置を指定できるようにする
 *    表示位置のアドレスはDDRAMのアドレスの設定
 *---------------------------------------------*/
void lcd_setpos(int8_t x, int8_t y)
{
  int8_t val = 0x80;

  if(x){
    val |= 0x40;
  }
  val |= (y & 0x0F);

  lcd_set_command(RS_MODE_COMMAND, val);
  lcd_busywait();

  return;
}


/*-----------------------------------------------
 * lcd画面のクリア
 *---------------------------------------------*/
void lcd_clear(void)
{
  lcd_set_command(RS_MODE_COMMAND, 0x01);
  __delay_ms(500);

  return;
}



