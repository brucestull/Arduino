//#include <Adafruit_I2CDevice.h>
//#include <Adafruit_I2CRegister.h>
//#include <Adafruit_SPIDevice.h>
#include <Adafruit_BusIO_Register.h>

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
#define MESSAGE_WAIT_SEC (5)

// set up the data feeds
AdafruitIO_Feed *led_status = io.feed("toggle-led");

void setup()
{

  // start the serial connection
  Serial.begin(115200);

  // wait for serial connection to open
  while (!Serial)
    ;

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{

  // io.run(); is required for all sketches.
  io.run();

  Serial.println("Next loop");

  digitalWrite(0, HIGH);
  digitalWrite(4, HIGH);

  // Send the temperature to Adafruit IO
  led_status->save("ON");

  delay(5000);

  // Send the temperature to Adafruit IO
  led_status->save("OFF");

  digitalWrite(0, LOW);
  digitalWrite(4, LOW);

    // Update this to use network time.
//  // TIME:
//  DateTime now = rtc.now();
//
//  Serial.print(now.hour(), DEC);
//  Serial.print(':');
//  Serial.print(now.minute(), DEC);
//  Serial.print(':');
//  Serial.print(now.second(), DEC);
//  Serial.println();

  Serial.print("Waiting ");
  Serial.print(MESSAGE_WAIT_SEC);
  Serial.println(" seconds");
  // wait between sends
  for (int i = 0; i < MESSAGE_WAIT_SEC; i++)
  {
    delay(1000);
  }
}
