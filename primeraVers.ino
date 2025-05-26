#include <Wire.h>
#include <Adafruit_TCS34725.h>

// Ultrasónico
const int trigPin = 9;
const int echoPin = 8;
const float correccion = 0.89;
const float distanciaUmbral = 10.0;

// Motores
const int A_IN1 = 7;
const int A_IN2 = 6;
const int A_ENA = 5; // PWM
const int B_IN3 = 2;
const int B_IN4 = 4;
const int B_ENB = 11; // PWM

// Sensor de color
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);

// --------------------------------------------------
// SETUP
// --------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Pines del ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Pines de motores
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);
  pinMode(A_ENA, OUTPUT);
  pinMode(B_IN3, OUTPUT);
  pinMode(B_IN4, OUTPUT);
  pinMode(B_ENB, OUTPUT);

  // Sensor de color
  if (!tcs.begin()) {
    Serial.println("No se detectó el sensor TCS34725.");
    while (1);
  } else {
    Serial.println("Sensor de color OK.");
  }
}

// --------------------------------------------------
// LOOP PRINCIPAL
// --------------------------------------------------
void loop() {
  float distancia = medirDistancia();
  String color = detectarColor();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm | Color: ");
  Serial.println(color);

  if (distancia < distanciaUmbral) {
    detener();
    delay(500);
  } else if (color == "Rojo") {
    girarIzquierda();
  } else if (color == "Verde") {
    girarDerecha();
  } else if (color == "Azul") {
    retroceder();
    delay(500);
    girarIzquierda();
  } else if (color == "Blanco") {
    avanzar();
  } else {
    detener();
  }

  delay(200);
}

// --------------------------------------------------
// FUNCIONES DE MOTOR
// --------------------------------------------------
void avanzar() {
  analogWrite(A_ENA, 150);
  analogWrite(B_ENB, 150);
  digitalWrite(A_IN1, HIGH);
  digitalWrite(A_IN2, LOW);
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
}

void retroceder() {
  analogWrite(A_ENA, 150);
  analogWrite(B_ENB, 150);
  digitalWrite(A_IN1, LOW);
  digitalWrite(A_IN2, HIGH);
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
}

void girarIzquierda() {
  analogWrite(A_ENA, 150);
  analogWrite(B_ENB, 150);
  digitalWrite(A_IN1, LOW);
  digitalWrite(A_IN2, HIGH);
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
}

void girarDerecha() {
  analogWrite(A_ENA, 150);
  analogWrite(B_ENB, 150);
  digitalWrite(A_IN1, HIGH);
  digitalWrite(A_IN2, LOW);
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
}

void detener() {
  analogWrite(A_ENA, 0);
  analogWrite(B_ENB, 0);
}

// --------------------------------------------------
// FUNCIONES DE SENSOR
// --------------------------------------------------
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracion = pulseIn(echoPin, HIGH);
  float distancia = duracion * 0.034 / 2.0 + correccion;
  return distancia;
}

String detectarColor() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (c == 0) c = 1;  // prevenir división por 0
  float fr = (float)r / c;
  float fg = (float)g / c;
  float fb = (float)b / c;

  if (c < 80) {
    return "Negro";
  } else if (fr > 0.4 && fg < 0.3 && fb < 0.3) {
    return "Rojo";
  } else if (fr < 0.3 && fg > 0.4 && fb < 0.3) {
    return "Verde";
  } else if (fr < 0.3 && fg < 0.3 && fb > 0.4) {
    return "Azul";
  } else if (fr > 0.27 && fg > 0.27 && fb > 0.27 && c > 1000) {
    return "Blanco";
  } else {
    return "Desconocido";
  }
}

