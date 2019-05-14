/*
The original authors and framework of the IS31FL3731 coding was done by Adafruit.
The original coding is heavily modified, non-existent, or has been expanded.
You'll want to install the Adafruit GFX library along with the DC26_Illuminati.cpp and DC26_Illuminati.h

The DEFCON 26 Illuminati Badge schematics, PCB layout, and coding was done by Kredence.
A substantial portion of the assembly and PR/advertising was done by Ajax.
*/

#ifndef _DC26_Illuminati_H_
#define _DC26_Illuminati_H_

#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>

#define ISSI_ADDR_DEFAULT 0x74

#define ISSI_REG_CONFIG  0x00
#define ISSI_REG_CONFIG_PICTUREMODE 0x00
#define ISSI_REG_CONFIG_AUTOPLAYMODE 0x08
#define ISSI_REG_CONFIG_AUDIOPLAYMODE 0x18

#define ISSI_CONF_PICTUREMODE 0x00
#define ISSI_CONF_AUTOFRAMEMODE 0x04
#define ISSI_CONF_AUDIOMODE 0x08

#define ISSI_REG_PICTUREFRAME  0x01

#define ISSI_REG_SHUTDOWN 0x0A
#define ISSI_REG_AUDIOSYNC 0x06

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_BANK_FUNCTIONREG 0x0B    // helpfully called 'page nine'


class DC26_Illuminati : public Adafruit_GFX {
 public:
  DC26_Illuminati(uint8_t x=16, uint8_t y=9); 
  boolean begin(uint8_t addr = ISSI_ADDR_DEFAULT);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void clear(void);

  void setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank = 0);
  void audioSync(boolean sync);
  void setFrame(uint8_t b);
  void displayFrame(uint8_t frame);

 protected:
  void selectBank(uint8_t bank);
  void writeRegister8(uint8_t bank, uint8_t reg, uint8_t data);
  uint8_t readRegister8(uint8_t bank, uint8_t reg);
  uint8_t _i2caddr, _frame;
  uint8_t translateLED(uint8_t call);
};

class DC26_Illuminati_Wing : public DC26_Illuminati {
 public:
  DC26_Illuminati_Wing(void);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
};



#endif