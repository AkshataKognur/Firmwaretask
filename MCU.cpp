#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define BAUD 2400
#define MY_UBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

unsigned char USART_Receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void storeDataInEEPROM(unsigned char *data, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        eeprom_write_byte((uint8_t*)i, data[i]);
    }
}

void retrieveDataFromEEPROM() {
    for (unsigned int i = 0; i < 1000; i++) { // Assuming 1000 bytes of text
        unsigned char data = eeprom_read_byte((uint8_t*)i);
        USART_Transmit(data);
    }
}

int main(void) {
    USART_Init(MY_UBRR);
    
    unsigned char buffer[1000];
    unsigned int index = 0;
    while (index < 1000) {
        buffer[index] = USART_Receive();
        storeDataInEEPROM(&buffer[index], 1);
        index++;

    }

    retrieveDataFromEEPROM();
    
    return 0;
}