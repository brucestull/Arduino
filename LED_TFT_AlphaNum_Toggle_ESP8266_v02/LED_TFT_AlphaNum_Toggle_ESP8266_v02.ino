// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
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
//   - Adafruit PyPortal -> https://www.adafruit.com/product/4116
//   - Adafruit Metro M4 Express AirLift Lite ->
//   https://www.adafruit.com/product/4000
//   - Adafruit AirLift Breakout -> https://www.adafruit.com/product/4201
//   - Adafruit AirLift Shield -> https://www.adafruit.com/product/4285
//   - Adafruit AirLift FeatherWing -> https://www.adafruit.com/product/4264

#define WIFI_SSID "<SSID>"
#define WIFI_PASS "<password>"

// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Include libraries for TFT

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include "Adafruit_miniTFTWing.h"

/************************ Example Starts Here *******************************/

// Create an "ss" (seesaw) object and define some important variables
Adafruit_miniTFTWing ss;
#define TFT_RST    -1    // we use the seesaw for resetting to save a pin
#define TFT_CS   2
#define TFT_DC   16

// Create the tft object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// led pin 0, for the red led
#define LED_PIN 0

// set up the 'led' feed
AdafruitIO_Feed *led = io.feed("toggle-led");

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void setup() {

  if (!ss.begin()) {
    Serial.println("seesaw init error!");
    while (1);
  }
  else Serial.println("seesaw started");

  alpha4.begin(0x70);  // pass in the address

  ss.tftReset();
  ss.setBacklight(0x0); //set the backlight fully on

  // Use this initializer (uncomment) if you're using a 0.96" 160x80 TFT
  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  tft.setRotation(3);

  Serial.println("Initialized");

  pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(9600);

  // wait for serial monitor to open
  while (! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'led' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  led->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  led->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'led' feed message
// is received from Adafruit IO. it was attached to
// the 'led' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH) {
    Serial.println("HIGH");

    // Line to set pin low, which turns led on.
    digitalWrite(LED_PIN, LOW); // Pin #0 needs "LOW" in order to go "on".

    // Block to display status on TFT display
    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(8);
    tft.println("ON");

    alpha4.clear();
    alpha4.writeDigitAscii(0, 'O');
    alpha4.writeDigitAscii(1, 'N');
    alpha4.writeDisplay();

  }
  else {
    Serial.println("LOW");

    // Line to set pin high, which turns led off.
    digitalWrite(LED_PIN, HIGH); // Pin #0 needs "HIGH" in order to go "off".

    // Block to display status on TFT display
    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(8);
    tft.println("OFF");

    alpha4.clear();
    alpha4.writeDigitAscii(0, 'O');
    alpha4.writeDigitAscii(1, 'F');
    alpha4.writeDigitAscii(2, 'F');
    alpha4.writeDisplay();

  }

}
