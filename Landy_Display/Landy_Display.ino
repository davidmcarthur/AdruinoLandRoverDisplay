

// include the library code:
#include <LiquidCrystal.h>
#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>
#include <EveryTimer.h>


// initialize FONA and serial
// standard pins for the shield, adjust as necessary
#define FONA_RX 2     // serial recieve pin
#define FONA_TX 3     // serial transmit pin
#define FONA_RST 4    // FONA hardware reset
#define FIVE_MINUTE 300000  // Five minutes in millis
#define TWOFOUR_HOURS 86400000

EveryTimer timer;     // timer object

char replybuffer[255];                   // this is a large buffer for replies
char fonaNotificationBuffer[64];          //for notifications from the FONA
char smsBuffer[250];
unsigned long time;                       // init timer for SMS
bool active = true;         // boolean for timer event

// We default to using software serial.

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  // init timer
  timer.Every(FIVE_MINUTE, fiveMinTimer);       // timer object uses 5mins in millis to call event function
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.setCursor(4,0);
  lcd.print("MPH");

  lcd.setCursor(9,0);
  lcd.print("HDG");
  
  lcd.setCursor(0,1);
  lcd.print("ALT");
  
  lcd.setCursor(10,1);
  lcd.print("Landy!");

  // Setup FONA
    while (! Serial);

  Serial.begin(115200);
  Serial.println(F("Adafruit FONA 808 & 3G GPS demo"));
  Serial.println(F("Initializing FONA... (May take a few seconds)"));

  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));
  // Try to enable GPRS
  

  Serial.println(F("Enabling GPS..."));
  fona.enableGPS(true);
  
}

void loop() {


  char* bufPtr = fonaNotificationBuffer;    //handy buffer pointer
  float latitude, longitude, speed_kph, heading, speed_mph, altitude;
  boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);

  timer.Update();       // Update Timer

  if (gps_success) {

    Serial.print("GPS lat:");
    Serial.println(latitude, 6);
    Serial.print("GPS long:");
    Serial.println(longitude, 6);
    Serial.print("GPS speed KPH:");
    Serial.println(speed_kph);
    Serial.print("GPS speed MPH:");
    speed_mph = speed_kph * 0.621371192;
    Serial.println(speed_mph);
    Serial.print("GPS heading:");
    Serial.println(heading);
    Serial.print("GPS altitude:");
    Serial.println(altitude);

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0,0);
    lcd.print(speed_mph);
  
    lcd.setCursor(13,0);
    lcd.print(heading);
  
    lcd.setCursor(4,1);
    lcd.print(altitude);

    time = millis();
    // control timer
    if (time %5000

  } //GPS Sucsess 
  else {
    Serial.println("Waiting for FONA GPS 3D fix...");
    
    lcd.setCursor(0,0);
    lcd.print("unk");
  
    lcd.setCursor(13,0);
    lcd.print("unk");
  
    lcd.setCursor(4,1);
    lcd.print("unk");

  }

} // end of program loop

////////////// Functions //////////////////

void fiveMinTimer(){
    // TODO timer action every five minutes

    // ADD SMS FUNCTIONALITY
   
    active = !active;
  }
