#include "main.h"

/** Setting the namespace and speed*/
namespace drive {
    double leftSpeed;
    double rightSpeed;
   /**Telling the brain what ports they are and that they are green motors*/
    pros::Motor frontLeftDrive(8, pros::E_MOTOR_GEARSET_18, true);
    pros::Motor backLeftDrive(10, pros::E_MOTOR_GEARSET_18, true);
    pros::Motor frontRightDrive(7, pros::E_MOTOR_GEARSET_18, true);
    pros::Motor backRightDrive(9, pros::E_MOTOR_GEARSET_18, true);
    pros::Controller master  (E_CONTROLLER_MASTER);

void setRightDrive(double right){
    frontRightDrive.move_voltage(voltage: right/127*12000);
    backRightDrive.move_voltage(voltage: right/127*12000);
}
void setLeftDrive(double left){
    frontLeftDrive.move_voltage(voltage: left/127*12000);
    backLeftDrive.move_voltage(voltage: left/127*12000);
    
}

/** Explaining some background information and working a little with the speed*/
    void control() {
        leftSpeed = 200 * (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0);
        rightSpeed = 200 * (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0);

        frontLeftDrive.move_velocity(leftSpeed);
        backLeftDrive.move_velocity(leftSpeed);
        frontRightDrive.move_velocity(rightSpeed);
        backRightDrive.move_velocity(rightSpeed);
    }
}

