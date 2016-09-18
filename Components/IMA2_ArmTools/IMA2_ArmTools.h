/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jan 28 14:30:04 2009
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_ArmTools\IMA2_ArmTools.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __IMA2_ArmTools_h__
#define __IMA2_ArmTools_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPID_NonLinController_FWD_DEFINED__
#define __IPID_NonLinController_FWD_DEFINED__
typedef interface IPID_NonLinController IPID_NonLinController;
#endif 	/* __IPID_NonLinController_FWD_DEFINED__ */


#ifndef __ISampIndPressure_FWD_DEFINED__
#define __ISampIndPressure_FWD_DEFINED__
typedef interface ISampIndPressure ISampIndPressure;
#endif 	/* __ISampIndPressure_FWD_DEFINED__ */


#ifndef __IKinematicModel_FWD_DEFINED__
#define __IKinematicModel_FWD_DEFINED__
typedef interface IKinematicModel IKinematicModel;
#endif 	/* __IKinematicModel_FWD_DEFINED__ */


#ifndef __IHomingController_FWD_DEFINED__
#define __IHomingController_FWD_DEFINED__
typedef interface IHomingController IHomingController;
#endif 	/* __IHomingController_FWD_DEFINED__ */


#ifndef __IStepFilter_FWD_DEFINED__
#define __IStepFilter_FWD_DEFINED__
typedef interface IStepFilter IStepFilter;
#endif 	/* __IStepFilter_FWD_DEFINED__ */


#ifndef __PID_NonLinController_FWD_DEFINED__
#define __PID_NonLinController_FWD_DEFINED__

#ifdef __cplusplus
typedef class PID_NonLinController PID_NonLinController;
#else
typedef struct PID_NonLinController PID_NonLinController;
#endif /* __cplusplus */

#endif 	/* __PID_NonLinController_FWD_DEFINED__ */


#ifndef __SampIndPressure_FWD_DEFINED__
#define __SampIndPressure_FWD_DEFINED__

#ifdef __cplusplus
typedef class SampIndPressure SampIndPressure;
#else
typedef struct SampIndPressure SampIndPressure;
#endif /* __cplusplus */

#endif 	/* __SampIndPressure_FWD_DEFINED__ */


#ifndef __KinematicModel_FWD_DEFINED__
#define __KinematicModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class KinematicModel KinematicModel;
#else
typedef struct KinematicModel KinematicModel;
#endif /* __cplusplus */

#endif 	/* __KinematicModel_FWD_DEFINED__ */


#ifndef __HomingController_FWD_DEFINED__
#define __HomingController_FWD_DEFINED__

#ifdef __cplusplus
typedef class HomingController HomingController;
#else
typedef struct HomingController HomingController;
#endif /* __cplusplus */

#endif 	/* __HomingController_FWD_DEFINED__ */


#ifndef __StepFilter_FWD_DEFINED__
#define __StepFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class StepFilter StepFilter;
#else
typedef struct StepFilter StepFilter;
#endif /* __cplusplus */

#endif 	/* __StepFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPID_NonLinController_INTERFACE_DEFINED__
#define __IPID_NonLinController_INTERFACE_DEFINED__

