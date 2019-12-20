/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1576510640_2_
#define _BUR_1576510640_2_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_GLOBAL struct ARNC0CNC_typ CNCsys;
_GLOBAL plcbit CoilPowered;
_GLOBAL signed short CoilPWM;
_GLOBAL unsigned short PWM_Period;
_GLOBAL struct SdcDiDoIf_typ Axis_Z_DiDoIf;
_GLOBAL struct SdcDrvIf16_typ Axis_Z_DrvIf;
_GLOBAL struct SdcEncIf16_typ Axis_Z_EncIf;
_GLOBAL struct SdcHwCfg_typ Axis_Z_HW;
_GLOBAL struct ACP10AXIS_typ Axis_Z;
_GLOBAL struct SdcDiDoIf_typ Axis_Y_DiDoIf;
_GLOBAL struct SdcDrvIf16_typ Axis_Y_DrvIf;
_GLOBAL struct SdcEncIf16_typ Axis_Y_EncIf;
_GLOBAL struct SdcHwCfg_typ Axis_Y_HW;
_GLOBAL struct ACP10AXIS_typ Axis_Y;
_GLOBAL struct SdcDiDoIf_typ Axis_X_DiDoIf;
_GLOBAL struct SdcDrvIf16_typ Axis_X_DrvIf;
_GLOBAL struct SdcEncIf16_typ Axis_X_EncIf;
_GLOBAL struct SdcHwCfg_typ Axis_X_HW;
_GLOBAL struct ACP10AXIS_typ Axis_X;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.var\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1576510640_2_ */

