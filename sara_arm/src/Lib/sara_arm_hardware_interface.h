#ifndef ARM_H_I
#define ARM_H_I

#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>

const int NOMBRE_DE_MOTEURS_KINOVA = 5;
//Handle for the library's command layer.
void * commandLayer_handle;
int result;  // Tampon de réception des résultats de certaines fonctions
int devicesCount;
KinovaDevice devices[MAX_KINOVA_DEVICE];

// Function pointers to the functions we need
int (*MyInitAPI)();
int (*MyCloseAPI)();
int (*MySendBasicTrajectory)(TrajectoryPoint command);
int (*MySendAdvanceTrajectory)(TrajectoryPoint command);
int (*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
int (*MySetActiveDevice)(KinovaDevice device);
int (*MyMoveHome)();
int (*MySetJointZero)(int ActuatorAdress);
int (*MyInitFingers)();
int (*MyGetAngularCommand)(AngularPosition &);
int (*MyEraseAllTrajectories)();
int (*MyGetSensorsInfo)(SensorsInfo &);
int (*MySetActuatorMaxVelocity)(float &);
int (*MyGetActuatorsPosition)(float *);
int (*MyGetAngularVelocity)(float *);






class MyRobot : public hardware_interface::RobotHW {
    public:
        MyRobot();
        void init();
        void Read();
        void Write();

    private:
        hardware_interface::VelocityJointInterface joint_velocity_interface_;
        hardware_interface::JointStateInterface    joint_state_interface_;
        hardware_interface::JointStateHandle       joint_state_Handle_;
        double cmd[NOMBRE_DE_MOTEURS_KINOVA];
        double pos[NOMBRE_DE_MOTEURS_KINOVA];
        double vel[NOMBRE_DE_MOTEURS_KINOVA];
        double eff[NOMBRE_DE_MOTEURS_KINOVA];
};

#endif