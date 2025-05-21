# Laboratorio 2 de Robótica y Sistemas Autónomos - ICI4150

## Integrantes del grupo
- Patricio Figueroa Gallardo
- Marcelo Flores Coloane
- Kavon Kermani Órdenes
- Gabriel Sanzana Cuibin
- Lucas Zamora Gatica

### Materiales:

* Arduino UNO
* Chasis de robot móvil con dos motores DC basado en impresión 3D.
* Sensores (ultrasónicos, Infrarrojo y RGB) para detección de obstáculos y
color.
* Sensor IMU (MPU 6050) para medición de inclinación y giro.
* Batería y módulo de alimentación.
* Driver de motores (puente H) L298N o similar.
* Protoboard y cables de conexión.

## Parte 1: Configuración del Hardware y pruebas iniciales
* Conectar los sensores ultrasónico HC-SR04 y RGB en Arduino.
* Programar Arduino para leer la distancia con HC-SR04 y mostrarla en
el monitor serie.
* Programar Arduino para leer los valores RGB y mostrar el color detectado.
* Analizar la precisión de los sensores en diferentes condiciones (luz,
superficie, distancia).

### Preguntas

* ¿ Qué es la percepción en robótica y por qué es fundamental en los
sistemas autónomos?

* En el sensor ultrasónico HC-SR04 ¿ Qué parámetro se mide para calcular la distancia?
  
* ¿ Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo
podría reducirse?

## Parte 2: Procesamiento de datos y Algoritmo de Navegación

* Aplicar umbralización al sensor ultrasónico para detectar si hay un
obstáculo a menos de 10cm.
* Definir umbrales para detectar colores, rojo, verde y azul usando el
sensor RGB.
* Implementar un algoritmo en Arduino que detenga el robot ante obstáculos y cambie de dirección según el color detectado.
* Probar navegación en un circuito con obstáculos y superficies en diferentes colores.
* Ajustar parámetros para mejorar la detección y estabilidad del sistema. 
* Implementación de estrategias de navegación basadas en reglas.

### Preguntas
* Si el robot detecta el color rojo en el suelo ¿ Qué acción debería tomar?
¿ Por qué?

* Si el sensor ultrasónico detecta valores erráticos ¿ Qué estrategias
podrías aplicar para mejorar la precisión?

* Si tuvieras que integrar un nuevo sensor para mejorar la navegación
del robot ¿ Cuál eligirías y por qué?.

* ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de
color?
