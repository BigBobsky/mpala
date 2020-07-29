//=====================================================================================================
// MadgwickAHRS.c
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
//
//=====================================================================================================

//---------------------------------------------------------------------------------------------------
// Header files

#include "MadgwickAHRS.h"
#include <stdint.h>
#include <math.h>

//---------------------------------------------------------------------------------------------------
// Definitions

#define sampleFreq	512.0f		// sample frequency in Hz
#define betaDef		0.1f		// 2 * proportional gain

//---------------------------------------------------------------------------------------------------
// Variable definitions

volatile double beta = betaDef;								// 2 * proportional gain (Kp)
volatile double q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;	// quaternion of sensor frame relative to auxiliary frame

uint8_t MadgwickAHRSinitialized = 0;

//---------------------------------------------------------------------------------------------------
// Function declarations

double invSqrt(double x);


void MadgwickAHRSinit(double ax, double ay, double az, double mx, double my, double mz)
{
    double initialRoll, initialPitch;
    double cosRoll, sinRoll, cosPitch, sinPitch;
    double magX, magY;
    double initialHdg, cosHeading, sinHeading;

    initialRoll = atan2(-ay, -az);
    initialPitch = atan2(ax, -az);

    cosRoll = cosf(initialRoll);
    sinRoll = sinf(initialRoll);
    cosPitch = cosf(initialPitch);
    sinPitch = sinf(initialPitch);

    magX = mx * cosPitch + my * sinRoll * sinPitch + mz * cosRoll * sinPitch;

    magY = my * cosRoll - mz * sinRoll;

    initialHdg = atan2f(-magY, magX);

    cosRoll = cosf(initialRoll * 0.5f);
    sinRoll = sinf(initialRoll * 0.5f);

    cosPitch = cosf(initialPitch * 0.5f);
    sinPitch = sinf(initialPitch * 0.5f);

    cosHeading = cosf(initialHdg * 0.5f);
    sinHeading = sinf(initialHdg * 0.5f);

    q0 = cosRoll * cosPitch * cosHeading + sinRoll * sinPitch * sinHeading;
    q1 = sinRoll * cosPitch * cosHeading - cosRoll * sinPitch * sinHeading;
    q2 = cosRoll * sinPitch * cosHeading + sinRoll * cosPitch * sinHeading;
    q3 = cosRoll * cosPitch * sinHeading - sinRoll * sinPitch * cosHeading;
}


//====================================================================================================
// Functions

//---------------------------------------------------------------------------------------------------
// AHRS algorithm update

//---------------------------------------------------------------------------------------------------
// AHRS algorithm update

void MadgwickAHRSupdate(double gx, double gy, double gz, double ax, double ay, double az, double mx, double my, double mz, double accelCutoff, uint8_t newMagData, double dt)
{
    double accelSquareSum, recipNorm;
    double s0, s1, s2, s3;
    double qDot0, qDot1, qDot2, qDot3;
    double hx, hy;
    double _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz;
    double _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3;
    double q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

    ///////////////////////////////////

    // Initialize AHRS on first pass with valid mag data
    if ((MadgwickAHRSinitialized == 0) && (newMagData == 1))
    {
        MadgwickAHRSinit(ax, ay, az, mx, my, mz);

        MadgwickAHRSinitialized = 1;
    }

    ///////////////////////////////////

    if (MadgwickAHRSinitialized == 1) {
        ///////////////////////////////

        // Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation) or
        // mag data has not been updated

        if (((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) || (newMagData == 0))
        {
            MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az, accelCutoff, dt);
            return;
        }

        ///////////////////////////////

        // Rate of change of quaternion from gyroscope
        qDot0 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
        qDot1 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
        qDot2 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
        qDot3 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

        accelSquareSum = ax * ax + ay * ay + az * az;

        // Compute feedback only if accelerometer abs(vector) less than cutoff value (also avoids NaN in accelerometer normalisation)
        if (fabs(sqrt(accelSquareSum) - 9.8065) < accelCutoff)
        {
            // Normalise accelerometer measurement
            recipNorm = invSqrt(accelSquareSum);

            ax *= recipNorm;
            ay *= recipNorm;
            az *= recipNorm;

            // Normalise magnetometer measurement
            recipNorm = invSqrt(mx * mx + my * my + mz * mz);
            mx *= recipNorm;
            my *= recipNorm;
            mz *= recipNorm;

            // Auxiliary variables to avoid repeated arithmetic
            _2q0mx = 2.0f * q0 * mx;
            _2q0my = 2.0f * q0 * my;
            _2q0mz = 2.0f * q0 * mz;
            _2q1mx = 2.0f * q1 * mx;
            _2q0 = 2.0f * q0;
            _2q1 = 2.0f * q1;
            _2q2 = 2.0f * q2;
            _2q3 = 2.0f * q3;
            _2q0q2 = 2.0f * q0 * q2;
            _2q2q3 = 2.0f * q2 * q3;
            q0q0 = q0 * q0;
            q0q1 = q0 * q1;
            q0q2 = q0 * q2;
            q0q3 = q0 * q3;
            q1q1 = q1 * q1;
            q1q2 = q1 * q2;
            q1q3 = q1 * q3;
            q2q2 = q2 * q2;
            q2q3 = q2 * q3;
            q3q3 = q3 * q3;

            // Reference direction of Earth's magnetic field
            hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
            hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
            _2bx = sqrt(hx * hx + hy * hy);
            _2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
            _4bx = 2.0f * _2bx;
            _4bz = 2.0f * _2bz;

            // Gradient decent algorithm corrective step
            s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 + ax) + _2q1 * (2.0f * q0q1 + _2q2q3 + ay) - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
            s1 = _2q3 * (2.0f * q1q3 - _2q0q2 + ax) + _2q0 * (2.0f * q0q1 + _2q2q3 + ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 + az) + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
            s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 + ax) + _2q3 * (2.0f * q0q1 + _2q2q3 + ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 + az) + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
            s3 = _2q1 * (2.0f * q1q3 - _2q0q2 + ax) + _2q2 * (2.0f * q0q1 + _2q2q3 + ay) + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);

            recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
            s0 *= recipNorm;
            s1 *= recipNorm;
            s2 *= recipNorm;
            s3 *= recipNorm;

            // Apply feedback step
            // qDot0 -= sensorConfig.beta * s0;
            // qDot1 -= sensorConfig.beta * s1;
            // qDot2 -= sensorConfig.beta * s2;
            // qDot3 -= sensorConfig.beta * s3;
        }
        // Apply feedback step
        qDot0 -= beta * s0;
        qDot1 -= beta * s1;
        qDot2 -= beta * s2;
        qDot3 -= beta * s3;

        // Integrate rate of change of quaternion to yield quaternion
        q0 += qDot0 * dt;
        q1 += qDot1 * dt;
        q2 += qDot2 * dt;
        q3 += qDot3 * dt;

        // Normalise quaternion
        recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
        q0 *= recipNorm;
        q1 *= recipNorm;
        q2 *= recipNorm;
        q3 *= recipNorm;
    }
}

