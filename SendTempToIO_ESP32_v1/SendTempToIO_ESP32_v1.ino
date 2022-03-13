// Adafruit IO ADT7410 Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Ladyada and Brent Rubell for Adafruit Industries
// Copyright (c) 2019 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME "<UserName>"
#define IO_KEY "<IOKey>"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056

#define WIFI_SSID "<SSID>"
#define WIFI_PASS "<password>"

/**************************************************************************/

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// time between sending data to adafruit io, in seconds
#define MESSAGE_WAIT_SEC (1 * 60)
//#define MESSAGE_WAIT_SEC 3

// Include the RTC library
#include "RTClib.h"

// Create an RTC_DS3231 object
RTC_DS3231 rtc;

// Include the adafruit library for the humidity and temperature sensor
#include "Adafruit_Si7021.h"

// Create an Adafruit_Si7021 object
Adafruit_Si7021 sensor = Adafruit_Si7021();

// Include library for 4-digit 7-segment display
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Create an "Adafruit_7segment()" object and call it "matrix"
Adafruit_7segment matrix = Adafruit_7segment();

// set up the data feeds
AdafruitIO_Feed *huzzah_temperature = io.feed("temperatureesp32");
AdafruitIO_Feed *huzzah_batteryvoltage = io.feed("batteryvoltageesp32");
AdafruitIO_Feed *huzzah_humidity = io.feed("humidityesp32");

// Create variable for display brightness
int brightness = 1;

void setup()
{

//#define BATPIN 13 // try using GPIO number "35" and see it if works.
//#define BATPIN 13 // Doesn't work properly.
#define BATPIN A13 // This pin setting seems to work properly.

  // start the serial connection
  Serial.begin(115200);

  // wait for serial connection to open
  while (!Serial)
    ;

  // Specify I2C address for the matrix
  matrix.begin(0x70);

  // Make sure the rtc is found
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC!");
    while (1)
      ;
  }

  // Use a short delay before first sensor reading
  delay(250);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{

  // io.run(); is required for all sketches.
  io.run();

  // Set display brightness
  matrix.setBrightness(brightness);

  // TEMPERATURE:
  // Read Celsius temperature and convert, print out the temperature in F
  float temperatureC = sensor.readTemperature();

  float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

  Serial.print("Temperature: ");
  Serial.println(temperatureF, 2);

  // Send the temperature to Adafruit IO
  huzzah_temperature->save(temperatureF, 0, 0, 0, 2);

  matrix.print(temperatureF, 2);
  matrix.writeDisplay();

  delay(3000);

  // HUMIDITY:
  // Display humidity on serial console, if attached.
  Serial.print("Humidity: "); Serial.print(sensor.readHumidity()); Serial.println();

  // Send the humidity to Adafruit IO
  huzzah_humidity->save(sensor.readHumidity(), 0, 0, 0, 1);

  delay(3000);

  // BATTERY VOLTAGE
  // Block to get and send battery voltage to console
  float measuredBatPinValue = analogRead(BATPIN);
  float batteryVoltage = measuredBatPinValue * 2.0 / 1024.0;
  Serial.print("VBat: " ); Serial.println(batteryVoltage);

  // Send the battery voltage to Adafruit IO
  huzzah_batteryvoltage->save(batteryVoltage, 0, 0, 0, 2);

  // TIME:
  DateTime now = rtc.now();

  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  matrix.writeDigitNum(0, now.hour() / 10);
  matrix.writeDigitNum(1, now.hour() % 10);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, now.minute() / 10);
  matrix.writeDigitNum(4, now.minute() % 10);
  matrix.writeDisplay();

  delay(250);

  Serial.print("Waiting ");
  Serial.print(MESSAGE_WAIT_SEC);
  Serial.println(" seconds");
  // wait between sends
  for (int i = 0; i < MESSAGE_WAIT_SEC; i++)
  {
    delay(1000);
  }
}
