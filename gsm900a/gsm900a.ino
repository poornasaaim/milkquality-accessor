// Techatronic.com   
  // Download Library of SoftwareSerial link given   
  // https://github.com/PaulStoffregen/SoftwareSerial   
  #include <SoftwareSerial.h>   
  SoftwareSerial SIM900A(10,11); // SoftSerial( RX , TX );   
  // 10 pin connect to TX of GSM SIM 900 Module   
  // 11 pin connect to RX of GSM SIM 900 Module   
  void setup()   
  {   
  SIM900A.begin(9600); // Setting the baud rate of GSM Module    
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)   
  Serial.println ("SIM900A Ready");   
  delay(100);   
  Serial.println (" Type c to Call ");   
  }   
  void loop()   
  {   
  if (Serial.available()>0)   
   switch(Serial.read())   
  {   
   case 'c':   
   RecieveMessage();   
   break;   
  }   
  if (SIM900A.available()>0)   
   Serial.write(SIM900A.read());   
  }   
  void RecieveMessage()   
  {   
  Serial.println ("SIM900A is Calling");   
  delay (1000);   
   SIM900A.println("ATD7305447831;"); //replace x by your number  
   delay(100);  
   SIM900A.println("ATH");   
  }   
