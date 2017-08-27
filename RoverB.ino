#include <VirtualWire.h>     //Adding the libraries
#include <AFMotor.h>
AF_DCMotor motor(4);
AF_DCMotor motor2(3);

int lanedetector1 = A0;         //PIR FOR GUIDANCE
int lanedetector2 = A1;         //PIR FOR GUIDANCE

int val0,val1;

void gostraight();
void straight();
void left();
void right();

int TX_PIN = A3;              //TRANSMITTER PIN FOR THE 433 MHz TXRX

const int trigPin = A4;       //ULTRASONIC TRIGGER
const int echoPin = A5;       //ULTRASONIC ECHO


int txdata;
char txmsg[4]; 

void setup() 
{
 vw_set_tx_pin(TX_PIN);
 Serial.begin(9600); 
 vw_setup(2000); 
motor.setSpeed(150);           //Default motor speed
motor2.setSpeed(150); 

pinMode(lanedetector1 , INPUT);   //Setting the PIR
pinMode(lanedetector2 , INPUT);

}

void loop() 
{
  
long duration, cm;

  val0=digitalRead(lanedetector1);
  val1=digitalRead(lanedetector2);
 
  gostraight();             // going at default speed

  
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);   //Setting the Ultrasonic sensor
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);   //Sending a pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);              //Recieving the echo
  duration = pulseIn(echoPin, HIGH);    //Storing the pulse duration  
  delay(100);
  cm = microsecondsToCentimeters(duration);
  

  txdata = cm;                         //copying the data to the transmitter
  itoa(txdata,txmsg,10);
  
  Serial.print(" ");
  Serial.print(txdata);
  Serial.print(" Txmsg: "); 
  Serial.print(txmsg);
  Serial.println(" ");
  delay(1000);
 
    
 vw_send((uint8_t *)txmsg, strlen(txmsg));     //Transmitting the distance
 vw_wait_tx(); // Wait until the whole message is gone
 
 delay(200); 
 }

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
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



