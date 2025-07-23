// Outputs to control the motor through the inverter
#define DRIVER_IN_1_PIN 2 //blue
#define DRIVER_IN_2_PIN 4 //yellow

void setup() {
    pinMode(DRIVER_IN_1_PIN, OUTPUT);
    pinMode(DRIVER_IN_2_PIN, OUTPUT);

    Serial.begin(9600);
    Serial.println("Setup completed");
}

void loop() {
    byte user_input=0;

    if (Serial.available()>0) {
        user_input=Serial.read();

        if (user_input=='f') {
            Serial.println("Forward");
            // digitalWrite(MOTOR_PIN_1, HIGH);
            // digitalWrite(MOTOR_PIN_2, LOW);
        } else if (user_input=='r') {
            Serial.println("Reverse");
            // digitalWrite(MOTOR_PIN_1, LOW);
            // digitalWrite(MOTOR_PIN_2, HIGH);
        } else if (user_input=='s') {
            Serial.println("Stop");
            // digitalWrite(MOTOR_PIN_1, LOW);
            // digitalWrite(MOTOR_PIN_2, LOW);
        } else {
            Serial.println("Invalid character");
        }
    }
}
