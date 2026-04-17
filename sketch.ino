#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4); 

const int buttonPin = 2;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

unsigned long fibonacci(int n) {
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void setup() {
  Serial.begin(9600);
  
  // Инициализация LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button");
  
  pinMode(buttonPin, INPUT_PULLUP); 
  randomSeed(analogRead(A0));       
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay && reading == LOW) {

    int randomN = random(5, 31); 

    unsigned long startMicros = micros();
    unsigned long fibResult = fibonacci(randomN);
    unsigned long endMicros = micros();
 
    double elapsedSeconds = (endMicros - startMicros) / 1000000.0;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Rand: ");
    lcd.print(randomN);
    lcd.print("     "); 
    
    lcd.setCursor(0, 0);
    lcd.print("NUmber: ");
    lcd.print(randomN);
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(elapsedSeconds, 5);
    lcd.print(" sec ");
    lcd.setCursor(0, 2);
    lcd.print("Fibonacci: ");
    lcd.print(fibResult);
    lcd.setCursor(0, 3);

    delay(300); 
  }
  
  lastButtonState = reading;
}