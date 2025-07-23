// Following the paper Lab 2B Updated Circuit
// Separated the pins by 2 so that in case there is bridging it doesn't break things from shorting

// Outputs to control the motor through the inverter
#define DRIVER_IN_1_PIN 2 //blue
#define DRIVER_IN_2_PIN 4 //yellow

// Inputs (pull-up)
#define LIMITER_SWITCH_PIN 11 //yellow, SPST
#define INPUT_SWITCH_PIN 13 //black, DPDT


void setup() {
    Serial.begin(9600);
    Serial.println("Serial set up");

    pinMode(DRIVER_IN_1_PIN, OUTPUT);
    pinMode(DRIVER_IN_2_PIN, OUTPUT);

    pinMode(LIMITER_SWITCH_PIN, INPUT); //ChatGPT told me there are no INPUT_PULLDOWN options so I added 10k resistors to manually pull these signals down
    pinMode(INPUT_SWITCH_PIN, INPUT);
}

void loop() {
    bool motorAtBase=digitalRead(LIMITER_SWITCH_PIN)==LOW; //when the switch is pressed, the motor is dormant and the switch is open, meaning `digitalRead` is LOW. When the motor is out and about, the NC means the switch is closed so `digitalRead ` is HIGH.
    bool personPressedInput=digitalRead(INPUT_SWITCH_PIN)==HIGH; //whether the person pressed the switch and the robot hasn't had time to press it yet (toward the "B" side of the board)
        //when the switch is moved toward the ink "B" on the board (person just pressed it), the motor should be moving toward it always since it needs to be turned off. Therefore, the motor should be FORWARD. In this case, IN1 should be HIGH and IN2 should be LOW
        //when the switch is in the opposite side to "B" (has been pushed back by the motor), the input switch pin is open so the pull-down resistor means it reads LOW.

    Serial.print("Motor at base: ");
    Serial.print(motorAtBase);
    Serial.print(", person pressed input: ");
    Serial.println(personPressedInput);

    
}

