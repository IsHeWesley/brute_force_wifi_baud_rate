# brute_force_wifi_baud_rate
For troubleshooting Wifi Module ESP8266
=====================================================
          ESP8266 BAUD RATE HUNTER & FIXER
=====================================================

DESCRIPTION
-----------
This script is a "rescue" tool for ESP8266 modules that have become 
unresponsive due to unknown baud rates. It cycles through the most 
common communication speeds and forces the module back to a 
standard 9600 baud using multiple AT command variations.

HARDWARE SETUP
--------------
1. Arduino Board (Uno, Nano, etc.)
2. ESP8266 Module (ESP-01, NodeMCU, etc.)
3. LEDs: Red, Yellow, Green
4. Passive Buzzer
5. 3.3V Power Source (External power recommended)

PIN MAPPING
-----------
[Component]       [Arduino Pin]    [Notes]
-----------------------------------------------------
ESP8266 TX   -->  Pin 2            (SoftwareSerial RX)
ESP8266 RX   -->  Pin 3            (SoftwareSerial TX)
RED LED      -->  Pin 13           (Idle/Scanning)
YELLOW LED   -->  Pin 12           (Switching Speeds)
GREEN LED    -->  Pin 11           (SUCCESS)
BUZZER       -->  Pin 8            (Victory Tone)

HOW IT WORKS
------------
1. STARTUP: The Arduino initializes pins and opens the Serial Monitor.
2. CHECK: It tests if the ESP is already at 9600 baud.
3. THE HUNT: If not found, it cycles through:
   - 115200, 74880, 57600, 38400, 19200, 4800
4. COMMAND ATTACK: At each speed, it sends three different reset 
   commands (AT+UART_DEF, AT+CIOBAUD, and AT+IPR) to ensure 
   compatibility with older and newer firmware.
5. VICTORY: Once the ESP responds "OK" at 9600 baud, the Green LED 
   lights up, a melody plays, and the script stops.

INSTRUCTIONS
------------
1. Connect the ESP8266 RX/TX to the Arduino pins listed above.
   *NOTE: ESP8266 RX should use a voltage divider if using a 5V Arduino.*
2. Power the ESP8266 with a stable 3.3V source.
3. Upload the code to the Arduino.
4. Open the Serial Monitor at 9600 Baud.
5. Wait for the Green LED. Once lit, your module is fixed!

CAUTION
-------
ESP8266 modules are 3.3V logic devices. Connecting them directly 
to 5V digital pins without a level shifter or voltage divider 
may damage the module over time.

=====================================================
Created by: [IsHeWesley]
Date: February 2026
=====================================================
