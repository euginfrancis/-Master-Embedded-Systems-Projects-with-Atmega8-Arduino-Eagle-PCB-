#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

// LCD commands and configurations
#define LCD_4BITMODE 0x02
#define LCD_CLEAR 0x01
#define LCD_DDRAMSET 0x80

// Pin definitions
#define EN PORTD6
#define RS PORTD7
#define LED PORTC4
#define D4 PORTD5
#define D5 PORTD4
#define D6 PORTD3
#define D7 PORTD2

// Constants for timing and error handling
#define LOOP_OVFL 200
#define ERROR 0

// Function Prototypes
void lcd_int(void);
void lcd_cmdWrite(uint8_t command);
void lcd_dataWrite(uint8_t data);
void lcd_send(uint8_t data, uint8_t mode);
void lcd_write(uint8_t data);
void lcd_enable_pulse(void);
void lcd_print(char *string);
void lcd_clear(void);
void lcd_setCursor(uint8_t col, uint8_t row);
void lcd_clearRow(uint8_t row);
uint8_t read_dht(uint8_t* data);
char* itoa(int value, char* str, int base);

// Global variable
uint8_t time = 0;

int main()
{
    // Configure LED pin as output
    DDRC |= (1<<DDC4);

    uint8_t data[5];        // Array to store DHT sensor data
    char buf[6];            // Buffer for converting numbers to strings

    lcd_int();              // Initialize the LCD

    while(1)
    {
        PORTC ^= (1<<LED);  // Toggle the LED

        if(read_dht(data))  // Read data from the DHT sensor
        {
            lcd_setCursor(0, 0); // Set cursor to first row
            lcd_print("HUMIDITY    :"); // Print humidity label
            lcd_print(itoa(data[0], buf, 10)); // Display humidity value

            lcd_setCursor(0, 1); // Set cursor to second row
            lcd_print("TEMPERATURE :"); // Print temperature label
            lcd_print(itoa(data[2], buf, 10)); // Display temperature value
        }
    }
}

// LCD initialization function
void lcd_int()
{
    DDRD = 0xFF;            // Configure all PORTD pins as outputs
    
    PORTD &= ~(1<<EN);      // Ensure EN is low
    PORTD &= ~(1<<RS);      // Ensure RS is low
    
    _delay_us(50000);       // Wait for the LCD to stabilize
    
    // Initialization sequence for 4-bit mode
    lcd_cmdWrite(0x03);
    _delay_us(4500);
    lcd_cmdWrite(0x03);
    _delay_us(4500);
    lcd_cmdWrite(0x03);
    _delay_us(150);
    lcd_cmdWrite(LCD_4BITMODE);
    _delay_us(4500);
    
    lcd_clear();            // Clear the LCD screen
}

// Function to send a command to the LCD
void lcd_cmdWrite(uint8_t command)
{
    lcd_send(command, 0);   // Send command with RS = 0
}

// Function to send data to the LCD
void lcd_dataWrite(uint8_t data)
{
    lcd_send(data, 1);      // Send data with RS = 1
}

// Helper function to send data/command to the LCD
void lcd_send(uint8_t data, uint8_t mode)
{
    if(mode) PORTD |= (1<<RS);  // Set RS for data
    else PORTD &= ~(1<<RS);     // Clear RS for command
    
    lcd_write(data >> 4);       // Send higher nibble
    lcd_write(data);            // Send lower nibble
}

// Function to write a nibble (4 bits) to the LCD
void lcd_write(uint8_t data)
{
    // Set each data pin according to the corresponding bit in the nibble
    if(data & 0x01) PORTD |= (1<<D4);
    else PORTD &= ~(1<<D4);
    
    if((data >> 1) & 0x01) PORTD |= (1<<D5);
    else PORTD &= ~(1<<D5);
    
    if((data >> 2) & 0x01) PORTD |= (1<<D6);
    else PORTD &= ~(1<<D6);
    
    if((data >> 3) & 0x01) PORTD |= (1<<D7);
    else PORTD &= ~(1<<D7);
    
    lcd_enable_pulse();     // Pulse the enable pin to latch data
}

// Function to create a pulse on the enable pin
void lcd_enable_pulse()
{
    PORTD &= ~(1<<EN);      // Ensure EN is low
    _delay_us(1);
    PORTD |= (1<<EN);       // Set EN high
    _delay_us(1);
    PORTD &= ~(1<<EN);      // Set EN low
    _delay_us(100);         // Wait for LCD to process the data
}

// Function to print a string on the LCD
void lcd_print(char *string)
{
    while(*string != '\0')  // Loop until null terminator is reached
        lcd_dataWrite(*string++); // Send each character to the LCD
}

// Function to clear the LCD screen
void lcd_clear()
{
    lcd_cmdWrite(LCD_CLEAR); // Send clear command
    _delay_us(2000);         // Wait for the command to complete
}

// Function to set the cursor position on the LCD
void lcd_setCursor(uint8_t col, uint8_t row)
{
    if(row) row = 0x40;      // Set row offset for second line
    lcd_cmdWrite(LCD_DDRAMSET | (col + row)); // Send command to set DDRAM address
}

// Function to clear a specific row on the LCD
void lcd_clearRow(uint8_t row)
{
    lcd_setCursor(0, row);   // Move cursor to the beginning of the row
    int i;
    for(i = 0; i < 16; i++)
        lcd_dataWrite(' ');  // Write spaces to clear the row
    lcd_setCursor(0, row);   // Move cursor back to the beginning of the row
}

// Function to read data from the DHT sensor
uint8_t read_dht(uint8_t* data)
{
    // Send start signal
    DDRC |= (1<<DDC1);       // Configure pin as output
    PORTC &= ~(1<<PORTC1);   // Pull pin low
    _delay_ms(25);           // Wait 25ms
    DDRC &= ~(1<<DDC1);      // Configure pin as input
    
    time = 0;
    _delay_us(1);
    
    // Wait for sensor to respond
    while((PINC & (1<<PINC1)) > 0)
        if(++time == LOOP_OVFL) return ERROR;

    _delay_us(1);
    time = 0;
    
    // Additional signal timing checks omitted for brevity
    // ...
    
    return 1; // Return success
}
