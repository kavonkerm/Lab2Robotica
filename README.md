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
R: La percepción es la capacidad del robot para obtener información del entorno mediante sensores. Es fundamental porque permite tomar decisiones y reaccionar ante cambios o estímulos externos, haciendo posible la autonomía.

* En el sensor ultrasónico HC-SR04 ¿ Qué parámetro se mide para calcular la distancia?
R: El tiempo que tarda un pulso de sonido en ir al objeto y regresar (tiempo de vuelo del eco).






  
* ¿ Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo
podría reducirse?
R: El ruido puede generar lecturas inestables o falsas. Puede reducirse usando filtros (media móvil, media ponderada), calibración y repitiendo lecturas para tomar promedios.

## Parte 2: Procesamiento de datos y Algoritmo de Navegación

* Aplicar umbralización al sensor ultrasónico para detectar si hay un
obstáculo a menos de 23 cm.
* Definir umbrales para detectar colores, rojo, verde y azul usando el
sensor RGB.
* Implementar un algoritmo en Arduino que detenga el robot ante obstáculos y cambie de dirección según el color detectado.
* Probar navegación en un circuito con obstáculos y superficies en diferentes colores.
* Ajustar parámetros para mejorar la detección y estabilidad del sistema. 
* Implementación de estrategias de navegación basadas en reglas.

### Preguntas
* Si el robot detecta el color rojo en el suelo ¿ Qué acción debería tomar?
¿ Por qué?
R: El robot debe girar a la izquierda, porque así fue programado para reaccionar a ese color específico en el algoritmo de navegación, interpretando el rojo como una instrucción de giro

* Si el sensor ultrasónico detecta valores erráticos ¿ Qué estrategias
podrías aplicar para mejorar la precisión?
R: Aplicar filtros (pasa bajo o media móvil), aumentar el tiempo entre mediciones, o ignorar valores fuera de un rango válido para estabilizar los datos.

* Si tuvieras que integrar un nuevo sensor para mejorar la navegación del robot ¿Cuál elegirías y por qué?
 Integraría un sensor LIDAR o una cámara con visión artificial, ya que permitirían detectar obstáculos con mayor resolución y anticipación, además de ofrecer una vista más completa del entorno. Esto mejoraría la navegación al permitir planificación de rutas más inteligente y adaptativa, especialmente en espacios complejos.


* ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de color?
 El tiempo de respuesta está dado principalmente por los delays programados tras la detección de color (por ejemplo delay(1000)). 

## Parte 3: Videos Detección de Colores y Reacción del Robot
Se realizaron pruebas para detectar colores con el sensor RGB, primero validando en entorno controlado y luego integrando las lecturas a la lógica de navegación del robot. Se definió un umbral de distancia de 10 cm para activar la lectura del color, con la finalidad de evitar lecturas erráticas por interferencia ambiental.
Videos del experimento
* Detección de Blanco y Negro:
 https://youtube.com/shorts/kTFypJSL3Ws
 En este video se muestra cómo el sensor RGB detecta el color blanco y negro al presentar una hoja de cada color. El sensor se acerca a una distancia de hasta 10 cm, y el color detectado se muestra en el monitor serie del IDE de Arduino. Esta etapa permitió validar la capacidad del sensor de diferenciar contraste.


* Detección de Rojo, Verde y Azul:
 https://youtube.com/shorts/RfA9dvZrhoA
 Aquí se extiende la detección a los colores primarios: rojo, verde y azul. Al igual que en la prueba anterior, se utiliza un umbral de distancia para estabilizar la lectura y se confirma la identificación correcta de cada color. Esta información es la base para programar comportamientos distintos según el color detectado.


* Reacción del robot a los colores detectados:
 https://youtube.com/shorts/cmTUWNssunw
 En este video se muestra el robot desplazándose sobre una mesa. Cuando detecta el color verde, gira a la derecha; al detectar rojo, gira a la izquierda; y con azul, retrocede durante 1 segundo y luego gira a la izquierda. Este comportamiento responde a reglas simples de navegación implementadas en base a la lectura del sensor RGB.
### Código: HC-SR04
Este código toma 100 lecturas del sensor ultrasónico HC-SR04, promedia los valores y aplica una corrección empírica para mejorar la precisión. Esto permite filtrar el ruido y obtener una distancia más estable, lo que es especialmente útil al trabajar con obstáculos cercanos donde los errores son más notorios.
 El resultado se imprime en el monitor serial y representa un ejemplo directo de preprocesamiento y calibración de datos de sensores, tal como se propone en los objetivos del laboratorio.
### Código: primeraVers.ino
Este código implementa la lógica completa de navegación del robot móvil. Combina el uso del sensor ultrasónico para detectar obstáculos y el sensor de color RGB (TCS34725) para decidir cómo reaccionar según el color detectado. La lógica es la siguiente:
* Si el color detectado es rojo, el robot gira a la izquierda.
* Si detecta verde, gira a la derecha.
* Si detecta azul, retrocede 1 segundo y luego gira a la izquierda.
* Para cualquier otro color o en caso de no detección, el robot se detiene.


Además, si no hay obstáculos dentro del umbral de 23 cm, el robot sigue avanzando. Este código ilustra cómo fusionar la percepción (distancia + color) con acciones reactivas, lo que permite que el robot tome decisiones autónomas en tiempo real, tal como se muestra en los videos de la Parte 3.
