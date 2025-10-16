// Adry Lain 2025

const int sensorPin = 15;
const int ledPin = 4;
const int buttonPin = 2;
bool collecting = false;
bool lastState = false; //this is just so we can use one button and make it toggleable. if the button changes from HIGH -> LOW
//then we know that the button was released and isn't just being held down. otherwise, holding the button will make the data
//collecting state spin between true and false like a slot machine

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {

  //if the button was LOW and then became HIGH, we know it was just pressed. turn on data collection.
  if (digitalRead(buttonPin) == HIGH && lastState == false) {
    if (collecting == false) {
      collecting = true;
      Serial.print("Begin");
      digitalWrite(ledPin, HIGH);
    }else{
      collecting = false;
      Serial.print("Stop");
      digitalWrite(ledPin, LOW);
    }
  }

  if (collecting == true) {
    //read from the analog sensor pin
    int analog_sample = analogRead(sensorPin);
    //or you can just send it directly as a 32 bit integer:
    Serial.write(analog_sample);
  }

  //update what the previous state of the button was. if it is low, let lastState be low. vice versa.
  if (digitalRead(buttonPin) == HIGH && lastState == false) {
    lastState = true;
  }else if (digitalRead(buttonPin) == LOW && lastState == true) {
    lastState = false;
  }

  delay(1); // 1 kHz max sample rate on 
  
}

//what we want to do  here is send all incoming signals over to serial. another program should listen in on the serial port and just log it into a csv file.
//the csv file should be openable in excel where we can just plot the data. If we want we can write another program that overlays vibration data on top of one another and checks
//peaks.