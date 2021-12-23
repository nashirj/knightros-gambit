// Sets the scale of the motor driver corresponding to "motor"
void setScale(int motor[], int scale) 
{
  if (scale == WHOLE_STEPS)
  {
    digitalWrite(motor[MS1_PIN], LOW);
    digitalWrite(motor[MS2_PIN], LOW);
  }
  else if (scale == HALF_STEPS)
  {
    digitalWrite(motor[MS1_PIN], HIGH);
    digitalWrite(motor[MS2_PIN], LOW);
  }
  else if (scale == QUARTER_STEPS)
  {
    digitalWrite(motor[MS1_PIN], LOW);
    digitalWrite(motor[MS2_PIN], HIGH);
  }
  else if (scale == EIGHTH_STEPS)
  {
    digitalWrite(motor[MS1_PIN], HIGH);
    digitalWrite(motor[MS2_PIN], HIGH);
  }
}

void enableMotors()
{
  digitalWrite(MOTOR_SLEEP, HIGH);
  digitalWrite(MOTOR_RESET, HIGH);
  digitalWrite(MOTOR_ENABLE, LOW);
}

void disableMotors() 
{
  digitalWrite(MOTOR_SLEEP, LOW);
  digitalWrite(MOTOR_RESET, LOW);
  digitalWrite(MOTOR_ENABLE, HIGH);
}

// Drives the motor corresponding to "motor" to it's home position (position 0)
void homeAxis(int motor[])
{
  int i;

  // Loop until endstop collision, then fine tune it
  // LEFT and DOWN have same value, as do RIGHT and UP. Use LEFT
  // and RIGHT arbitrarily while tuning end stop for both x and y axes.

  digitalWrite(motor[DIR_PIN], LEFT);
  setScale(motor, WHOLE_STEPS);
  while (digitalRead(motor[ENDSTOP_PIN]) == LOW)
  {
    digitalWrite(motor[STEP_PIN], LOW);
    delay(1);
    digitalWrite(motor[STEP_PIN], HIGH);
  }

  digitalWrite(motor[DIR_PIN], RIGHT);
  for (i = 0; i < HOME_CALIBRATION_OFFSET; i++)
  {
    digitalWrite(motor[STEP_PIN], LOW);
    delay(1);
    digitalWrite(motor[STEP_PIN], HIGH);
  }

  digitalWrite(motor[DIR_PIN], LEFT);
  setScale(motor, EIGHTH_STEPS);
  while (digitalRead(motor[ENDSTOP_PIN]) == LOW)
  {
    digitalWrite(motor[STEP_PIN], LOW);
    delay(1);
    digitalWrite(motor[STEP_PIN], HIGH);
  }
}

// Homes both axis
void home()
{
  homeAxis(xMotor);
  homeAxis(yMotor);
}

// Moves the magnet from the "start" point to the "end" point
// This can only move in straight lines
// Returns a boolean indicating success/error
bool moveStraight(int motor[], int startCol, int startRow, int endCol, int endRow)
{
  // A specific motor is passed to this function since we are only moving one here

  // How many steps per space
  int spaces, dir, numSteps;
  int i;

  // This could be two cases, x or y movement
  if (endRow == startRow)
  {
    // X movement
    spaces = abs(endCol - startCol);
    dir = (endCol > startCol) ? RIGHT : LEFT;
    setScale(xMotor, WHOLE_STEPS);
  }
  else if (endCol == startCol)
  {
    // Y movement
    spaces = abs(endRow - startRow);
    dir = (endRow > startRow) ? UP : DOWN;
    setScale(yMotor, WHOLE_STEPS);
  }
  else
  {
    return false;
  }

  numSteps = spaces * stepsPerSpace;

  // Enable motor driver inputs/output
  enableMotors();

  // Set direction of motor
  digitalWrite(motor[DIR_PIN], dir);

  // Rotate motor some number of steps
  for (i = 0; i < numSteps; i++) 
  {
    if (digitalRead(X_AXIS_ENDSTOP_SWITCH) == HIGH  ||  digitalRead(Y_AXIS_ENDSTOP_SWITCH))
      return false;
    
    digitalWrite(motor[STEP_PIN], LOW);
    delay(1);  // 1 milliSecond
    digitalWrite(motor[STEP_PIN], HIGH);
  }

  return true;
}

// Moves the magnet from the "start" point to the "end" point
// This can move in diagonal lines of slopes: 1, 2, and 1/2
// Returns a boolean indicating success/error
bool moveDiagonal(int startCol, int startRow, int endCol, int endRow)
{
  int dirX, dirY, spacesX, spacesY;
  int numStepsX, numStepsY;
  int i;

  // Abs ensures that numStepsX and numStepsY will be positive
  // to ensure proper for loop execution
  spacesX = abs(endCol - startCol);
  dirX = (endCol > startCol) ? RIGHT : LEFT;

  spacesY = abs(endRow - startRow);
  dirY = (endRow > startRow) ? UP : DOWN;

  numStepsX = spacesX * stepsPerSpace;
  numStepsY = spacesY * stepsPerSpace;

  enableMotors();

  digitalWrite(xMotor[DIR_PIN], dirX);
  digitalWrite(yMotor[DIR_PIN], dirY);
  
  if (numStepsX == numStepsY)
  {
    setScale(xMotor, WHOLE_STEPS);
    setScale(yMotor, WHOLE_STEPS);
  }
  else if (numStepsY > numStepsX && (numStepsY / numStepsX) == 2)
  {
    setScale(xMotor, HALF_STEPS);
    setScale(yMotor, WHOLE_STEPS);
  }
  else if (numStepsY < numStepsX && (numStepsX / numStepsY) == 2)
  {
    setScale(xMotor, WHOLE_STEPS);
    setScale(yMotor, HALF_STEPS);
  }
  else
  {
    return false;
  }

  for (i = 0; i < numStepsX; i++)
  {
    if (digitalRead(X_AXIS_ENDSTOP_SWITCH) == HIGH  ||  digitalRead(Y_AXIS_ENDSTOP_SWITCH))
      return false;

    digitalWrite(xMotor[STEP_PIN], LOW);
    digitalWrite(yMotor[STEP_PIN], LOW);
    delay(1);
    digitalWrite(xMotor[STEP_PIN], HIGH);
    digitalWrite(yMotor[STEP_PIN], HIGH);
  }

  return true;
}
