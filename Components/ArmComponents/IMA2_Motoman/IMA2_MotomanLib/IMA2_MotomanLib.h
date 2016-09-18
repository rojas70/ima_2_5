/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 09 22:55:31 2009
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_Motoman\IMA2_MotomanLib\IMA2_MotomanLib.idl:
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

#ifndef __IMA2_MotomanLib_h__
#define __IMA2_MotomanLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IHP3JC_FWD_DEFINED__
#define __IHP3JC_FWD_DEFINED__
typedef interface IHP3JC IHP3JC;
#endif 	/* __IHP3JC_FWD_DEFINED__ */


#ifndef __HP3JC_FWD_DEFINED__
#define __HP3JC_FWD_DEFINED__

#ifdef __cplusplus
typedef class HP3JC HP3JC;
#else
typedef struct HP3JC HP3JC;
#endif /* __cplusplus */

#endif 	/* __HP3JC_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IHP3JC_INTERFACE_DEFINED__
#define __IHP3JC_INTERFACE_DEFINED__

/* interface IHP3JC */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHP3JC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0BF23BE8-DE51-4716-B3DE-CCDF0F35ADEC")
    IHP3JC : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE connect_Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE move_Incremental( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE move_UsersChoice( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE connect_Disconnect( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ErrorMessage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MotionType( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MotionType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Speed( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Speed( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndToolForm( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EndToolForm( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE move_LinearMotion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE move_JointMotion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE move_JointAngles( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE read_CurrentPosition( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_read_PositionType( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_read_PositionType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE servo_ServoOn( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE servo_ServoOff( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE error_GetError( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE error_ClearError( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE error_GetAlarm( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE error_ClearAlarm( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE job_SelectJob( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE job_StartJob( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JobName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_JobName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE job_CopyTextQueue( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToolType( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ToolType( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHP3JCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHP3JC __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHP3JC __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHP3JC __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *connect_Initialize )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *move_Incremental )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *move_UsersChoice )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *connect_Disconnect )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorMessage )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErrorMessage )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MotionType )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MotionType )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speed )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Speed )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndToolForm )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EndToolForm )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *move_LinearMotion )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *move_JointMotion )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *move_JointAngles )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *read_CurrentPosition )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_read_PositionType )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_read_PositionType )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *servo_ServoOn )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *servo_ServoOff )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *error_GetError )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *error_ClearError )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *error_GetAlarm )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *error_ClearAlarm )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *job_SelectJob )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *job_StartJob )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_JobName )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_JobName )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *job_CopyTextQueue )( 
            IHP3JC __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToolType )( 
            IHP3JC __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ToolType )( 
            IHP3JC __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IHP3JCVtbl;

    interface IHP3JC
    {
        CONST_VTBL struct IHP3JCVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHP3JC_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHP3JC_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHP3JC_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHP3JC_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHP3JC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHP3JC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHP3JC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IHP3JC_connect_Initialize(This)	\
    (This)->lpVtbl -> connect_Initialize(This)

#define IHP3JC_move_Incremental(This)	\
    (This)->lpVtbl -> move_Incremental(This)

#define IHP3JC_move_UsersChoice(This)	\
    (This)->lpVtbl -> move_UsersChoice(This)

#define IHP3JC_connect_Disconnect(This)	\
    (This)->lpVtbl -> connect_Disconnect(This)

#define IHP3JC_get_ErrorMessage(This,pVal)	\
    (This)->lpVtbl -> get_ErrorMessage(This,pVal)

#define IHP3JC_put_ErrorMessage(This,newVal)	\
    (This)->lpVtbl -> put_ErrorMessage(This,newVal)

#define IHP3JC_get_MotionType(This,pVal)	\
    (This)->lpVtbl -> get_MotionType(This,pVal)

#define IHP3JC_put_MotionType(This,newVal)	\
    (This)->lpVtbl -> put_MotionType(This,newVal)

#define IHP3JC_get_Speed(This,pVal)	\
    (This)->lpVtbl -> get_Speed(This,pVal)

#define IHP3JC_put_Speed(This,newVal)	\
    (This)->lpVtbl -> put_Speed(This,newVal)

#define IHP3JC_get_EndToolForm(This,pVal)	\
    (This)->lpVtbl -> get_EndToolForm(This,pVal)

#define IHP3JC_put_EndToolForm(This,newVal)	\
    (This)->lpVtbl -> put_EndToolForm(This,newVal)

#define IHP3JC_move_LinearMotion(This)	\
    (This)->lpVtbl -> move_LinearMotion(This)

#define IHP3JC_move_JointMotion(This)	\
    (This)->lpVtbl -> move_JointMotion(This)

#define IHP3JC_move_JointAngles(This)	\
    (This)->lpVtbl -> move_JointAngles(This)

#define IHP3JC_read_CurrentPosition(This)	\
    (This)->lpVtbl -> read_CurrentPosition(This)

#define IHP3JC_get_read_PositionType(This,pVal)	\
    (This)->lpVtbl -> get_read_PositionType(This,pVal)

#define IHP3JC_put_read_PositionType(This,newVal)	\
    (This)->lpVtbl -> put_read_PositionType(This,newVal)

#define IHP3JC_servo_ServoOn(This)	\
    (This)->lpVtbl -> servo_ServoOn(This)

#define IHP3JC_servo_ServoOff(This)	\
    (This)->lpVtbl -> servo_ServoOff(This)

#define IHP3JC_error_GetError(This)	\
    (This)->lpVtbl -> error_GetError(This)

#define IHP3JC_error_ClearError(This)	\
    (This)->lpVtbl -> error_ClearError(This)

#define IHP3JC_error_GetAlarm(This)	\
    (This)->lpVtbl -> error_GetAlarm(This)

#define IHP3JC_error_ClearAlarm(This)	\
    (This)->lpVtbl -> error_ClearAlarm(This)

#define IHP3JC_job_SelectJob(This)	\
    (This)->lpVtbl -> job_SelectJob(This)

#define IHP3JC_job_StartJob(This)	\
    (This)->lpVtbl -> job_StartJob(This)

#define IHP3JC_get_JobName(This,pVal)	\
    (This)->lpVtbl -> get_JobName(This,pVal)

#define IHP3JC_put_JobName(This,newVal)	\
    (This)->lpVtbl -> put_JobName(This,newVal)

#define IHP3JC_job_CopyTextQueue(This)	\
    (This)->lpVtbl -> job_CopyTextQueue(This)

#define IHP3JC_get_ToolType(This,pVal)	\
    (This)->lpVtbl -> get_ToolType(This,pVal)

#define IHP3JC_put_ToolType(This,newVal)	\
    (This)->lpVtbl -> put_ToolType(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_connect_Initialize_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_connect_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_move_Incremental_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_move_Incremental_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_move_UsersChoice_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_move_UsersChoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_connect_Disconnect_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_connect_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_ErrorMessage_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_ErrorMessage_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHP3JC_put_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_MotionType_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_MotionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_MotionType_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHP3JC_put_MotionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_Speed_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_Speed_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IHP3JC_put_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_EndToolForm_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_EndToolForm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_EndToolForm_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IHP3JC_put_EndToolForm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_move_LinearMotion_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_move_LinearMotion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_move_JointMotion_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_move_JointMotion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_move_JointAngles_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_move_JointAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_read_CurrentPosition_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_read_CurrentPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_read_PositionType_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_read_PositionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_read_PositionType_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHP3JC_put_read_PositionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_servo_ServoOn_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_servo_ServoOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_servo_ServoOff_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_servo_ServoOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_error_GetError_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_error_GetError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_error_ClearError_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_error_ClearError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_error_GetAlarm_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_error_GetAlarm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_error_ClearAlarm_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_error_ClearAlarm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_job_SelectJob_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_job_SelectJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_job_StartJob_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_job_StartJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_JobName_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_JobName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_JobName_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHP3JC_put_JobName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHP3JC_job_CopyTextQueue_Proxy( 
    IHP3JC __RPC_FAR * This);


void __RPC_STUB IHP3JC_job_CopyTextQueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHP3JC_get_ToolType_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHP3JC_get_ToolType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHP3JC_put_ToolType_Proxy( 
    IHP3JC __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHP3JC_put_ToolType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHP3JC_INTERFACE_DEFINED__ */



#ifndef __IMA2_MOTOMANLIBLib_LIBRARY_DEFINED__
#define __IMA2_MOTOMANLIBLib_LIBRARY_DEFINED__

/* library IMA2_MOTOMANLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_MOTOMANLIBLib;

EXTERN_C const CLSID CLSID_HP3JC;

#ifdef __cplusplus

class DECLSPEC_UUID("898C35A9-D83C-4354-B2FE-4E9FDE00C464")
HP3JC;
#endif
#endif /* __IMA2_MOTOMANLIBLib_LIBRARY_DEFINED__ */

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
