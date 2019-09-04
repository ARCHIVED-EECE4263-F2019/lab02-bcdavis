// Ben Davis
// EECE4263 Embedded Systems
// Lab 02 -- Small motorized fan with button adjustment
//9-4-2019

/***************************************/
// system defines

#define motorIn1 D5                 // the one pin of the motor attach to pin 3 on L293D
#define motorIn2 D6                 // the another pin of the motor attach to pin 6 on L293D

const int btnPressed = 1023;        // abstracting the value of a button press for readability

const int directionbtn = D1;        
const int speedbtn = D0;            
int speedlvl = 0;                   // 0 = off, 1023 = fast, 700 = slow
char directionlvl = 'r';            // 'r' for clockwise, 'l' for counter-clockwise 

// variables to help determine if button is pressed/held down .
int speedbtnState = 0;              // current button state
int prevSpeedbtnState = 0;          // last button state  

int dirbtnState = 0;                // current button state
int prevDirbtnState = 0;            // last button state
/***************************************/

void setup()
{
  Serial.begin(9600);
  pinMode(motorIn1,OUTPUT); //initialize the motorIn1 pin as output 
  pinMode(motorIn2,OUTPUT); //initialize the motorIn2 pin as output 
  pinMode(directionbtn, INPUT);
  pinMode(speedbtn, INPUT);
}
/****************************************/

void loop()
{
  speedbtnState = analogRead(speedbtn);
  dirbtnState = analogRead(directionbtn);
  if((speedbtnState == btnPressed) && (dirbtnState == btnPressed)){ // first check to see if both buttons are pressed 
    Serial.println("@@@@@@@ Both buttons pressed at the same time! @@@@@@@");
    speedlvl = 0;
    directionlvl = 'r';
  }
  else if((speedbtnState == btnPressed) && (prevSpeedbtnState != speedbtnState)){ // if button is pressed for multiple iterations, only first one matters
    /*Serial.print("Current Button State, Previous button State: ");
    Serial.print(speedbtnState);
    Serial.print(prevSpeedbtnState);
    Serial.println();
    delay(500);*/
    checkSpeedbtn();
    prevSpeedbtnState = speedbtnState;
  }
  
  else if((dirbtnState == btnPressed) && (prevDirbtnState != dirbtnState)){
    /*Serial.print("Current direction State, Prev dir state: ");
    Serial.print(dirbtnState);
    Serial.print(prevDirbtnState);
    Serial.println();
    delay(500);*/
    changeDirection();
    prevDirbtnState = dirbtnState;
  }
  

  go(directionlvl, speedlvl);
  Serial.print("Current Speed, Current direction: ");
  Serial.print(speedlvl);
  Serial.print(", ");
  Serial.print(directionlvl);
  Serial.println();
  prevSpeedbtnState = speedbtnState; 
  prevDirbtnState = dirbtnState;
  Serial.print("prev Speedbtn State, prev directionbtn state: ");
  Serial.print(prevSpeedbtnState);
  Serial.print(", ");
  Serial.print(prevDirbtnState);
  Serial.println();

}
/****************************************/

//The function to drive motor & rotate clockwise
void clockwise(int Speed){
  analogWrite(motorIn1,Speed); //set the speed of motor
  analogWrite(motorIn2,0); //stop the motorIn2 pin of motor
}

//The function to drive motor & rotate counterclockwise
void counterclockwise(int Speed){
  analogWrite(motorIn1,0); //stop the motorIn1 pin of motor
  analogWrite(motorIn2,Speed); //set the speed of motor
}

// This function makes the motor 'go' according to speedlvl and directionlvl
void go(char dir, int spd){
  if(dir == 'l'){
    counterclockwise(spd);
  }
  else{
    clockwise(spd);
  }
}

// This function executes when directionbtn is pressed. Changes direction of motor rotation.
void changeDirection(){
  Serial.println("------------------ changeDirection function executing.");
  if(directionlvl == 'r'){              // if current direction is counter-clockwise, change to clockwise
    directionlvl = 'l';
    // Serial.println("Right --> Left");
  }
  else if(directionlvl == 'l'){         // if current direction is clockwise, change to counter-clockwise
    directionlvl = 'r';
    //Serial.println("Left --> Right");
  }
}

// This function executes when speedbtn is pressed. Changes to the next motor speed.
void checkSpeedbtn(){
  Serial.println("----------------------------- checkSpeedbtn function executing.");
  if(speedlvl == 0){
    //Serial.println("OFF --> FAST");
    speedlvl = 1023; 
  }
  else if(speedlvl == 1023){
    //Serial.println("FAST --> SLOW");
    speedlvl = 700;
  }
  else if(speedlvl == 700){
    //Serial.println("SLOW --> OFF");
    speedlvl = 0;
  }
}
/****************************************/
