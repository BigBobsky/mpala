//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=====================================================================================================
#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h

#include <stdint.h>
//----------------------------------------------------------------------------------------------------
// Variable declaration

extern volatile double beta;				// algorithm gain
extern volatile double q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

/*--------------------------------------------------------------------------------------------------*/
// Function declarations

void MadgwickAHRSupdate(double gx, double gy, double gz, double ax, double ay, double az, double mx, double my, double mz, double accelCutoff, uint8_t newMagData, double dt);
void MadgwickAHRSupdateIMU(double gx, double gy, double gz, double ax, double ay, double az, double accelCutoff, double dt);

#endif
//=====================================================================================================
// End of file
//=====================================================================================================
