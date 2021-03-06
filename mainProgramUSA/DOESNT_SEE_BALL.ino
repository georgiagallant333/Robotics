void doesnt_see_ball() {
  if (ballAngle != 10000) {
    int x = 0;
    for (int i = 0; i < 10; i++) {
      calculateAngle();
      if (ballAngle < 2000) x++;
    }
    if (x >= 8) currentState = SEES_BALL; //if sees ball at any point, switches state
  }
  else if (millis() - lastTimeSawBall <= 400 && spinningToBall == false) { //if the ball is in the front half of the robot when it loses it, immediately stops. If the ball is in the back half of the robot (meaning it is spinning in place) keeps spinning for 250ms to see if it sees it
    dribblerIn();
    stopMotors();
  }
  else if (millis() - lastTimeSawBall >= 400 && millis() - lastTimeSawBall <= 1000) { //stops motors no matter what after 250ms. Stays stopped looking for ball for 1.85 seconds
    dribblerOff();
    stopMotors();
  }
  else if (millis() - lastTimeSawBall >= 1000 && millis() - lastTimeSawBall <= 7000) { //tries to get back to center for 4 seconds
    updateDistances();
    int x = (rightDist >= leftDist) ? 1 : -1;
    int y = (frontDist >= backDist) ? 1 : -1;

    int lrdiff = abs(rightDist - leftDist);
    int fbdiff = abs(frontDist - backDist);

    boolean lrcentered = (lrdiff < 30 && rightDist + leftDist > 120); //if the difference between right and left is less than 30 and greater than 120 (not blocked by robot) means that it is centered
    boolean fbcentered = (fbdiff < 30 && frontDist + backDist > 120);

    if (lrcentered && fbcentered) {
      stopMotors();
      if (checkPossession() == true) {
        currentState = HAS_BALL;
        stopMotors();
      }
    } else {
      driveToHeadingIMU(g_goal, xyToAngle(x, y), 200); //drive to center
    }

  }
  else if (millis() - lastTimeSawBall >= 7000 && millis()) {
    if (checkPossession() == true) {
      currentState = HAS_BALL;
      stopMotors();
    }
    stopMotors(); //stop motors after trying to get to center for 4 seconds
  }
}

void goalieFindBall() {
  calculateAngleGoalie();
  if (checkPossession() == true) {
    currentState = HAS_BALL;
    stopMotors();
  }
  if (inGoal() && yPos < 2000) currentState = SEES_BALL;
  else if (inGoal() == false) currentState = OUT_OF_GOAL;
  else if (millis() - lastTimeSawBall > 250) {
    IMU_spinToDirection(g_goal);
  }
}

