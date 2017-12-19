# Tagminator
The process goes as follows:

Wait for nextTag signal to be HIGH
After receiving the signal:
Turn "jump" on for specified amount of steps.
Enable stepper motor driver power.
Start running the motor and ignore contrast sensor until the jump is over.
After Turn off the jump and start reading the contrast sensor for detecting tags.
After detecting a tag:
stop motor.
disable stepper motor driver power.

IMPORTANT: While not running the motor it's mandatory to disable the stepper motor driver power to prevent motor from heating up.
