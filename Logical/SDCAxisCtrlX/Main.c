#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	//Устанавливаем типы SDC модулей
	Axis_X_HW.EncIf1_Typ = ncSDC_ENC16;
	Axis_X_HW.DiDoIf_Typ = ncSDC_DIDO;
	Axis_X_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	
	//Устанавливаем имена переменных
	strcpy(Axis_X_HW.EncIf1_Name, "Axis_X_EncIf");
	strcpy(Axis_X_HW.DrvIf_Name, "Axis_X_DrvIf");
	strcpy(Axis_X_HW.DiDoIf_Name, "Axis_X_DiDoIf");
		
	//Устанавливаем входы готовности и нормальной работы
	Axis_X_EncIf.iEncOK = 1;
	Axis_X_DrvIf.iDrvOK = 1;
	Axis_X_DrvIf.iStatusEnable = 1;
	Axis_X_DiDoIf.iDriveReady = 1;
	
	Regulator.integrator.dt = 0.002;
	Regulator.integrator.direct = 0;
	Regulator.k_i = 0.16;
	Regulator.k_p = 0.0001;
	Regulator.max_abs_value = 24.0;
	
	axis_X.MaxSpeed = 6500;
}

void _CYCLIC ProgramCyclic(void)
{	
	Axis_X_EncIf.iLifeCnt++;
	Axis_X_DiDoIf.iLifeCntDriveEnable++; 
	Axis_X_DiDoIf.iLifeCntDriveReady++; 
	Axis_X_DiDoIf.iLifeCntNegHwEnd++; 
	Axis_X_DiDoIf.iLifeCntPosHwEnd++; 
	Axis_X_DiDoIf.iLifeCntReference++;
	Axis_X_DrvIf.iLifeCnt++;
	
	Axis_X_EncIf.iActTime = (INT)	AsIOTimeCyclicStart();
	Axis_X_EncIf.iActPos = axis_X.Counter;
	
	Axis_X_DiDoIf.iPosHwEnd = (axis_X.EndSwitchA || axis_X.ForceSwitchA);
	Axis_X_DiDoIf.iNegHwEnd = (axis_X.EndSwitchB || axis_X.ForceSwitchB);
	
	CoilPWM = CoilPowered ? 32767 : 0;
	
	if (CoilPowered)
	{
		Regulator.e = (axis_X.Manual ? axis_X.UserSpeed : Axis_X_DrvIf.oSetPos * 6500.0 / 32767.0) - axis_X.FeedbackSpeed;
		FB_Regulator(&Regulator);
		
		axis_X.U = Regulator.u;
		FB_Axis(&axis_X);
	}
	else
	{
		axis_X.PWM = 0;
	}
}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}

