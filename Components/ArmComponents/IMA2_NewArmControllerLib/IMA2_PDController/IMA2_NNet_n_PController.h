/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Nov 17 12:07:18 2008
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_NewArmControllerLib\IMA2_PDController\IMA2_NNet_n_PController.idl:
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

#ifndef __IMA2_NNet_n_PController_h__
#define __IMA2_NNet_n_PController_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INewValveController_FWD_DEFINED__
#define __INewValveController_FWD_DEFINED__
typedef interface INewValveController INewValveController;
#endif 	/* __INewValveController_FWD_DEFINED__ */


#ifndef __NewValveController_FWD_DEFINED__
#define __NewValveController_FWD_DEFINED__

#ifdef __cplusplus
typedef class NewValveController NewValveController;
#else
typedef struct NewValveController NewValveController;
#endif /* __cplusplus */

#endif 	/* __NewValveController_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INewValveController_INTERFACE_DEFINED__
#define __INewValveController_INTERFACE_DEFINED__

/* interface INewValveController */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INewValveController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B53073D1-1C5C-4916-8A27-92A5B7402F17")
    INewValveController : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoHomingRoutine( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhatArm( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WhatArm( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ErrorMessage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ValveOutputsIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ValveOutputsIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ValveOutputs( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ValveOutputs( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JointAngles( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_JointAngles( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JointAnglesIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_JointAnglesIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_PGainValue( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_PGainValue( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_PGainValueIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_PGainValueIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumOfSteps( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumOfSteps( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rate_InflationRate( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rate_InflationRate( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rate_DeflationRate( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rate_DeflationRate( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE gripper_OpenGripper( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE gripper_CloseGripper( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INewValveControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INewValveController __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INewValveController __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INewValveController __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoHomingRoutine )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatArm )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WhatArm )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorMessage )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErrorMessage )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ValveOutputsIndex )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ValveOutputsIndex )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ValveOutputs )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ValveOutputs )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_JointAngles )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_JointAngles )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_JointAnglesIndex )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_JointAnglesIndex )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_PGainValue )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_PGainValue )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_PGainValueIndex )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_PGainValueIndex )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumOfSteps )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumOfSteps )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rate_InflationRate )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rate_InflationRate )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rate_DeflationRate )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rate_DeflationRate )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *gripper_OpenGripper )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *gripper_CloseGripper )( 
            INewValveController __RPC_FAR * This);
        
        END_INTERFACE
    } INewValveControllerVtbl;

    interface INewValveController
    {
        CONST_VTBL struct INewValveControllerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INewValveController_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INewValveController_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INewValveController_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INewValveController_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INewValveController_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INewValveController_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INewValveController_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INewValveController_DoHomingRoutine(This)	\
    (This)->lpVtbl -> DoHomingRoutine(This)

#define INewValveController_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define INewValveController_get_WhatArm(This,pVal)	\
    (This)->lpVtbl -> get_WhatArm(This,pVal)

#define INewValveController_put_WhatArm(This,newVal)	\
    (This)->lpVtbl -> put_WhatArm(This,newVal)

#define INewValveController_Move(This)	\
    (This)->lpVtbl -> Move(This)

#define INewValveController_get_ErrorMessage(This,pVal)	\
    (This)->lpVtbl -> get_ErrorMessage(This,pVal)

#define INewValveController_put_ErrorMessage(This,newVal)	\
    (This)->lpVtbl -> put_ErrorMessage(This,newVal)

#define INewValveController_get_ValveOutputsIndex(This,pVal)	\
    (This)->lpVtbl -> get_ValveOutputsIndex(This,pVal)

#define INewValveController_put_ValveOutputsIndex(This,newVal)	\
    (This)->lpVtbl -> put_ValveOutputsIndex(This,newVal)

#define INewValveController_get_ValveOutputs(This,pVal)	\
    (This)->lpVtbl -> get_ValveOutputs(This,pVal)

#define INewValveController_put_ValveOutputs(This,newVal)	\
    (This)->lpVtbl -> put_ValveOutputs(This,newVal)

#define INewValveController_get_JointAngles(This,pVal)	\
    (This)->lpVtbl -> get_JointAngles(This,pVal)

#define INewValveController_put_JointAngles(This,newVal)	\
    (This)->lpVtbl -> put_JointAngles(This,newVal)

#define INewValveController_get_JointAnglesIndex(This,pVal)	\
    (This)->lpVtbl -> get_JointAnglesIndex(This,pVal)

#define INewValveController_put_JointAnglesIndex(This,newVal)	\
    (This)->lpVtbl -> put_JointAnglesIndex(This,newVal)

#define INewValveController_get_gain_PGainValue(This,pVal)	\
    (This)->lpVtbl -> get_gain_PGainValue(This,pVal)

#define INewValveController_put_gain_PGainValue(This,newVal)	\
    (This)->lpVtbl -> put_gain_PGainValue(This,newVal)

#define INewValveController_get_gain_PGainValueIndex(This,pVal)	\
    (This)->lpVtbl -> get_gain_PGainValueIndex(This,pVal)

#define INewValveController_put_gain_PGainValueIndex(This,newVal)	\
    (This)->lpVtbl -> put_gain_PGainValueIndex(This,newVal)

#define INewValveController_get_NumOfSteps(This,pVal)	\
    (This)->lpVtbl -> get_NumOfSteps(This,pVal)

#define INewValveController_put_NumOfSteps(This,newVal)	\
    (This)->lpVtbl -> put_NumOfSteps(This,newVal)

#define INewValveController_get_rate_InflationRate(This,pVal)	\
    (This)->lpVtbl -> get_rate_InflationRate(This,pVal)

#define INewValveController_put_rate_InflationRate(This,newVal)	\
    (This)->lpVtbl -> put_rate_InflationRate(This,newVal)

#define INewValveController_get_rate_DeflationRate(This,pVal)	\
    (This)->lpVtbl -> get_rate_DeflationRate(This,pVal)

#define INewValveController_put_rate_DeflationRate(This,newVal)	\
    (This)->lpVtbl -> put_rate_DeflationRate(This,newVal)

#define INewValveController_gripper_OpenGripper(This)	\
    (This)->lpVtbl -> gripper_OpenGripper(This)

#define INewValveController_gripper_CloseGripper(This)	\
    (This)->lpVtbl -> gripper_CloseGripper(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_DoHomingRoutine_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_DoHomingRoutine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_Close_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_WhatArm_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_WhatArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_WhatArm_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INewValveController_put_WhatArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_Move_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_ErrorMessage_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_ErrorMessage_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INewValveController_put_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_ValveOutputsIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_ValveOutputsIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_ValveOutputsIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_ValveOutputsIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_ValveOutputs_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_ValveOutputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_ValveOutputs_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INewValveController_put_ValveOutputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_JointAngles_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_JointAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_JointAngles_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INewValveController_put_JointAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_JointAnglesIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_JointAnglesIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_JointAnglesIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_JointAnglesIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_gain_PGainValue_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_gain_PGainValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_gain_PGainValue_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INewValveController_put_gain_PGainValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_gain_PGainValueIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_gain_PGainValueIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_gain_PGainValueIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_gain_PGainValueIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_NumOfSteps_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_NumOfSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_NumOfSteps_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_NumOfSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_rate_InflationRate_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_rate_InflationRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_rate_InflationRate_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_rate_InflationRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_rate_DeflationRate_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_rate_DeflationRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_rate_DeflationRate_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_rate_DeflationRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_gripper_OpenGripper_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_gripper_OpenGripper_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_gripper_CloseGripper_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_gripper_CloseGripper_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INewValveController_INTERFACE_DEFINED__ */



#ifndef __IMA2_NNET_N_PCONTROLLERLib_LIBRARY_DEFINED__
#define __IMA2_NNET_N_PCONTROLLERLib_LIBRARY_DEFINED__

/* library IMA2_NNET_N_PCONTROLLERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_NNET_N_PCONTROLLERLib;

EXTERN_C const CLSID CLSID_NewValveController;

#ifdef __cplusplus

class DECLSPEC_UUID("71645483-B459-4EEA-A355-B3F3D8A5748D")
NewValveController;
#endif
#endif /* __IMA2_NNET_N_PCONTROLLERLib_LIBRARY_DEFINED__ */

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
