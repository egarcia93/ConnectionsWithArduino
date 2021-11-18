//Based on ITP Physical Computing Labs
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-input-to-the-p5-js-ide/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-output-from-p5-js/
//https://itp.nyu.edu/physcomp/labs/labs-serial-communication/two-way-duplex-serial-communication-using-p5js/


//Variable for Serial library object
let serial;   
// Your port name here 
let portName = 'COM3'; 

// Variable for incoming data from Arduino
let inputData;  


function setup() {

  //Serial port library
  serial = new p5.SerialPort();       
  //Event listeners for serial port

  //When receiving list of available ports
  serial.on('list', printList);  
  //Connection listener
  serial.on('connected', serverConnected);
  //Port opened
  serial.on('open', portOpen);
  //This will be the listener to incoming data        
  serial.on('data', serialEvent);    
  
  serial.on('error', serialError);   
  serial.on('close', portClose);      
 
  //List available ports & open port
  serial.list();                      
  serial.open(portName);           

  const c = createCanvas(500,500);
  c.parent("canvas-container");
  rectMode(CENTER);
}

function printList(portList) {
    // portList is an array of serial port names
    for (var i = 0; i < portList.length; i++) {
      // Display the list the console:
      console.log(i + portList[i]);
    }
  }

  function serverConnected() {
    console.log('connected to server.');
  }
   
  function portOpen() {
    console.log('the serial port opened.')
  }
   
  function serialEvent() {
    inputData = serial.read();
    
  }
   
  function serialError(err) {
    console.log('Something went wrong with the serial port. ' + err);
  }
   
  function portClose() {
    console.log('The serial port closed.');
  }

  function draw() {
    background(120);
    fill(255);
    text("Button value: " + inputData, (width/2)-50, (height/2)-100);
    //If button is pressed change color of rectangle
    if(inputData==1){
      fill('white');
    }else if(inputData==0){
      fill('black');
    }
    rect(width/2,height/2,100,100);
 }
 