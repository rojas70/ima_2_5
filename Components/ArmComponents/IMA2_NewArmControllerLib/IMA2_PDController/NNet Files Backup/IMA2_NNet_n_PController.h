/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 30 15:46:12 2008
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
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WhatArm( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PIDController( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoToHomePosition( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitializeValves( void) = 0;
        
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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadLogicalAngles( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogicalAngles( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogicalAngles( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LogicalAnglesIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LogicalAnglesIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetArmVoltages( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_P_LeftValue( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_P_LeftValue( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_P_RightValue( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_P_RightValue( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_P_LeftValueIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_P_LeftValueIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_P_RightValueIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_P_RightValueIndex( 
            /* [in] */ short newVal) = 0;
        
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
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WhatArm )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PIDController )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoToHomePosition )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitializeValves )( 
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadLogicalAngles )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogicalAngles )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogicalAngles )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LogicalAnglesIndex )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LogicalAnglesIndex )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetArmVoltages )( 
            INewValveController __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_P_LeftValue )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_P_LeftValue )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_P_RightValue )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_P_RightValue )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_P_LeftValueIndex )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_P_LeftValueIndex )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_P_RightValueIndex )( 
            INewValveController __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_P_RightValueIndex )( 
            INewValveController __RPC_FAR * This,
            /* [in] */ short newVal);
        
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

#define INewValveController_PIDController(This)	\
    (This)->lpVtbl -> PIDController(This)

#define INewValveController_GoToHomePosition(This)	\
    (This)->lpVtbl -> GoToHomePosition(This)

#define INewValveController_InitializeValves(This)	\
    (This)->lpVtbl -> InitializeValves(This)

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

#define INewValveController_ReadLogicalAngles(This)	\
    (This)->lpVtbl -> ReadLogicalAngles(This)

#define INewValveController_get_LogicalAngles(This,pVal)	\
    (This)->lpVtbl -> get_LogicalAngles(This,pVal)

#define INewValveController_put_LogicalAngles(This,newVal)	\
    (This)->lpVtbl -> put_LogicalAngles(This,newVal)

#define INewValveController_get_LogicalAnglesIndex(This,pVal)	\
    (This)->lpVtbl -> get_LogicalAnglesIndex(This,pVal)

#define INewValveController_put_LogicalAnglesIndex(This,newVal)	\
    (This)->lpVtbl -> put_LogicalAnglesIndex(This,newVal)

#define INewValveController_SetArmVoltages(This)	\
    (This)->lpVtbl -> SetArmVoltages(This)

#define INewValveController_get_P_LeftValue(This,pVal)	\
    (This)->lpVtbl -> get_P_LeftValue(This,pVal)

#define INewValveController_put_P_LeftValue(This,newVal)	\
    (This)->lpVtbl -> put_P_LeftValue(This,newVal)

#define INewValveController_get_P_RightValue(This,pVal)	\
    (This)->lpVtbl -> get_P_RightValue(This,pVal)

#define INewValveController_put_P_RightValue(This,newVal)	\
    (This)->lpVtbl -> put_P_RightValue(This,newVal)

#define INewValveController_get_P_LeftValueIndex(This,pVal)	\
    (This)->lpVtbl -> get_P_LeftValueIndex(This,pVal)

#define INewValveController_put_P_LeftValueIndex(This,newVal)	\
    (This)->lpVtbl -> put_P_LeftValueIndex(This,newVal)

#define INewValveController_get_P_RightValueIndex(This,pVal)	\
    (This)->lpVtbl -> get_P_RightValueIndex(This,pVal)

#define INewValveController_put_P_RightValueIndex(This,newVal)	\
    (This)->lpVtbl -> put_P_RightValueIndex(This,newVal)

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
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_WhatArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_WhatArm_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB INewValveController_put_WhatArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_PIDController_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_PIDController_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_GoToHomePosition_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_GoToHomePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_InitializeValves_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_InitializeValves_Stub(
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


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_ReadLogicalAngles_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_ReadLogicalAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_LogicalAngles_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_LogicalAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_LogicalAngles_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INewValveController_put_LogicalAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_LogicalAnglesIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_LogicalAnglesIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_LogicalAnglesIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_LogicalAnglesIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INewValveController_SetArmVoltages_Proxy( 
    INewValveController __RPC_FAR * This);


void __RPC_STUB INewValveController_SetArmVoltages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_P_LeftValue_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_P_LeftValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_P_LeftValue_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INewValveController_put_P_LeftValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_P_RightValue_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_P_RightValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_P_RightValue_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INewValveController_put_P_RightValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_P_LeftValueIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_P_LeftValueIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_P_LeftValueIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_P_LeftValueIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INewValveController_get_P_RightValueIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INewValveController_get_P_RightValueIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INewValveController_put_P_RightValueIndex_Proxy( 
    INewValveController __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB INewValveController_put_P_RightValueIndex_Stub(
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
