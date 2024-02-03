#ifndef __FOC_H__
#define __FOC_H__

//limit range(low,high)
#define PI 3.14
#define _constance(amt,low,high) (amt<low?low:(amt>high?high:amt))
extern int pwmA = 30;
extern int pwmB = 30;
extern int pwmC = 30;

extern float voltage_limit = 10;
extern float voltage_power_supply = 12.6;//µÁ—π
float shaft_angle = 0,open_loop_timestamp = 0;
float zero_electric_angle = 0,Ualpha,Ubeta=0,Ua = 0,Ub = 0,dc_a=0,dc_b=0,dc_c=0;

extern float dc_a;
extern float dc_b;

typedef struct foc
{   
    int id;
    float foc_a;
    int pwm_total;
    

}FOC_t;


#endif

