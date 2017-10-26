*************************
Robot Class Documentation
*************************

.. contents::

Robot Class
***********

Description: This class turns on and off the pins needed to drive the robot. The pins we are using are 7,13,11,15,16, and 18. All these pins are output except 18 which is input. 


External libraries used in Project
**********************************

**RPi.GPIO** - To control the GPIO pins
**time** - To pause the application for a set amout of seconds
**os** - To shut down the robot after running
**curses** - For keyboard support


SetUp
*****

**WarmUp()** - This method sets up the robot for use. The output and input pins are initalized

**SetOutputPins()** - Initalizes all the output pins (7,13,11,15,16) 

**SetInitialState()** - Sets all outpin pins to False


Range Finder
************

**GetDistance()** - Calculates the distance that something is in context to the range finder component. The way this works is that the finder emits a pulse and then receives the signal back. The time it took to recieve can be used to calculate the distance. The distance is in cm (source for more information http://www.modmypi.com/blog/hc-sr04-ultrasonic-range-sensor-on-the-raspberry-pi)

**EmitPulse()** - Turns the trig range finder pin on then off. This pulse is release then recieved by the echo pin.

**GetPulseDuration()** - The echo pin receives the signal. The time from when the echo pin was false to when it is true is calculated.


Movement
********

**DriveForwardSeconds(seconds)** - Turns on the appropriate pins on to drive forward for a number of seconds then these are turned off.

**DriveForward()** - Turns on the appropriate pins on to drive forward and do not stop until something else is called.

**DriveBackwards(seconds)** - Turns on the appropriate pins on to drive backwards for a number of seconds then these are turned off.

**DriveBackwards()** - Turns on the appropriate pins on to drive backwards and do not stop until something else is called.

**TurnRight(seconds)** - Turns on the appropriate pins to turn right. Turning will happen for the number of seconds in the seconds parameter. Note: .97 seconds is about 90 degrees.

**TurnLeft(seconds)** - Turns on the appropriate pins to turn left. Turning will happen for the number of seconds in the seconds parameter. Note: .97 seconds is about 90 degrees.


Testing
*******

**RunTest()** - Toggles all the output pins for 1 second.

**Toggle()** - Turns the output pin on for 1 second then off


Programs
********

**DrawShapes_Driver.py** - Ask the user for the number of sides in a shape and how many seconds the robot should drive for that size. So for example if you said 4 sides and 1 second it the robot would drive in a square returning back to the place it started. The keyboard interrupt exits the program and shuts down the pi.

**DriveAround_Driver.py** - Robot drives forward until a wall is detected with in 12 cms of the range finder. When the distance is less than 12 cms the robot stops, turns 90 degrees right, the drives forward again.The keyboard interrupt exits the program and shuts down the pi.

**RemoteControl_Driver.py** - The robot is controlled by keyboard input. Up, down, left, and right control the path of the robot. "t" will make the robot "dance" by running the RunTest() method. "s" stops the robot and "q" or keyboard interrupt will exit the program and shut down the pi.

**RobotRangeFinderTest.py** - Test the range finder component of the robot, make sure it can calculate a distance away from an object.
