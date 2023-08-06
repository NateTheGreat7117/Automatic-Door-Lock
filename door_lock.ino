#include <Servo.h>


Servo servo;
int servoPin = 18; // Change this to the GPIO pin you connected the servo's control signal wire

int key_presses[] = {0, 0, 0};
bool locked = true;
int lock_password[] = {3, 1, 2};
int unlock_password[] = {2, 1, 3};

void setup() {
  servo.attach(servoPin);
  servo.write(180);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // if(digitalRead(16) == HIGH)
  // {
  //   keyPress(20);
  // }if(digitalRead(17) == HIGH)
  // {
  //   keyPress(22);
  // }if(digitalRead(18) == HIGH)
  // {
  //   keyPress(26);
  // }

  // if(checkPassword('l'))
  // {
  //   Serial.print("lock");
  //   resetPassword();
  //   servo.write(0);
  //   locked = true;
  // }
  // if(checkPassword('u'))
  // {
  //   Serial.print("unlock");
  //   resetPassword();
  //   servo.write(180);
  //   locked = false;
  // }
}

bool checkPassword(char p) {
  int password[] = {0, 0, 0};
  if(p == 'l')
  {
    for(int i = 0; i < 2; i++)
    {
      password[i] = lock_password[i];
    }
  }else if(p == 'u')
  {
    for(int i = 0; i < 2; i++)
    {
      password[i] = unlock_password[i];
    }
  }
  for(int i = 0; i < 2; i++)
  {
    if(key_presses[i] != password[i])
    {
      return false;
    }
  }
  return true;
}

void keyPress(int key) {
  if(key_presses[0] == 0)
  {
    key_presses[0] = key_presses[1];
  }
  if(key_presses[1] == 0)
  {
    key_presses[1] = key_presses[2];
  }

  key_presses[2] = getKey(key);
  Serial.println("Key press");
}

int getKey(int key) {
  if(key == 20)
  {
    return 1;
  }else if(key == 22)
  {
    return 2;
  }else if(key == 26)
  {
    return 3;
  }
  return 0;
}

void resetPassword()
{
  for(int i = 0; i < 2; i++)
  {
    key_presses[i] = 0;
  }
}