## 🔴 Importante !
Si se esta usando una placa BQ Zum deben instalarse los [drivers](https://github.com/a-esh/Robot_Siguelineas-UCLM-2022/tree/main/drivers) para el correcto funcionamiento de la placa.
> Arduino IDE 2.3.2 
> 1. Seleciona el COM de la placa
> 2. **Tools > Board** seleciona `Arduino BT`
> 3. **Tools > Processor** seleciona `ATmega328P`

## Descripción del Código para el Sigue Líneas Arduino

Este código está diseñado para un robot sigue líneas que participa en un concurso de robótica. El robot utiliza una placa Arduino BQ y debe completar un circuito con los siguientes desafíos:

* **Dos rotondas:** El robot debe navegar por dos rotondas, tomando una dirección u otra dependiendo de si hay una pared cercana detectada por un sensor ultrasónico.
* **Laberinto:** El robot debe atravesar un laberinto usando los sensores infrarrojos para seguir las líneas del camino.
* **Zona sin línea:** Al final, el robot debe salir del laberinto y dirigirse hacia un área sin línea negra que seguir.

### Variables utilizadas en el código:

* **Líneas:**
    * `blackLine`: Representa el valor digital asociado a la línea negra (0 o 1).
    * `positionZone`: Indica en qué zona de la rotonda se encuentra el robot (0 o 1).
    * `movementState`: Activa o desactiva el movimiento del robot (1 encendido, 0 apagado).
* **Tiempos:**
    * `time`, `time2`, `timeMaze`: Almacenan tiempos de inicio para temporizadores.
    * `counter`, `counter2`, `counter3`, `counterMaze`, `counterMaze_position_1`: Contadores para controlar tiempos.
    * `T_phase`, `T_phase_2`, `T_phase_3`, `T_phase_Maze`: Banderas para controlar estados de temporizadores.
* **Velocidades:**
    * `maxSpeed`, `minSpeed`: Valores para la velocidad máxima y mínima de los motores. 
    * `Cmax`, `Cmin`: Constantes para ajustar la velocidad en las curvas.
* **Fases:**
    * `Position_1`, `Position_2`: Indican si el robot ha pasado por la posición 1 o 2 de la primera rotonda.
    * `circleWall`: Indica si se ha detectado una pared en la rotonda (0 no detectada, 1 detectada).
    * `delayMaze`: Controla el retardo después de salir del laberinto (1 activado, 0 desactivado).
    * `mazeWall_counter`: Contador para las paredes detectadas en el laberinto.
* **Secuestro:**
    * `secuestro`: Bandera para indicar si el robot debe retomar la navegación después de la zona sin línea (1 si, 0 no).

### Librerías utilizadas:

* `Servo.h`: Controla los servos para la dirección del robot.
* `NewPing.h`: Maneja el sensor ultrasónico para detectar paredes.

### Funciones principales:

* `setup()`: Configura los pines de los sensores infrarrojos y los servos, e inicia la comunicación serial.
* `loop()`: Ejecuta el ciclo principal del robot, que incluye:
    * Lectura de los sensores infrarrojos y el sensor ultrasónico.
    * Control de movimiento del robot en base a la lectura de los sensores y el estado actual.
    * Detección de paredes en las rotondas y control del giro según la posición.
    * Temporizadores para controlar el tiempo en cada sección del circuito.
    * Navegación por el laberinto siguiendo las líneas con los sensores infrarrojos.
    * Control del robot en la zona final sin línea negra.
    * Reinicio de la navegación si se detecta la posición inicial después de la zona sin línea.

## Descripción Detallada del Código Sigue Líneas Arduino

### Funciones y Secciones del Código:

**1. Detección de Líneas y Control de Movimiento:**

* `infraRight_value` e `infraLeft_value`: Almacenan el valor digital de los sensores infrarrojos derecho e izquierdo.
* `movimiento()`: Función que define el movimiento del robot en base a la información de los sensores:
    * Si ambos sensores detectan la línea negra, el robot avanza recto.
    * Si solo un sensor detecta la línea, el robot gira hacia la dirección del sensor que no la detecta.
    * Si ningún sensor detecta la línea, el robot se detiene.

**2. Control de Rotondas:**

* `circleWall`: Variable que indica si se ha detectado una pared en la rotonda (0 no detectada, 1 detectada).
* `dist`: Variable que almacena la distancia medida por el sensor ultrasónico.
* `counter`, `counter2`: Contadores para controlar el tiempo en las rotondas.
* `T_phase`, `T_phase_2`: Banderas para controlar estados de temporizadores en las rotondas.
* `Position_1`, `Position_2`: Variables que indican si el robot ha pasado por la posición 1 o 2 de la primera rotonda.
* `delayMaze`: Controla el retardo después de salir del laberinto (1 activado, 0 desactivado).
* `secuestro`: Bandera para indicar si el robot debe retomar la navegación después de la zona sin línea (1 si, 0 no).

**2.1. Detección de Paredes:**

* Se utiliza el sensor ultrasónico para medir la distancia a las paredes.
* Si la distancia es menor a un umbral predefinido, se considera que hay una pared cerca.

**2.2. Giro en las Rotondas:**

* El robot gira en la dirección contraria a la pared detectada.
* El tiempo de giro se controla con un temporizador.
* Se utilizan diferentes temporizadores para las dos rotondas.
* Se utilizan las variables `Position_1` y `Position_2` para controlar el giro en la primera rotonda.

**3. Navegación por el Laberinto:**

* `mazeWall_counter`: Contador para las paredes detectadas en el laberinto.
* `timeMaze`: Almacena el tiempo de inicio para el temporizador del laberinto.
* `T_phase_Maze`: Bandera para controlar el estado del temporizador del laberinto.

**3.1. Seguimiento de Líneas:**

* Se utilizan los sensores infrarrojos para seguir las líneas del laberinto.
* El robot ajusta su dirección en base a la posición de los sensores sobre la línea.

**3.2. Detección de Paredes en el Laberinto:**

* Se utiliza el sensor ultrasónico para detectar paredes en el laberinto.
* Si se detecta una pared, el robot gira en la dirección contraria.

**4. Zona Final sin Línea:**

* El robot se desplaza a una velocidad constante sin seguir líneas.
* Se utiliza un temporizador para controlar el tiempo en esta zona.
* El robot se detiene al final del temporizador.

**5. Reanudación de la Navegación:**

* El robot se reinicia a la posición inicial y comienza a navegar de nuevo.
* La variable `secuestro` se utiliza para controlar este proceso.

### Consideraciones adicionales:

* El código está optimizado para la eficiencia y la velocidad.
* Se utilizan diferentes técnicas para mejorar la precisión del robot en el seguimiento de las líneas y la detección de paredes.
* El código está diseñado para ser modular y fácil de modificar.
