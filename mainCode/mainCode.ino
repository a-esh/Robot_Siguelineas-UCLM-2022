/* VARIABLES*/

//Lineas
int blackLine = 0; //Negro
int positionZone = 0; //Posición
int movementState = 1; //On Movimiento

// Tiempos
unsigned long time = 0; unsigned long time2 = 0; unsigned long timeMaze = 0; //maze = Laberinto
int counter = 0; int counter2 = 0; int counter3 = 0; int counterMaze = 0; int counterMaze_position_1 = 0;
int T_phase = 0; int T_phase_2 = 0; int T_phase_3 = 0; int T_phase_Maze = 0;

//Velocidades
int maxSpeed = 180; int Cmax = -20;
int minSpeed = 0; int Cmin = 20;
//Fases

int Position_1 = 0; int Position_2 = 0;
int circleWall = 0;//Pared rotnoda
int delayMaze = 0;//Delay laberinto
int mazeWall_counter = 0;//Paredes laberinto

//secuestro
int secuestro = 0;

/* SERVO CONFIG */
#include <Servo.h>
Servo servoRight; Servo servoLeft;

/* INFRAROJOS INT */
int infraRight = 2; int infraLeft = 3;
int infraRight_value = 0; int infraLeft_value = 0;

/* DISTANCIA */
#include <NewPing.h>
int pinEcho = 5; int pinTrig = 4;
int max_distance = 200;
int dist = 0;
NewPing sonar(pinTrig, pinEcho, max_distance);

void setup() {
  /* INFRAROJOS */
  pinMode(infraRight, INPUT);
  pinMode(infraLeft, INPUT);

  /* SERVO */
  servoRight.attach(9);
  servoLeft.attach(8);

  Serial.begin(9600);

}

