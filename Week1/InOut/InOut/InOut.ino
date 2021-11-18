//Based on ITP Physical Computing Labs
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-input-to-the-p5-js-ide/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-output-from-p5-js/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/two-way-duplex-serial-communication-using-p5js/

//Input pin for button
const int button =  2;
//Input pin for potentiometer
const int pot = 0;
//Output pin for LED
const int led = 3;
//Variable for keeping inputs states
int buttonState = 0;
int potValue = 0;

void setup() {

  //Starting serial communication
  Serial.begin(9600);

  //Set inputs and outputs
  pinMode(button,INPUT);
  pinMode(led,OUTPUT);
  
}

void loop() {
  
  //Constantly read inputs
  buttonState = digitalRead(button);
  potValue = analogRead(pot);
  
  //Print data in serial port as ASCII
  Serial.print(buttonState);
  //Concatenate values with a comma
  Serial.print(",");

  Serial.println(potValue);


 //Check if Serial is available for reading data 
  if (Serial.available() > 0) { 
    //Read what is incoming
    int inByte = Serial.read();
    //If a 1 is coming then turn on LED   
    if(inByte==1){
        digitalWrite(led,HIGH);
      }else{
        digitalWrite(led,LOW);      
      }
    }
  //Delay for stabilizing the ADC
  delay(1);
}
