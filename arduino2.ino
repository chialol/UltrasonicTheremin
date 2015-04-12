// Authors: Chia-Lo Lee and Emily Hsu
// 4/12/2015
#define DIST_PIN   0
#define SPEAKER   11


int dist_pin = DIST_PIN ;// define LED Interface
int knock_pin = A1;
int duration;
void setup ()
{
  Serial.begin(9600);
  duration = 0;
  pinMode (dist_pin, INPUT) ;// define LED as output interface
  pinMode(knock_pin, INPUT);
  pinMode(SPEAKER, OUTPUT);
}

void loop ()
{
  // Play the tone with the some frequency measured from A0
  duration = analogRead(A0);
  
  if (duration < 800) {
    playTone(min(duration, 2000), 50);
  } else {
    playTone(10, 50);
  }
}

/* 
Code from 
https://learn.adafruit.com/adafruit-trinket-modded-stuffed-animal/animal-sounds
*/
// Play a tone for duration
void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(SPEAKER, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER, LOW);
     delayMicroseconds(tone1);
  }     
}

// Play a dog ruff
void ruff() {   // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}
