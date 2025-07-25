// Following the paper Final: Lab 2B Circuit with Battery Power

// Outputs to control the motor through the inverter
#define DRIVER_IN_1_PIN 2 //blue
#define DRIVER_IN_2_PIN 4 //yellow
    // Separated the pins by 2 so that in case there is bridging it doesn't break things from shorting

// Inputs (pull-up)
#define INPUT_SWITCH_PIN 12 //black, DPDT

#define NOISE_PIN A2 //for seeding

bool personPressedInput=false;

void setup() {
    Serial.begin(9600);
    Serial.println("Serial set up");

    pinMode(DRIVER_IN_1_PIN, OUTPUT);
    pinMode(DRIVER_IN_2_PIN, OUTPUT);

    pinMode(INPUT_SWITCH_PIN, INPUT_PULLUP);

    // Make it very random (since only 1 number from the sequence is used since it is turned off after each turn)
    unsigned long seed=analogRead(NOISE_PIN)+micros();
    // Spend first 0.1 seconds making sure truly random
    for (byte i=0; i<33; i++) { //from ChatGPT for more randomization
        auto noise=analogRead(NOISE_PIN) << i;
        // Serial.println(noise);
        seed^=noise;
        delay(3);
    }
    // Serial.print("Final seed: ");
    // Serial.println(seed);
    randomSeed(seed); //from documentation
}

int actionNumberCounter=0;

void loop() {
    updatePersonPressedInput();

    // Debug information:
    // Serial.print("Person pressed input: ");
    // Serial.println(personPressedInput);


    if (personPressedInput) { //FORWARD, finite state machine state where the motor moves forward
        // hesitantAtLastMinute();
        // int actionNumber=actionNumberCounter;
        // actionNumberCounter=(actionNumberCounter+1)%4;
        int actionNumber=random(10); //0–9 (some cases are more likely than others)
        Serial.print("Action number");
        Serial.println(actionNumber);
        switch (actionNumber) {
            case 0:
                indecisive();
                break;
            case 1:
                hesitantAtLastMinute();
                break;
            case 2:
                stopsMidway();
                break;
            case 3:
            case 4:
                crazy();
                break;
            case 5:
            case 6:
                crazy2();
                break;
            case 7:
            case 8:
            case 9:
            default:
                normal();
                break;
        }
    } else { //REVERSE, finite state machine state where the motor moves backward to go back to its base. The power management system will automatically turn off the machine when it gets back to the base so no need for there to be a third state in the code
        moveMotorInReverse();
    }
}

// Utility
void updatePersonPressedInput() {
    personPressedInput=digitalRead(INPUT_SWITCH_PIN)==LOW; //whether the person pressed the switch and the robot hasn't had time to press it yet (toward the "B" side of the board)
    //when ==LOW, the switch is closed such that the pin is pulled down to GND. This is when the person pushed it forward
    //when ==HIGH, the switch is open (default PULLUP means it is HIGH), so the switch has been hit and the robot can go in reverse back to its base
}

void moveForwardUntilDone() {
    moveMotorForward();
    while (personPressedInput) {
        updatePersonPressedInput();
        delay(10);
    }
}


// Basic motor operations
void moveMotorForward() {
    digitalWrite(DRIVER_IN_1_PIN, LOW);
    digitalWrite(DRIVER_IN_2_PIN, HIGH);
}

void moveMotorInReverse() {
    digitalWrite(DRIVER_IN_1_PIN, HIGH);
    digitalWrite(DRIVER_IN_2_PIN, LOW);
}

void stopMotor() {
    digitalWrite(DRIVER_IN_1_PIN, LOW);
    digitalWrite(DRIVER_IN_2_PIN, LOW);
}


// Turn OFF Switch Modes
// 280 ms is needed to turn off the motor
void normal() {
    moveForwardUntilDone();
}

void indecisive() {
    moveMotorForward();
    delay(170);
    stopMotor();
    delay(20);
    moveMotorInReverse();
    delay(130);
    stopMotor();
    delay(800); //wait in suspense
    moveForwardUntilDone();
}

void hesitantAtLastMinute() {
    moveMotorForward();
    delay(180);
    stopMotor();
    delay(1000);
    moveForwardUntilDone();
}

void stopsMidway() {
    moveMotorForward();
    delay(140);
    stopMotor();
    delay(1000);
    moveForwardUntilDone();
}

void crazy() {
    moveMotorForward();
    delay(30);

    for (int i=0; i<5; i++) {
        moveMotorForward();
        delay(100);
        moveMotorInReverse();
        delay(100);
    }
    moveForwardUntilDone();
}

void crazy2() {
    moveMotorForward();
    delay(30);

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            moveMotorForward();
            delay(100);
            stopMotor();
            delay(50);
            moveMotorInReverse();
            delay(100);
            stopMotor();
            delay(50);
        }
        stopMotor();
        delay(200);
    }
    delay(400);

    moveForwardUntilDone();
}

