/*
 This sketch demonstrate how to run read an RFID
 card reader and verify it against a database
 using a python script using an Arduino Yún. 
 
 created 01 Oct 2013
 by Surya Mattu
 
 This example code is in the public domain.
 
 This code uses the CardReader Library Luis Daniels
 and I wrote for HID Card readers available 
 on Github here:
 https://github.com/samatt/CardReader
 */

#include <Process.h>
#include <CardReader.h>

CardReader reader(2, 3);
long cardNumber = 0;

void setup() {
  // Initialize Bridge
  Bridge.begin();
  attachInterrupt(1, readBit, RISING);
  // Initialize Serial
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);  
  // Wait until a Serial Monitor is connected.
  while (!Serial);

  Serial.println("ITP Card reader. Ready to read card.");
}

void loop() {

  if (reader.cardRead()) {
    Serial.print("Card ID: ");
    cardNumber = reader.getIdNumber();
    Serial.println(cardNumber);
    if(runScript(cardNumber)){
      Serial.println("Approved!");
      digitalWrite(6,HIGH);
      delay(1000);
      digitalWrite(6,LOW);     
    }
    else{
      Serial.println("Denied ");  
      digitalWrite(7,HIGH);
      delay(1000);
      digitalWrite(7,LOW);           
    }
  }

}

void readBit() {
  reader.readBit();
}

bool runScript(long cardNumber) {
  bool isVerified = false;
  
  // Process that launches the python script
  Process p;		
  p.begin("/usr/bin/python");	
  p.addParameter("/root/checkID.py"); 
  p.addParameter(String(cardNumber));
  p.run();
  
  
  
  // Read data back from the script. 
  while (p.available()>0) {
    
    char c = p.read();
    
    //If the card ID is on the database the python script will return a 1
    //value will come in as an ascii char
    if( c == '1'){
      isVerified = true;
    }

  }
  
  // Ensure the last bit of data is sent.
  Serial.flush();
  
  return isVerified;
}



