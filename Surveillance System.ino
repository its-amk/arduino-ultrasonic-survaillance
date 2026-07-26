  /*
========================================================
IOT BASED MILITARY SURVEILLANCE SYSTEM
--------------------------------------------------------
Components:
- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- OLED Display (SSD1306 I2C)
- Red LED
- Yellow LED
- Green LED

FEATURES:
- Fast radar scanning
- OLED radar display with angle grids
- Red LED -> Object < 15 cm
- Yellow LED -> Object 15 cm to 50 cm
- Green LED -> No object detected
- "MISSILE DETECTED" warning
- Increased servo speed

========================================================
*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================================
// OLED SETTINGS
// =====================================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// =====================================================
// ULTRASONIC SENSOR PINS
// =====================================================

#define trigPin 9
#define echoPin 10

// =====================================================
// LED PINS
// =====================================================

#define redLED 2
#define yellowLED 3
#define greenLED 4

// =====================================================
// SERVO PIN
// =====================================================

#define servoPin 5

Servo radarServo;

// =====================================================

long duration;
int distance;

// Faster Servo Variables
int angle = 0;
int direction = 1;

// =====================================================
// SETUP
// =====================================================

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  radarServo.attach(servoPin);

  Serial.begin(9600);

  // OLED START
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed");
    while (1);
  }

  display.clearDisplay();
  display.display();

  startupScreen();
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
  // FAST SERVO ROTATION
  radarServo.write(angle);

  // READ DISTANCE
  distance = getDistance();

  // =================================================
  // LED CONDITIONS
  // =================================================

  // CLOSE OBJECT
  if (distance > 0 && distance < 15)
  {
    blinkLED(redLED, 60);

    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  // OBJECT DETECTED
  else if (distance >= 15 && distance <= 50)
  {
    blinkLED(yellowLED, 80);

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  // SAFE
  else
  {
    blinkLED(greenLED, 120);

    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
  }

  // DRAW RADAR
  drawRadar(angle, distance);

  // =================================================
  // FASTER SERVO SPEED
  // =================================================

  angle += direction * 15;

  if (angle >= 180)
  {
    angle = 180;
    direction = -1;
  }

  if (angle <= 0)
  {
    angle = 0;
    direction = 1;
  }

  delay(5);
}

// =====================================================
// DISTANCE FUNCTION
// =====================================================

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  int dist = duration * 0.034 / 2;

  if (dist > 200 || dist <= 0)
  {
    return 0;
  }

  return dist;
}

// =====================================================
// LED BLINK FUNCTION
// =====================================================

void blinkLED(int ledPin, int blinkDelay)
{
  digitalWrite(ledPin, HIGH);
  delay(blinkDelay);

  digitalWrite(ledPin, LOW);
  delay(blinkDelay);
}

// =====================================================
// STARTUP SCREEN
// =====================================================

void startupScreen()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 20);
  display.println("MILITARY RADAR");

  display.setCursor(15, 35);
  display.println("INITIALIZING...");

  display.display();

  delay(1500);
}

// =====================================================
// RADAR DISPLAY
// =====================================================

void drawRadar(int angle, int distance)
{
  display.clearDisplay();

  // Radar Center
  int centerX = 64;
  int centerY = 63;

  // =================================================
  // RADAR CIRCLES
  // =================================================

  display.drawCircle(centerX, centerY, 15, WHITE);
  display.drawCircle(centerX, centerY, 30, WHITE);
  display.drawCircle(centerX, centerY, 45, WHITE);
  display.drawCircle(centerX, centerY, 60, WHITE);

  // =================================================
  // ANGLE GRID LINES
  // =================================================

  for (int a = 0; a <= 180; a += 20)
  {
    float rad = radians(a);

    int x = centerX + cos(rad) * 60;
    int y = centerY - sin(rad) * 60;

    display.drawLine(centerX, centerY, x, y, WHITE);
  }

  // =================================================
  // RADAR SWEEP LINE
  // =================================================

  float sweepRad = radians(angle);

  int sweepX = centerX + cos(sweepRad) * 60;
  int sweepY = centerY - sin(sweepRad) * 60;

  display.drawLine(centerX, centerY, sweepX, sweepY, WHITE);

  // =================================================
  // OBJECT DETECTION DOT
  // =================================================

  if (distance > 0 && distance < 50)
  {
    int objRadius = map(distance, 0, 50, 0, 60);

    int objX = centerX + cos(sweepRad) * objRadius;
    int objY = centerY - sin(sweepRad) * objRadius;

    display.fillCircle(objX, objY, 3, WHITE);
  }

  // =================================================
  // TEXT INFORMATION
  // =================================================

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Angle:");
  display.print(angle);

  display.setCursor(0, 10);
  display.print("Dist:");
  display.print(distance);
  display.print("cm");

  // =================================================
  // MISSILE ALERT
  // =================================================

  if (distance > 0 && distance < 15)
  {
    display.setCursor(5, 20);
    display.println("MISSILE DETECTED");
  }

  else if (distance >= 15 && distance <= 50)
  {
    display.setCursor(20, 20);
    display.println("OBJECT FOUND");
  }

  else
  {
    display.setCursor(40, 20);
    display.println("SAFE");
  }

  display.display();
}