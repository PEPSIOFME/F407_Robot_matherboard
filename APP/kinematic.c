#include "kinematic.h"

#define l1 4.3
#define l2 8
#define Pi 3.14159265358979323846

double posture0[2] = {0, 0};
double posture1[2] = {0.2431, 1.72745};
double posture2[2] = {2.0806, 2.7135};
double posture3[2] = {3.4677, 4.52254};
double posture4[2] = {4.7568, 1.72745};
double posture5[2] = {5, 0};

uint8_t *GET_Angle(double *p)
{
    static uint8_t servo[2];
    double x = p[0], y = p[1];
    double ST1 = atan(l2 / l1) - acos((x * x + y * y + l1 * l1 - l2 * l2) / (2 * l1 * sqrt(l1 * l1 + l2 * l2)));
	double ST2 = Pi - acos((l1 * l1 + l2 * l2 - x * x - y * y) / (2 * l1 * l2));
    printf("ST1 = %f\n", ST1);
    printf("ST2 = %f\n", ST2);
    ST1 *= 57.32;
    ST2 *= 57.32;
    servo[0] = ST1;
    servo[1] = ST2;
    return servo;
}

void move(void)
{
    printf("xxx1\n");
    uint8_t *ps;
    uint16_t pwm;
    ps = GET_Angle(posture0);
    printf("ps0 = %d,%d\n", ps[0], ps[1]);

    pwm = calculate_PWM(ps[0]);
    setPWM(0x1,0,pwm);
    delay_ms(1);
    pwm = calculate_PWM(ps[1]);
    setPWM(0x2,0,pwm);
    delay_ms(500);

    ps = GET_Angle(posture1);
    printf("ps1 = %d,%d\n", ps[0], ps[1]);

    pwm = calculate_PWM(ps[0]);
    setPWM(0x1,0,pwm);
    delay_ms(1);
    pwm = calculate_PWM(ps[1]);
    setPWM(0x2,0,pwm);
    delay_ms(500);

    ps = GET_Angle(posture2);
    printf("ps2 = %d,%d\n", ps[0], ps[1]);

    pwm = calculate_PWM(ps[0]);
    setPWM(0x1,0,pwm);
    delay_ms(1);
    pwm = calculate_PWM(ps[1]);
    setPWM(0x2,0,pwm);
    delay_ms(500);

    ps = GET_Angle(posture3);
    printf("ps3 = %d,%d\n", ps[0], ps[1]);

    pwm = calculate_PWM(ps[0]);
    setPWM(0x1,0,pwm);
    delay_ms(1);
    pwm = calculate_PWM(ps[1]);
    setPWM(0x2,0,pwm);
    delay_ms(500);

    ps = GET_Angle(posture4);
    printf("ps4 = %d,%d\n", ps[0], ps[1]);
    
    pwm = calculate_PWM(ps[0]);
    setPWM(0x1,0,pwm);
    delay_ms(1);
    pwm = calculate_PWM(ps[1]);
    setPWM(0x2,0,pwm);
    delay_ms(500);

    ps = GET_Angle(posture5);
    printf("ps5 = %d,%d\n", ps[0], ps[1]);

    pwm = calculate_PWM(ps[0]);
    setPWM(0x1,0,pwm);
    delay_ms(1);
    pwm = calculate_PWM(ps[1]);
    setPWM(0x2,0,pwm);
    delay_ms(500);

}
