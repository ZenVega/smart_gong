## Init and configure littleFS

follow these [instructions] (https://components.espressif.com/components/joltwallet/littlefs)

## Hardware
RGB LED Strip Control:

Uses 3 N-channel MOSFETs for switching the RGB channels
220Ω gate resistors to protect the ESP32 pins and reduce switching noise
Common anode configuration (12V+ to LED strip, MOSFETs switch the ground paths)

Solenoid Control:

3 separate N-channel MOSFETs for individual solenoid control
Flyback diodes (1N4007) across each solenoid to protect against voltage spikes
Same 220Ω gate resistors for protection

Power Management:

Single 12V power supply feeds both LED strips and solenoids
ESP32 powered through VIN pin (can handle 5-12V input)
Common ground reference for all components

Recommended Components:

MOSFETs: IRLZ44N or IRLB8743 (logic-level N-channel)
Diodes: 1N4007 for flyback protection
Resistors: 220Ω for gate protection
Power Supply: 12V with sufficient current capacity

GPIO Pin Assignments:

GPIO2, 4, 16: RGB LED channels (Red, Green, Blue)
GPIO17, 18, 19: Solenoid controls

Make sure your 12V power supply can handle the combined current draw of your LED strips and solenoids. You may also want to add capacitors for power supply filtering if you experience noise issues.
