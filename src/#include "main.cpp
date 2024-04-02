#include "main.h"
#include "api.h"
// #include "drive.cpp"
#include "drive.h"
// #include "okapi/api.hpp"
// #include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
// #include "okapi/api/chassis/controller/chassisController.hpp"

std::shared_ptr chassis = 
ChassisControllerBuilder().withMotors(1,-2)
//.withDimensions(AbstractMotor::gearset::green, {{3.25_in,10.2_in}, imev5GreenTPR})
.build();

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



/** Explaining some background information and working a little with the speed*/
    void control() {
        leftSpeed = 200 * (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0);
        rightSpeed = 200 * (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0);

        frontLeftDrive.move_velocity(leftSpeed);
        backLeftDrive.move_velocity(leftSpeed);
        frontRightDrive.move_velocity(rightSpeed);
        backRightDrive.move_velocity(rightSpeed);
  		/**frontLeftDrive.move_voltage(voltage:left/127*12000);
		backLeftDrive.move_voltage(voltage:left/127*12000);**/
   
   
   
    }
}





/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 /** Setting right and left drive as green motors*/
void initialize() {

	pros::lcd::initialize();
	pros::Motor drive_left_ (MOTOR_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	pros::Motor drive_right_ (MOTOR_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.

 */
void autonomous(void) {
//std::shared_ptr<ChassisController> chassis =
//ChassisControllerBuilder()
//.withMotors(1,-2)
//.withDimensions(AbstractMotor::gearset::green, {{3.25_in,10.2_in}, imev5GreenTPR})
//.build();
/**3.25 inches 10.2 inches in circumference*/


/** Moving to score a triball in the offensive zone*/
chassis->moveDistance(2.5);
/** Moving backwards to position the robot across from the goal*/
chassis->moveDistance(-2.5);
/** Turning to be straight across from the goal*/
chassis->turnAngle(135);
/** Scoring the triball into the goal*/
chassis->moveDistance(3.25);
/** moving backwards to avoid being under the goal*/
chassis->moveDistance(-3.25);
}
/***/
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


/** Idk this is just telling the brain what a port is basically and setting some rules*/
#define MOTOR_PORT 1

/** Ok so this is telling the brain what the drives are and setting ports for the motors */

/** This is telling the brain about the controller*/
pros::Controller controller(pros::E_CONTROLLER_MASTER);

/** This is setting the voltage for the left Drive*/
void setLeftDrive(double left){
	//frontLeftDrive.move_voltage(voltage:left/127*12000);
	//backLeftDrive.move_voltage(voltage:left/127*12000);
}




/** This is setting the voltage for the right drive*/
void setRightDrive(double right){
//	frontRightDrive.move_voltage(voltage:right/127*12000);
//	backRightDrive.move_voltage(voltage:right/127*12000);
}

/** This is for a tank drive*/
void setDriveMotors(){
	int leftJoystick = controller.get_analog
	(channel: pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	int rightJoystick = controller.get_analog
	(channel: pros::E_CONTROLLER_ANALOG_LEFT_Y);
	if(abs(leftJoystick>10)) leftJoystick = 0;
	if(abs(rightJoystick)<10) rightJoystick = 0;
	setLeftDrive(left:leftJoystick);
	setRightDrive(right:rightJoystick);
}
/**CODING FOR PNEUMATICS*/

/** Setting the port for the pneumatics*/
digital_out dig1= digital_out( Brain.ThreeWirePort.C );

int main() {
	int count = 0;

	while(1) {
		if( Controller1.ButtonR1.pressed() ) {
			dig1.set( true );
		}
		if( Controller1.ButtonR2.pressed() ) {
			dig1.set( false);
		}
		else {
			dig1.set( false );
		}
	this_thread::sleep_for(10);
	}
}



void opcontrol() {
	while(true) {
		drive::control();
	}
	
	pros::delay(10);


/** Programming the punch*/
/** Setting the port and telling the brain it is a red motor*/
	pros::Motor ourPunch(5, pros::E_MOTOR_GEARSET_36,true);

	while(1) {
	int ourPunch;

	/** Setting the "on" button*/
		if( Controller1.ButtonA.pressed() ) {
			ourPunch = 200;
			ourPunch.move_velocity(ourPunch);


		} /** Setting the "off" button*/
		if( Controller1.ButtonB.pressed){
			ourPunch = 0;
			ourPunch.move_velocity(ourPunch);
		}
	}
	/** Programming the Intake*/

	/** Setting the port and telling the brain it is a green motor*/
     pros::Motor theIntake(6, pros::E_MOTOR_GEARSET_18,true);
	while (1) {
		int theIntake;
/** Setting the "on" button*/
		if( Controller1.ButtonL1.pressed){
			theIntake = 200;
			theIntake.move_velocity(ourPunch);


		}/** Setting the "off" button*/
		if( Controller1.ButtonL2.pressed){
			theIntake = 0;
			theIntake.move_velocity(ourPunch);
		}
	 }

	}


