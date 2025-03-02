#ifndef SPI_H
#define SPI_H

//basically plagurized from that one time I made a ps2 library but then the thing i was working on broke so i didnt finish it

//halts polling and sends a byte to the spi slave
void spiSendByte(unsigned char commandByte, unsigned char cdata, gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck);

//halts polling and sends a byte to the spi slave. This variant only sends a command byte with no data, for commands with no parameters such as reset 0xFF
void spiSendByte(unsigned char commandByte, gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck);

//this polls the input until it read 8 bits then it returns that byte
unsigned char spiReadByte(gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck);

//basically just wait until a byte happens and return it when it does
//vector<unsigned char>& spiPollByte(gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck);

//figures out if there is a byte or not. returns 0 if there is no start bit, returns 1 if a start bit was detected
int spiPollStatus(gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck);

#include "spi.hpp"
#endif