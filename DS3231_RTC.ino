
#include <Wire.h>

#define DS3231_ADDRESS 0X68
#define DS3231_SECONDS_REG 0X00

  static uint8_t convertValueIN(uint8_t value);
  static uint8_t convertValueOUT(uint8_t value);

typedef struct timeParameters {
  
    uint8_t ss ;
    uint8_t mm ;
    uint8_t hh ;
    uint8_t dy ;
    uint8_t d ;
    uint8_t m ;
    uint8_t y ;
  
  };

  void setTime(timeParameters *timeVals)

  {
    /* 
     *  0 - seconds   
     *  1 - minutes
     *  2 - hours
     *  3 - day
     *  4 - date 
     *  5 - month
     *  6 - year     
     */

       Wire.beginTransmission(DS3231_ADDRESS) ;
       Wire.write(DS3231_SECONDS_REG) ;

           Wire.write(convertValueOUT(timeVals->ss)) ;
           Wire.write(convertValueOUT(timeVals->mm)) ;
           Wire.write(convertValueOUT(timeVals->hh)) ;
           Wire.write(convertValueOUT(timeVals->dy)) ;
           Wire.write(convertValueOUT(timeVals->d)) ;
           Wire.write(convertValueOUT(timeVals->m)) ;
           Wire.write(convertValueOUT(timeVals->y)) ;
           Wire.endTransmission() ;

           delay (1000) ;
    }

    void readTime(timeParameters *timeVals)
    {
      Wire.beginTransmission(DS3231_ADDRESS);
      Wire.write(DS3231_SECONDS_REG) ;
      Wire.endTransmission() ;

      Wire.requestFrom(DS3231_ADDRESS, (byte) sizeof(timeParameters)) ;

      timeVals->ss = convertValueIN(Wire.read()) ;
      timeVals->mm = convertValueIN(Wire.read()) ;
      timeVals->hh = convertValueIN(Wire.read()) ;
      timeVals->dy = convertValueIN(Wire.read()) ;
      timeVals->d = convertValueIN(Wire.read()) ;
      timeVals->m = convertValueIN(Wire.read()) ;
      timeVals->y = convertValueIN(Wire.read()) ;

      delay(1000);
    
      }

static uint8_t convertValueIN(uint8_t value){

        uint8_t convertedVal = value - 6 * (value >> 4);
        return convertedVal ;  
  }

static uint8_t convertValueOUT(uint8_t value)
{
  uint8_t convertedVal = value + 6 * (value / 10) ;
  return convertedVal ;
}

timeParameters foo;

void setup() {
 Serial.begin(9600) ;
 Wire.begin() ;
 delay (2000) ;

 timeParameters example_vals = {

  50,
  41,
  20,
  31,
  1,
  19
  };

  uint8_t desiredFreq = 4;

    setTime(&example_vals) ;
        
  }

void loop() {
delay (1000) ;

readTime(&foo) ;

Serial.print(foo.y) ;
Serial.print("Ano") ;
Serial.print(foo.m) ;
Serial.print("Mês") ;
Serial.print(foo.d) ;
Serial.print("Data") ;

Serial.print(foo.hh) ;
Serial.print("Horas") ;
Serial.print(foo.mm) ;
Serial.print("minutos") ;
Serial.print(foo.ss) ;
Serial.print("Segundos") ;
  
}
