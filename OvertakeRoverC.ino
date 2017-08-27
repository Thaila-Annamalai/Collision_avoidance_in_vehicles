#include <VirtualWire.h>
#include <AFMotor.h>

const int trigPin = A4; //ULTRASONIC TRIGGER 
const int echoPin = A5; //ULTRASONIC ECHO


int RX_PIN = A2;               //RECIEVER PIN FOR THE 433 MHz TXRX

int lanedetector1 = A0;         //PIR FOR GUIDANCE
int lanedetector2 = A1;         //PIR FOR GUIDANCE

int val0,val1;

int rxdata;
char rxmsg[4]; 

AF_DCMotor motor(4);
AF_DCMotor motor2(3);

//void straight();
//void staright1();
//void left();
//void right();
//void avoidsequence();
//void overtakesequence();
//void gostraight1();
//void gostraight()

void setup() 
{
 
 Serial.begin(9600);
    
 vw_set_rx_pin(RX_PIN);        //setting the reciever 
 vw_set_ptt_inverted(true); 
 vw_setup(2000);     
 vw_rx_start();

 
motor.setSpeed(150);         //Default motor speed
motor2.setSpeed(150); 

pinMode(lanedetector1 , INPUT);   //Setting the PIR
pinMode(lanedetector2 , INPUT);

} 

void loop(){

 long duration, cm;

  val0=digitalRead(lanedetector1);
  val1=digitalRead(lanedetector2);
  gostraight();  // going at default speed
  pinMode(trigPin, OUTPUT);    //Setting the Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //Sending a pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);    //Recieving the echo
  duration = pulseIn(echoPin, HIGH);  //Storing the pulse duration
  cm = microsecondsToCentimeters(duration);
  Serial.print("The nearest vehicle is at :");
  Serial.print(cm);
  Serial.print("  ");
  Serial.println();
  

  delay(100);
    uint8_t buf[VW_MAX_MESSAGE_LEN];         //Settign the recirver buffer 
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) 
    {                                       //Revieving the mesage
    int i;
        for (i = 0; i < buflen; i++)
    {            
 rxmsg[i] = char(buf[i]);                     //Storing the message
    }
        rxmsg[buflen] = '\0';
        rxdata = atoi(rxmsg);
        Serial.print("Preceedding vehicle diatance:");
        Serial.print(rxmsg);
        Serial.println();
        
if(rxdata<30 || cm<40)
        {
          avoidsequence();
          Serial.print("Avoid Collision Sequence ");
        }
        else
        {
          overtakesequence();
           Serial.print("Overtake the vehicle ");
        }
    }
}

void straight()
{
   motor.run(FORWARD);
  motor2.run(FORWARD);
  }
void right()
{
  motor.run(BACKWARD);
  motor2.run(FORWARD);
  
}
void left()
{
  motor.run(FORWARD);
  motor2.run(BACKWARD);
   
} 

void gostraight()
{
  if( val0==1 && val1==0)
  left();
  
  else if(val0==0 && val1==1)
   right();
  
  else
  straight();

  
}



void goovertake()
{
  
  if( val0==1 && val1==0)
  left();
  
  else if(val0==0 && val1==1)
   right();
  
  else
  straightspeed();


}


void avoidsequence()
{

goavoid();


}
void overtakesequence()
{
  goovertake();

}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void goavoid()
{
  
  if( val0==1 && val1==0)
  left();
  
  else if(val0==0 && val1==1)
   right();
  
  else
  straightslow();


}


void straightspeed()
{
  int i;
for(i=150;i<230;i++)
{
motor.setSpeed(i);
motor2.setSpeed(i); 
motor.run(FORWARD);
motor2.run(FORWARD);
delay(5);

  }
}

void straightslow()
{
  int i;
for(i=150;i>50;i--)
{
motor.setSpeed(i);
motor2.setSpeed(i); 
motor.run(FORWARD);
motor2.run(FORWARD);
delay(5);

  }
}




  


  
