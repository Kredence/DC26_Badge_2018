/*
The original authors and framework of the IS31FL3731 coding was done by Adafruit.
The original coding is heavily modified, non-existent, or has been expanded.
You'll want to install the Adafruit GFX library along with the DC26_Illuminati.cpp and DC26_Illuminati.h

The DEFCON 26 Illuminati Badge schematics, PCB layout, and coding was done by Kredence.
A substantial portion of the assembly and PR/advertising was done by Ajax.
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <DC26_Illuminati.h>

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif


/* Constructor */
DC26_Illuminati::DC26_Illuminati(uint8_t x, uint8_t y) : Adafruit_GFX(x, y) {
}



boolean DC26_Illuminati::begin(uint8_t addr) {
  Wire.begin();

  _i2caddr = addr;
  _frame = 0;

  // shutdown
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);

  delay(10);

  // out of shutdown
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);

  // picture mode
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE);

  displayFrame(_frame);

  // all LEDs on & 0 PWM
  clear(); // set each led to 0 PWM

  for (uint8_t f=0; f<8; f++) {  
    for (uint8_t i=0; i<=0x11; i++)
      writeRegister8(f, i, 0xff);     // each 8 LEDs on
  }

  audioSync(false);

  return true;
}

void DC26_Illuminati::clear(void) {
  // all LEDs on & 0 PWM

  selectBank(_frame);

  for (uint8_t i=0; i<6; i++) {
    Wire.beginTransmission(_i2caddr);
    Wire.write((byte) 0x24+i*24);
    // write 24 bytes at once
    for (uint8_t j=0; j<24; j++) {
      Wire.write((byte) 0);
    }
    Wire.endTransmission();
  }
}

void DC26_Illuminati::setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank) {
	uint8_t led = translateLED(lednum);
  //if (lednum >= 144) return;
  writeRegister8(bank, 0x24+led, pwm);
}

//void DC26_Illuminati::setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank) {
//  if (lednum >= 144) return;
//  writeRegister8(bank, 0x24+lednum, pwm);
//}


void DC26_Illuminati::drawPixel(int16_t x, int16_t y, uint16_t color) {
 // check rotation, move pixel around if necessary
  switch (getRotation()) {
  case 1:
    _swap_int16_t(x, y);
    x = 16 - x - 1;
    break;
  case 2:
    x = 16 - x - 1;
    y = 9 - y - 1;
    break;
  case 3:
    _swap_int16_t(x, y);
    y = 9 - y - 1;
    break;
  }

  if ((x < 0) || (x >= 16)) return;
  if ((y < 0) || (y >= 9)) return;
  if (color > 255) color = 255; // PWM 8bit max

  setLEDPWM(x + y*16, color, _frame);
  return;
}

