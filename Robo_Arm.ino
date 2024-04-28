#include <SoftwareSerial.h>
#include <Servo.h>

int bluetoothRX = 0;
int bluetoothTX = 1;

int motor_1 = 5;
int motor_2 = 4;
int cylinder_1 = 3;
int cylinder_2 = 2;
int string_motor_1 = 8;
int string_motor_2 = 9;
int servo = 12;
int air_pump = 10;
int valve = 11;
int en_motor = 6;
int servo_power = 13;


char input = 0;
int en_speed = 255;
int pos = 90;

SoftwareSerial bluetooth(bluetoothRX,bluetoothTX);
Servo hand;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(cylinder_1, OUTPUT);
  pinMode(cylinder_2, OUTPUT);
  pinMode(string_motor_1, OUTPUT);
  pinMode(string_motor_2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(motor_1, LOW);
  digitalWrite(motor_2, LOW);
  digitalWrite(cylinder_1, LOW);
  digitalWrite(cylinder_2, LOW);
  digitalWrite(string_motor_1, LOW);
  digitalWrite(string_motor_2, LOW);
  Serial.begin(9600);
  bluetooth.begin(9600);
  hand.attach(servo);
  Serial.println("Start");
  hand.write(pos);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available() > 0) 
  {
    Serial.println("Available");
    input = bluetooth.read();
    Serial.println(input);

    //Controlling Robo Cylinder
    if (input == 'W')
    {
        digitalWrite(cylinder_1, HIGH);
        digitalWrite(cylinder_2, LOW);
        delay(10);
    }
    else if (input == 'S')
    {
        digitalWrite(cylinder_1, LOW);
        digitalWrite(cylinder_2, HIGH);
        delay(10);
    }

    //Controlling Motor
    else if (input == 'A')
    {
        digitalWrite(motor_1, HIGH);
        digitalWrite(motor_2, LOW);
        analogWrite(en_motor, en_speed);
        delay(10);
    }
    
    else if (input == 'D')
    {
        digitalWrite(motor_1, LOW);
        digitalWrite(motor_2, HIGH);
        analogWrite(en_motor, en_speed);
        delay(10);
    }

    //Controlling String Motor
    else if (input == 'U')
    {
        digitalWrite(string_motor_1, LOW);
        digitalWrite(string_motor_2, HIGH);
        delay(10);
    }
    
    else if (input == 'K')
    {
        digitalWrite(string_motor_1, HIGH);
        digitalWrite(string_motor_2, LOW);
        delay(10);
    }

    else if (input == 'O')
    {
      while (true) {
        digitalWrite(servo_power, HIGH);
        hand.write(pos - 1);
        pos = hand.read();
        delay(10);

        if (bluetooth.available() > 0) {
          input = bluetooth.read();
          Serial.println(input);
          break;
        }
      }
    }
    
    else if (input == 'P')
    {
      while (true) {
        digitalWrite(servo_power, HIGH);
        hand.write(pos + 1);
        pos = hand.read();
        delay(10);

        if (bluetooth.available() > 0) {
          input = bluetooth.read();
          Serial.println(input);
          break;
        }
      }
    }

    else if (input == 'G')
    {
        digitalWrite(air_pump, HIGH);
        digitalWrite(valve, LOW);
        delay(10);
    }

     else if (input == 'I')
    {
        digitalWrite(air_pump, LOW);
        delay(10);
    }
    
    else if (input == 'L')
    {
        digitalWrite(air_pump, LOW);
        digitalWrite(valve, HIGH);
    }

    else if (input == 'M')
    {
        stopMotors();
    }

    else
    {
      if (input == '3')
      {
        en_speed = 255;
      }
      else if (input == '2')
      {
        en_speed = 170;
      }
      else if (input == '1')
      {
        en_speed = 100;
      }
    }
  }
}

// Function to stop all motors
void stopMotors() {
  digitalWrite(motor_1, LOW);
  digitalWrite(motor_2, LOW);
  digitalWrite(cylinder_1, LOW);
  digitalWrite(cylinder_2, LOW);
  digitalWrite(string_motor_1, LOW);
  digitalWrite(string_motor_2, LOW);
  digitalWrite(servo_power, LOW);
}
