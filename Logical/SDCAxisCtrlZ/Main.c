#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	//Устанавливаем типы SDC модулей
	Axis_Z_HW.EncIf1_Typ = ncSDC_ENC16;
	Axis_Z_HW.DiDoIf_Typ = ncSDC_DIDO;
	Axis_Z_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	
	//Устанавливаем имена переменных
	strcpy(Axis_Z_HW.EncIf1_Name, "Axis_Z_EncIf");
	strcpy(Axis_Z_HW.DrvIf_Name, "Axis_Z_DrvIf");
	strcpy(Axis_Z_HW.DiDoIf_Name, "Axis_Z_DiDoIf");
		
	//Устанавливаем входы готовности и нормальной работы
	Axis_Z_EncIf.iEncOK = 1;
	Axis_Z_DrvIf.iDrvOK = 1;
	Axis_Z_DrvIf.iStatusEnable = 1;
	Axis_Z_DiDoIf.iDriveReady = 1;
	
	Regulator.integrator.dt = 0.002;
	Regulator.integrator.direct = 0;
	Regulator.k_i = 0.16;
	Regulator.k_p = 0.0001;
	Regulator.max_abs_value = 24.0;
	
	axis_Z.MaxSpeed = 6500;
	
	PWM_Period = 200;
}

void _CYCLIC ProgramCyclic(void)
{	
	Axis_Z_EncIf.iLifeCnt++;
	Axis_Z_DiDoIf.iLifeCntDriveEnable++; 
	Axis_Z_DiDoIf.iLifeCntDriveReady++; 
	Axis_Z_DiDoIf.iLifeCntNegHwEnd++; 
	Axis_Z_DiDoIf.iLifeCntPosHwEnd++; 
	Axis_Z_DiDoIf.iLifeCntReference++;
	Axis_Z_DrvIf.iLifeCnt++;
	
	Axis_Z_EncIf.iActTime = (INT)	AsIOTimeCyclicStart();
	Axis_Z_EncIf.iActPos = -axis_Z.Counter;
	
	Axis_Z_DiDoIf.iPosHwEnd = (axis_Z.EndSwitchA || axis_Z.ForcePosSwitch);
	Axis_Z_DiDoIf.iNegHwEnd = (axis_Z.EndSwitchB || axis_Z.ForceNegSwitch);
	
	CoilPWM = CoilPowered ? 32767 : 0;
	
	if (CoilPowered)
	{
		Regulator.e = (axis_Z.Manual ? axis_Z.UserSpeed : Axis_Z_DrvIf.oSetPos * 6500.0 / 32767.0) - axis_Z.FeedbackSpeed;
		FB_Regulator(&Regulator);
		
		axis_Z.U = Regulator.u;
		FB_Axis(&axis_Z);
	}
	else
	{
		axis_Z.PWM = 0;
	}
}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}
