/*
The Smart Fish Tank
University of Waterloo Electrical Engineering 4th Year Design Project
Author: Hao Luo
License: GPL
Version: 0.1
Date: July, 2015
 */

 // In order to run the code, you must donwload the following Arduino libraries 
 // and include them properly
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include <Process.h>


// Listen on default port 5555, the webserver on the Yún
// will forward there all the HTTP requests for us.
YunServer server;
long hits = 0;

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 13
#define LIGHT1 5
#define LIGHT2 6
#define FILTER 2
#define HEATER 4
#define FEEDER 3
#define STEP1 12
#define DIR1 11
#define STEP2 8
#define DIR2 7
#define SUPSTEP 10
#define SUPDIR 9

int Distance = 0;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup() {

  Serial.begin(9600);
  // Bridge startup
  Bridge.begin();
  Console.begin();
  
  Serial.println("connected to serial");

  while (!Console) {
    ; // wait for Console port to connect.
  }
  Console.println("You're connected to the Console!!!!");

  //pin setup
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(HEATER, OUTPUT);
  pinMode(FILTER, OUTPUT);
  pinMode(FEEDER, OUTPUT);
  pinMode(STEP1, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(SUPSTEP, OUTPUT);
  pinMode(SUPDIR, OUTPUT);
  //Heater
  //Food 1
  // AccelStepper food1(3,4,5);
  //Food 2
  // AccelStepper food2(6,7,8);
  //Supplement
  //AccelStepper supp(9,10,11);

  int f1 = 380;
  int f2 = 380;
  int sup = 380;
  //food1.setMaxSpeed(1000);
  //food1.setAcceleration(500);
  //food2.setMaxSpeed(1000);
  //food2.setAcceleration(500);
  //supp.setMaxSpeed(1000);
  //supp.setAcceleration(500);

  digitalWrite(LIGHT1, HIGH);
  digitalWrite(LIGHT2, HIGH);
  digitalWrite(HEATER, HIGH);
  digitalWrite(FILTER, HIGH);
  digitalWrite(FEEDER, HIGH);
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  digitalWrite(SUPDIR, LOW);
  digitalWrite(STEP1, LOW);
  digitalWrite(STEP2, LOW);
  digitalWrite(SUPSTEP, LOW);

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
  sensors.begin();

}

// the main loop
void loop() {
  // Get clients coming from server
  YunClient client = server.accept();
  // There is a new client?
  if (client) {
    Console.println("We have a new client!");

    process(client);

    client.stop();
  }
  delay(50);
}

void process (YunClient client)
{
  String command = client.readString();
  command.trim();
  Console.print("The command is ");
  Console.print(command);

  if (command == "temperature") {
    temperatureCommand(client, command);
  }
  if (command == "lightOn1") {
    lightOn1(client, command);
  }
  if (command == "lightOff1") {
    lightOff1(client, command);
  }
  if (command == "lightOn2") {
    lightOn2(client, command);
  }
  if (command == "lightOff2") {
    lightOff2(client, command);
  }
  if (command == "heaterOn"){
     heaterOn(client, command); 
  }
  if (command == "heaterOff"){
     heaterOff(client, command); 
  }
  if (command == "filterOn"){
     filterOn(client, command); 
  }
  if (command == "filterOff"){
     filterOff(client, command); 
  }
  if (command == "feederOn"){
     feederOn(client, command); 
  }
  if (command == "feederOff"){
     feederOff(client, command); 
  }
  if (command == "food1") {
    food1Command(client, command);
  }
  if (command == "food2") {
    food2Command(client, command);
  }
  if (command == "Supp") {
    supplementCommand(client, command);
  }
  if (command == "videoOn") {
    videoOnCommand(client, command);
  }
  if (command == "videoOff") {
    videoOffCommand(client, command);
  }
}

void temperatureCommand (YunClient client, String command) {
  Console.println("temperatureCommand");
  sensors.requestTemperatures();
  client.print(sensors.getTempCByIndex(0));
  client.println(" degrees C");
}

void lightOn1 (YunClient client, String command) {
  Console.println("lightOn1");
  digitalWrite(LIGHT1, LOW);
  client.println("Light 1 is ON");
}

void lightOff1 (YunClient client, String command) {
  Console.println("lightOff1");
  digitalWrite(LIGHT1, HIGH);
  client.println("Light 1 is OFF");
}

void lightOn2 (YunClient client, String command) {
  Console.println("lightOn2");
  digitalWrite(LIGHT2, LOW);
  client.println("Light 2 is ON");
}

void lightOff2 (YunClient client, String command) {
  Console.println("lightOff2");
  digitalWrite(LIGHT2, HIGH);
  client.println("Light 2 is OFF");
}
void heaterOn (YunClient client, String command) {
  Console.println("heaterOn");
  digitalWrite(HEATER, LOW);
  client.println("Heater is ON");
}
void heaterOff (YunClient client, String command) {
  Console.println("heaterOff");
  digitalWrite(HEATER, HIGH);
  client.println("Heater is OFF");
}
void filterOn (YunClient client, String command) {
  Console.println("filterOn");
  digitalWrite(FILTER, LOW);
  client.println("Filter is ON");
}
void filterOff (YunClient client, String command) {
  Console.println("filterOff");
  digitalWrite(FILTER, HIGH);
  client.println("Filter is OFF");
}
void feederOn (YunClient client, String command) {
  Console.println("feederOn");
  digitalWrite(FEEDER,HIGH);
  client.println("Feeder is ON");
}
void feederOff (YunClient client, String command) {
  Console.println("feederOff");
  digitalWrite(FEEDER, HIGH);
  client.println("Feeder is OFF");
}
void food1Command (YunClient client, String command) {
  Console.println("food1Command");
    Distance = 0;
    while(Distance<=780)
    {
    Distance = Distance +1;
    digitalWrite(STEP1, HIGH);
    delay(3);
    digitalWrite(STEP1, LOW);
    delay(3);
    }
  Console.println("food1");
}

void food2Command(YunClient client, String command) {
  Distance = 0;
  while (Distance <= 780) {
    if (digitalRead(STEP2) == 1) {
      digitalWrite(STEP2, LOW);
      delay(3);
      digitalWrite(STEP2, HIGH);
    }
    else {
      digitalWrite(STEP2, HIGH);
      delay(3);
      digitalWrite(STEP2, LOW);
    }
    if (Distance == 380)
    {

      // We are! Reverse direction (invert DIR signal)
      if (digitalRead(DIR2) == HIGH)
      {
        digitalWrite(DIR2, LOW);
      }
      else
      {
        digitalWrite(DIR2, HIGH);
      }
    }
    Console.println("food2Command");

  }
}

void supplementCommand(YunClient client, String command) {
  Distance = 0;
  while (Distance <= 780)
  {
    if (digitalRead(SUPSTEP) == 1) {
      digitalWrite(SUPSTEP, LOW);
      delay(3);
      digitalWrite(SUPSTEP, HIGH);
    }
    else {
      digitalWrite(SUPSTEP, HIGH);
      delay(3);
      digitalWrite(SUPSTEP, LOW);
    }

    // Check to see if we are at the end of our move
    if (Distance == 390)
    {
      // We are! Reverse direction (invert DIR signal)
      if (digitalRead(SUPDIR) == HIGH)
      {
        digitalWrite(SUPDIR, LOW);
      }
      else
      {
        digitalWrite(SUPDIR, HIGH);
      }
      // Reset our distance back to zero since we're
      // starting a new move
      // Now pause for half a second
      delay(500);
    }
    Distance += 1;
  }
  digitalWrite(SUPDIR, LOW);
  Console.println("supplementCommand");
}

void videoOnCommand (YunClient client, String command){
  Console.println("Turning on the video");
  Process p;
  p.runShellCommand("mjpg_streamer -i \"input_uvc.so -d /dev/video0 -r 320x240 -f 10\" -o \"output_http.so -p 8080 -w /www/webcam\"");
  while(p.running());
}

void videoOffCommand (YunClient client, String command){
  Console.println("Turning off the video");
  Process d;
  d.runShellCommand("pidof mjpg_streamer");
  while(d.running());
  int result;
  while(d.available()) {
    result = d.parseInt();          // look for an integer
    Console.println(result);         // print the number as well
  }
  d.runShellCommand("kill " + result); 
  while(d.running());
}









