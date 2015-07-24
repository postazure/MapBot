#include "motion_driver.cpp"
#include <Servo.h> 

#define leftServoPin 2
#define rightServoPin 3
MotionDriver driver( leftServoPin, rightServoPin );
            
void setup() 
{ 
  delay(2000);
} 
 
void loop() 
{ 
  driver.forward( 300, 30 );
  delay(500);
  driver.backward( 300, 30 );
  delay(500);
  driver.turnRight( 90 );
  delay(500);
  driver.turnLeft( 180 );
//  delay(500);
//  driver.turnRight( 45 );
  delay(2000);
  
}









