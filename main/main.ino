int sensorPin = A0;  // LDR read
int sensorValue = 0;  // Current LDR value
int sensorBaseline = 0; // Startup value of sensor. Baseline will need to adjust throughout the day.

int state = 0;
int lastState = 0;
int stateDuration = 0; // How many cycles has the current state (on or off) been set?
int stateLoops = 0; // Count each time the state duration hits maximum. Used to reset message if no activity for some time.

int charBlock[5]; // 0 = no signal, 1 = short, 2 = long

int dot[5] = {0,0,1,1,1};
int dash[5] = {0,0,2,2,2};

String theMsg = "";

void setup() {
  Serial.begin(9600);

  sensorBaseline = analogRead(sensorPin);  
  Serial.print("baseline set to ");
  Serial.println(sensorBaseline);

}

void loop() {
  readSensorState();
  // dumpSensorValue();
  // printArray();
  delay(50);
}

void dumpSensorValue() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
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

void readSensorState() {
  sensorValue = analogRead(sensorPin);
  // Serial.println(sensorValue);
  if (sensorValue - sensorBaseline > 50) {
    // Serial.println(" ON!");
    if (state == 0) {
      stateChange(1);
    } else {
      stateDuration = stateDuration + 1;
    };
  } else {
    // Serial.println("");    
    if (state == 1) {
      stateChange(0);
    } else {
      stateDuration = stateDuration + 1;
    };
  }

  if (state == 0 && stateDuration > 10) {
    // Serial.print(" / ");
    // addToArray(0);
    inspectorMorse();
    memset(charBlock, 0, sizeof(charBlock));
    stateDuration = 0;

    if (stateLoops > 10) {
      theMsg = "";
    } else {
      stateLoops = stateLoops + 1;
      // Serial.println("State loop + 1");
    }
  }
  
  // printArray();
  // inspectorMorse();
}

void stateChange(int newState) {
  /*
  if (state == 0) {
    Serial.print("Off for ");
    Serial.print(stateDuration / 10);
    Serial.println(" seconds");
  } else {
    Serial.print("On for ");
    Serial.print(stateDuration / 10);
    Serial.println(" seconds");
  }
  */
  
  if (state == 1 && stateDuration > 4) {
    // Serial.print("-");
    addToArray(2);
  } else if (state == 1 && stateDuration > 1 && stateDuration < 10) {
    // Serial.print(".");
    addToArray(1);
  }

  // printArray();

  state = newState;
  stateDuration = 0;
  stateLoops = 0;
}