void loop() {

  /* INFRAROJOS */
  infraRight_value = digitalRead(infraRight); //Serial.print("SENSOR-DER "); Serial.println(infraRight_value);
  infraLeft_value = digitalRead(infraLeft); //Serial.print("SENSOR-IZQ "); Serial.println(infraLeft_value);

  /* DISTANCIA */
  dist = sonar.ping_cm(); Serial.print ("dist = "); Serial.println (dist);

  /* MOVIMIENTO */
  if (movementState == 1) {
    if (infraRight_value == blackLine) // D -> Derecha , I -> Izquierda
    {
      if (infraLeft_value == blackLine) { //Sensores D&I-1
        if (positionZone == 0) {
          servoRight.write(90);
          servoLeft.write(minSpeed);
        } else {
          servoRight.write(maxSpeed + Cmax);
          servoLeft.write(90);
        }
      }
      else //Sensores D-Negro / I-1
      {
        if (positionZone == 0) {
          servoRight.write(maxSpeed);
          servoLeft.write(minSpeed);
        }
        else {
          servoRight.write(maxSpeed);
          servoLeft.write(90);
        }
      }
    }
    else
    {
      if (infraLeft_value == blackLine) //Sensores D-0 / I-1
      {
        if (positionZone == 0) {
          servoRight.write(90);
          servoLeft.write(minSpeed);
        }
        else {
          servoRight.write(maxSpeed);
          servoLeft.write(minSpeed);
        }
      }
      else { //Sensores D&I 0
        if (positionZone == 0) {
          servoRight.write(maxSpeed);
          servoLeft.write(90);
        }
        else {
          servoRight.write(90);
          servoLeft.write(minSpeed + Cmin);
        }
      }
    }
  }
  //Pared rotonda
  if (circleWall == 0) {
    if ((dist > 25) && (dist < 40)) {
      positionZone = 0;
      circleWall = 1;
      counterMaze = 1;
      counter = 1;
      Position_1 = 1;
    }
    if ((dist > 110) && (dist < 130)) {
      positionZone = 1; servoRight.write(maxSpeed); servoLeft.write(90); delay(200);
      circleWall = 1;
      counterMaze = 1;
      counter2 = 1;
      Position_2 = 1;
    }
  }

  //Tiempos
  Serial.print ("time = "); Serial.println (time);
  if (counter == 1) {
    if  (T_phase == 0) {
      time = millis();
      T_phase = 1;
    }
    if (millis() >= time + 9000) {
      T_phase = 0;
      positionZone = 1; servoRight.write(maxSpeed); servoLeft.write(90) ; delay(200);
      counter = 0;
    }
  }
  if (counter2 == 1) {
    if  (T_phase_2 == 0) {
      time2 = millis();
      T_phase_2 = 1;
    }
    if (millis() >= time2 + 9000) {
      T_phase_2 = 0;
      positionZone = 0; servoRight.write(90); servoLeft.write(minSpeed); delay(200);
      counter2 = 0;
    }
  }
  if (counterMaze == 1) {
    if  (T_phase_Maze == 0) {
      timeMaze = millis();
      T_phase_Maze = 1;
    }
    if (millis() >= timeMaze + 20000) {
      T_phase_Maze = 0;
      counterMaze = 0;
      delayMaze = 1;
      if (positionZone == 1) {
        positionZone = 0; servoRight.write(90); servoLeft.write(minSpeed); delay(200);
      }
    }
  }

  //Laberinto
  if ((circleWall == 1) && (delayMaze == 1)) {
    if ((dist <= 26) && (dist >= 24) && (mazeWall_counter == 0)) {
      servoRight.write(maxSpeed); servoLeft.write(minSpeed); delay(600);
      servoRight.write(maxSpeed); servoLeft.write(90); delay(1100);
      mazeWall_counter = mazeWall_counter + 1;
      dist = sonar.ping_cm();
    }
    if ((dist <= 26) && (dist >= 24) && (mazeWall_counter == 1)) {
      servoRight.write(maxSpeed); servoLeft.write(minSpeed); delay(300);
      servoRight.write(90); servoLeft.write(minSpeed); delay(1100);
      mazeWall_counter = mazeWall_counter + 1;
      dist = sonar.ping_cm();
    }
    if ((dist <= 26) && (dist >= 24) && (mazeWall_counter == 2)) {
      servoRight.write(maxSpeed); servoLeft.write(minSpeed); delay(300);
      servoRight.write(90); servoLeft.write(minSpeed); delay(1100);
      mazeWall_counter = mazeWall_counter + 1;
      dist = sonar.ping_cm();
    }
    if ((dist <= 26) && (dist >= 24) && (mazeWall_counter == 3)) {
      servoRight.write(180); servoLeft.write(0); delay(500);
      servoRight.write(180); servoLeft.write(90); delay(1100);
      servoRight.write(180); servoLeft.write(0); delay(3000);
      servoRight.write(180); servoLeft.write(60); delay(2000);
      servoRight.write(180); servoLeft.write(0); delay(4000);
      servoRight.write(90); servoLeft.write(90);
      circleWall = 2;
      mazeWall_counter = 0;
      delayMaze = 0;
      secuestro = 1;
      delay(10000);
    }
  }
  if ((secuestro == 1) && (circleWall = 2)) {
    if ((Position_1 == 1) && ((dist < 40) && (dist > 25))) {
      positionZone = 0;
      circleWall = 1;
      counterMaze = 1;
      counter = 1;
    }
    if ((Position_1 == 1) && ((dist < 130) && (dist > 110))) {
      positionZone = 1; servoRight.write(maxSpeed); servoLeft.write(90); delay(200);
      circleWall = 1;
      T_phase_Maze = 0; counterMaze_position_1 = 1;
      T_phase_2 = 0; counter2 = 1;
    }
    if ((Position_2 == 1) && ((dist < 40) && (dist > 25))) {

    }
    if ((Position_2 == 1) && ((dist < 130) && (dist > 110))) {

    }
  }
  if (counterMaze_position_1 == 1) {
    if  (T_phase_Maze == 0) {
      timeMaze = millis();
      T_phase_Maze = 1;
    }
    if (millis() >= timeMaze + 9000) {
      T_phase_Maze = 0;
      counterMaze_position_1 = 0;
      delayMaze = 1;
    }
  }
}
