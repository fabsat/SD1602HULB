#ifndef _SD1602HULB_H_
#define _SD1602HULB_H_

#include <xc.h>


/* クロックの設定 */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ (8000000)
#endif


/* ピンの定義 */
#define LCD_RS    (RC5)
#define LCD_RW    (RC6)
#define LCD_EN    (RC7)
#define LCD_D4    (RB4)
#define LCD_D5    (RB5)
#define LCD_D6    (RB6)
#define LCD_D7    (RB7)

/* イネーブルパルス出力 */
#define ENABLE_PULSE \
  do{ \
      LCD_EN = 1; \
      LCD_EN = 0; \
  } while(0)


/* RSモードenum定義 */
typedef enum {
  RS_MODE_COMMAND,
  RS_MODE_DATA,
} rs_mode_t;


/* char -> int8_t */
typedef char int8_t;
typedef unsigned char uint8_t;


/* 関数プロトタイプ */
void lcd_set_command_4bit(rs_mode_t mode, uint8_t data);
void lcd_set_command(rs_mode_t mode, uint8_t data);
void lcd_init(void);
void lcd_busywait(void);
void lcd_putc(int8_t data);//渡されるのがuint8_tなので修正が必要
void lcd_puts(const int8_t *str);//渡されれるのがuint8_tなので修正が必要
int8_t *convert_int_into_string(const int value);
void lcd_setpos(int8_t x, int8_t y);
void lcd_clear(void);



#endif
