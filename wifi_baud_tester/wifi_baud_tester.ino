#include <SoftwareSerial.h>

// --- PINS ---
const int RED_LED    = 13;
const int YELLOW_LED = 12;
const int GREEN_LED  = 11;
const int BUZZER     = 8;
SoftwareSerial espSerial(2, 3); // RX, TX

// We will try ALL these speeds
long possibleSpeeds[] = {115200, 74880, 57600, 38400, 19200, 4800};
int speedCount = 6;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  
  Serial.println("--- ENHANCED HUNTER STARTED ---");
}

void loop() {
  // First, check if we are ALREADY fixed (Green Light Check)
  if (checkConnection(9600)) {
    victory();
  }

  // If not, cycle through all speeds
  for (int i = 0; i < speedCount; i++) {
    long currentSpeed = possibleSpeeds[i];
    
    // Blink Yellow to show we are switching speeds
    digitalWrite(YELLOW_LED, HIGH);
    delay(100);
    digitalWrite(YELLOW_LED, LOW);

    Serial.print("Attacking speed: ");
    Serial.println(currentSpeed);
    
    attemptFix(currentSpeed);
    
    // Check if it worked immediately
    if (checkConnection(9600)) {
      victory();
    }
  }
}

void attemptFix(long baudRate) {
  espSerial.begin(baudRate);
  delay(50);
  
  // Fire EVERY known command to change baud rate
  espSerial.println("AT+UART_DEF=9600,8,1,0,0"); // Standard
  delay(50);
  espSerial.println("AT+CIOBAUD=9600");          // Older Firmware
  delay(50);
  espSerial.println("AT+IPR=9600");              // Rare Firmware
  delay(50);
  
  // Reset just in case
  espSerial.println("AT+RST");
  delay(100);
  
  espSerial.end(); 
}

bool checkConnection(long baudRate) {
  espSerial.begin(baudRate);
  delay(200);
  
  // Clear buffer
  while(espSerial.available()) espSerial.read();
  
  // Ask "Are you there?"
  espSerial.println("AT");
  delay(800); 
  
  // Listen for "OK"
  String response = "";
  long start = millis();
  while (millis() - start < 1000) {
    while(espSerial.available()) {
      char c = espSerial.read();
      response += c;
    }
  }
  espSerial.end();
  
  if (response.indexOf("OK") >= 0) {
    return true;
  }
  return false;
}

void victory() {
  Serial.println("FIXED! SUCCESS!");
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, HIGH); // GREEN LIGHT!
  
  // Victory Sound
  tone(BUZZER, 1000, 100); delay(200);
  tone(BUZZER, 2000, 100); delay(200);
  tone(BUZZER, 3000, 500); delay(500);
  
  while(1) { } // Stay Green forever
}
