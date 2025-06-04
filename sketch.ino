#include<Wire.h>
#include <Adafruit_SSD1306.h>

//define the A4988 driver pins
#define DIR_PIN 32 // direction pin connected to GPIO32
#define STEP_PIN 33 // step pin connected to GPIO33

//OLED DISPLAY SETTINGS
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // no reset pin for wokwi simuation 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  //Potentiometer Pin

 #define POT_PIN 34  // Potentiometer connected to GP1034

 void setup() {
 // Initialize Serial Monitor
Serial.begin(115200);

// Initialize OLED display
 if (!display.begin(SSD1306_SWITCHCAPVCC, 0X3C)) {
  Serial.println(F("OLED display not found"));
 for (;;);
 }
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(SSD1306_WHITE);
 display.setCursor(0, 0);
 // Set the direction and step pins as outputs
 pinMode (DIR_PIN, OUTPUT);
 pinMode(STEP_PIN, OUTPUT);

 //initialize the display
 display.println("Step motor speed control");
 display.display();
 delay(2000);
 }
 void loop(){
  //read potentiometer value (0 to 1023)
  int potvalue = analogRead(POT_PIN);
  //map the potentiometer value to the range of 1 to 1000 RPM 
  int motorSpeed = map(potvalue,0,1023,1,1000);

  // Display motor speed on OLED screen
 display.clearDisplay();
 display.setCursor(0, 0);
 display.print("Speed: ");
  display.print(motorSpeed);
 display.println(" RPM");
 display.display();

 // Rotate the stepper motor based on the potentiometer speed
 // Set direction 
 digitalWrite(DIR_PIN, HIGH); // set the direction to clockwise (change to low)
 // Pulse the step pin to move the motor
 digitalWrite(STEP_PIN, HIGH);
 delayMicroseconds(1000000 / motorSpeed); // Adjust delay to change motor
 digitalWrite(STEP_PIN,LOW);
 delayMicroseconds(1000000 / motorSpeed); 
 // Print potentiometer value to serial monitor (for debugging)
  
 Serial.print("Potentiometer Value: ");
 Serial.println(potvalue);

 }






