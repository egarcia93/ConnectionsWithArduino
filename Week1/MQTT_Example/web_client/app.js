//Modified from Tom Igoe's code https://tigoe.github.io/mqtt-examples/p5js-mqtt-client/
//Using public testing hostname on shiftr.io you can make an account for a personal one
let broker = {
    hostname: 'public.cloud.shiftr.io',
    port: 443
};
// MQTT client:
let client;
// client credentials:
let creds = {
    clientID: 'p5LowResClient',
    userName: 'public',
    password: 'public'
}
// topic to subscribe to when you connect:
let topic = 'buttonLowRes';
// Storing data from MQTT topic
let incomingData = 0;

function setup() {
    createCanvas(400, 400);
    // Create an MQTT client:
    client = new Paho.MQTT.Client(broker.hostname, Number(broker.port), creds.clientID);
    // set callback handlers for the client:
    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;
    // connect to the MQTT broker:
    client.connect(
        {
            onSuccess: onConnect,       // callback function for when you connect
            userName: creds.userName,   // username
            password: creds.password,   // password
            useSSL: true                // use SSL
        }
    );
    
}

function draw() {
    background(120);
    //Changing color deppending on button data
    if(incomingData==1){
      fill(0);
    }else{
      fill(255);
    }
    circle(width/2, height/2, width/2);

    
}

// called when the client connects
function onConnect() {
   
    client.subscribe(topic);
}

// called when the client loses its connection
function onConnectionLost(response) {

}

// called when a message arrives
function onMessageArrived(message) {
   console.log(message.payloadString);
   incomingData =  message.payloadString;
}

// called when you want to send a message:
function sendMqttMessage() {
    // if the client is connected to the MQTT broker:
    if (client.isConnected()) {
       
        message = new Paho.MQTT.Message(msg);
        // choose the destination topic:
        message.destinationName = topic;
        // send it:
        client.send(message);
        
    }
}