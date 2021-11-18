//Modified from https://tigoe.github.io/mqtt-examples/MqttClientSender/
//Libraries for MQTT and WiFi
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
//File for secret passwords
//On this file change SSID and Password of your network
#include "Secret.h"
// WiFi and MQTT clients
WiFiClient wifi;
MqttClient mqttClient(wifi);

// details for MQTT client:
char broker[] = BROKER;
int port = 1883;
//topics and name of client
char topic[] = "buttonLowRes";
char topic2[] = "potLowRes";
char clientID[] = "arduinoLowRes";


// Pins for button and potentiometer
const int button = 2;
const int pot = 0;
const int debounceDelay = 5;
//Storing last button state 
int lastButtonState = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // wait for serial monitor to open:
  while (!Serial);

  // initialize I/O pins:
  pinMode(button, INPUT);
  

  // initialize WiFi, if not connected:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(SECRET_SSID);
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(2000);
  }
 
  // print IP address once connected:
  Serial.print("Connected. My IP address: ");
  Serial.println(WiFi.localIP());
 
  // set the credentials for the MQTT client:
  mqttClient.setId(clientID);
  mqttClient.setUsernamePassword(SECRET_MQTT_USER, SECRET_MQTT_PASS);

  // try to connect to the MQTT broker once you're connected to WiFi:
  while (!connectToBroker()) {
    Serial.println("attempting to connect to broker");
    delay(1000);
  }
  Serial.println("connected to broker");
}

void loop() {
  // if not connected to the broker, try to connect:
  if (!mqttClient.connected()) {
    Serial.println("reconnecting");
    connectToBroker();
  }

  // read the pushbutton:
  int buttonState = digitalRead(button);
  //read potentiometer
  int potValue = analogRead(pot);
  
  // if it's changed:
  if (buttonState != lastButtonState) {
    // debounce delay:
    delay(debounceDelay);
    // and it's pressed:
    if (buttonState == HIGH) {
      // start a new message on the topic:
      mqttClient.beginMessage(topic);
      mqttClient.print(1);
      // send the message:
      mqttClient.endMessage();
    //If stopped pressing
    }else{
       mqttClient.beginMessage(topic);
      mqttClient.print(0);
      // send the message:
      mqttClient.endMessage();
    }
    // save current state 
    lastButtonState = buttonState;
  }

  mqttClient.beginMessage(topic2);
  mqttClient.print(potValue);
  mqttClient.endMessage();

  delay(1);
  
}

boolean connectToBroker() {
  // if the MQTT client is not connected:
  if (!mqttClient.connect(broker, port)) {
    // print out the error message:
    Serial.print("MOTT connection failed. Error no: ");
    Serial.println(mqttClient.connectError());
    // return that you're not connected:
    return false;
  }
  // once you're connected, you can proceed:
  mqttClient.subscribe(topic);
  // return that you're connected:
  return true;
}
