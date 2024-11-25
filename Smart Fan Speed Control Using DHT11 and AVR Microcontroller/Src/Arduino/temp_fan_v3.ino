#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#define LCD_4BITMODE 0x02
#define LCD_CLEAR 0x01
#define LCD_DDRAMSET 0x80

#define EN PORTD6
#define RS PORTD7
#define LED PORTC4
#define D4 PORTD5
#define D5 PORTD4
#define D6 PORTD3
#define D7 PORTD2

#define LOOP_OVFL 200
#define ERROR 0

uint8_t time = 0;

int main()
{
  DDRC |= (1<<DDC4);
  uint8_t data[5];
  char buf[6];
  
  lcd_int();
 
  while(1)
  {
    PORTC ^= (1<<LED);
    if(read_dht(data))
    {
      lcd_setCursor(0,0);
      lcd_print("HUMIDITY    :");
      lcd_print(itoa(data[0],buf,10));
      
      lcd_setCursor(0,1);
      lcd_print("TEMPERATURE :");
      lcd_print(itoa(data[2],buf,10));
  
    }
  }
}
void lcd_int()
{
  DDRD = 0xFF;
  
  PORTD &= ~(1<<EN);
  PORTD &= ~(1<<RS);
  
  _delay_us(50000);
  
  lcd_cmdWrite(0x03);
  _delay_us(4500);
  
  lcd_cmdWrite(0x03);
  _delay_us(4500);
  
  lcd_cmdWrite(0x03);
  _delay_us(150);
  
  lcd_cmdWrite(LCD_4BITMODE);
  _delay_us(4500);
  
  lcd_clear();
}
void lcd_cmdWrite(uint8_t command)
{
  lcd_send(command,0);
}
void lcd_dataWrite(uint8_t data)
{
  lcd_send(data,1);
}
void lcd_send(uint8_t data, uint8_t mode)
{
  if(mode)PORTD |= (1<<RS);
    else PORTD &= ~(1<<RS);
  lcd_write(data>>4);
  lcd_write(data);
}
void lcd_write(uint8_t data)
{
  if((data) & 0x01) PORTD |= (1<<D4);
    else PORTD &= ~(1<<D4);
    
  if((data>>1) & 0x01) PORTD |= (1<<D5);
    else PORTD &= ~(1<<D5);
    
  if((data>>2) & 0x01) PORTD |= (1<<D6);
    else PORTD &= ~(1<<D6);
    
  if((data>>3) & 0x01) PORTD |= (1<<D7);
    else PORTD &= ~(1<<D7);
    
  lcd_enable_pulse();
}
void lcd_enable_pulse()
{
  PORTD &= ~(1<<EN);
  _delay_us(1);
  PORTD |= (1<<EN);
  _delay_us(1);
  PORTD &= ~(1<<EN);
  _delay_us(100);
}
void lcd_print(char *string)
{
  while(*string != '\0')
     lcd_dataWrite(*string++);
}
void lcd_clear()
{
  lcd_cmdWrite(LCD_CLEAR);
  _delay_us(2000);
}
void lcd_setCursor(uint8_t col,uint8_t row)
{
  if(row) row = 0x40;
  lcd_cmdWrite(LCD_DDRAMSET | (col + row));
}
void lcd_clearRow(uint8_t row)
{
  lcd_setCursor(0,row);
  for(int i =0; i<16; i++)
     lcd_dataWrite(' ');
  lcd_setCursor(0,row);
}
uint8_t read_dht(uint8_t* data)
{
  
  DDRC |= (1<<DDC1);
  PORTC &= ~(1<<PORTC1);
  _delay_ms(25);
  DDRC &= ~(1<<DDC1);
   
  time = 0;
   _delay_us(1);
   
  while((PINC & (1<<PINC1))>0)
    if(++time == LOOP_OVFL) return ERROR;
    
  _delay_us(1);
  time = 0;
  
  while((PINC & (1<<PINC1)) == 0)
    if(++time == LOOP_OVFL) return ERROR;
  
  time =0;
  _delay_us(1);
  
  while((PINC & (1<<PINC1))>0)
    if(++time == LOOP_OVFL) return ERROR;
  
  _delay_us(1);
  
  for( uint8_t j = 0; j<5; j++)
  {  
    for(int i =7;i>=0;i--)
     {
       time =0;
       
       while((PINC & (1<<PINC1)) == 0)
          if(++time == LOOP_OVFL) return ERROR;
          
       time =0;
       _delay_us(1);
       
       while((PINC & (1<<PINC1))>0)
          if(++time == LOOP_OVFL) return ERROR;
       
       if(time <45) *data &= ~(1<<i);
         else *data |= (1<<i);
         
       time = 0;
      }
      data++;
   }
  return true;  
}

