#include <Servo.h>


Servo servo;
int servoPin = 5; // Change this to the GPIO pin you connected the servo's control signal wire

int key_presses[] = {0, 0, 0, 0, 0};
int password[] = {0, 0, 0, 0, 0};
int lock_password[] = {1, 1, 2, 2, 3};
int unlock_password[] = {3, 2, 1, 1, 3};
int passwordLength = sizeof(key_presses)/sizeof(key_presses[0]);

void setup() {
  servo.attach(servoPin);
  servo.write(90);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if(digitalRead(4) == LOW)
  {
    keyPress(4);
  }if(digitalRead(3) == LOW)
  {
    keyPress(3);
  }if(digitalRead(2) == LOW)
  {
    keyPress(2);
  }

  if(checkPassword('l'))
  {
    Serial.print("lock");
    resetPassword();
    servo.write(30);
  }
  if(checkPassword('u'))
  {
    Serial.print("unlock");
    resetPassword();
    servo.write(90);
  }
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

void keyPress(int key) {
  for(int i = 0; i < passwordLength; i++)
  {
    key_presses[i] = key_presses[i+1];
  }
  key_presses[passwordLength-1] = getKey(key);

  for(int i = 0; i < passwordLength; i++)
  {
    Serial.print(key_presses[i]);
  }
  Serial.println();
  delay(220);
}

int getKey(int key) {
  if(key == 4)
  {
    return 1;
  }else if(key == 3)
  {
    return 2;
  }else if(key == 2)
  {
    return 3;
  }
  return 0;
}

void resetPassword()
{
  for(int i = 0; i < passwordLength; i++)
  {
    key_presses[i] = 0;
  }
}