/* interface IPID_NonLinController */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPID_NonLinController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("547AD78C-6C0D-45FF-8A7F-D04DE3A9BD51")
    IPID_NonLinController : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InvertPressure( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InvertPressure( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A0( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A0( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A1( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A1( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A2( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A2( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A3( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A3( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A4( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A4( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinClamp( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinClamp( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxClamp( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxClamp( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Kp( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Kp( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ki( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Ki( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Kd( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Kd( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Control_Law( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Control_Law( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BiasedPressure( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BiasedPressure( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InvertPressureIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InvertPressureIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A0Index( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A0Index( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A1Index( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A1Index( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A2Index( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A2Index( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A3Index( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A3Index( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_A4Index( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_A4Index( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinClampIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MinClampIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxClampIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxClampIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KpIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KpIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KiIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KiIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KdIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KdIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Control_LawIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Control_LawIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BiasedPressureIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BiasedPressureIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AlphaIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AlphaIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initial( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PID_NonLin_6Press( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PID_NonLin_12Press( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_CurrentPressure( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftArm( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftArm( 
            /* [in] */ short newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPID_NonLinControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPID_NonLinController __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPID_NonLinController __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InvertPressure )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InvertPressure )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A0 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A0 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A1 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A1 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A2 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A2 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A3 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A3 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A4 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A4 )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinClamp )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinClamp )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxClamp )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxClamp )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kp )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Kp )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ki )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Ki )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kd )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Kd )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control_Law )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Control_Law )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BiasedPressure )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BiasedPressure )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InvertPressureIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InvertPressureIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A0Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A0Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A1Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A1Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A2Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A2Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A3Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A3Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_A4Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_A4Index )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinClampIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MinClampIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxClampIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxClampIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KpIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KpIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KiIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KiIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KdIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KdIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control_LawIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Control_LawIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BiasedPressureIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BiasedPressureIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlphaIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AlphaIndex )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initial )( 
            IPID_NonLinController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PID_NonLin_6Press )( 
            IPID_NonLinController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PID_NonLin_12Press )( 
            IPID_NonLinController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_CurrentPressure )( 
            IPID_NonLinController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftArm )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftArm )( 
            IPID_NonLinController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        END_INTERFACE
    } IPID_NonLinControllerVtbl;

    interface IPID_NonLinController
    {
        CONST_VTBL struct IPID_NonLinControllerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPID_NonLinController_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPID_NonLinController_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPID_NonLinController_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPID_NonLinController_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPID_NonLinController_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPID_NonLinController_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPID_NonLinController_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPID_NonLinController_get_InvertPressure(This,pVal)	\
    (This)->lpVtbl -> get_InvertPressure(This,pVal)

#define IPID_NonLinController_put_InvertPressure(This,newVal)	\
    (This)->lpVtbl -> put_InvertPressure(This,newVal)

#define IPID_NonLinController_get_A0(This,pVal)	\
    (This)->lpVtbl -> get_A0(This,pVal)

#define IPID_NonLinController_put_A0(This,newVal)	\
    (This)->lpVtbl -> put_A0(This,newVal)

#define IPID_NonLinController_get_A1(This,pVal)	\
    (This)->lpVtbl -> get_A1(This,pVal)

#define IPID_NonLinController_put_A1(This,newVal)	\
    (This)->lpVtbl -> put_A1(This,newVal)

#define IPID_NonLinController_get_A2(This,pVal)	\
    (This)->lpVtbl -> get_A2(This,pVal)

#define IPID_NonLinController_put_A2(This,newVal)	\
    (This)->lpVtbl -> put_A2(This,newVal)

#define IPID_NonLinController_get_A3(This,pVal)	\
    (This)->lpVtbl -> get_A3(This,pVal)

#define IPID_NonLinController_put_A3(This,newVal)	\
    (This)->lpVtbl -> put_A3(This,newVal)

#define IPID_NonLinController_get_A4(This,pVal)	\
    (This)->lpVtbl -> get_A4(This,pVal)

#define IPID_NonLinController_put_A4(This,newVal)	\
    (This)->lpVtbl -> put_A4(This,newVal)

#define IPID_NonLinController_get_MinClamp(This,pVal)	\
    (This)->lpVtbl -> get_MinClamp(This,pVal)

#define IPID_NonLinController_put_MinClamp(This,newVal)	\
    (This)->lpVtbl -> put_MinClamp(This,newVal)

#define IPID_NonLinController_get_MaxClamp(This,pVal)	\
    (This)->lpVtbl -> get_MaxClamp(This,pVal)

#define IPID_NonLinController_put_MaxClamp(This,newVal)	\
    (This)->lpVtbl -> put_MaxClamp(This,newVal)

#define IPID_NonLinController_get_Kp(This,pVal)	\
    (This)->lpVtbl -> get_Kp(This,pVal)

#define IPID_NonLinController_put_Kp(This,newVal)	\
    (This)->lpVtbl -> put_Kp(This,newVal)

#define IPID_NonLinController_get_Ki(This,pVal)	\
    (This)->lpVtbl -> get_Ki(This,pVal)

#define IPID_NonLinController_put_Ki(This,newVal)	\
    (This)->lpVtbl -> put_Ki(This,newVal)

#define IPID_NonLinController_get_Kd(This,pVal)	\
    (This)->lpVtbl -> get_Kd(This,pVal)

#define IPID_NonLinController_put_Kd(This,newVal)	\
    (This)->lpVtbl -> put_Kd(This,newVal)

#define IPID_NonLinController_get_Control_Law(This,pVal)	\
    (This)->lpVtbl -> get_Control_Law(This,pVal)

#define IPID_NonLinController_put_Control_Law(This,newVal)	\
    (This)->lpVtbl -> put_Control_Law(This,newVal)

#define IPID_NonLinController_get_BiasedPressure(This,pVal)	\
    (This)->lpVtbl -> get_BiasedPressure(This,pVal)

#define IPID_NonLinController_put_BiasedPressure(This,newVal)	\
    (This)->lpVtbl -> put_BiasedPressure(This,newVal)

#define IPID_NonLinController_get_InvertPressureIndex(This,pVal)	\
    (This)->lpVtbl -> get_InvertPressureIndex(This,pVal)

#define IPID_NonLinController_put_InvertPressureIndex(This,newVal)	\
    (This)->lpVtbl -> put_InvertPressureIndex(This,newVal)

#define IPID_NonLinController_get_A0Index(This,pVal)	\
    (This)->lpVtbl -> get_A0Index(This,pVal)

#define IPID_NonLinController_put_A0Index(This,newVal)	\
    (This)->lpVtbl -> put_A0Index(This,newVal)

#define IPID_NonLinController_get_A1Index(This,pVal)	\
    (This)->lpVtbl -> get_A1Index(This,pVal)

#define IPID_NonLinController_put_A1Index(This,newVal)	\
    (This)->lpVtbl -> put_A1Index(This,newVal)

#define IPID_NonLinController_get_A2Index(This,pVal)	\
    (This)->lpVtbl -> get_A2Index(This,pVal)

#define IPID_NonLinController_put_A2Index(This,newVal)	\
    (This)->lpVtbl -> put_A2Index(This,newVal)

#define IPID_NonLinController_get_A3Index(This,pVal)	\
    (This)->lpVtbl -> get_A3Index(This,pVal)

#define IPID_NonLinController_put_A3Index(This,newVal)	\
    (This)->lpVtbl -> put_A3Index(This,newVal)

#define IPID_NonLinController_get_A4Index(This,pVal)	\
    (This)->lpVtbl -> get_A4Index(This,pVal)

#define IPID_NonLinController_put_A4Index(This,newVal)	\
    (This)->lpVtbl -> put_A4Index(This,newVal)

#define IPID_NonLinController_get_MinClampIndex(This,pVal)	\
    (This)->lpVtbl -> get_MinClampIndex(This,pVal)

#define IPID_NonLinController_put_MinClampIndex(This,newVal)	\
    (This)->lpVtbl -> put_MinClampIndex(This,newVal)

#define IPID_NonLinController_get_MaxClampIndex(This,pVal)	\
    (This)->lpVtbl -> get_MaxClampIndex(This,pVal)

#define IPID_NonLinController_put_MaxClampIndex(This,newVal)	\
    (This)->lpVtbl -> put_MaxClampIndex(This,newVal)

#define IPID_NonLinController_get_KpIndex(This,pVal)	\
    (This)->lpVtbl -> get_KpIndex(This,pVal)

#define IPID_NonLinController_put_KpIndex(This,newVal)	\
    (This)->lpVtbl -> put_KpIndex(This,newVal)

#define IPID_NonLinController_get_KiIndex(This,pVal)	\
    (This)->lpVtbl -> get_KiIndex(This,pVal)

#define IPID_NonLinController_put_KiIndex(This,newVal)	\
    (This)->lpVtbl -> put_KiIndex(This,newVal)

#define IPID_NonLinController_get_KdIndex(This,pVal)	\
    (This)->lpVtbl -> get_KdIndex(This,pVal)

#define IPID_NonLinController_put_KdIndex(This,newVal)	\
    (This)->lpVtbl -> put_KdIndex(This,newVal)

#define IPID_NonLinController_get_Control_LawIndex(This,pVal)	\
    (This)->lpVtbl -> get_Control_LawIndex(This,pVal)

#define IPID_NonLinController_put_Control_LawIndex(This,newVal)	\
    (This)->lpVtbl -> put_Control_LawIndex(This,newVal)

#define IPID_NonLinController_get_BiasedPressureIndex(This,pVal)	\
    (This)->lpVtbl -> get_BiasedPressureIndex(This,pVal)

#define IPID_NonLinController_put_BiasedPressureIndex(This,newVal)	\
    (This)->lpVtbl -> put_BiasedPressureIndex(This,newVal)

#define IPID_NonLinController_get_AlphaIndex(This,pVal)	\
    (This)->lpVtbl -> get_AlphaIndex(This,pVal)

#define IPID_NonLinController_put_AlphaIndex(This,newVal)	\
    (This)->lpVtbl -> put_AlphaIndex(This,newVal)

#define IPID_NonLinController_Initial(This)	\
    (This)->lpVtbl -> Initial(This)

#define IPID_NonLinController_PID_NonLin_6Press(This)	\
    (This)->lpVtbl -> PID_NonLin_6Press(This)

#define IPID_NonLinController_PID_NonLin_12Press(This)	\
    (This)->lpVtbl -> PID_NonLin_12Press(This)

#define IPID_NonLinController_Read_CurrentPressure(This)	\
    (This)->lpVtbl -> Read_CurrentPressure(This)

#define IPID_NonLinController_get_LeftArm(This,pVal)	\
    (This)->lpVtbl -> get_LeftArm(This,pVal)

#define IPID_NonLinController_put_LeftArm(This,newVal)	\
    (This)->lpVtbl -> put_LeftArm(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_InvertPressure_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_InvertPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_InvertPressure_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IPID_NonLinController_put_InvertPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A0_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A0_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A0_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_A0_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A1_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A1_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_A1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A2_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A2_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_A2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A3_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A3_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_A3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A4_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A4_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_A4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_MinClamp_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_MinClamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_MinClamp_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_MinClamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_MaxClamp_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_MaxClamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_MaxClamp_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_MaxClamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_Kp_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_Kp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_Kp_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_Kp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_Ki_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_Ki_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_Ki_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_Ki_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_Kd_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_Kd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_Kd_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_Kd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_Control_Law_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_Control_Law_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_Control_Law_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IPID_NonLinController_put_Control_Law_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_BiasedPressure_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_BiasedPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_BiasedPressure_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPID_NonLinController_put_BiasedPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_InvertPressureIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_InvertPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_InvertPressureIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_InvertPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A0Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A0Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A0Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_A0Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A1Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A1Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A1Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_A1Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A2Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A2Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A2Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_A2Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A3Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A3Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A3Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_A3Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_A4Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_A4Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_A4Index_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_A4Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_MinClampIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_MinClampIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_MinClampIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_MinClampIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_MaxClampIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_MaxClampIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_MaxClampIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_MaxClampIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_KpIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_KpIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_KpIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_KpIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_KiIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_KiIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_KiIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_KiIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_KdIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_KdIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_KdIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_KdIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_Control_LawIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_Control_LawIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_Control_LawIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_Control_LawIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_BiasedPressureIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_BiasedPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_BiasedPressureIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_BiasedPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_AlphaIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_AlphaIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_AlphaIndex_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_AlphaIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_Initial_Proxy( 
    IPID_NonLinController __RPC_FAR * This);


void __RPC_STUB IPID_NonLinController_Initial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_PID_NonLin_6Press_Proxy( 
    IPID_NonLinController __RPC_FAR * This);


void __RPC_STUB IPID_NonLinController_PID_NonLin_6Press_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_PID_NonLin_12Press_Proxy( 
    IPID_NonLinController __RPC_FAR * This);


void __RPC_STUB IPID_NonLinController_PID_NonLin_12Press_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_Read_CurrentPressure_Proxy( 
    IPID_NonLinController __RPC_FAR * This);


void __RPC_STUB IPID_NonLinController_Read_CurrentPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_get_LeftArm_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPID_NonLinController_get_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPID_NonLinController_put_LeftArm_Proxy( 
    IPID_NonLinController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPID_NonLinController_put_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPID_NonLinController_INTERFACE_DEFINED__ */


#ifndef __ISampIndPressure_INTERFACE_DEFINED__
#define __ISampIndPressure_INTERFACE_DEFINED__

/* interface ISampIndPressure */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISampIndPressure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EF1AF1A7-0FBB-42D0-AF5D-E6EFF12B96B5")
    ISampIndPressure : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceFilename( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeviceFilename( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SamplingPeriod( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SamplingPeriod( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderGain( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderGain( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderOffset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BiasedPressure( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BiasedPressure( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureMax( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderMax( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderMin( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZMask( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ZMask( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InvertPressure( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InvertPressure( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HomeAngles( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HomeAngles( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumAxes( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumAxes( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HomeAnglesIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HomeAnglesIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderMinIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderMinIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderMaxIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderMaxIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureMaxIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureMaxIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BiasedPressureIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BiasedPressureIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderOffsetIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderOffsetIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncoderGainIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncoderGainIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InvertPressureIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InvertPressureIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftArm( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftArm( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HW_IO_6( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HW_IO_12( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Enable_ZMasking( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disable_ZMasking( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteHomePositions( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISampIndPressureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISampIndPressure __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISampIndPressure __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISampIndPressure __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceFilename )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeviceFilename )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SamplingPeriod )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SamplingPeriod )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderGain )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderGain )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderOffset )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderOffset )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BiasedPressure )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BiasedPressure )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureMax )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureMax )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderMax )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderMax )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderMin )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderMin )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ZMask )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ZMask )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InvertPressure )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InvertPressure )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomeAngles )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomeAngles )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumAxes )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumAxes )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomeAnglesIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomeAnglesIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderMinIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderMinIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderMaxIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderMaxIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureMaxIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureMaxIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BiasedPressureIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BiasedPressureIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderOffsetIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderOffsetIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncoderGainIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EncoderGainIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InvertPressureIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InvertPressureIndex )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftArm )( 
            ISampIndPressure __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftArm )( 
            ISampIndPressure __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ISampIndPressure __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ISampIndPressure __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HW_IO_6 )( 
            ISampIndPressure __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HW_IO_12 )( 
            ISampIndPressure __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Enable_ZMasking )( 
            ISampIndPressure __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disable_ZMasking )( 
            ISampIndPressure __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteHomePositions )( 
            ISampIndPressure __RPC_FAR * This);
        
        END_INTERFACE
    } ISampIndPressureVtbl;

    interface ISampIndPressure
    {
        CONST_VTBL struct ISampIndPressureVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISampIndPressure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISampIndPressure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISampIndPressure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISampIndPressure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISampIndPressure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISampIndPressure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISampIndPressure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISampIndPressure_get_DeviceFilename(This,pVal)	\
    (This)->lpVtbl -> get_DeviceFilename(This,pVal)

#define ISampIndPressure_put_DeviceFilename(This,newVal)	\
    (This)->lpVtbl -> put_DeviceFilename(This,newVal)

#define ISampIndPressure_get_SamplingPeriod(This,pVal)	\
    (This)->lpVtbl -> get_SamplingPeriod(This,pVal)

#define ISampIndPressure_put_SamplingPeriod(This,newVal)	\
    (This)->lpVtbl -> put_SamplingPeriod(This,newVal)

#define ISampIndPressure_get_EncoderGain(This,pVal)	\
    (This)->lpVtbl -> get_EncoderGain(This,pVal)

#define ISampIndPressure_put_EncoderGain(This,newVal)	\
    (This)->lpVtbl -> put_EncoderGain(This,newVal)

#define ISampIndPressure_get_EncoderOffset(This,pVal)	\
    (This)->lpVtbl -> get_EncoderOffset(This,pVal)

#define ISampIndPressure_put_EncoderOffset(This,newVal)	\
    (This)->lpVtbl -> put_EncoderOffset(This,newVal)

#define ISampIndPressure_get_BiasedPressure(This,pVal)	\
    (This)->lpVtbl -> get_BiasedPressure(This,pVal)

#define ISampIndPressure_put_BiasedPressure(This,newVal)	\
    (This)->lpVtbl -> put_BiasedPressure(This,newVal)

#define ISampIndPressure_get_PressureMax(This,pVal)	\
    (This)->lpVtbl -> get_PressureMax(This,pVal)

#define ISampIndPressure_put_PressureMax(This,newVal)	\
    (This)->lpVtbl -> put_PressureMax(This,newVal)

#define ISampIndPressure_get_EncoderMax(This,pVal)	\
    (This)->lpVtbl -> get_EncoderMax(This,pVal)

#define ISampIndPressure_put_EncoderMax(This,newVal)	\
    (This)->lpVtbl -> put_EncoderMax(This,newVal)

#define ISampIndPressure_get_EncoderMin(This,pVal)	\
    (This)->lpVtbl -> get_EncoderMin(This,pVal)

#define ISampIndPressure_put_EncoderMin(This,newVal)	\
    (This)->lpVtbl -> put_EncoderMin(This,newVal)

#define ISampIndPressure_get_ZMask(This,pVal)	\
    (This)->lpVtbl -> get_ZMask(This,pVal)

#define ISampIndPressure_put_ZMask(This,newVal)	\
    (This)->lpVtbl -> put_ZMask(This,newVal)

#define ISampIndPressure_get_InvertPressure(This,pVal)	\
    (This)->lpVtbl -> get_InvertPressure(This,pVal)

#define ISampIndPressure_put_InvertPressure(This,newVal)	\
    (This)->lpVtbl -> put_InvertPressure(This,newVal)

#define ISampIndPressure_get_HomeAngles(This,pVal)	\
    (This)->lpVtbl -> get_HomeAngles(This,pVal)

#define ISampIndPressure_put_HomeAngles(This,newVal)	\
    (This)->lpVtbl -> put_HomeAngles(This,newVal)

#define ISampIndPressure_get_NumAxes(This,pVal)	\
    (This)->lpVtbl -> get_NumAxes(This,pVal)

#define ISampIndPressure_put_NumAxes(This,newVal)	\
    (This)->lpVtbl -> put_NumAxes(This,newVal)

#define ISampIndPressure_get_HomeAnglesIndex(This,pVal)	\
    (This)->lpVtbl -> get_HomeAnglesIndex(This,pVal)

#define ISampIndPressure_put_HomeAnglesIndex(This,newVal)	\
    (This)->lpVtbl -> put_HomeAnglesIndex(This,newVal)

#define ISampIndPressure_get_EncoderMinIndex(This,pVal)	\
    (This)->lpVtbl -> get_EncoderMinIndex(This,pVal)

#define ISampIndPressure_put_EncoderMinIndex(This,newVal)	\
    (This)->lpVtbl -> put_EncoderMinIndex(This,newVal)

#define ISampIndPressure_get_EncoderMaxIndex(This,pVal)	\
    (This)->lpVtbl -> get_EncoderMaxIndex(This,pVal)

#define ISampIndPressure_put_EncoderMaxIndex(This,newVal)	\
    (This)->lpVtbl -> put_EncoderMaxIndex(This,newVal)

#define ISampIndPressure_get_PressureMaxIndex(This,pVal)	\
    (This)->lpVtbl -> get_PressureMaxIndex(This,pVal)

#define ISampIndPressure_put_PressureMaxIndex(This,newVal)	\
    (This)->lpVtbl -> put_PressureMaxIndex(This,newVal)

#define ISampIndPressure_get_BiasedPressureIndex(This,pVal)	\
    (This)->lpVtbl -> get_BiasedPressureIndex(This,pVal)

#define ISampIndPressure_put_BiasedPressureIndex(This,newVal)	\
    (This)->lpVtbl -> put_BiasedPressureIndex(This,newVal)

#define ISampIndPressure_get_EncoderOffsetIndex(This,pVal)	\
    (This)->lpVtbl -> get_EncoderOffsetIndex(This,pVal)

#define ISampIndPressure_put_EncoderOffsetIndex(This,newVal)	\
    (This)->lpVtbl -> put_EncoderOffsetIndex(This,newVal)

#define ISampIndPressure_get_EncoderGainIndex(This,pVal)	\
    (This)->lpVtbl -> get_EncoderGainIndex(This,pVal)

#define ISampIndPressure_put_EncoderGainIndex(This,newVal)	\
    (This)->lpVtbl -> put_EncoderGainIndex(This,newVal)

#define ISampIndPressure_get_InvertPressureIndex(This,pVal)	\
    (This)->lpVtbl -> get_InvertPressureIndex(This,pVal)

#define ISampIndPressure_put_InvertPressureIndex(This,newVal)	\
    (This)->lpVtbl -> put_InvertPressureIndex(This,newVal)

#define ISampIndPressure_get_LeftArm(This,pVal)	\
    (This)->lpVtbl -> get_LeftArm(This,pVal)

#define ISampIndPressure_put_LeftArm(This,newVal)	\
    (This)->lpVtbl -> put_LeftArm(This,newVal)

#define ISampIndPressure_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define ISampIndPressure_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define ISampIndPressure_HW_IO_6(This)	\
    (This)->lpVtbl -> HW_IO_6(This)

#define ISampIndPressure_HW_IO_12(This)	\
    (This)->lpVtbl -> HW_IO_12(This)

#define ISampIndPressure_Enable_ZMasking(This)	\
    (This)->lpVtbl -> Enable_ZMasking(This)

#define ISampIndPressure_Disable_ZMasking(This)	\
    (This)->lpVtbl -> Disable_ZMasking(This)

#define ISampIndPressure_WriteHomePositions(This)	\
    (This)->lpVtbl -> WriteHomePositions(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_DeviceFilename_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_DeviceFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_DeviceFilename_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISampIndPressure_put_DeviceFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_SamplingPeriod_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_SamplingPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_SamplingPeriod_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_SamplingPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderGain_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderGain_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_EncoderGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderOffset_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderOffset_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_EncoderOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_BiasedPressure_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_BiasedPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_BiasedPressure_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_BiasedPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_PressureMax_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_PressureMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_PressureMax_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_PressureMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderMax_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderMax_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_EncoderMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderMin_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderMin_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_EncoderMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_ZMask_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_ZMask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_ZMask_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISampIndPressure_put_ZMask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_InvertPressure_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_InvertPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_InvertPressure_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB ISampIndPressure_put_InvertPressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_HomeAngles_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_HomeAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_HomeAngles_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ISampIndPressure_put_HomeAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_NumAxes_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_NumAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_NumAxes_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISampIndPressure_put_NumAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_HomeAnglesIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_HomeAnglesIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_HomeAnglesIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_HomeAnglesIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderMinIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderMinIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_EncoderMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderMaxIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderMaxIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_EncoderMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_PressureMaxIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_PressureMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_PressureMaxIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_PressureMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_BiasedPressureIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_BiasedPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_BiasedPressureIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_BiasedPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderOffsetIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderOffsetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderOffsetIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_EncoderOffsetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_EncoderGainIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_EncoderGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_EncoderGainIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_EncoderGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_InvertPressureIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_InvertPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_InvertPressureIndex_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_InvertPressureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_get_LeftArm_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISampIndPressure_get_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_put_LeftArm_Proxy( 
    ISampIndPressure __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ISampIndPressure_put_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_Initialize_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_Reset_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_HW_IO_6_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_HW_IO_6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_HW_IO_12_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_HW_IO_12_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_Enable_ZMasking_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_Enable_ZMasking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_Disable_ZMasking_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_Disable_ZMasking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISampIndPressure_WriteHomePositions_Proxy( 
    ISampIndPressure __RPC_FAR * This);


void __RPC_STUB ISampIndPressure_WriteHomePositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISampIndPressure_INTERFACE_DEFINED__ */


#ifndef __IKinematicModel_INTERFACE_DEFINED__
#define __IKinematicModel_INTERFACE_DEFINED__

/* interface IKinematicModel */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IKinematicModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C934E656-A909-4C6D-99E7-925D3E068619")
    IKinematicModel : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhatArm( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WhatArm( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_param_A2( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_param_A2( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_param_A3( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_param_A3( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_param_D3( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_param_D3( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_param_D4( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_param_D4( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_transform_BaseXformIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_transform_BaseXformIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_transform_EndEffXformIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_transform_EndEffXformIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_transform_EndEffXform( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_transform_EndEffXform( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_transform_BaseXform( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_transform_BaseXform( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisMax( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisMin( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisMaxIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisMaxIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisMinIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisMinIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE kin_ForwardKinematics( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE kin_InverseKinematics( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKinematicModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IKinematicModel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IKinematicModel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IKinematicModel __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatArm )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WhatArm )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_param_A2 )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_param_A2 )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_param_A3 )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_param_A3 )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_param_D3 )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_param_D3 )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_param_D4 )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_param_D4 )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transform_BaseXformIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_transform_BaseXformIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transform_EndEffXformIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_transform_EndEffXformIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transform_EndEffXform )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_transform_EndEffXform )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_transform_BaseXform )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_transform_BaseXform )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisMax )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisMax )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisMin )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisMin )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisMaxIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisMaxIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisMinIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisMinIndex )( 
            IKinematicModel __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *kin_ForwardKinematics )( 
            IKinematicModel __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *kin_InverseKinematics )( 
            IKinematicModel __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IKinematicModel __RPC_FAR * This);
        
        END_INTERFACE
    } IKinematicModelVtbl;

    interface IKinematicModel
    {
        CONST_VTBL struct IKinematicModelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKinematicModel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKinematicModel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKinematicModel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKinematicModel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IKinematicModel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IKinematicModel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IKinematicModel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IKinematicModel_get_WhatArm(This,pVal)	\
    (This)->lpVtbl -> get_WhatArm(This,pVal)

#define IKinematicModel_put_WhatArm(This,newVal)	\
    (This)->lpVtbl -> put_WhatArm(This,newVal)

#define IKinematicModel_get_param_A2(This,pVal)	\
    (This)->lpVtbl -> get_param_A2(This,pVal)

#define IKinematicModel_put_param_A2(This,newVal)	\
    (This)->lpVtbl -> put_param_A2(This,newVal)

#define IKinematicModel_get_param_A3(This,pVal)	\
    (This)->lpVtbl -> get_param_A3(This,pVal)

#define IKinematicModel_put_param_A3(This,newVal)	\
    (This)->lpVtbl -> put_param_A3(This,newVal)

#define IKinematicModel_get_param_D3(This,pVal)	\
    (This)->lpVtbl -> get_param_D3(This,pVal)

#define IKinematicModel_put_param_D3(This,newVal)	\
    (This)->lpVtbl -> put_param_D3(This,newVal)

#define IKinematicModel_get_param_D4(This,pVal)	\
    (This)->lpVtbl -> get_param_D4(This,pVal)

#define IKinematicModel_put_param_D4(This,newVal)	\
    (This)->lpVtbl -> put_param_D4(This,newVal)

#define IKinematicModel_get_transform_BaseXformIndex(This,pVal)	\
    (This)->lpVtbl -> get_transform_BaseXformIndex(This,pVal)

#define IKinematicModel_put_transform_BaseXformIndex(This,newVal)	\
    (This)->lpVtbl -> put_transform_BaseXformIndex(This,newVal)

#define IKinematicModel_get_transform_EndEffXformIndex(This,pVal)	\
    (This)->lpVtbl -> get_transform_EndEffXformIndex(This,pVal)

#define IKinematicModel_put_transform_EndEffXformIndex(This,newVal)	\
    (This)->lpVtbl -> put_transform_EndEffXformIndex(This,newVal)

#define IKinematicModel_get_transform_EndEffXform(This,pVal)	\
    (This)->lpVtbl -> get_transform_EndEffXform(This,pVal)

#define IKinematicModel_put_transform_EndEffXform(This,newVal)	\
    (This)->lpVtbl -> put_transform_EndEffXform(This,newVal)

#define IKinematicModel_get_transform_BaseXform(This,pVal)	\
    (This)->lpVtbl -> get_transform_BaseXform(This,pVal)

#define IKinematicModel_put_transform_BaseXform(This,newVal)	\
    (This)->lpVtbl -> put_transform_BaseXform(This,newVal)

#define IKinematicModel_get_AxisMax(This,pVal)	\
    (This)->lpVtbl -> get_AxisMax(This,pVal)

#define IKinematicModel_put_AxisMax(This,newVal)	\
    (This)->lpVtbl -> put_AxisMax(This,newVal)

#define IKinematicModel_get_AxisMin(This,pVal)	\
    (This)->lpVtbl -> get_AxisMin(This,pVal)

#define IKinematicModel_put_AxisMin(This,newVal)	\
    (This)->lpVtbl -> put_AxisMin(This,newVal)

#define IKinematicModel_get_AxisMaxIndex(This,pVal)	\
    (This)->lpVtbl -> get_AxisMaxIndex(This,pVal)

#define IKinematicModel_put_AxisMaxIndex(This,newVal)	\
    (This)->lpVtbl -> put_AxisMaxIndex(This,newVal)

#define IKinematicModel_get_AxisMinIndex(This,pVal)	\
    (This)->lpVtbl -> get_AxisMinIndex(This,pVal)

#define IKinematicModel_put_AxisMinIndex(This,newVal)	\
    (This)->lpVtbl -> put_AxisMinIndex(This,newVal)

#define IKinematicModel_kin_ForwardKinematics(This)	\
    (This)->lpVtbl -> kin_ForwardKinematics(This)

#define IKinematicModel_kin_InverseKinematics(This)	\
    (This)->lpVtbl -> kin_InverseKinematics(This)

#define IKinematicModel_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_WhatArm_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_WhatArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_WhatArm_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IKinematicModel_put_WhatArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_param_A2_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_param_A2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_param_A2_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_param_A2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_param_A3_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_param_A3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_param_A3_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_param_A3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_param_D3_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_param_D3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_param_D3_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_param_D3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_param_D4_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_param_D4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_param_D4_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_param_D4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_transform_BaseXformIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_transform_BaseXformIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_transform_BaseXformIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IKinematicModel_put_transform_BaseXformIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_transform_EndEffXformIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_transform_EndEffXformIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_transform_EndEffXformIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IKinematicModel_put_transform_EndEffXformIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_transform_EndEffXform_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_transform_EndEffXform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_transform_EndEffXform_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_transform_EndEffXform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_transform_BaseXform_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_transform_BaseXform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_transform_BaseXform_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_transform_BaseXform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_AxisMax_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_AxisMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_AxisMax_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_AxisMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_AxisMin_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_AxisMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_AxisMin_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IKinematicModel_put_AxisMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_AxisMaxIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_AxisMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_AxisMaxIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IKinematicModel_put_AxisMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IKinematicModel_get_AxisMinIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IKinematicModel_get_AxisMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IKinematicModel_put_AxisMinIndex_Proxy( 
    IKinematicModel __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IKinematicModel_put_AxisMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IKinematicModel_kin_ForwardKinematics_Proxy( 
    IKinematicModel __RPC_FAR * This);


void __RPC_STUB IKinematicModel_kin_ForwardKinematics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IKinematicModel_kin_InverseKinematics_Proxy( 
    IKinematicModel __RPC_FAR * This);


void __RPC_STUB IKinematicModel_kin_InverseKinematics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IKinematicModel_Initialize_Proxy( 
    IKinematicModel __RPC_FAR * This);


void __RPC_STUB IKinematicModel_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKinematicModel_INTERFACE_DEFINED__ */


#ifndef __IHomingController_INTERFACE_DEFINED__
#define __IHomingController_INTERFACE_DEFINED__

/* interface IHomingController */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHomingController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("313A8403-E0B0-47A2-9987-3ABBF724D137")
    IHomingController : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMinIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMinIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMaxIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMaxIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMin( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMax( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initial( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HomingSteps( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HomingSteps( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ComputeHomingPressures( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftArm( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftArm( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveThroughDexterousWorkspace( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveRightArmUpperQuadrant( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHomingControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHomingController __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHomingController __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHomingController __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMinIndex )( 
            IHomingController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMinIndex )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMaxIndex )( 
            IHomingController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMaxIndex )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMin )( 
            IHomingController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMin )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMax )( 
            IHomingController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMax )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initial )( 
            IHomingController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomingSteps )( 
            IHomingController __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomingSteps )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ComputeHomingPressures )( 
            IHomingController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftArm )( 
            IHomingController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftArm )( 
            IHomingController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveThroughDexterousWorkspace )( 
            IHomingController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveRightArmUpperQuadrant )( 
            IHomingController __RPC_FAR * This);
        
        END_INTERFACE
    } IHomingControllerVtbl;

    interface IHomingController
    {
        CONST_VTBL struct IHomingControllerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHomingController_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHomingController_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHomingController_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHomingController_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHomingController_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHomingController_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHomingController_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IHomingController_get_OutputMinIndex(This,pVal)	\
    (This)->lpVtbl -> get_OutputMinIndex(This,pVal)

#define IHomingController_put_OutputMinIndex(This,newVal)	\
    (This)->lpVtbl -> put_OutputMinIndex(This,newVal)

#define IHomingController_get_OutputMaxIndex(This,pVal)	\
    (This)->lpVtbl -> get_OutputMaxIndex(This,pVal)

#define IHomingController_put_OutputMaxIndex(This,newVal)	\
    (This)->lpVtbl -> put_OutputMaxIndex(This,newVal)

#define IHomingController_get_OutputMin(This,pVal)	\
    (This)->lpVtbl -> get_OutputMin(This,pVal)

#define IHomingController_put_OutputMin(This,newVal)	\
    (This)->lpVtbl -> put_OutputMin(This,newVal)

#define IHomingController_get_OutputMax(This,pVal)	\
    (This)->lpVtbl -> get_OutputMax(This,pVal)

#define IHomingController_put_OutputMax(This,newVal)	\
    (This)->lpVtbl -> put_OutputMax(This,newVal)

#define IHomingController_Initial(This)	\
    (This)->lpVtbl -> Initial(This)

#define IHomingController_get_HomingSteps(This,pVal)	\
    (This)->lpVtbl -> get_HomingSteps(This,pVal)

#define IHomingController_put_HomingSteps(This,newVal)	\
    (This)->lpVtbl -> put_HomingSteps(This,newVal)

#define IHomingController_ComputeHomingPressures(This)	\
    (This)->lpVtbl -> ComputeHomingPressures(This)

#define IHomingController_get_LeftArm(This,pVal)	\
    (This)->lpVtbl -> get_LeftArm(This,pVal)

#define IHomingController_put_LeftArm(This,newVal)	\
    (This)->lpVtbl -> put_LeftArm(This,newVal)

#define IHomingController_MoveThroughDexterousWorkspace(This)	\
    (This)->lpVtbl -> MoveThroughDexterousWorkspace(This)

#define IHomingController_MoveRightArmUpperQuadrant(This)	\
    (This)->lpVtbl -> MoveRightArmUpperQuadrant(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHomingController_get_OutputMinIndex_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IHomingController_get_OutputMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHomingController_put_OutputMinIndex_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IHomingController_put_OutputMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHomingController_get_OutputMaxIndex_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IHomingController_get_OutputMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHomingController_put_OutputMaxIndex_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IHomingController_put_OutputMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHomingController_get_OutputMin_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IHomingController_get_OutputMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHomingController_put_OutputMin_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IHomingController_put_OutputMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHomingController_get_OutputMax_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IHomingController_get_OutputMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHomingController_put_OutputMax_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IHomingController_put_OutputMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHomingController_Initial_Proxy( 
    IHomingController __RPC_FAR * This);


void __RPC_STUB IHomingController_Initial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHomingController_get_HomingSteps_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IHomingController_get_HomingSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHomingController_put_HomingSteps_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IHomingController_put_HomingSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHomingController_ComputeHomingPressures_Proxy( 
    IHomingController __RPC_FAR * This);


void __RPC_STUB IHomingController_ComputeHomingPressures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHomingController_get_LeftArm_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IHomingController_get_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHomingController_put_LeftArm_Proxy( 
    IHomingController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IHomingController_put_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHomingController_MoveThroughDexterousWorkspace_Proxy( 
    IHomingController __RPC_FAR * This);


void __RPC_STUB IHomingController_MoveThroughDexterousWorkspace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHomingController_MoveRightArmUpperQuadrant_Proxy( 
    IHomingController __RPC_FAR * This);


void __RPC_STUB IHomingController_MoveRightArmUpperQuadrant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHomingController_INTERFACE_DEFINED__ */


#ifndef __IStepFilter_INTERFACE_DEFINED__
#define __IStepFilter_INTERFACE_DEFINED__

/* interface IStepFilter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStepFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51CFCA6D-0D8E-4FF7-B36A-0B9C3469A7B5")
    IStepFilter : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_alpha( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_alpha( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AlphaIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AlphaIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FilterDesiredAngles( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStepFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStepFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStepFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStepFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStepFilter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStepFilter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStepFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStepFilter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_alpha )( 
            IStepFilter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_alpha )( 
            IStepFilter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlphaIndex )( 
            IStepFilter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AlphaIndex )( 
            IStepFilter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FilterDesiredAngles )( 
            IStepFilter __RPC_FAR * This);
        
        END_INTERFACE
    } IStepFilterVtbl;

    interface IStepFilter
    {
        CONST_VTBL struct IStepFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStepFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStepFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStepFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStepFilter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStepFilter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStepFilter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStepFilter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStepFilter_get_alpha(This,pVal)	\
    (This)->lpVtbl -> get_alpha(This,pVal)

#define IStepFilter_put_alpha(This,newVal)	\
    (This)->lpVtbl -> put_alpha(This,newVal)

#define IStepFilter_get_AlphaIndex(This,pVal)	\
    (This)->lpVtbl -> get_AlphaIndex(This,pVal)

#define IStepFilter_put_AlphaIndex(This,newVal)	\
    (This)->lpVtbl -> put_AlphaIndex(This,newVal)

#define IStepFilter_FilterDesiredAngles(This)	\
    (This)->lpVtbl -> FilterDesiredAngles(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStepFilter_get_alpha_Proxy( 
    IStepFilter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IStepFilter_get_alpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IStepFilter_put_alpha_Proxy( 
    IStepFilter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IStepFilter_put_alpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStepFilter_get_AlphaIndex_Proxy( 
    IStepFilter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IStepFilter_get_AlphaIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IStepFilter_put_AlphaIndex_Proxy( 
    IStepFilter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IStepFilter_put_AlphaIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStepFilter_FilterDesiredAngles_Proxy( 
    IStepFilter __RPC_FAR * This);


void __RPC_STUB IStepFilter_FilterDesiredAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStepFilter_INTERFACE_DEFINED__ */



#ifndef __IMA2_ARMTOOLSLib_LIBRARY_DEFINED__
#define __IMA2_ARMTOOLSLib_LIBRARY_DEFINED__

/* library IMA2_ARMTOOLSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_ARMTOOLSLib;

EXTERN_C const CLSID CLSID_PID_NonLinController;

#ifdef __cplusplus

class DECLSPEC_UUID("60F271DF-84CD-4945-8C66-6731D71E96D8")
PID_NonLinController;
#endif

EXTERN_C const CLSID CLSID_SampIndPressure;

#ifdef __cplusplus

class DECLSPEC_UUID("6AF8BEB2-72B5-464E-B3CE-55137C193BE1")
SampIndPressure;
#endif

EXTERN_C const CLSID CLSID_KinematicModel;

#ifdef __cplusplus

class DECLSPEC_UUID("1B0D7731-DF1B-42A5-8CC2-FA878BE758C5")
KinematicModel;
#endif

EXTERN_C const CLSID CLSID_HomingController;

#ifdef __cplusplus

class DECLSPEC_UUID("534ADA75-66E2-4AEA-AD32-50EC69EC8B71")
HomingController;
#endif

EXTERN_C const CLSID CLSID_StepFilter;

#ifdef __cplusplus

class DECLSPEC_UUID("F119E00B-89CE-4876-A58C-9958C30A7DD4")
StepFilter;
#endif
#endif /* __IMA2_ARMTOOLSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
