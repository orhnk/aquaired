#include <Deneyap_Servo.h>

/*
Inital Servo position:

 .-------.   .-----SIG---> A0
 | SERVO |---+-----VCC---> A1 + DC
 '-------'   '-----GND---> A2 - DC

*/

Servo servo_motor;

/**
a_sec   = 1000ms
a_min   = 60 * a_sec
an_hour = 60 * a_min
*/
const auto a_sec   = 1000;
const auto a_min   = 60 * a_sec;
const auto an_hour = 60 * a_min;

auto servo_pin    = D9;
auto batch_delay  = 8 * an_hour;
auto  move_delay  = 1000;
auto initial_pos  = 0;
auto offset       = 170; // motor offsetting in degrees
auto fixup_offset = 13; // backstep offset to satisfy the motor grumbling
auto fixup_secnd  = 1;  // second forward-step to reduce grumbling motor
auto fixup_delay  = 500;

void setup() {
  Serial.begin(9600);
  servo_motor.attach(servo_pin);
}

void loop() {
  servo_motor.write(initial_pos + offset);
  delay(move_delay);
  servo_motor.write(initial_pos);
  delay(move_delay);
  servo_motor.write(initial_pos + fixup_offset);
  delay(fixup_delay);
  servo_motor.write(initial_pos + fixup_offset - fixup_secnd);
  Serial.println("Servo moved");
  delay(batch_delay);
}