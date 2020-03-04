// includes
#ifndef odrive_hw_if_h
#define odrive_hw_if_h


#include <ros/ros.h>
#include <hardware_interface/robot_hw.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>

#include <iostream>
#include <vector>
#include <termios.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <math.h>

class OdriveHwIf: public hardware_interface::RobotHW
{

  public:
    OdriveHwIf();// vector.resize(4);
    ~OdriveHwIf();// close serial + stop(velocitats)
    bool init(ros::NodeHandle& _root_nh,ros::NodeHandle& _robot_hw_nh);//open serial
    void read(const ros::Time& _time,const ros::Duration& _period );// tots i pujar a velocities i positions
    void write(const ros::Time& _time,const ros::Duration& _period );//

// posicio per angles utilitzar n/2*pi i cocient *2*pi per sapiguer el angle i

  protected:
    // serial and comm related
    int serial_id_od1, serial_id_od2;
    int ret_value;
    termios ttySettings_1, ttySettings_2; //termios variable to configure serial port
    termios stdInOldSettings, stdInNewSettings;


    std::string read_msg_;
    std::string token_;
    std::string delimiter_;
    std::string mensg_;// variable that will provide flexibility to the messages
    unsigned char byte_;


    std::vector<double> positions_fb_;
    std::vector<double> velocities_fb_;
    std::vector<double> efforts_fb_; // cannot be used
    std::vector<double> velocities_cmmd_;
    //unsigned char readByte(const int & _serial_id);

    float to_rad_;
    const double PI  =3.141592653589793238463;


};


#endif
