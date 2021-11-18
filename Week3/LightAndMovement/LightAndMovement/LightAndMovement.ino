//Libraries for IMU and converting data
#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>

//Object for filtering IMU data
Madgwick filter;

//Sensor rate of IMU sensor
const float sensorRate = 104.00;

//Input pin for LDR
int light = 0;
//Variable for storing light value
int lightValue = 0;
//LED pin
int led = 13;
void setup() {
  //Start Serial
  Serial.begin(9600);
  //Check if IMU is working
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    //Stop if its not working
    while (true);
  }
  // start the filter to run at the sample rate:
  filter.begin(sensorRate);
  pinMode(led,OUTPUT);
}

void loop() {
  //Read analog value
  lightValue = analogRead(light);
  //Values for acceleration and rotation
  float xAcc,yAcc,zAcc;
  float xGyro,yGyro,zGyro;

  //Orientation
  float roll,pitch,heading;
  //Reading IMU data
  if(IMU.accelerationAvailable() &&IMU.gyroscopeAvailable()){

    IMU.readAcceleration(xAcc,yAcc,zAcc);
    IMU.readGyroscope(xGyro,yGyro,zGyro);
    //Filter data
    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);
    // Get the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    //Print IMU & LDR values
    Serial.print(heading);
    Serial.print(";");
    Serial.print(pitch);
    Serial.print(";");
    Serial.print(roll);
    Serial.print(";");
    Serial.println(lightValue);
    }

  //Read incoming data
   if(Serial.available() > 0 ){
      char incomingData = Serial.read();
      if(incomingData == 'A') {
        digitalWrite(led,HIGH);
      }else if(incomingData == 'Z') {
        digitalWrite(led,LOW); 
      }
  }
  //Delay for ADC stabilizing;
  delay(1);
  

}
