#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For Sleep function on Windows

// Macros for looping
#define LOOP_6 for (int i = 0; i < 6; i++)
#define LOOP_100 for (int j = 0; j < 100; j++)

// Define a structure to hold servo information
typedef struct
{
    int pin;                // Servo connection pin
    int direction;          // Direction for movement
    double range[2];        // Movement range
    double stepSize;        // Step size for movement
    double currentPosition; // Current position of the servo
} Servo;

// Initialize array of Servo structures
Servo Fingers[6] = {
    {11, 1, {0, 100}, 0, 0},
    {10, 1, {0, 100}, 0, 0},
    {9, 1, {0, 180}, 0, 0},
    {6, 1, {0, 120}, 0, 0},
    {5, 1, {0, 100}, 0, 0},
    {3, 1, {110, 135}, 0, 0}};

double commands[6] = {1, 0, 0, 0, 1, 1}; // Initial positions for each servo

void setup()
{
    // Initialize serial communication
    Serial.begin(9600); // Ensure this matches the baud rate in your Python script

    // Initialize each servo and calculate step sizes
    LOOP_6
    {
        attachServo(&Fingers[i]);
        Fingers[i].stepSize = (Fingers[i].range[1] - Fingers[i].range[0]) / 100;
        Fingers[i].direction = 1;
    }
}

void loop()
{
    // Check for serial data
    posRead();
    Sleep(20); // Wait for 20 milliseconds
}

// Function to read positions from serial and update servos
void posRead()
{
    if (Serial.available() >= 13) // Expecting 13 bytes of data: index and 6 values for the servos
    {
        int index = Serial.parseInt();      // Read servo index
        double value = Serial.parseFloat(); // Read desired position value

        // Ensure index is within valid range
        if (index >= 0 && index < 6)
        {
            writeServo(&Fingers[index], value); // Set servo to desired position
            Serial.print("Servo ");
            Serial.print(index);
            Serial.print(": ");
            Serial.println(value);
        }
    }
}

// Function to simulate attaching a servo
void attachServo(Servo *servo)
{
    // In real C, this would involve setting up PWM or similar
    // This is a placeholder function
}

// Function to simulate writing to a servo
void writeServo(Servo *servo, double position)
{
    servo->currentPosition = position;
    // In real C, this would involve sending a PWM signal or similar
}
