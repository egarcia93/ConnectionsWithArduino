//Based on ITP Physical Computing Labs
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-input-to-the-p5-js-ide/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-output-from-p5-js/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/two-way-duplex-serial-communication-using-p5js/

//Input pin for button
const int button =  2;
//Variable for keeping button state
int buttonState = 0;

void setup() {

  //Starting serial communication
  Serial.begin(9600);

  //Set button pin as Input
  pinMode(button,INPUT);
  
}

void loop() {
  //Read data from button
  buttonState = digitalRead(button);
  //Send it over serial
  Serial.write(buttonState);
  //Small time for ADC
  delay(1);
}
