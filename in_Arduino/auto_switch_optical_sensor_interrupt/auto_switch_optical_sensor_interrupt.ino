#include <MsTimer2.h>
#include <Servo.h>

//definition of pin assgin
#define SERVO_PIN           5
#define VCC_PIN            13

//definition of servo direction for dgree
#define SERVO_DEGREE_ON   180
#define SERVO_DEGREE_OFF  150
#define SERVO_DEGREE_NEU   90

//definition of timer millis
#define SERVO_ON_DELAY   5000
#define SERVO_OFF_DELAY   300
#define CHATTER_DELAY       1

//servo instance
Servo myservo;

void setup() {

  //set up serial port
  Serial.begin(9600);
  
  //servo initilize
  myservo.attach(SERVO_PIN);
  servoOutputNeutral();

  //optical sensor's power
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);
  
  //interrupt port settings
  DDRD = 0;
  PORTD = 0;
  
  PCICR |= _BV(PCIE2);
  PCMSK2 = _BV(PCINT20) ;
  sei();
  
}

ISR(PCINT2_vect)
{
  
  //It will be called when optical sensor value will be changed  
  //prevent fault behabior for chatterring
  //wait 1 msec
  MsTimer2::set(CHATTER_DELAY, wakeup);
  MsTimer2::start();
  
}

void wakeup () {
  
  //pin condition
  if(bit_is_set(PIND, 4)) {
    
    MsTimer2::set(SERVO_ON_DELAY, servoOutputON);
    MsTimer2::start();
  
  } else {
    
    MsTimer2::stop();
  
  }

}

void servoOutputON() {
  
  //servo rotate to on position, next start timer for rotating servo to neutral
  myservo.write( SERVO_DEGREE_ON );
  MsTimer2::set(SERVO_OFF_DELAY, servoOutputNeutral);
  MsTimer2::start();
  
}

void servoOutputOFF() {
  
  //servo rotate to off position, next start timer for rotating servo to neutral
  myservo.write( SERVO_DEGREE_OFF );
  MsTimer2::set(SERVO_OFF_DELAY, servoOutputNeutral);
  MsTimer2::start();
  
}

void servoOutputNeutral() {

  //servo rotate to neutral
  myservo.write( SERVO_DEGREE_NEU );   

}

void loop() {

  //read serial
  char c = Serial.read();
  if (c == 0x01) {
 
    //command to rotate to on position
    servoOutputON();
    
  }
  if(c == 0x00){
    
    //command to rotate to off position
    servoOutputOFF();
    
  }
  
  delay(100);
  
}
