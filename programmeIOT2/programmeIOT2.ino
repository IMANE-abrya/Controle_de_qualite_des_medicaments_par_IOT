#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <RTClib.h>

#define SS_PIN 53 // RFID reader SS pin
#define RST_PIN 3 // RFID reader reset pin

// Define the expiration date for each medicine (in format: year, month, day, hour, minute, second)
const DateTime medicine1Expiration(2024, 12, 31, 23, 59, 59);
const DateTime medicine2Expiration(2025, 6, 30, 23, 59, 59);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
RTC_DS1307 rtc; // Change to RTC_DS1307

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor to open
  Serial.println("Initializing RFID reader...");
  
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  Serial.println("RFID reader initialized");
  
  Serial.println("Initializing RTC...");
  Wire.begin(); // Initialize I2C bus
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);}
  if (!rtc.isrunning()) {
    Serial.println("RTC is not running");
    rtc.adjust(DateTime (F(__DATE__), F(_TIME__))); // Adjust RTC with compile time
    }
  Serial.println("RTC initialized");}
void loop() {
// Look for new RFID cards
if (!mfrc522.PICC_IsNewCard Present() || !mfrc522.PICC_ReadCardSerial()) {
delay(1000);
return;
}
// Show UID on serial monitor 
Serial.println("Card detected");
Serial.print("UID tag: "); 
String content = "";
for (byte i = 0; i<mfrc522.uid.size; i++) {
content.concat(String (mfrc522.uid.uidByte[i] < 0x10 ? "0" : " " ));
content.concat(String (mfrc522.uid.uidByte[i], HEX));
}
content.toUpperCase(); 
Serial.println(content);
// Check expiration date based on medicine UID
if (content == "A5 D7 De 28") { // the UID of medicine 1 
    checkMedicineExpiration (medicinelExpiration, "Medicine 1");
}else if (content == B6 EA FF 28 ") { // the UID of medicine 2
 checkMedicineExpiration (medicine2Expiration, "Medicine 2");
} else {
Serial.println("Unknown medicine");
}

mfrc522.PICC_HaltA(); // Halt PICC
mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD 
delay(1000); // Delay before checking for a new card

// The Function to check if medicine has expired
void checkMedicineExpiration (DateTime expirationDate, String medicineName) 
{ DateTime currentTime = rtc.now(); // Get current time from RTC

Serial.print(medicineName);
Serial.print(" expiration date: ");
Serial.print(expirationDate.year(), DEC);
Serial.print("-");
print2digits (expiration Date.month());
Serial.print("-");
print2digits (expirationDate.day());
Serial.print(" ");
print2digits (expirationDate.hour()); 
Serial.print(":");
print2digits (expirationDate.minute());
Serial.print(":");
print2digits (expirationDate.second());
Serial.println();

if (currentTime > expirationDate) {
  Serial.println("Medicine has expired!");
} else {
  Serial.println("Medicine is still valid");
}
}  

// Helper function to print two digits (leading zero if needed) 
void print2digits (int number) {
   if (number < 10) {
      Serial.print("0");
   }
   Serial.print(number);
}
