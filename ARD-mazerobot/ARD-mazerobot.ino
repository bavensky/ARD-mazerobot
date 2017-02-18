#define ENA 11
#define IN1 9
#define IN2 8
#define ENB 10
#define IN3 7
#define IN4 6

#define C_TRIG A0
#define C_ECHO A1
#define L_TRIG A2
#define L_ECHO A3
#define R_TRIG A4
#define R_ECHO A5

boolean l_state, c_state, r_state;
long duration, distance;

void fw() {
  analogWrite(ENA, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void bw() {
  analogWrite(ENA, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, 200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void tl() {
  analogWrite(ENA, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void tr() {
  analogWrite(ENA, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void bk() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void ultraso(int trig, int echo) {

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;

  //  Serial.print("Distance = ");
  //  Serial.print(distance);
  //  Serial.println(" cm");
  //  delay(200);

}

void setup() {
  Serial.begin (9600);
  //  pinMode(TRIG, OUTPUT);
  //  pinMode(ECHO, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  ultraso(L_TRIG, L_ECHO);
  if (distance >= 3 && distance <= 15) {
    l_state = true;
  } else {
    l_state = false;
  }

  ultraso(C_TRIG, C_ECHO);
  if (distance >= 3 && distance <= 15) {
    c_state = true;
  } else {
    c_state = false;
  }

  ultraso(R_TRIG, R_ECHO);
  if (distance >= 3 && distance <= 15) {
    r_state = true;
  } else {
    r_state = false;
  }

  if (l_state == 0 && c_state == 0 && r_state == 0) {
    fw();
  }

  if (l_state == 1 && c_state == 1 && r_state == 1) {
    bk();
  }

  if (l_state == 1 && c_state == 0 && r_state == 0) {
    tr();
  }

  if (l_state == 0 && c_state == 0 && r_state == 1) {
    tl();
  }
}
