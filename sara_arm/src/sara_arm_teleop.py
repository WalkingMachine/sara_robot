#!/usr/bin/env python

# SARA teleoperation
# input: sensor_msgs/Joy
# output: geometry_msgs/Twist

# tutorial on how to setup joy_node http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick

# axes: [LeftJoystickEastWest LeftJoystickNorthSouth LeftTrigger RightJoystickEastWest  ...
#        RightJoystickNorthSouth RightTrigger PadEastWest PadNorthSouth]
# For joysticks and directional pad: West==1.0, East==-1.0, North==1.0, South==-1
# For triggers: fully pushed==-1.0, at rest==1.0
# joysticks and triggers can take any value between [-1.0, 1.0], 0.0 is at rest state
# directional pad values are 0.0 or 1.0
# buttons: [a, b, x, y, LeftBumper, RightBumper, back, start, XboxButton, LeftJoystickPress, RightJoystickPress]
# all buttons values are either 1.0 (button is pushed) or 0.0 (button is not pushed)

import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Int8, Int8MultiArray, UInt8, String
from geometry_msgs.msg import Twist
from math import pi, sin, cos, sqrt, atan2
from robotiq_c_model_control.msg import CModel_robot_output as eef_cmd
from robotiq_c_model_control.msg import CModel_robot_input as eef_status


class desjardinsTeleop:

    def __init__(self):

        self.sub = rospy.Subscriber('joy2', Joy, self.callback)

        self.pub = rospy.Publisher('teleop_arm', Int8MultiArray, queue_size=1)
        self.anim_pub = rospy.Publisher('animation_arm', String, queue_size=1)
        self.eef_pub = rospy.Publisher('/CModelRobotOutput', eef_cmd, queue_size=1, latch=True)
        self.face_pub = rospy.Publisher('/control_emo', UInt8, queue_size=1, latch=True)

        hand_cmd = eef_cmd()
        hand_cmd.rACT = 1  # activate gripper
        hand_cmd.rGTO = 1  # request to go to position
        hand_cmd.rSP = 200  # set activation speed (0[slowest]-255[fastest])
        hand_cmd.rFR = 0  # set force limit (0[min] - 255[max])
        hand_cmd.rPR = 0  # request to open
        self.eef_pub.publish(hand_cmd)
        #self.maxLinearVelocity = float(rospy.get_param('max_linear_vel', 1))
        # max angular velocity, in rad/s
        #divisor = rospy.get_param('angular_vel_div', 6)
        #self.maxAngularVelocity = pi/divisor


    def callback(self, joy):

        #twist = Twist()
    	if joy.buttons[13] == 1:
	        hand_cmd = eef_cmd()
	        hand_cmd.rACT = 1 # activate gripper
	        hand_cmd.rGTO = 1  # request to go to position
	        hand_cmd.rSP = 200  # set activation speed (0[slowest]-255[fastest])
	        hand_cmd.rFR = 0  # set force limit (0[min] - 255[max])
	        hand_cmd.rPR = 0  # request to open
	        self.eef_pub.publish(hand_cmd)

        elif joy.buttons[14] == 1:
            hand_cmd = eef_cmd()
            hand_cmd.rACT = 1  # activate gripper
            hand_cmd.rGTO = 1  # request to go to position
            hand_cmd.rSP = 200  # set activation speed (0[slowest]-255[fastest])
            hand_cmd.rFR = 0  # set force limit (0[min] - 255[max])
            hand_cmd.rPR = 250  # request to close
            self.eef_pub.publish(hand_cmd)

        if joy.buttons[8] == 1:
            self.face_pub.publish(1)
        elif joy.buttons[9] == 1:
            self.face_pub.publish(7)


        # Add point to sequence
        if joy.buttons[0] == 1:
            self.anim_pub.publish("ajoute_point")
        # Clear sequence
        if joy.buttons[1] == 1:
            self.anim_pub.publish("clear_sequence")
        # Run sequence
        if joy.buttons[2] == 1:
            self.anim_pub.publish("jouer_sequence")


        #Trigger L and R must be on to use
        safety = float(joy.buttons[6]) * float(joy.buttons[7])

        # linear velocity
        #vLinear = safety * sqrt(joy.axes[0]**2 + joy.axes[1]**2)

        # movement orientation
        #Heading = atan2(joy.axes[0], joy.axes[1])

        # x axis linear velocity
        #twist.linear.x = self.maxLinearVelocity * vLinear * cos(Heading)
        # y axis linear velocity
        #twist.linear.y = self.maxLinearVelocity * vLinear * sin(Heading)
        # YAW axis rotational velocity
        #twist.angular.z = self.maxAngularVelocity * safety * joy.axes[2] / 2.0
        # joy.buttons[0] * (joy.axes[5] - joy.axes[2]) / 2.0
        arm = Int8MultiArray()
        arm.data.append(safety * joy.axes[0] * -100)
        arm.data.append(safety * joy.axes[1] * -100)
        arm.data.append(safety * joy.axes[2] * 100)
        arm.data.append(safety * joy.axes[3] * -100)
        arm.data.append(safety * (float(joy.buttons[4])*100 - float(joy.buttons[5])*100))
        arm.data.append(0)
        self.pub.publish(arm)


if __name__ == '__main__':

    try:
        rospy.init_node('desjardinsTeleop')

        desjardinsTeleop()

        rospy.spin()

    except rospy.ROSInterruptException:
        pass
