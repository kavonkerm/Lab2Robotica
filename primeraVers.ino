#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>          
// -------------- Ultrasonido --------------
const int trigPin = 9;
const int echoPin = 8;
const float correccion      = 0.89;   // ajuste fino de distancia
const float distanciaUmbral = 23.0;   // cm

// -------------- Motores --------------
const int A_IN1 = 7;
const int A_IN2 = 6;
const int A_ENA = 5;   // PWM
const int B_IN3 = 2;
const int B_IN4 = 4;
const int B_ENB = 11;  // PWM

// -------------- Sensor de color --------------
Adafruit_TCS34725 tcs(
  TCS34725_INTEGRATIONTIME_154MS,
  TCS34725_GAIN_1X
);

// -------------- Servomotor (opcional) --------------
Servo servoMotor;          // borra si no usas servo
const int servoPin = 10;   // idem
const int anguloFrente = 90;

// --------------------------------------------------
// SETUP
// --------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motores
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);
  pinMode(A_ENA, OUTPUT);
  pinMode(B_IN3, OUTPUT);
  pinMode(B_IN4, OUTPUT);
  pinMode(B_ENB, OUTPUT);

  // Servomotor (quítalo si no lo usas)
  servoMotor.attach(servoPin);
  servoMotor.write(anguloFrente);   // mira al frente

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
  String color    = detectarColor();
  Serial.print("Distancia: ");
  Serial.print(distancia, 1);
  Serial.print(" cm | Color: ");
  Serial.println(color);

  if (distancia < distanciaUmbral) {    // Objeto cerca
    detener();                          // Detener primero
    delay(400);
    // Dependiendo del color, hacer acción
    if (color == "Rojo") {     
               
      girarIzquierda();
      delay(300);
      Serial.println("OBSTÁCULO ROJO: GIRAR IZQUIERDA");
    } 
    else if (color == "Verde") {        
      girarDerecha();
      delay(300);
      Serial.println("OBSTÁCULO VERDE: GIRAR DERECHA");
    } 
    else if (color == "Azul") {
      retroceder();                 // Comienza a retroceder
      delay(1000);                  // Retrocede durante 1 segundo
      girarIzquierda();                    // Detiene después de retroceder
      Serial.println("OBSTÁCULO AZUL: DETENER + RETROCEDER");
    }
    else {  // Otros colores o desconocido
      detener();
      Serial.println("OBSTÁCULO: DETENERSE");
    }

    delay(500);  // Pausa para que la maniobra se note y evitar lecturas rápidas repetidas
  } 
  else {
    avanzar();  // Si no hay obstáculo, sigue avanzando normalmente
  }

  //delay(200);
}


// --------------------------------------------------
// FUNCIONES DE MOTOR
// --------------------------------------------------
void retroceder() {
  analogWrite(A_ENA, 150);
  analogWrite(B_ENB, 150);
  digitalWrite(A_IN1, HIGH);
  digitalWrite(A_IN2, LOW);
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
}

void avanzar() {
  analogWrite(A_ENA, 150);
  analogWrite(B_ENB, 150);
  digitalWrite(A_IN1, LOW);
  digitalWrite(A_IN2, HIGH);
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
}

void girarIzquierda() {
  analogWrite(A_ENA, 130);
  analogWrite(B_ENB, 100);
  digitalWrite(A_IN1, LOW);
  digitalWrite(A_IN2, HIGH);
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
}

void girarDerecha() {
  analogWrite(A_ENA, 100);
  analogWrite(B_ENB, 130);
  digitalWrite(A_IN1, HIGH);
  digitalWrite(A_IN2, LOW);
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
}

void detener() {
  // Aplica frenado activo: ambos pines HIGH
  digitalWrite(A_IN1, HIGH);
  digitalWrite(A_IN2, HIGH);
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, HIGH);

  // Corta PWM
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
  float distancia = duracion * 0.034 / 2.0 + correccion;   // cm
  return distancia;
}

String detectarColor() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (c == 0) c = 1;           // evita división por 0

  float fr = (float)r / c;     // componentes normalizadas
  float fg = (float)g / c;
  float fb = (float)b / c;
  /*
  Serial.println(fr);
  Serial.println(fg);
  Serial.println(fb);
  */
  if (c < 80) return "Negro";
  
  else if (fr > 0.40 && fg < 0.30 && fb < 0.30) return "Rojo";
  else if (fr < 0.30 && fg > 0.40 && fb < 0.30) return "Verde";
  else if (fr < 0.25 && fg < 0.37 && fb > 0.42) return "Azul";
  

  else if (fr > 0.27 && fg > 0.27 && fb > 0.27 && c > 1000) return "Blanco";
  else                                         
    return "Desconocido";
}

