// Authors: Chia-Lo Lee and Emily Hsu
// 4/12/2015
#define SPEAKER   11

int Led = 13 ;// define LED Interface
int buttonpin = 3; // define the obstacle avoidance sensor interface
int val ;// define numeric variables val
int us_pin = 2;
int duration_pin = 5;
unsigned long duration;
unsigned long prevDuration = -1;
void setup ()
{
  Serial.begin(9600);
  pinMode (Led, OUTPUT) ;// define LED as output interface
  pinMode (buttonpin, INPUT) ;// define the obstacle avoidance sensor output interface
  pinMode(SPEAKER, OUTPUT);
  pinMode(us_pin, INPUT);
  pinMode(7, OUTPUT);
  pinMode(duration_pin, OUTPUT);
}
void loop ()
{
  val = digitalRead (buttonpin) ;// digital interface will be assigned a value of 3 to read val
  if (val == HIGH) // When the obstacle avoidance sensor detects a signal, LED flashes
  {
    digitalWrite (Led, LOW);
  }
  else
  {
    digitalWrite (Led, HIGH);
    chirp();
  }
  
  // Trigger the ultrasonic sensor
  pulseOut(7, 1000);
  duration = pulseIn(us_pin, HIGH);
  Serial.println(duration);
  analogWrite(duration_pin, min(duration, 2000)/8);
  delay(30);
}

void pulseOut(int pin, int us)
{
   digitalWrite(pin, HIGH);
   us = max(us - 20, 1);
   delayMicroseconds(us);
   digitalWrite(pin, LOW);
}


/* 
Code from 
https://learn.adafruit.com/adafruit-trinket-modded-stuffed-animal/animal-sounds
*/
void varyFrequency() {   
//  use potentiometer to produce one tone per value of pot
//  good for getting pitch value to use in making sound routines
  int reading;
  const uint8_t scale = 1; // 1 for high frequencies, scale up to 15 for lowest freqs
 
  reading = scale * analogRead(POT);
  playTone(reading, 1000);
#ifdef SERIAL
  Serial.print("Freq = ");
  Serial.println(reading);
#endif
}
 
void chirp() {  // Bird chirp
  for(uint8_t i=200; i>180; i--)
     playTone(i,9);
}
 
void meow() {  // cat meow (emphasis ow "me")
  uint16_t i;
  playTone(5100,50);        // "m" (short)
  playTone(394,180);        // "eee" (long)
  for(i=990; i<1022; i+=2)  // vary "ooo" down
     playTone(i,8);
  playTone(5100,40);        // "w" (short)
}
 
void meow2() {  // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}
 
void mew() {  // cat mew
  uint16_t i;
  playTone(5100,55);       // "m"   (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w"   (short)
}
 
void ruff() {   // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}
 
void arf() {    // dog arf
  uint16_t i;
  playTone(890,25);          // "a"    (short)
  for(i=890; i<910; i+=2)    // "rrr"  (vary down)
     playTone(i,5);
  playTone(4545,80);         // intermediate
  playTone(12200,70);        // "ff"   (shorter, hard to do)
}
 
// play tone on a piezo speaker: tone shorter values produce higher frequencies
//  which is opposite beep() but avoids some math delay - similar to code by Erin Robotgrrl
 
void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(SPEAKER, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER, LOW);
     delayMicroseconds(tone1);
  }     
}
 
// another sound producing function similar to http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
void beep (int16_t frequencyInHertz, long timeInMilliseconds) {
    long x;	 
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++) {	 
       digitalWrite(SPEAKER,HIGH);
       delayMicroseconds(delayAmount);
       digitalWrite(SPEAKER,LOW);
       delayMicroseconds(delayAmount);
    }	 
}
 
void scale() {
  for(uint16_t i=50; i<15000; i++)  {
     playTone(i,20);
  }
}
