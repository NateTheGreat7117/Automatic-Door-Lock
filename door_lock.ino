#include <Servo.h>
#include <Keypad.h>
#include <avr/sleep.h>

// Servo motor
Servo servo;
int servoPin = 12;

// Keypad
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5, 4}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Password
char key_presses[] = {'0', '0', '0', '0', '0', '0'};
char password[] = {'0', '0', '0', '0', '0', '0'};
char lock_password[] = {'1', '9', '7', '3', '9', '7'};
char unlock_password[] = {'0', '9', '0', '3', '1', '9'};
bool locked = false;
int passwordLength = sizeof(key_presses)/sizeof(key_presses[0]);
int lock_angle = 10;
int unlock_angle = 50;

// Button
const int buttonPin = 3;

void setup() {
  servo.attach(servoPin);
  servo.write(lock_angle);

  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), moveServo, FALLING);

  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();
  // Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    keyPress(customKey);
  }

  sleep_mode();
}

bool checkPassword(char p) {
  if(p == 'l')
  {
    for(int i = 0; i < passwordLength; i++)
    {
      password[i] = lock_password[i];
    }
  }else if(p == 'u')
  {
    for(int i = 0; i < passwordLength; i++)
    {
      password[i] = unlock_password[i];
    }
  }
  for(int i = 0; i < passwordLength; i++)
  {
    if(key_presses[i] != password[i])
    {
      return false;
    }
  }
  return true;
}

void keyPress(char key) {
  // Serial.println("Presses");
  for(int i = 0; i < passwordLength; i++)
  {
    key_presses[i] = key_presses[i+1];
  }
  key_presses[passwordLength-1] = key;

  if(checkPassword('l') || checkPassword('u'))
  {
    resetPassword();
    moveServo();
  }

  delay(220);
}

void resetPassword()
{
  for(int i = 0; i < passwordLength; i++)
  {
    key_presses[i] = 0;
  }
}

void moveServo()
{
  if(!locked)
  {
    servo.write(lock_angle);
    locked = true;
  }else
  {
    servo.write(unlock_angle);
    locked = false;
  }
  delay(500);
}
