#include <Arduino.h>
#include <Servo.h> 

class MotionDriver {  
public:
  void initialize(int leftServo, int rightServo){
    _leftServoPin = leftServo;
    _rightServoPin = rightServo; 
  }

  void forward(int duration, int speed){
    Serial.println("Forward distance: " + String(duration) + " Speed: " + String(speed));
    doMove( "forward", duration, speed, speed );
  }

  void backward(int duration, int speed){
    Serial.println("Backward distance: " + String(duration) + " Speed: " + String(speed));
    doMove( "backward", duration, speed, speed );
  }

private:
  int _leftServoPin;
  int _rightServoPin;
  Servo _rServo;  
  Servo _lServo;
  
  int boundedSpeed(int speed){
    if( speed > 90 ) { return 90; }
    if( speed < 1  ) { return 1; }
    return speed;
  }
  
  void fullStop(){
    _lServo.detach();
    _rServo.detach();   
  }

  void start(){
    _rServo.attach(_rightServoPin);  
    _lServo.attach(_leftServoPin);
  }

  void doMove( String towards, int duration, int leftSpeed, int rightSpeed ){
    start();
    int spd[2];
    spd[0] = setDirection( towards, leftSpeed, rightSpeed )[0];
    spd[1] = setDirection( towards, leftSpeed, rightSpeed )[1];
    leftSpeed = spd[0];
    rightSpeed = spd[1];

    do {   
      _lServo.write( leftSpeed );
      _rServo.write( rightSpeed );  
      delay(15);
      duration -= 1;
    } while (duration >= 0);
    
    fullStop();
  }

 int * setDirection( String heading, int leftSpeed, int rightSpeed ) {
    int left = 90;
    int right = 90;
    Serial.println("before - " +String(leftSpeed) + " | " + String(rightSpeed));
        
    if ( heading == "forward" ) {
        Serial.println("forward");
        left = 90 + leftSpeed;
        right = 90 - rightSpeed;
    } else if ( heading == "backward" ) {
        Serial.println("backward");
        left = 90 - leftSpeed;
        right = 90 + rightSpeed;
    } else {
        Serial.println("Warning setDirection: Direction " + heading + " not recognized."); 
    }
    
    int speeds [2] = { left, right };
    Serial.println("after - " +String(speeds[0]) + " | " + String(speeds[1]));
    return speeds;
  }
};

