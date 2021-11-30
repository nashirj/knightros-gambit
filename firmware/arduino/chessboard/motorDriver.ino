/*
  Motor array format in order of indicies:
  Index:
  0         1        2        3
  Step pin, Dir pin, MS1 pin, MS2 pin
*/
void moveMotor(int motor[], int steps, int dir) 
{
  int i;

  // Enable motor driver inputs/output
  digitalWrite(MOTOR_SLEEP, HIGH);
  digitalWrite(MOTOR_RESET, HIGH);
  digitalWrite(MOTOR_ENABLE, LOW);

  // Set direction of motor
  digitalWrite(motor[1], dir);

  // Rotate motor some number of steps
  for (i = 0; i < steps; i++) {
    digitalWrite(motor[0], LOW);
    delay(1);  // 1 milliSecond
    digitalWrite(motor[0], HIGH);
  }

}

void moveSpaces(int motor[], int spaces, int dir)
{
  int i;

  // How many steps per space
  float numSteps = spaces * stepsPerSpace;

  digitalWrite(MOTOR_SLEEP, HIGH);
  digitalWrite(MOTOR_RESET, HIGH);
  digitalWrite(MOTOR_ENABLE, LOW);

  digitalWrite(motor[1], dir);

  for(i = 0; i < numSteps; i++);
  {
    digitalWrite(motor[0], LOW);
    delay(1);  // 1 milliSecond
    digitalWrite(motor[0], HIGH);
  }

}

void moveDiagonal(int motor[], int dir, int spaces)
{
  int i;

  // similary subject to change as above function dictation, same number as above though
  float numSteps = spaces * stepsPerSpace;

  digitalWrite(MOTOR_SLEEP, HIGH);
  digitalWrite(MOTOR_RESET, HIGH);
  digitalWrite(MOTOR_ENABLE, LOW);

  digitalWrite(xMotor[1], dir);
  digitalWrite(yMotor[1], dir);

  for(i = 0; i < numSteps; i++)
  {
    digitalWrite(xMotor[0], LOW);
    digitalWrite(yMotor[0], LOW);
    delay(1);
    digitalWrite(xMotor[0], HIGH);
    digitalWrite(yMotor[0], HIGH);
  }
}

void disableMotors() 
{
  digitalWrite(MOTOR_SLEEP, LOW);
  digitalWrite(MOTOR_RESET, LOW);
  digitalWrite(MOTOR_ENABLE, HIGH);
}

/*
  Motor array format in order of indicies:
  Index:
  0         1        2        3
  Step pin, Dir pin, MS1 pin, MS2 pin
*/
void setScale(int motor[], int scale) 
{
  if (scale == 1)  // whole steps
  {
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], LOW);
  }
  else if (scale == 2)  // 1/2 steps
  {
    digitalWrite(motor[2], HIGH);
    digitalWrite(motor[3], LOW);
  }
  else if (scale == 4)  // 1/4 steps
  {
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], HIGH);
  }
  else if (scale == 8)  // 1/8 steps
  {
    digitalWrite(motor[2], HIGH);
    digitalWrite(motor[3], HIGH);
  }
}