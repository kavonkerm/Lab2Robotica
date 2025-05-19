#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Crear objeto del sensor con tiempos válidos
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
  
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("No se encontró el sensor TCS34725.");
    while (1); // Se detiene
  }
}

// Función para detectar color en base a los valores normalizados y a la claridad
String detectarColor(float fr, float fg, float fb, uint16_t c) {
  if (c < 200) {
    return "Negro";
  } else if (fr > 0.4 && fg < 0.3 && fb < 0.3) {
    return "Rojo";
  } else if (fr < 0.3 && fg > 0.4 && fb < 0.3) {
    return "Verde";
  } else if (fr < 0.3 && fg < 0.3 && fb > 0.4) {
    return "Azul";
  } else if (fr > 0.3 && fg > 0.3 && fb > 0.3 && c > 1500) {
    return "Blanco";
  } else {
    return "Desconocido";
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Normaliza los valores RGB
  float fr = (float)r / c;
  float fg = (float)g / c;
  float fb = (float)b / c;

  // Detecta el color
  String colorDetectado = detectarColor(fr, fg, fb, c);

  // Calcula temperatura y lux
  uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b);
  uint16_t lux = tcs.calculateLux(r, g, b);

  // Muestra información en el monitor serial
  Serial.print("Rojo: "); Serial.print(r);
  Serial.print(" Verde: "); Serial.print(g);
  Serial.print(" Azul: "); Serial.print(b);
  Serial.print(" Clear: "); Serial.print(c);
  Serial.print(" Lux: "); Serial.print(lux);
  Serial.print(" Temp Color: "); Serial.print(colorTemp); Serial.print(" K");
  Serial.print(" | Color Detectado: "); Serial.println(colorDetectado);

  delay(1000);
}
