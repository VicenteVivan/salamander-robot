// ============================================================
// Salamander Robot with Arduino Nano. Four servo motors are
// used to control the body segments. The legs are controlled
// by four DC motors.
// ============================================================
// |       : `            _..-=-=-=-.._.--.                   |
// |        `-._ ___,..-'" -~~`         __')                  |
// |             `'"---'"`>>"'~~"~"~~>>'`                     |
// ============================================================

// Includes
#include "Servo.h"
#include <math.h>

// Define pins for the servos and motors 
#define SERVO_PIN_1  9
#define SERVO_PIN_2  10
#define SERVO_PIN_3  11
#define SERVO_PIN_4  12
#define MOTOR_PIN_1  3
#define MOTOR_PIN_2  5
#define MOTOR_PIN_3  6
#define MOTOR_PIN_4  7
#define NUM_SERVOS   4
#define NUM_MOTORS   4
#define PI 3.14159 

// ================== Global Variables =====================

Servo servo1; //    m1-(S1)-m2    (Head)
Servo servo2; //       |S2|
Servo servo3; //       |S3|
Servo servo4; //    m3-(S4)-m4    (Tail)

// Wave parameters
int frequency = 1; // Frequency of movement
int amplitude = 20; // Amplitude of movement (degrees of rotation)
int lag = 2 * PI / (NUM_SERVOS - 1); // Phase lag between segments


// ================= Function prototypes ===================
void setup();
void loop(); 
double toRadians(double degrees);
void wave(Servo *segment, int frequency, int counter, int n);


// ================== Setup Salamander =====================
void setup() {
    // Initialize servos
    servo1.attach(SERVO_PIN_1);
    servo2.attach(SERVO_PIN_2);
    servo3.attach(SERVO_PIN_3);
    servo4.attach(SERVO_PIN_4);

    // Set servos to neutral position
    // (Salamander starts in a straight position)
    servo1.write(90); 
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
    delay(1000)
    
    // Set up DC motors
    // (OUTPUT: means that the pin will give power to the motor)
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);
}


// =========================================================
//                        Main Loop                         
// =========================================================
void loop() {
    // Salamander's undulation (S)
    for (int counter = 0; counter < 180; counter++) {
        wave(&servo1, 10, 10, counter, 1, 3);
        wave(&servo2, 10, 10, counter, 1, 1);
        wave(&servo3, 10, 10, counter, 1, -1);
        wave(&servo4, 10, 10, counter, 1, -3);
        delay(10);
    }
    delay(1000); 

    // Salamander's leg movement 1 (Front-Left & Back-Right Legs)
    digitalWrite(MOTOR_PIN_1, HIGH); // 5V
    digitalWrite(MOTOR_PIN_2, LOW); // 0V
    digitalWrite(MOTOR_PIN_3, HIGH); // 5V
    digitalWrite(MOTOR_PIN_4, LOW); // 0V
    delay(1000); 

    // Stop leg movement 1
    digitalWrite(MOTOR_PIN_1, LOW); // 0V
    digitalWrite(MOTOR_PIN_2, LOW); // 0V
    digitalWrite(MOTOR_PIN_3, LOW); // 0V
    digitalWrite(MOTOR_PIN_4, LOW); // 0V
    delay(100); 

    // Salamander's undulation (Ƨ)
    for (int counter = 180; counter < 360; i++) {
        wave(&servo1, 10, 10, counter, 1, 0);
        wave(&servo2, 10, 10, counter, 1, 1);
        wave(&servo3, 10, 10, counter, 1, 2);
        wave(&servo4, 10, 10, counter, 1, 3);
        delay(10); 
    }
    delay(1000); // Wait for 1 second

    // Salamander's leg movement 2 (Front-Right & Back-Left Legs)
    digitalWrite(MOTOR_PIN_1, LOW); // 0V
    digitalWrite(MOTOR_PIN_2, HIGH); // 5V
    digitalWrite(MOTOR_PIN_3, LOW); // 0V
    digitalWrite(MOTOR_PIN_4, HIGH); // 5V
    delay(1000); 

    // Stop leg movement 2
    digitalWrite(MOTOR_PIN_1, LOW); // 0V
    digitalWrite(MOTOR_PIN_2, LOW); // 0V
    digitalWrite(MOTOR_PIN_3, LOW); // 0V
    digitalWrite(MOTOR_PIN_4, LOW); // 0V
    delay(100); 
}


// ========== Auxiliary Functions for Movement =============

double toRadians(double degrees) {
    return (degrees * PI / 180);
}

// wave(): n is the number of the current segment (1, 2, 3, or 4) amplitude 
// determines how wide the wave is (i.e. how much the "S" shape is curved),
// frequency determines the speed of the salamander, counter is the loop
// variable that takes the salamander through its undulation and lag is the
// constant angular difference between segments.
void wave(Servo *sn, int counter, int n) {
    segment->write(90 + amplitude*cos(toRadians(frequency*counter) - n*lag));
}
