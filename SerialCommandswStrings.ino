
void setup() {
  Serial.begin(9600); 
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    String incomingString = Serial.readString();
    if(incomingString == "SetLedOn")
      {
        digitalWrite(LED_BUILTIN, HIGH);    
        
      }
    else if(incomingString == "SetLedOff")
      {
        digitalWrite(LED_BUILTIN, LOW);    
        
      }
    else if(incomingString == "ToggleLed")
      {
        digitalWrite(LED_BUILTIN,  !digitalRead(LED_BUILTIN));
      }
  
  }
    
}
