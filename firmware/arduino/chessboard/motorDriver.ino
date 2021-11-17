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

  digitalWrite(MOTOR_SLEEP, HIGH)
  digitalWrite(MOTOR_RESET, HIGH)
  digitalWrite(MOTOR_ENABLE, LOW)

  for(i=0; i < )

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