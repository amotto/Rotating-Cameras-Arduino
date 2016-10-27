// Controlling Servos With RC Controller V1
// 
// Made by amotto
// Based off of video/code by Brian Patton. Video found here: https://www.youtube.com/watch?v=BcyPer--Yi0

/* 

THINGS TO KNOW

The different parts of the controller correspond to different channels.  CH5 is the swtich on the top left. CH1 and CH4 are the main control sticks.

*/

#include <Servo.h>
#include <stdio.h>
 
Servo S1;
Servo S2;

int CH1, CH2, CH3, CH4, CH5, CH6;
int timeRunning;
int POS;

void setup(){
  
  Serial.begin(9600);
  
  pinMode(7, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
    
  S1.attach(13);
  S2.attach(12);
  
}

void loop(){

timeRunning = micros();

/* A huge problem currently is that the pulseIn's below drastically reduce response times on the servos. This is because the processor needs to 
spend time checking each one before it can move on to writing to the ones that are active. That is why all of them except CH1 and 4 are commented out.
The timeRunning integer above may help solve this problem, but this will take some googling. 

Also, the conditional statements are commented out for now because we don't have enough wires to hook up every channel, so CH5 is not working yet.*/


CH1 = pulseIn(7, HIGH);
//CH2 = pulseIn(2, HIGH);
//CH3 = pulseIn(3, HIGH);
CH4 = pulseIn(4, HIGH);
//CH5 = pulseIn(5, HIGH);
//CH6 = pulseIn(6, HIGH);
   
//if (CH5 > 1800)
 writeToServos();
 // S1.writeMicroseconds(CH1);
//else
 showInput();

}


void writeToServos() {

  if (CH1 > 1450 && CH1 < 1550)
    S1.writeMicroseconds(1500); // Basically stay still. Might need to adjust the condition values, may be too broad
  else 
  {
    if (CH1 >= 1000 && CH1 <= 2000){ //1000 is fully counter-clockwise, and 2000 is fully clockwise. Assuming 1000 == 0 degrees, 2000 == 180 degrees on the servos
      
      //S1.writeMicroseconds(CH1);

      /* Ok, so this section is a little strange. Right now the RC controller is only able to make the servos turn at a minimum of 1300 and a 
	 maximum of 1700. The min and max should be 1000 and 2000 respectively, so something is wrong here. For now, the workaround has been to
	 artificially extend these ranges by mutliplying the difference between the max and min and the base value of 1500 by 2.5. This gets us to 
	 those maximum ranges, however the amount of rotation precision we had before is hampered by this. The servos also 'wobble' a bit when
	 you try holding them to a certain value 

	 It's possible this problem is simply because the controller has low batteries or something like that, but until it's figured out we're
	 using this. Once it's fixed we can just uncomment the normal implementation. */

      POS = 2.5 * (CH1 - 1500) + 1500;
      S1.writeMicroseconds(POS);
    }
    else if (CH1 < 1000) // prevent servo from going beyond its minimum limit
      S1.writeMicroseconds(1000);
    else if (CH1 > 2000) // prevent servo from going beyond its maximum limit
      S1.writeMicroseconds(2000);
  }
  
  
  //See comments above, they apply for below
  
  if (CH4 > 1450 && CH4 < 1550)
    S2.writeMicroseconds(1500); 

    // Currently our second servo is busted, so I haven't bothered copying the code from above for this one.
  else 
  {
    if (CH4 >= 1000 && CH4 <= 2000)
      S2.writeMicroseconds(CH4);
    else if (CH4 < 1000)
      S2.writeMicroseconds(1000);
    else if (CH4 > 2000)
      S2.writeMicroseconds(2000);
  }

}

void showInput() {

	if (timeRunning > ){
 	 Serial.print("\nCH1: ");
	  Serial.println(CH1);
	  Serial.print("CH2: ");
	  Serial.println(CH2);
	  Serial.print("CH3: ");
	  Serial.println(CH3);
	  Serial.print("CH4: ");
	  Serial.println(CH4);
	  Serial.print("CH5: ");
	  Serial.println(CH5);
	  Serial.print("CH6: ");
	  Serial.println(CH6);
	  timeRunning = 0;
	}

	/* This thing is currently screwed up. Ideally I would to clear the serial monitor every time this prints so that it looks clean...
	easier said than done I suppose. */
  
}