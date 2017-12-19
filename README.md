# Tagminator
The process goes as follows:

Wait for nextTag signal to go high.
After receiving the signal:
Enable "jump" for specified amount of steps.
Enable stepper motor driver power.
Start running the motor and ignore contrast sensor until the jump is over.
After Turn off the jump and start reading the contrast sensor for detecting tags.
After detecting a tag:
Stop motor.
Disable stepper motor driver power.
Wait for nextTag signal to go high.

IMPORTANT: While not running the motor it's mandatory to disable the stepper motor driver power to prevent motor from heating up.
