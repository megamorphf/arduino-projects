volatile int tc = 0; //tick Counter!
volatile int sw = -1; //sprite width, -1 meants that now new sprite is available
volatile char c = 0;
volatile boolean allowSh = false;
volatile boolean runSh = false;

void printMsg() {
  if (ledM.ena > 0) {
    if (ledM.f > 0) {
    }// if flash
    for (int i = 0; i < ledM.ena; i++) {
      Serial.println(ledM.m); //----
      printStringWithShift(ledM.m, ledM.s);
    }
    ledM.ena = 0;
    Serial.println("Message has been sent x r times!"); //----
  }//if enabled
}//printMsg

void printStringWithShift(char* s, int shift_speed)
{
  while (*s != 0)
  {
     c =*s;
    printCharWithShift(*s, shift_speed); //++++
    s++;
  }
}

void printCharWithShift(char c, int shift_speed)
{
  if (c < 32) return; // exit function if first 31 characters of ascii table are found
  c -= 32;
  memcpy_P(buffer, CH + (7 * c), 7); // first ROW index CH + (7 * C) second is length index how many collumns you have to take to the buffer!
  m.writeSprite(bSize, 0, buffer); // writes the sprite not in the display
  m.setColumn(bSize + buffer[0], 0); //Adds a gap to the end of the  SPRITE, buffer[0] holds sprites width

  for (int i = 0; i < buffer[0] + 1; i++)
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}







