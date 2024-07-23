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

// Function to simulate serial functions (replace with actual Windows serial code if needed)
int serialAvailable()
{
    // Simulate serial availability check
    return 0; // Always returns 0 in this mockup
}

int serialParseInt()
{
    // Simulate reading an integer from serial
    return 0; // Replace with actual reading logic
}

void setup()
{
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
    // Example commands to set servo positions
    // CmdSet(0, 0, 0, 0, 0, 0);
    // dynamicPosition(commands, 2);

    CmdSet(1, 1, 0, 0, 0, 0);
    dynamicPosition(commands, 2);
    Sleep(2000); // Wait for 2 seconds

    CmdSet(0, 0, 1, 1, 1, 1);
    dynamicPosition(commands, 2);
    Sleep(2000); // Wait for 2 seconds

    // openHand();
    // Sleep(2000);
    // posRead();
}

// Function to read positions from serial and update servos
void posRead()
{
    if (serialAvailable())
    {
        Sleep(4);                           // Small delay to ensure data is available
        int index = serialParseInt();       // Read servo index
        int angle = serialParseInt();       // Read desired angle
        writeServo(&Fingers[index], angle); // Set servo to desired angle
        printf("%d:%d\n", index, angle);
    }
}

// Function to set target positions for servos
void CmdSet(double a, double b, double c, double d, double e, double f)
{
    commands[0] = a;
    commands[1] = b;
    commands[2] = c;
    commands[3] = d;
    commands[4] = e;
    commands[5] = f;
}

// Function to move servos back and forth within their range
void handLoop()
{
    LOOP_6
    {
        double currentPos = Fingers[i].currentPosition;
        Fingers[i].direction = (currentPos >= Fingers[i].range[1]) ? -1 : (currentPos <= Fingers[i].range[0]) ? 1
                                                                                                              : Fingers[i].direction;
        writeServo(&Fingers[i], currentPos + Fingers[i].direction);
    }
    Sleep(20); // Wait for 20 milliseconds
}

// Function to open the hand by moving servos to their minimum positions
void openHand()
{
    LOOP_100
    {
        LOOP_6
        {
            double currentPos = Fingers[i].currentPosition;
            if (currentPos >= Fingers[i].range[0])
            {
                writeServo(&Fingers[i], currentPos - 1);
            }
        }
        Sleep(20); // Wait for 20 milliseconds
    }
}

// Function to move servos to specified target positions smoothly
void dynamicPosition(double targets[6], int delayTime)
{
    LOOP_6
    {
        targets[i] = (targets[i] * -1) + 1;
        targets[i] = (Fingers[i].range[1] - Fingers[i].range[0]) * targets[i] + Fingers[i].range[0];
    }

    LOOP_100
    {
        LOOP_6
        {
            double currentPos = Fingers[i].currentPosition;
            if (currentPos > targets[i])
            {
                writeServo(&Fingers[i], currentPos - Fingers[i].stepSize);
            }
            else if (currentPos < targets[i])
            {
                writeServo(&Fingers[i], currentPos + Fingers[i].stepSize);
            }
        }
        Sleep(delayTime); // Wait for specified time in milliseconds
    }
}
