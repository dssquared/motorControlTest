/*
 *   Motor control test using SN754410 and two DC motors
 *
 *   Not practical for any application, just for testing
 *   and learning purposes
 *
 *  Micro controller is expecting a serial input of: motor, direction, speed. ie af6, br8 etc.
                                            motor: a - motor one,  b - motor two
											direction: f -forward, r -reverse
											speed: integer 0 - 9 that will be mapped to PWM value

 *  If using a switch case: need to "turn off" new line char in serial monitor or
 *  terminal program in order for the switch case to work properly or it will pick
 *  up the CR and go to the default case

      Author: David Schwehr  dpschwehr@gmail.com  dssquared @ google+      Rev. 1 - May 2015

 */

//  motor one control pins
 const int motor1a = 5;   //pin2 1A on SN754410
 const int motor2a = 6;   //pin7 2A on SN754410
 const int enPin12 = 9;   //pin1 1,2EN on SN754410
 //  motor two control pins
 const int motor3a = 7;   //pin10 3A on SN754410
 const int motor4a = 8;   //pin15 4A on SN754410
 const int enPin34 = 10;  //pin9 3,4EN on SN754410 
 
 char direction12;        //direction for motor one
 char direction34;        //direction for motor two
 
 
 void setup(){
	 //initialize control pins for motor one to outputs
   pinMode(motor1a, OUTPUT);  //input pin to motor one control
   pinMode(motor2a, OUTPUT);  //input pin to motor one control
   pinMode(enPin12, OUTPUT);  //enable pin to motor one control
     //initialize control pins for motor two to outputs
   pinMode(motor3a, OUTPUT);  //input pin to motor two control
   pinMode(motor4a, OUTPUT);  //input pin to motor two control
   pinMode(enPin34, OUTPUT);  //enable pin to motor two control
   
   //??  initialize enable pins to something ??
   
   //initialize motor control pins to keep motors from
   //turning when enable pins are set high or PWM
   digitalWrite(motor1a, LOW);
   digitalWrite(motor2a, LOW);
   digitalWrite(motor3a, LOW);
   digitalWrite(motor4a, LOW);
   
   Serial.begin(9600);
 }  // end setup()

 
 void loop(){
   if(Serial.available() > 2){
     char motor = Serial.read();
	 //*************   motorOne control   *************
	 if(motor == 'a'){  // 'a' for motor one
		 direction12 = Serial.read();
		/*if(input == 'r'){  //set direction
			 direction12 = 'r';
		}else if(input == 'f'){
			 direction12 = 'f';
		}
		*/
		int rate = Serial.read();
		if(rate >= '0' && rate <= '9'){ 
			int speed = map(rate, 0, 9, 50, 200);   //map to value 0-255 play with each motor to see how close to 0 and 255 without binding/whining
			runMotorOne(speed);                     //run motor at speed and direction
        }
        else{
			brakeOne();
			Serial.println("Put on brake motor one!! Invalid value for speed entered for motor one");
		}
	 } //end input a
	 
	 //**********  motorTwo control   ******************
	 if(motor == 'b'){  // 'b' for motor two
		 //if(input == 'r'){  //set direction
			 direction34 = Serial.read();
			 //}else if(input == 'f'){
			 //direction34 = 'f';
		 //}
		 int rate = Serial.read();
		 if(rate >= '0' && rate <= '9'){
			 int speed = map(rate, 0, 9, 70, 200);  //map to value 0-255 play with each motor to see how close to 0 and 255 without binding/whining
			 runMotorTwo(speed);                    //run motor at speed and direction
		 }
		 else{
			 brakeTwo();
			 Serial.println("Put on brake motor two!! Invalid value for speed entered for motor two.");
		 }
	 } //end input b
  }  //end serial.avail
  //      ??  maybe put in an else statement if first input does not match 'a' or 'b' ??
 }  // end loop
 
 	 
/*********************************************
    motorOne functions
 ********************************************/	
void runMotorOne(int rate){
	brakeOne();
	analogWrite(enPin12, rate);
	if(direction12 == 'r'){
		reverseOne();
		}else if(direction12 == 'f'){
		forwardOne();
		}else{
		brakeOne();
		Serial.println("Invalid data entered!!  Brakes!!");
	}
}  //end runMotorOne()
	 
 void forwardOne(){
   digitalWrite(motor1a, HIGH);
   digitalWrite(motor2a, LOW);
 }
 
 void reverseOne(){
   digitalWrite(motor1a, LOW);
   digitalWrite(motor2a, HIGH);
 }
 
 void brakeOne(){
   digitalWrite(motor1a, LOW);
   digitalWrite(motor2a, LOW);
 }
 /********************************************/
                                                // maybe make one function runMotor() that takes
                                                // parameters for motor, speed, and direction
 /*******************************************
    motorTwo functions
 ********************************************/
 void runMotorTwo(int rate){
	 brakeTwo();
	 analogWrite(enPin34, rate);
	 if (direction34 == 'r'){
		 reverseTwo();
		 }else if (direction34 == 'f'){
		 forwardTwo();
		 }else{
		 brakeTwo();
		 Serial.println("Invalid data entered!!  Brakes!!");
	 }
 }  // end runMotorTwo()
 
 void forwardTwo(){
 digitalWrite(motor3a, HIGH);
 digitalWrite(motor4a, LOW);
 }
 
 void reverseTwo(){
 digitalWrite(motor3a, LOW);
 digitalWrite(motor4a, HIGH);
 }
 
 void brakeTwo(){
 digitalWrite(motor3a, LOW);
 digitalWrite(motor4a, LOW);
 }
 /***********************************************/