//This was used to make the LED ordering a lot easier to code
//The LED layout was a bit random due to the multiplexing of the IS31FL chip
uint8_t  DC26_Illuminati::translateLED(uint8_t call) {
	uint8_t translated;
	
	switch(call){
		case 1: translated = 0;
		break;
		case 2: translated = 16;
		break;
		case 3: translated = 32;
		break;
		case 4: translated = 48;
		break;
		case 5: translated = 64;
		break;
		case 6: translated = 80;
		break;
		case 7: translated = 96;
		break;
		case 8: translated = 112;
		break;
		case 9: translated = 128;
		break;
		case 10: translated = 1;
		break;
		case 11: translated = 17;
		break;
		case 12: translated = 33;
		break;
		case 13: translated = 49;
		break;
		case 14: translated = 65;
		break;
		case 15: translated = 81;
		break;
		case 16: translated = 97;
		break;
		case 17: translated = 113;
		break;
		case 18: translated = 129;
		break;
		case 19: translated = 2;
		break;
		case 20: translated = 18;
		break;
		case 21: translated = 34;
		break;
		case 22: translated = 50;
		break;
		case 23: translated = 66;
		break;
		case 24: translated = 82;
		break;
		case 25: translated = 98;
		break;
		case 26: translated = 114;
		break;
		case 27: translated = 130;
		break;
		case 28: translated = 3;
		break;
		case 29: translated = 19;
		break;
		case 30: translated = 35;
		break;
		case 31: translated = 51;
		break;
		case 32: translated = 67;
		break;
		case 33: translated = 83;
		break;
		case 34: translated = 99;
		break;
		case 35: translated = 115;
		break;
		case 36: translated = 131;
		break;
		case 37: translated = 20;
		break;
		case 38: translated = 4;
		break;
		case 39: translated = 36;
		break;
		case 40: translated = 52;
		break;
		case 41: translated = 68;
		break;
		case 42: translated = 84;
		break;
		case 43: translated = 100;
		break;
		case 44: translated = 116;
		break;
		case 45: translated = 132;
		break;
		case 46: translated = 21;
		break;
		case 47: translated = 5;
		break;
		case 48: translated = 37;
		break;
		case 49: translated = 53;
		break;
		case 50: translated = 69;
		break;
		case 51: translated = 85;
		break;
		case 52: translated = 101;
		break;
		case 53: translated = 117;
		break;
		case 54: translated = 133;
		break;
		case 55: translated = 22;
		break;
		case 56: translated = 6;
		break;
		case 57: translated = 38;
		break;
		case 58: translated = 54;
		break;
		case 59: translated = 70;
		break;
		case 60: translated = 86;
		break;
		case 61: translated = 102;
		break;
		case 62: translated = 118;
		break;
		case 63: translated = 134;
		break;
		case 64: translated = 7;
		break;
		case 65: translated = 23;
		break;
		case 66: translated = 39;
		break;
		case 67: translated = 55;
		break;
		case 68: translated = 71;
		break;
		case 69: translated = 87;
		break;
		case 70: translated = 103;
		break;
		case 71: translated = 119;
		break;
		case 72: translated = 135;
		break;
		case 73: translated = 8;
		break;
		case 74: translated = 24;
		break;
		case 75: translated = 40;
		break;
		case 76: translated = 56;
		break;
		case 77: translated = 72;
		break;
		case 78: translated = 88;
		break;
		case 79: translated = 9;
		break;
		case 80: translated = 25;
		break;
		case 81: translated = 41;
		break;
		case 82: translated = 57;
		break;
		case 83: translated = 73;
		break;
		case 84: translated = 89;
		break;
		case 85: translated = 10;
		break;
		case 86: translated = 26;
		break;
		case 87: translated = 42;
		break;
		case 88: translated = 58;
		break;
		case 89: translated = 74;
		break;
		case 90: translated = 90;
		break;
		case 91: translated = 11;
		break;
		case 92: translated = 27;
	}
  return translated;
}

void DC26_Illuminati::setFrame(uint8_t f) {
  _frame = f;
}

void DC26_Illuminati::displayFrame(uint8_t f) {
  if (f > 7) f = 0;
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_PICTUREFRAME, f);
}


void DC26_Illuminati::selectBank(uint8_t b) {
 Wire.beginTransmission(_i2caddr);
 Wire.write((byte)ISSI_COMMANDREGISTER);
 Wire.write(b);
 Wire.endTransmission();
}

void DC26_Illuminati::audioSync(boolean sync) {
  if (sync) {
    writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x1);
  } else {
    writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x0);
  }
}

/*************/
void DC26_Illuminati::writeRegister8(uint8_t b, uint8_t reg, uint8_t data) {
  selectBank(b);

  Wire.beginTransmission(_i2caddr);
  Wire.write((byte)reg);
  Wire.write((byte)data);
  Wire.endTransmission();
  //Serial.print("$"); Serial.print(reg, HEX);
  //Serial.print(" = 0x"); Serial.println(data, HEX);
}

uint8_t  DC26_Illuminati::readRegister8(uint8_t bank, uint8_t reg) {
 uint8_t x;

 selectBank(bank);

 Wire.beginTransmission(_i2caddr);
 Wire.write((byte)reg);
 Wire.endTransmission();

 Wire.beginTransmission(_i2caddr);
 Wire.requestFrom(_i2caddr, (byte)1);
 x = Wire.read();
 Wire.endTransmission();

// Serial.print("$"); Serial.print(reg, HEX);
//  Serial.print(": 0x"); Serial.println(x, HEX);

  return x;
}
