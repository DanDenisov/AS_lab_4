/* Automation Studio generated header file */
/* Do not edit ! */
/* MotorCtrl  */

#ifndef _MOTORCTRL_
#define _MOTORCTRL_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef enum AxisStates
{	STOP = 0,
	HOMING = 1,
	MOVING = 2
} AxisStates;

typedef struct FB_Integrator
{
	/* VAR_INPUT (analog) */
	float in;
	/* VAR_OUTPUT (analog) */
	float out;
	/* VAR (analog) */
	float dt;
	/* VAR (digital) */
	plcbit direct;
} FB_Integrator_typ;

typedef struct FB_Regulator
{
	/* VAR_INPUT (analog) */
	float e;
	float e_prev;
	/* VAR_OUTPUT (analog) */
	float u;
	/* VAR (analog) */
	float u_raw;
	float k_p;
	float k_i;
	struct FB_Integrator integrator;
	float iyOld;
	float max_abs_value;
} FB_Regulator_typ;

typedef struct FB_Motor
{
	/* VAR_INPUT (analog) */
	float u;
	/* VAR_OUTPUT (analog) */
	float w;
	float phi;
	/* VAR (analog) */
	struct FB_Integrator integrator;
	struct FB_Integrator integrator_phi;
	float Tm;
	float ke;
	/* VAR (digital) */
	plcbit enable_reg;
} FB_Motor_typ;

typedef struct FB_Axis
{
	/* VAR_INPUT (analog) */
	float U;
	signed short UserSpeed;
	signed short Counter;
	/* VAR_OUTPUT (analog) */
	float FeedbackSpeed;
	signed short PWM;
	/* VAR (analog) */
	unsigned short MaxSpeed;
	/* VAR_INPUT (digital) */
	plcbit EndSwitchA;
	plcbit EndSwitchB;
	plcbit ForceSwitchA;
	plcbit ForceSwitchB;
	plcbit UserResetCounter;
	/* VAR_OUTPUT (digital) */
	plcbit ResetError;
	plcbit ResetCounter;
	/* VAR (digital) */
	plcbit Manual;
} FB_Axis_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void FB_Regulator(struct FB_Regulator* inst);
_BUR_PUBLIC void FB_Motor(struct FB_Motor* inst);
_BUR_PUBLIC void FB_Integrator(struct FB_Integrator* inst);
_BUR_PUBLIC void FB_Axis(struct FB_Axis* inst);


#ifdef __cplusplus
};
#endif
#endif /* _MOTORCTRL_ */

