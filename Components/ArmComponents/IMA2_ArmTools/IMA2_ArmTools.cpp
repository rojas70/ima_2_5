/***************************** IMA 25 Users, post Jan. 2009 **********************************************/
/*  Will find KinematicModel.cpp and SAKinematics.cpp the files useful for work.
/*  These contain the kinematic computations for ISAC.
/*
/*  The rest of the files are used with the old servo valves to control the arms.
/*  In early 2008, a new system of servo valves was installed and new code has been implemented for these.
/*  It can be found under: O:\Compnents\Arm Components\IMA2_NewArmControllerLib
/*********************************************************************************************************/


// IMA2_ArmToolsLib
// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f IMA2_ArmToolsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "IMA2_ArmTools.h"

#include "IMA2_ArmTools_i.c"
#include "PID_NonLinController.h"
#include "SampIndPressure.h"
#include "KinematicModel.h"
#include "HomingController.h"
#include "StepFilter.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_PID_NonLinController, CPID_NonLinController)
OBJECT_ENTRY(CLSID_SampIndPressure, CSampIndPressure)
OBJECT_ENTRY(CLSID_KinematicModel, CKinematicModel)
OBJECT_ENTRY(CLSID_HomingController, CHomingController)
OBJECT_ENTRY(CLSID_StepFilter, CStepFilter)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_IMA2_ARMTOOLSLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


