void setup()
{
    Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop()
{
    if (Serial.available() > 0)
    {
        int gesture = Serial.read(); // Read gesture from serial port
        Serial.print("Gesture Received: ");
        Serial.println(gesture);

        // Handle gestures here
        // For example, control LEDs or motors based on gesture value
        if (gesture == '0')
        {
            // Example action for gesture 0
            digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
        }
        else
        {
            digitalWrite(LED_BUILTIN, LOW); // Turn off LED
        }
    }
}
