//Viral Science
//RFID
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_R 5 //define red LED
#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int led = 13;                // the pin that the LED is atteched to
int sensor = 7;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  lcd.begin();
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input

}
void loop() 
{
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
     
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;    
      digitalWrite(LED_R, HIGH);
      tone(BUZZER, 300);
      delay(1000);
      digitalWrite(LED_R, LOW);
      noTone(BUZZER);
      lcd.setCursor(0, 0);
      lcd.print("Illegal Access");
      lcd.setCursor(0, 1);
      lcd.print("Thieft");
         // update variable state to HIGH
    }
  } 
  else {
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "53 A7 2B 95") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Access Approved");
    Serial.println();
    delay(500);
    tone(BUZZER, 1000);
    delay(300);
    noTone(BUZZER);
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Legal Access");
    lcd.setCursor(0, 1);
    lcd.print("Owner");
    delay(3000);
  }

  else if (content.substring(1) == "53 4D 1D 98") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Access Approved");
    Serial.println();
    delay(500);
    tone(BUZZER, 1000);
    delay(300);
    noTone(BUZZER);
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Legal Access");
    lcd.setCursor(0, 1);
    lcd.print("Owner");
    delay(5000);
  }
  
//  else   {
//     Serial.println(" Access denied");
//     digitalWrite(LED_R, HIGH);
//     tone(BUZZER, 300);
//     delay(1000);
//     digitalWrite(LED_R, LOW);
//     noTone(BUZZER);
//     lcd.setCursor(0, 0);
//     lcd.print("Illegal Access");
//     lcd.setCursor(0, 1);
//     lcd.print("Error");
//   }
} 

