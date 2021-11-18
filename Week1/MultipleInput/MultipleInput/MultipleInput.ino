//Based on ITP Physical Computing Labs
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-input-to-the-p5-js-ide/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-output-from-p5-js/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/two-way-duplex-serial-communication-using-p5js/

//Input pin for button
const int button =  2;

const int pot = 0;

//Variable for keeping button state
int buttonState = 0;
int potValue = 0;
void setup() {

  //Starting serial communication
  Serial.begin(9600);

  //Set button pin as Input
  pinMode(button,INPUT);
 
  
}

void loop() {
  
  //Constantly read button pin
  buttonState = digitalRead(button);
  potValue = analogRead(pot);
  
  //Write data in serial port
  //(buttonState,potValue)
  
  Serial.print(buttonState);
  
  Serial.print(",");

  Serial.println(potValue);

  //Delay for stabilizing ADC
  
  delay(1);
}
