#include <Arduino.h>
#include <Servo.h> 

class MotionDriver {  
 const int TUNING = 7;
public:
  void initialize(int leftServo, int rightServo){
    _leftServoPin = leftServo;
    _rightServoPin = rightServo; 
  }

  void forward(int duration, int spd){
    Serial.println("Forward distance: " + String(duration) + " Speed: " + String(spd));
    doMove( "forward", duration, spd );
  }

  void backward(int duration, int spd){
    Serial.println("Backward distance: " + String(duration) + " Speed: " + String(spd));
    doMove( "backward", duration, spd );
  }

  void turnRight(int angle){
    int compensatedAngle = angle - TUNING * (angle/90);
    doMove( "right", compensatedAngle, 50 );
  }

  void turnLeft(int angle){
    int compensatedAngle = angle - TUNING * (angle/90);
    doMove( "left", compensatedAngle, 50 );
  }
  
private:
  int _leftServoPin;
  int _rightServoPin;
  Servo _rServo;  
  Servo _lServo;
  
  void fullStop(){
    _lServo.detach();
    _rServo.detach();   
  }

  void start(){
    _rServo.attach(_rightServoPin);  
    _lServo.attach(_leftServoPin);
  }

  void doMove( String towards, int duration, int spd ){
    start();
    
    int leftSpeed = setDirection( towards, spd )[0];
    int rightSpeed = setDirection( towards, spd )[1];

    for(int i = 0; i <= duration; i++) {
      _lServo.write( leftSpeed );
      _rServo.write( rightSpeed );  
      delay(15);     
    } 
    
    fullStop();
  }

 int * setDirection( String heading, int spd ) {
    int left = 90;
    int right = 90;
    
    Serial.println( "Heading: " + heading + " Speed: " + String(spd) );
    
    if (        heading == "forward"  ) {    
      left = 90 + spd;
      right = 90 - spd;
    } else if ( heading == "backward" ) {
      left = 90 - spd;
      right = 90 + spd;
    } else if ( heading == "right"    ) {
      left = 90 + spd/2;
      right = left;
    } else if ( heading == "left"     ) {
      left = 90 - spd/2;
      right = left;
    } else {
        Serial.println("Warning setDirection: Direction " + heading + " not recognized."); 
    }

    int speeds [2] = { left, right };
    Serial.println("after - " +String(speeds[0]) + " | " + String(speeds[1]));
    return speeds;
  }
};

