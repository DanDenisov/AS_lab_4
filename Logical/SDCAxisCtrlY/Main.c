#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	//Устанавливаем типы SDC модулей
	Axis_Y_HW.EncIf1_Typ = ncSDC_ENC16;
	Axis_Y_HW.DiDoIf_Typ = ncSDC_DIDO;
	Axis_Y_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	
	//Устанавливаем имена переменных
	strcpy(Axis_Y_HW.EncIf1_Name, "Axis_Y_EncIf");
	strcpy(Axis_Y_HW.DrvIf_Name, "Axis_Y_DrvIf");
	strcpy(Axis_Y_HW.DiDoIf_Name, "Axis_Y_DiDoIf");
		
	//Устанавливаем входы готовности и нормальной работы
	Axis_Y_EncIf.iEncOK = 1;
	Axis_Y_DrvIf.iDrvOK = 1;
	Axis_Y_DrvIf.iStatusEnable = 1;
	Axis_Y_DiDoIf.iDriveReady = 1;
	
	Regulator.integrator.dt = 0.002;
	Regulator.integrator.direct = 0;
	Regulator.k_i = 0.16;
	Regulator.k_p = 0.0001;
	Regulator.max_abs_value = 24.0;
	
	axis_Y.MaxSpeed = 6500;
}

void _CYCLIC ProgramCyclic(void)
{	
	Axis_Y_EncIf.iLifeCnt++;
	Axis_Y_DiDoIf.iLifeCntDriveEnable++; 
	Axis_Y_DiDoIf.iLifeCntDriveReady++; 
	Axis_Y_DiDoIf.iLifeCntNegHwEnd++; 
	Axis_Y_DiDoIf.iLifeCntPosHwEnd++; 
	Axis_Y_DiDoIf.iLifeCntReference++;
	Axis_Y_DrvIf.iLifeCnt++;
	
	Axis_Y_EncIf.iActTime = (INT)	AsIOTimeCyclicStart();
	Axis_Y_EncIf.iActPos = axis_Y.Counter;
	
	Axis_Y_DiDoIf.iPosHwEnd = (axis_Y.EndSwitchA || axis_Y.ForceSwitchA);
	Axis_Y_DiDoIf.iNegHwEnd = (axis_Y.EndSwitchB || axis_Y.ForceSwitchB);
	
	CoilPWM = CoilPowered ? 32767 : 0;
	
	if (CoilPowered)
	{
		Regulator.e = (axis_Y.Manual ? axis_Y.UserSpeed : Axis_Y_DrvIf.oSetPos * 6500.0 / 32767.0) - axis_Y.FeedbackSpeed;
		FB_Regulator(&Regulator);
		
		axis_Y.U = Regulator.u;
		FB_Axis(&axis_Y);
	}
	else
	{
		axis_Y.PWM = 0;
	}
}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}
