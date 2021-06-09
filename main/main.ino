int sensorPin = A0;  // LDR read
int sensorValue = 0;  // Current LDR value
int sensorBaseline = 0; // Startup value of sensor. Baseline will need to adjust throughout the day.

int state = 0; // current state of signal

bool listening = false;
bool listeningWordBreak = false;

int timeUnit = 0; // length of a unit (dot)
unsigned long stateTime = 0; // how long have we been receiving a signal

int charBlock[5]; // stores time of on states
String theMsg = "";

void setup() {
  Serial.begin(9600);

  sensorBaseline = analogRead(sensorPin);  
  Serial.print("baseline set to ");
  Serial.println(sensorBaseline);
}

void loop() {
  readSensorState();
}

void readSensorState() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue - sensorBaseline > 50) {
    if (state == 0) {
      stateChange(1);
    };
  } else {
    if (state == 1) {
      stateChange(0);
    };
  }


  if ((state == 0) && (millis() - stateTime > timeUnit * 3) && (listening)) {
    inspectorMorse();
    memset(charBlock, 0, sizeof(charBlock));
    listening = false;
  }

  if ((state == 0) && theMsg != "" && (millis() - stateTime > timeUnit * 6.5) && (listeningWordBreak)) {
    theMsg = theMsg + " ";
    listeningWordBreak = false;
  }

  if ((state == 0) && theMsg != "" && (millis() - stateTime > timeUnit * 10) && (!listening)) {
    printMsg();
    theMsg = "";
    timeUnit = 0;
  }
}

void stateChange(int newState) {
  if (newState == 1) {
    int offTime = millis() - stateTime;

    if (timeUnit == 0 || timeUnit / 2 > offTime && offTime > 5) {
      // set calculated timeUnit if less than current measure
      timeUnit = offTime;
    }

    stateTime = millis();
  } else {
    int onTime = millis() - stateTime;

    
    Serial.print("On time ");
    Serial.println(onTime);

    Serial.print("Time unit ");
    Serial.println(timeUnit);
    
    
    if (onTime > 15) { // ignore noise       
      addToArray(onTime);

      
    } else {
      /*
      Serial.println("Ignored on time");
      Serial.print("Time unit ");
      Serial.println(timeUnit);
      */
    }

    stateTime = millis(); // record time state set to off
    listening = true;
    listeningWordBreak = true;
  }
  
  state = newState;
}



void addToArray(int intToAdd) {
  for (int i = 0; i < sizeof(charBlock) / sizeof(charBlock[0]); i++) {
    charBlock[i] = charBlock[i+1];
  }
  charBlock[sizeof(charBlock) / sizeof(charBlock[0])-1] = intToAdd;  
}

void printArray() {
  for (int i = 0; i < sizeof(charBlock) / sizeof(charBlock[0]); i++) {
    Serial.print(charBlock[i]);
    Serial.print (" ");
  }
  Serial.println (" ");
}

void printMsg() {
  Serial.println(theMsg);

  if (theMsg == "SOS") {
    Serial.println("==========");
    Serial.println("SOS SOS SOS SOS");
    Serial.println("==========");
  }  
}




void inspectorMorseSmall() {

  // Convert rolling character array to string for easy comparison
  String theChar = "";
  
  // printArray();

  for (int i = 0;  i < 5; i++)
  {
    if( charBlock[i] != 0 ) 
    {
      if (charBlock[i] > timeUnit * 0.25 && charBlock[i] < timeUnit * 1.5) {
        theChar = theChar + "1";
      } else if (charBlock[i] > timeUnit * 2.5 && charBlock[i] < timeUnit * 3.5) {
        theChar = theChar + "2";        
      }
      
    }
  }

  // Serial.println(theChar);

  if (theChar == "111") {
    // Serial.println("S");
    theMsg = theMsg + "S";
    Serial.println(theMsg);
  } else if (theChar == "222") {
    // Serial.println("O");
    theMsg = theMsg + "O";
    Serial.println(theMsg);
  }

  if (theMsg == "SOS") {
    Serial.println("==========");
    Serial.println("SOS SOS SOS SOS");
    Serial.println("==========");
  }  
}