void inspectorMorse() {

  // Convert rolling character array to string for easy comparison
  String theChar = "";
  
  for (int i = 0;  i < 5; i++)
  {
    if( charBlock[i] != 0 ) 
    {
      theChar = theChar + charBlock[i];
    }
  }

  if (theChar == "111") {
    // Serial.println("S");
    theMsg = theMsg + "S";
    Serial.println(theMsg);
  } else if (theChar == "222") {
    // Serial.println("O");
    theMsg = theMsg + "O";
    Serial.println(theMsg);
  } else if (theChar == "12") {
    // Serial.println("A");  
    theMsg = theMsg + "A";
    Serial.println(theMsg);
  } else if (theChar == "2111") {
    // Serial.println("B");  
    theMsg = theMsg + "B";
    Serial.println(theMsg);
  } else if (theChar == "2121") {
    // Serial.println("B");  
    theMsg = theMsg + "C";
    Serial.println(theMsg);
  } else if (theChar == "211") {
    // Serial.println("B");  
    theMsg = theMsg + "D";
    Serial.println(theMsg);
  } else if (theChar == "1") {
    // Serial.println("B");  
    theMsg = theMsg + "E";
    Serial.println(theMsg);
  } else if (theChar == "1121") {
    // Serial.println("B");  
    theMsg = theMsg + "F";
    Serial.println(theMsg);
  } else if (theChar == "221") {
    // Serial.println("B");  
    theMsg = theMsg + "G";
    Serial.println(theMsg);
  } else if (theChar == "1111") {
    // Serial.println("B");  
    theMsg = theMsg + "H";
    Serial.println(theMsg);
  } else if (theChar == "11") {
    // Serial.println("B");  
    theMsg = theMsg + "I";
    Serial.println(theMsg);
  } else if (theChar == "1222") {
    // Serial.println("B");  
    theMsg = theMsg + "J";
    Serial.println(theMsg);
  } else if (theChar == "2121") {
    // Serial.println("B");  
    theMsg = theMsg + "K";
    Serial.println(theMsg);
  } else if (theChar == "1211") {
    // Serial.println("B");  
    theMsg = theMsg + "L";
    Serial.println(theMsg);
  } else if (theChar == "22") {
    // Serial.println("B");  
    theMsg = theMsg + "M";
    Serial.println(theMsg);
  } else if (theChar == "21") {
    // Serial.println("B");  
    theMsg = theMsg + "N";
    Serial.println(theMsg);
  } else if (theChar == "222") {
    // Serial.println("B");  
    theMsg = theMsg + "O";
    Serial.println(theMsg);
  } else if (theChar == "1221") {
    // Serial.println("B");  
    theMsg = theMsg + "P";
    Serial.println(theMsg);
  } else if (theChar == "2212") {
    // Serial.println("B");  
    theMsg = theMsg + "Q";
    Serial.println(theMsg);
  } else if (theChar == "121") {
    // Serial.println("B");  
    theMsg = theMsg + "R";
    Serial.println(theMsg);
  } else if (theChar == "111") {
    // Serial.println("B");  
    theMsg = theMsg + "S";
    Serial.println(theMsg);
  } else if (theChar == "2") {
    // Serial.println("B");  
    theMsg = theMsg + "T";
    Serial.println(theMsg);
  } else if (theChar == "112") {
    // Serial.println("B");  
    theMsg = theMsg + "U";
    Serial.println(theMsg);
  } else if (theChar == "1112") {
    // Serial.println("B");  
    theMsg = theMsg + "V";
    Serial.println(theMsg);
  } else if (theChar == "122") {
    // Serial.println("B");  
    theMsg = theMsg + "W";
    Serial.println(theMsg);
  } else if (theChar == "2112") {
    // Serial.println("B");  
    theMsg = theMsg + "X";
    Serial.println(theMsg);
  } else if (theChar == "2122") {
    // Serial.println("B");  
    theMsg = theMsg + "Y";
    Serial.println(theMsg);
  } else if (theChar == "2211") {
    // Serial.println("B");  
    theMsg = theMsg + "Z";
    Serial.println(theMsg);
  } else if (theChar == "12222") {
    // Serial.println("B");  
    theMsg = theMsg + "1";
    Serial.println(theMsg);
  } else if (theChar == "11222") {
    // Serial.println("B");  
    theMsg = theMsg + "2";
    Serial.println(theMsg);
  } else if (theChar == "11122") {
    // Serial.println("B");  
    theMsg = theMsg + "3";
    Serial.println(theMsg);
  } else if (theChar == "11112") {
    // Serial.println("B");  
    theMsg = theMsg + "4";
    Serial.println(theMsg);
  } else if (theChar == "11111") {
    // Serial.println("B");  
    theMsg = theMsg + "5";
    Serial.println(theMsg);
  } else if (theChar == "21111") {
    // Serial.println("B");  
    theMsg = theMsg + "6";
    Serial.println(theMsg);
  } else if (theChar == "22111") {
    // Serial.println("B");  
    theMsg = theMsg + "7";
    Serial.println(theMsg);
  } else if (theChar == "22211") {
    // Serial.println("B");  
    theMsg = theMsg + "8";
    Serial.println(theMsg);
  } else if (theChar == "22221") {
    // Serial.println("B");  
    theMsg = theMsg + "9";
    Serial.println(theMsg);
  } else if (theChar == "22222") {
    // Serial.println("B");  
    theMsg = theMsg + "0";
    Serial.println(theMsg);
  }

  if (theMsg == "SOS") {
    Serial.println("==========");
    Serial.println("SOS SOS SOS SOS");
    Serial.println("==========");
  }  
}