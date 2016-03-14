#define resolution 8
#define mains 50
#define thresold 20000

#define refresh 2 * 1000000 / mains
uint8_t sendData;
void setup() {
  Serial.begin(9600);

  // unused pins are fairly insignificant,
  // but pulled low to reduce unknown variables
  for(int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  for(int i = 8; i < 14; i++)
    pinMode(i, INPUT);
  for(int i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i,LOW);
  }
  startTimer();
}

void loop() {  
 sendData = 0;
 if(time(8, B00000001) > thresold) {
    sendData = 1;
    digitalWrite(2,HIGH);
  } else {
    sendData = 0;
    digitalWrite(2,LOW);
  }
  
  if(time(9, B00000010) >thresold) {
    sendData += 2;
    digitalWrite(3,HIGH); 
  } else {
    sendData += 0;
    digitalWrite(3,LOW); 
  }
  
  if(time(10, B00000100) >thresold) {
    sendData += 4;
    digitalWrite(4,HIGH);
  } else {
    sendData += 0;
    digitalWrite(4,LOW);
  }
  
  if(time(11, B00001000) > thresold) {
    sendData += 8;
    digitalWrite(5,HIGH);
  } else {
    sendData += 0;
    digitalWrite(5,LOW);
  }

  if(time(12, B00010000) > thresold) {
    sendData += 16;
    digitalWrite(6,HIGH);
  } else {
    sendData += 0;
    digitalWrite(6,LOW);
  }

  if(time(13, B00100000) > thresold) {
    sendData += 32;
    digitalWrite(7,HIGH);
  } else {
    sendData += 0;
    digitalWrite(7,LOW);
  }

 Serial.write(sendData);
} 

long time(int pin, byte mask) {
  unsigned long count = 0, total = 0;
  while(checkTimer() < refresh) {
    // pinMode is about 6 times slower than assigning
    // DDRB directly, but that pause is important
    pinMode(pin, OUTPUT);
    PORTB = 0;
    pinMode(pin, INPUT);
    while((PINB & mask) == 0)
      count++;
    total++;
  }
  startTimer();
  return (count << resolution) / total;
}

extern volatile unsigned long timer0_overflow_count;

void startTimer() {
  timer0_overflow_count = 0;
  TCNT0 = 0;
}

unsigned long checkTimer() {
  return ((timer0_overflow_count << 8) + TCNT0) << 2;
}

/*
 * 
  Serial.println(" ");Serial.print(time(8, B00000001), DEC);
  Serial.print(" ");
  Serial.print(time(9, B00000010), DEC);
  Serial.print(" ");
  Serial.print(time(10, B00000100), DEC);
  Serial.print(" ");
  Serial.println(time(11, B00001000), DEC);

 */
 
