# Setting the time of the RTC
1. In Arduino IDE, set 'Tools' >> 'Board' to appropriate board.
2. In Arduino IDE, open sketch 'ds3231_SetTime.ino'.
3. In sketch 'ds3231_SetTime.ino', set '#ifndef ESP8266' to appropriate board.
4. Get COM port number in Windows >> Device Manager >> Ports (COM & LPT).
5. Set COM port number in Arduino IDE, 'Tools' >> 'Port'.
6. Set Serial Monitor to appropriate baud rate (default in code is '57600').
7. In Arduino IDE, compile and upload the sketch 'ds3231_SetTime.ino'.
    - The Serial Monitor time should now be updated to current date-time.
    - The Local display on the Feather will still show the time when the display last received a command, this will be the incorrect (unupdated time).
    - We will now compile and upload the appropriate board-specific sketch to the Feather.
8. In Arduino IDE, open appropriate sketch.
    - In Arduino IDE, open sketch 'SendTempToIO_ESP8266_v02.ino'.
    - Set appropriate WIFI and ADAFRUIT_IO settings in 'SendTempToIO_ESP8266_v02.ino'. These changes need to stay private, so don't commit these changes. (Need to find way to import these values)
    - Load or Compile/Upload sketch 'SendTempToIO_ESP8266_v02.ino' to 'ESP8266'.
        - 921600 baud seems to be acceptible upload rate for ESP32.