//---------------------------------------------------------------------------------------------------
// IMU algorithm update

void MadgwickAHRSupdateIMU(double gx, double gy, double gz, double ax, double ay, double az, double accelCutoff, double dt)
{
    double accelSquareSum, recipNorm;
    double s0, s1, s2, s3;
    double qDot0, qDot1, qDot2, qDot3;
    double _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2, _8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

    // Rate of change of quaternion from gyroscope
    qDot0 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
    qDot1 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
    qDot2 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
    qDot3 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

    accelSquareSum = ax * ax + ay * ay + az * az;

    // Compute feedback only if accelerometer abs(vector) less than cutoff value (also avoids NaN in accelerometer normalisation)
    if (fabs(sqrt(accelSquareSum) - 9.8065) < accelCutoff) {
        // Normalise accelerometer measurement
        recipNorm = invSqrt(accelSquareSum);

        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic
        _2q0 = 2.0f * q0;
        _2q1 = 2.0f * q1;
        _2q2 = 2.0f * q2;
        _2q3 = 2.0f * q3;
        _4q0 = 4.0f * q0;
        _4q1 = 4.0f * q1;
        _4q2 = 4.0f * q2;
        _8q1 = 8.0f * q1;
        _8q2 = 8.0f * q2;
        q0q0 = q0 * q0;
        q1q1 = q1 * q1;
        q2q2 = q2 * q2;
        q3q3 = q3 * q3;

        // Gradient decent algorithm corrective step
        s0 = _4q0 * q2q2 - _2q2 * ax + _4q0 * q1q1 + _2q1 * ay;
        s1 = _4q1 * q3q3 + _2q3 * ax + 4.0f * q0q0 * q1 + _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 - _4q1 * az;
        s2 = 4.0f * q0q0 * q2 - _2q0 * ax + _4q2 * q3q3 + _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 - _4q2 * az;
        s3 = 4.0f * q1q1 * q3 + _2q1 * ax + 4.0f * q2q2 * q3 + _2q2 * ay;

        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);     // normalise step magnitude
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        // Apply feedback step
        // qDot0 -= sensorConfig.beta * s0;
        // qDot1 -= sensorConfig.beta * s1;
        // qDot2 -= sensorConfig.beta * s2;
        // qDot3 -= sensorConfig.beta * s3;
    }
    // Apply feedback step
    qDot0 -= beta * s0;
    qDot1 -= beta * s1;
    qDot2 -= beta * s2;
    qDot3 -= beta * s3;

    // Integrate rate of change of quaternion to yield quaternion
    q0 += qDot0 * dt;
    q1 += qDot1 * dt;
    q2 += qDot2 * dt;
    q3 += qDot3 * dt;

    // Normalise quaternion
    recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 *= recipNorm;
    q1 *= recipNorm;
    q2 *= recipNorm;
    q3 *= recipNorm;
}

double invSqrt(double x) {

#ifdef FASTBITOPTIM
    double halfx = 0.5f * x;
    double y = x;
    long long i = *(long long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(double*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
#else
    double ret = 1.0 / (sqrt(x));
    return ret;
#endif
}

//====================================================================================================
// END OF CODE
//====================================================================================================
