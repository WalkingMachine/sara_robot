/*
 * kinovaApi.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: xhache
 */

/* This work is greatly inspired by Clearpath Robotics' jaco-driver ROS package */

#include <vector>
#include <iostream>
#include "wm_arm_driver/kinova_api.h"

namespace kinova
{

	void* checkApiInit(void * usbLib, const char* name)
	{
		void * function_pointer = dlsym(usbLib, name);
		assert(function_pointer != NULL);
		return function_pointer;
	}

	kinovaAPI::kinovaAPI()
	{
		void *usbLib = dlopen(KINOVA_USB_LIBRARY, RTLD_NOW | RTLD_GLOBAL);
		if (usbLib == NULL)
		{
			ROS_FATAL("%s", dlerror());
			return;
		}

		initAPI = (int (*)())checkApiInit(usbLib, "InitAPI");

		closeAPI = (int (*)())checkApiInit(usbLib, "CloseAPI");

		getAPIVersion = (int (*)(std::vector<int> &))checkApiInit(usbLib, "GetAPIVersion");

		getDevices = (int (*)(KinovaDevice[MAX_KINOVA_DEVICE], int &))checkApiInit(usbLib, "GetDevices");

		setActiveDevice = (int (*)(KinovaDevice))checkApiInit(usbLib, "SetActiveDevice");

		getCodeVersion = (int (*)(std::vector<int> &))checkApiInit(usbLib, "GetCodeVersion");

		getGeneralInformations = (int (*)(GeneralInformations &))checkApiInit(usbLib, "GetGeneralInformations");

		getCartesianPosition = (int (*)(CartesianPosition &))checkApiInit(usbLib, "GetCartesianPosition");

		getAngularPosition = (int (*)(AngularPosition &))checkApiInit(usbLib, "GetAngularPosition");

		getAngularVelocity = (int (*)(AngularPosition &))checkApiInit(usbLib, "GetAngularVelocity");

		getCartesianForce = (int (*)(CartesianPosition &))checkApiInit(usbLib, "GetCartesianForce");

		setCartesianForceMinMax = (int (*)(CartesianInfo, CartesianInfo))checkApiInit(usbLib, "SetCartesianForceMinMax");

		setCartesianInertiaDamping = (int (*)(CartesianInfo, CartesianInfo))checkApiInit(usbLib, "SetCartesianInertiaDamping");

		startForceControl = (int (*)())checkApiInit(usbLib, "StartForceControl");

		stopForceControl = (int (*)())checkApiInit(usbLib, "StopForceControl");

		getAngularForce = (int (*)(AngularPosition &))checkApiInit(usbLib, "GetAngularForce");

		getAngularCurrent = (int (*)(AngularPosition &))checkApiInit(usbLib, "GetAngularCurrent");

		getActualTrajectoryInfo = (int (*)(TrajectoryPoint &))checkApiInit(usbLib, "GetActualTrajectoryInfo");

		getGlobalTrajectoryInfo = (int (*)(TrajectoryFIFO &))checkApiInit(usbLib, "GetGlobalTrajectoryInfo");

		getSensorsInfo = (int (*)(SensorsInfo &))checkApiInit(usbLib, "GetSensorsInfo");

		setAngularControl = (int (*)())checkApiInit(usbLib, "SetAngularControl");

		setCartesianControl = (int (*)())checkApiInit(usbLib, "SetCartesianControl");

		startControlAPI = (int (*)())checkApiInit(usbLib, "StartControlAPI");

		stopControlAPI = (int (*)())checkApiInit(usbLib, "StopControlAPI");

		moveHome = (int (*)())checkApiInit(usbLib, "MoveHome");

		initFingers = (int (*)())checkApiInit(usbLib, "InitFingers");

		restoreFactoryDefault = (int (*)())checkApiInit(usbLib, "RestoreFactoryDefault");

		sendJoystickCommand = (int (*)(JoystickCommand))checkApiInit(usbLib, "SendJoystickCommand");

		sendAdvanceTrajectory = (int (*)(TrajectoryPoint))checkApiInit(usbLib, "SendAdvanceTrajectory");

		sendBasicTrajectory = (int (*)(TrajectoryPoint))checkApiInit(usbLib, "SendBasicTrajectory");

		getControlType = (int (*)(int &)) checkApiInit(usbLib, "GetControlType");

		getQuickStatus = (int (*)(QuickStatus &))checkApiInit(usbLib, "GetQuickStatus");

		getClientConfigurations = (int (*)(ClientConfigurations &))checkApiInit(usbLib, "GetClientConfigurations");

		setClientConfigurations = (int (*)( ClientConfigurations))checkApiInit(usbLib, "SetClientConfigurations");

		eraseAllTrajectories = (int (*)())checkApiInit(usbLib, "EraseAllTrajectories");

		getPositionCurrentActuators = (int (*)(std::vector<float> &))checkApiInit(usbLib, "GetPositionCurrentActuators");

		setActuatorPID = (int (*)(unsigned int, float, float, float))checkApiInit(usbLib, "SetActuatorPID");
	}

	kinovaAPI::~kinovaAPI()
	{

	}

}  // namespace kinova

