#define left_motor_forward 7
#define left_motor_backward 8
#define right_motor_forward 4
#define right_motor_backward 5
#define left_motor_speed 3
#define right_motor_speed 11
#define light 13
#define spl 16    //left motor speed coefficient
#define spr 17   //right motor speed coefficient
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(light, OUTPUT);
}
void loop() {
  int r = button_read();
  if (r != 0) {
    if (r == 1) bluetooth();
  }
  r = button_read_2();
  if (r != 0) {
    if (r == 1) {
      motor(10 * spl, 10 * spr);
      delay(2500); motor(0, 0);
    }
  }
}
void bluetooth() {
  int s = 10;
  char x;
  while (1) {
    if (Serial.available() > 0) {
      x = Serial.read();
      Serial.println(x);
      if (x == 'F') motor(s * spl, s * spr);
      else if (x == 'B') motor(-s * spl, -s * spr);
      else if (x == 'L') motor(-s * spl, s * spr);
      else if (x == 'R') motor(s * spl, -s * spr);
      else if (x == 'G') motor(0, s * spr);
      else if (x == 'I') motor(s * spl, 0);
      else if (x == 'H') motor(0, -s * spr);
      else if (x == 'J') motor(-s * spl, 0);
      else if (x == 'S') motor(0, 0);
      else if (x == '0') s = 0;
      else if (x == '1') s = 1;
      else if (x == '2') s = 2;
      else if (x == '3') s = 3;
      else if (x == '4') s = 4;
      else if (x == '5') s = 5;
      else if (x == '6') s = 6;
      else if (x == '7') s = 7;
      else if (x == '8') s = 8;
      else if (x == '9') s = 9;
      else if (x == 'q') s = 10;
    }
  }
}
int button_read() {
  int cl = 0;
p:  int t = 0;
  if (digitalRead(2) == 0) {
    digitalWrite(light, HIGH);
    while (digitalRead(2) == 0) {
      delay(1); t++;
    }
    digitalWrite(light, LOW);
    if (t > 15) {
      t = 0; cl++;
      while (digitalRead(2) == HIGH) {
        delay(1); t++;
        if (t > 1000) return cl;
      }
      goto p;
    }
  }
  return cl;
}
int button_read_2() {
  int cl = 0;
p:  int t = 0;
  if (digitalRead(12) == 0) {
    digitalWrite(light, HIGH);
    while (digitalRead(12) == 0) {
      delay(1); t++;
    }
    digitalWrite(light, LOW);
    if (t > 15) {
      t = 0; cl++;
      while (digitalRead(12) == HIGH) {
        delay(1); t++;
        if (t > 1000) return cl;
      }
      goto p;
    }
  }
  return cl;
}
void motor(int a, int b) {
  if (a >= 0) {
    digitalWrite(left_motor_forward, 1);
    digitalWrite(left_motor_backward, 0);
  }
  else {
    a = -a;
    digitalWrite(left_motor_forward, 0);
    digitalWrite(left_motor_backward, 1);
  }
  if (b >= 0) {
    digitalWrite(right_motor_forward, 1);
    digitalWrite(right_motor_backward, 0);
  }
  else {
    b = -b;
    digitalWrite(right_motor_forward, 0);
    digitalWrite(right_motor_backward, 1);
  }
  analogWrite(left_motor_speed, a);
  analogWrite(right_motor_speed, b);
}
