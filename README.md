A low-cost military surveillance system using Arduino, ultrasonic sensor, and rotating motor. Detects objects within 2cm-200cm perimeter and triggers local alerts (OLED display + red LED). Real-time data is sent to a role-based web dashboard via serial communication.

**Hardware:** Arduino Uno, HC-SR04 ultrasonic sensor, servo motor, OLED display, red LED

**Working:** Servo motor rotates sensor 0°–180°. Ultrasonic sensor measures distance. If object detected within 2cm-200cm, OLED shows alert and LED turns on. Data is sent to dashboard every 500ms.
