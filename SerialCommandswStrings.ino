
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    String incomingByte = Serial.readString();
    if(incomingByte == "SetLedOn")
      {
        digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
        
      }
    else if(incomingByte == "SetLedOff")
      {
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        
      }
    else if(incomingByte == "ToggleLed")
      {
        digitalWrite(LED_BUILTIN,  !digitalRead(LED_BUILTIN));
      }
  
  }
    
}
