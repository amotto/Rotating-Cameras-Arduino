//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// Controlling Servos With Buttons V2
// 
// Made by amotto
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/2839175-controlling-servos-with-buttons-v2
//
//
// Last change made: Removed delays throughout the program. 

#include <Servo.h>
#include <stdio.h>
 
Servo S1;
Servo S2;

//int LED = 2; In case an LED is desired I suppose

int BU1 = 11;
int BU2 = 10;
int BU3 = 9;
int BU4 = 8;
int BU5 = 7;
int BU6 = 6;

int S1_POSITION;
int S2_POSITION;
int INCREMENT_VAL = 20;

int BU1_STATE;
int BU2_STATE;
int BU3_STATE;
int BU4_STATE;
int BU5_STATE;
int BU6_STATE;

char serialInput;

void setup(){
  
  Serial.begin(9600);
  
  pinMode(BU1, INPUT);
  pinMode(BU2, INPUT);
  pinMode(BU3, INPUT);
  pinMode(BU4, INPUT);
  pinMode(LED, OUTPUT);
    
  S1.attach(13);
  S2.attach(12);
  
  S1.write(S1_POSITION);
  S2.write(S2_POSITION);
  // delay(100);  A delay here isn't terrible, although unnecessary I think
}

void loop(){
 
  BU1_STATE = digitalRead(BU1);
  BU2_STATE = digitalRead(BU2);
  BU3_STATE = digitalRead(BU3);
  BU4_STATE = digitalRead(BU4);
  BU5_STATE = digitalRead(BU5);
  serialInput = Serial.read();
   
  
  if (BU1_STATE == HIGH || serialInput == 'w') {

    S1_POSITION += INCREMENT_VAL;
    
    if (S1_POSITION > 180) // Restricting the maximum angle of S1
      	S1_POSITION = 180;
    
    S1.write(S1_POSITION);
    printf("%d" , S1_POSITION);
  	

 }

 if (BU2_STATE == HIGH || serialInput == 's'){

    S1_POSITION -= INCREMENT_VAL;
   
   	if (S1_POSITION < 0) // Restricting the minimum angle of S2
      	S1_POSITION = 0;
   
    S1.write(S1_POSITION);
    printf("%d" , S1_POSITION);
  	
 }

 if (BU3_STATE == HIGH || serialInput == 'a'){

    S2_POSITION += INCREMENT_VAL; // Restricting the maximum angle S3
   
   	if (S2_POSITION > 180)
      	S2_POSITION = 180;
   
    S2.write(S2_POSITION);
    printf("%d" , S2_POSITION);
  	
 }

 if (BU4_STATE == HIGH || serialInput == 'd'){

    S2_POSITION -= INCREMENT_VAL; // Restricting the minimum angle S4
   
   	if (S2_POSITION < 0) 
      	S2_POSITION = 0;
   
    S2.write(S2_POSITION);
    printf("%d" , S2_POSITION);
  	

 }
  
 if (BU5_STATE == HIGH || serialInput == 'i'){

   if (INCREMENT_VAL == 20){
      	INCREMENT_VAL = 5;
     	digitalWrite(LED, HIGH);
     	
   }
    
   else if (INCREMENT_VAL == 5){
      	INCREMENT_VAL = 20;
        digitalWrite(LED, LOW);
      	
   }

 }
  
}
