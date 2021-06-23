// I am Sangam Prashar.
// Student of Electrical and Electronics Engineering in HIET, Shahpur under HPTU
// Reg. ID 18BTL100508

// ABOUT PROJECT: SOCIAL DISTANCING SENSING ALARM
// DESCRIPTION: when circuit is working and person A is 90cm away from the person B
//              neopixel will glow green. and when this condition doesn't satisfied
//				neopixel will glow red and alarm start beeping. LCD screen shows the
//				real time distance.

// NOTE: In real case use 9V battery and connect it to the dc adaptor terminal of arduino.

// #Arduino #Embedded Code #NeoLamp #LCD #Potentiometer_250_k_ohm #Buzzer #Jumper_wires #resistance_220_ohm



// 			--->EMBEDDED CODE<---

// Importing libaries
 #include <LiquidCrystal.h> //LCD library
 #include <Adafruit_NeoPixel.h> // Neopixel library

// defining variables  
  #define ledNo 1
  #define echo 2
  #define trig 3
  #define ledPin 4
  #define buzzerPin 6
 
// defining data types useing in LCD display outut
  float  duration; // time taken by the pulse to return back
  float  distance; // oneway distance travelled by the pulse
 
// declearing variable for lcd and neopixel
  LiquidCrystal lcd(13, 12, 11, 10, 9, 8);//lcd(RS,EN,D4,D5,D6,D7) 
  Adafruit_NeoPixel pixel= Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);

// Setting up Arduino Pins
  void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);//opens serial port, sets data rate to 9600 bps
    lcd.begin(16, 2);//starting LCD of 16X2
    pixel.begin();//starting neopixel
 	pixel.show();//showing neopixel
    }
  
// Code which work in loop
  void loop() {
  
    time_Measurement();
    distance = duration * (0.0343) / 2;// calculate the oneway distance travelled by the pulse   
    display_distance(); 
 //function to glow led
    if (distance >= 90)
    {
      pixel.setPixelColor(0,50,0,0);//brightness,green,red,blue
      pixel.show();
      pixel.clear();
      digitalWrite(buzzerPin, LOW);
    }
    else{
      pixel.setPixelColor(0,0,100,0);
      pixel.show();
      digitalWrite(buzzerPin, HIGH);
    }
  }
        
//function to measure the time taken by the pulse to return back 
  void time_Measurement()
  { 
    digitalWrite(trig, LOW);
    delayMicroseconds(0.2);
  
    digitalWrite(trig, HIGH);
    delayMicroseconds(0.1);
    digitalWrite(trig, LOW);
  
    duration = pulseIn(echo, HIGH);
  }

//function to display the distance on LCD/Serial Monitor
  void display_distance()
  { 
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.print("Distance in Cm: ");
    Serial.print(distance);
    Serial.println();
    lcd.print("Distance in Cm: ");
    lcd.setCursor(5, 1);
    lcd.print(distance);
    delay(100);
  }