void clearSerial() {
  while (Serial.available()) { // clears the serial buffer if wrong command was called
    Serial.read();
  }
}
void haltSerial() {
  while (!Serial.available()) { // will wait intill there will be bytes in the buffer
  }
}

void handShakeLd(char HET, char HAT, long SLP) { // leader handshake function, SLP send listen period in milliseconds
  clearSerial();
  long sendListenPeriod;
label:
  while (true) {
    yield();
    Serial.write(HET);
    Serial.flush();
    sendListenPeriod = millis();
    while ((millis() - sendListenPeriod) < SLP) { //Will listen for a fixed amout of time
      yield(); //call background functions
    }
    if (Serial.available()) { //its either time out or new data is in the serial buffer
      if (Serial.read() == HAT) {
        // Serial.println("GotaHat!"); //----
        clearSerial();
        break;
      }//if2
      else {
        clearSerial();
        //Serial.println("CrappyInput!"); //----
        //Serial.write(HET);//----
        //Serial.flush();//----
        goto label;
      }//else2

    }//If1
    else {
      //sendListenPeriod = millis(); // prepares for the new timeOut
      // Serial.println("TimedOut!"); //----
      // Serial.write(HET);//----
      //Serial.flush(); //----
      goto label;
    }//else
  } //while
}



int parseInts(char terminator) //If more data is sent to the buffer code wont work//Will return a char array of bytes from serial port //x param+1
{
  int buff = Serial.available();
  if (buff > 1 ) { // serial port must have at least two symbols in the buffer something related to interrupt triggring
    char serialIn;
    char charArr[64] = "";
    int inc = 64;
    if (buff < 64)
      inc = buff;
    char nextChar; //gets the first char from serial buffer
    for (int i = 0; i < inc; i++) {
      nextChar = Serial.peek();
      if (nextChar != terminator) {
        charArr[i] = Serial.read();
      }
      else { //remove bad symbols
        Serial.read(); //remove terminator
        break; // parses just the firstword matching the query
      }
    }
  //  Serial.println(charArr);

    newData = true;
    return atoi(charArr);
  }
  else
    newData = false;
  return -1;
}

float parseFloats(char terminator) //If more data is sent to the buffer code wont work//Will return a char array of bytes from serial port //x param+1
{
  int buff = Serial.available();//*****
  if (buff > 1 ) { // serial port must have at least two symbols in the buffer something related to interrupt triggring
    char serialIn;
    char charArr[64] = "";
    int inc = 64;
    if (buff < 64)
      inc = buff;
    char nextChar; //gets the first char from serial buffer
    for (int i = 0; i < inc; i++) {
      nextChar = Serial.peek();
      if (nextChar != terminator) {
        charArr[i] = Serial.read();
      }
      else { //remove bad symbols
        Serial.read(); //remove terminator
        break; // parses just the firstword matching the query
      }
    }
    //Serial.println(charArr);
    //rSerial.println(atof(charArr));

    newData = true;
    return atof(charArr);
  }
  else
    newData = false;
  return -1;
}