void inspectorMorse() {

  // Convert rolling character array to string for easy comparison
  String theChar = "";
  
  for (int i = 0;  i < 5; i++)
  {
    if( charBlock[i] != 0 ) 
    {
      if (charBlock[i] < timeUnit * 1.5) {
        theChar = theChar + "1";
      } else if (charBlock[i] > timeUnit * 2.5 && charBlock[i] < timeUnit * 3.5) {
        theChar = theChar + "2";        
      }
      
    }
  }


  if (theChar == "12") {
    // Serial.println("A");  
    theMsg = theMsg + "A";
    // Serial.println(theMsg);
  } else if (theChar == "2111") {
    // Serial.println("B");  
    theMsg = theMsg + "B";
    // Serial.println(theMsg);
  } else if (theChar == "2121") {
    // Serial.println("B");  
    theMsg = theMsg + "C";
    // Serial.println(theMsg);
  } else if (theChar == "211") {
    // Serial.println("B");  
    theMsg = theMsg + "D";
    // Serial.println(theMsg);
  } else if (theChar == "1") {
    // Serial.println("B");  
    theMsg = theMsg + "E";
    // Serial.println(theMsg);
  } else if (theChar == "1121") {
    // Serial.println("B");  
    theMsg = theMsg + "F";
    // Serial.println(theMsg);
  } else if (theChar == "221") {
    // Serial.println("B");  
    theMsg = theMsg + "G";
    // Serial.println(theMsg);
  } else if (theChar == "1111") {
    // Serial.println("B");  
    theMsg = theMsg + "H";
    // Serial.println(theMsg);
  } else if (theChar == "11") {
    // Serial.println("B");  
    theMsg = theMsg + "I";
    // Serial.println(theMsg);
  } else if (theChar == "1222") {
    // Serial.println("B");  
    theMsg = theMsg + "J";
    // Serial.println(theMsg);
  } else if (theChar == "2121") {
    // Serial.println("B");  
    theMsg = theMsg + "K";
    // Serial.println(theMsg);
  } else if (theChar == "1211") {
    // Serial.println("B");  
    theMsg = theMsg + "L";
    // Serial.println(theMsg);
  } else if (theChar == "22") {
    // Serial.println("B");  
    theMsg = theMsg + "M";
    // Serial.println(theMsg);
  } else if (theChar == "21") {
    // Serial.println("B");  
    theMsg = theMsg + "N";
    // Serial.println(theMsg);
  } else if (theChar == "222") {
    // Serial.println("B");  
    theMsg = theMsg + "O";
    // Serial.println(theMsg);
  } else if (theChar == "1221") {
    // Serial.println("B");  
    theMsg = theMsg + "P";
    // Serial.println(theMsg);
  } else if (theChar == "2212") {
    // Serial.println("B");  
    theMsg = theMsg + "Q";
    // Serial.println(theMsg);
  } else if (theChar == "121") {
    // Serial.println("B");  
    theMsg = theMsg + "R";
    // Serial.println(theMsg);
  } else if (theChar == "111") {
    // Serial.println("B");  
    theMsg = theMsg + "S";
    // Serial.println(theMsg);
  } else if (theChar == "2") {
    // Serial.println("B");  
    theMsg = theMsg + "T";
    // Serial.println(theMsg);
  } else if (theChar == "112") {
    // Serial.println("B");  
    theMsg = theMsg + "U";
    // Serial.println(theMsg);
  } else if (theChar == "1112") {
    // Serial.println("B");  
    theMsg = theMsg + "V";
    // Serial.println(theMsg);
  } else if (theChar == "122") {
    // Serial.println("B");  
    theMsg = theMsg + "W";
    // Serial.println(theMsg);
  } else if (theChar == "2112") {
    // Serial.println("B");  
    theMsg = theMsg + "X";
    // Serial.println(theMsg);
  } else if (theChar == "2122") {
    // Serial.println("B");  
    theMsg = theMsg + "Y";
    // Serial.println(theMsg);
  } else if (theChar == "2211") {
    // Serial.println("B");  
    theMsg = theMsg + "Z";
    // Serial.println(theMsg);
  } else if (theChar == "12222") {
    // Serial.println("B");  
    theMsg = theMsg + "1";
    // Serial.println(theMsg);
  } else if (theChar == "11222") {
    // Serial.println("B");  
    theMsg = theMsg + "2";
    // Serial.println(theMsg);
  } else if (theChar == "11122") {
    // Serial.println("B");  
    theMsg = theMsg + "3";
    // Serial.println(theMsg);
  } else if (theChar == "11112") {
    // Serial.println("B");  
    theMsg = theMsg + "4";
    // Serial.println(theMsg);
  } else if (theChar == "11111") {
    // Serial.println("B");  
    theMsg = theMsg + "5";
    // Serial.println(theMsg);
  } else if (theChar == "21111") {
    // Serial.println("B");  
    theMsg = theMsg + "6";
    // Serial.println(theMsg);
  } else if (theChar == "22111") {
    // Serial.println("B");  
    theMsg = theMsg + "7";
    // Serial.println(theMsg);
  } else if (theChar == "22211") {
    // Serial.println("B");  
    theMsg = theMsg + "8";
    // Serial.println(theMsg);
  } else if (theChar == "22221") {
    // Serial.println("B");  
    theMsg = theMsg + "9";
    // Serial.println(theMsg);
  } else if (theChar == "22222") {
    // Serial.println("B");  
    theMsg = theMsg + "0";
    // Serial.println(theMsg);
  }

  // Serial.println(theMsg);
}


