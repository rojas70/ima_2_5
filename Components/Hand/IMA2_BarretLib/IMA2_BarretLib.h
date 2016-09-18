/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 02 15:08:18 2006
 */
/* Compiler settings for O:\Components\Hand\IMA2_BarretLib\IMA2_BarretLib.idl:
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

#ifndef __IMA2_BarretLib_h__
#define __IMA2_BarretLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBarretComp_FWD_DEFINED__
#define __IBarretComp_FWD_DEFINED__
typedef interface IBarretComp IBarretComp;
#endif 	/* __IBarretComp_FWD_DEFINED__ */


#ifndef __BarretComp_FWD_DEFINED__
#define __BarretComp_FWD_DEFINED__

#ifdef __cplusplus
typedef class BarretComp BarretComp;
#else
typedef struct BarretComp BarretComp;
#endif /* __cplusplus */

#endif 	/* __BarretComp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBarretComp_INTERFACE_DEFINED__
#define __IBarretComp_INTERFACE_DEFINED__

/* interface IBarretComp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBarretComp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F38AA5F-6EDF-4841-8809-B42056B8B9FE")
    IBarretComp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HandParamter( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HandParamter( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StepSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StepSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoHome( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StepOpen( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StepClose( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoToPosition( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoToDefaultPosition( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Velocity( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Velocity( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StrainGauge( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultPosition( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultPosition( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParameterFlag( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ParameterFlag( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParameterValue( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ParameterValue( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _ThreeFingerGrasp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _ClosedHandGrasp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _IndexFingerPointing( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopMotors( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBarretCompVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBarretComp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBarretComp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBarretComp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HandParamter )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HandParamter )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StepSize )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StepSize )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoHome )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StepOpen )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StepClose )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoToPosition )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoToDefaultPosition )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Velocity )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Velocity )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StrainGauge )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultPosition )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultPosition )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParameterFlag )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ParameterFlag )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParameterValue )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ParameterValue )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            IBarretComp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            IBarretComp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_ThreeFingerGrasp )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_ClosedHandGrasp )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_IndexFingerPointing )( 
            IBarretComp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopMotors )( 
            IBarretComp __RPC_FAR * This);
        
        END_INTERFACE
    } IBarretCompVtbl;

    interface IBarretComp
    {
        CONST_VTBL struct IBarretCompVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBarretComp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBarretComp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBarretComp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBarretComp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBarretComp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBarretComp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBarretComp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBarretComp_get_HandParamter(This,pVal)	\
    (This)->lpVtbl -> get_HandParamter(This,pVal)

#define IBarretComp_put_HandParamter(This,newVal)	\
    (This)->lpVtbl -> put_HandParamter(This,newVal)

#define IBarretComp_get_StepSize(This,pVal)	\
    (This)->lpVtbl -> get_StepSize(This,pVal)

#define IBarretComp_put_StepSize(This,newVal)	\
    (This)->lpVtbl -> put_StepSize(This,newVal)

#define IBarretComp_Open(This)	\
    (This)->lpVtbl -> Open(This)

#define IBarretComp_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IBarretComp_GoHome(This)	\
    (This)->lpVtbl -> GoHome(This)

#define IBarretComp_StepOpen(This)	\
    (This)->lpVtbl -> StepOpen(This)

#define IBarretComp_StepClose(This)	\
    (This)->lpVtbl -> StepClose(This)

#define IBarretComp_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IBarretComp_GoToPosition(This)	\
    (This)->lpVtbl -> GoToPosition(This)

#define IBarretComp_GoToDefaultPosition(This)	\
    (This)->lpVtbl -> GoToDefaultPosition(This)

#define IBarretComp_get_Velocity(This,pVal)	\
    (This)->lpVtbl -> get_Velocity(This,pVal)

#define IBarretComp_put_Velocity(This,newVal)	\
    (This)->lpVtbl -> put_Velocity(This,newVal)

#define IBarretComp_get_StrainGauge(This,pVal)	\
    (This)->lpVtbl -> get_StrainGauge(This,pVal)

#define IBarretComp_get_DefaultPosition(This,pVal)	\
    (This)->lpVtbl -> get_DefaultPosition(This,pVal)

#define IBarretComp_put_DefaultPosition(This,newVal)	\
    (This)->lpVtbl -> put_DefaultPosition(This,newVal)

#define IBarretComp_get_ParameterFlag(This,pVal)	\
    (This)->lpVtbl -> get_ParameterFlag(This,pVal)

#define IBarretComp_put_ParameterFlag(This,newVal)	\
    (This)->lpVtbl -> put_ParameterFlag(This,newVal)

#define IBarretComp_Get(This)	\
    (This)->lpVtbl -> Get(This)

#define IBarretComp_Set(This)	\
    (This)->lpVtbl -> Set(This)

#define IBarretComp_get_ParameterValue(This,pVal)	\
    (This)->lpVtbl -> get_ParameterValue(This,pVal)

#define IBarretComp_put_ParameterValue(This,newVal)	\
    (This)->lpVtbl -> put_ParameterValue(This,newVal)

#define IBarretComp_get_Position(This,pVal)	\
    (This)->lpVtbl -> get_Position(This,pVal)

#define IBarretComp_put_Position(This,newVal)	\
    (This)->lpVtbl -> put_Position(This,newVal)

#define IBarretComp__ThreeFingerGrasp(This)	\
    (This)->lpVtbl -> _ThreeFingerGrasp(This)

#define IBarretComp__ClosedHandGrasp(This)	\
    (This)->lpVtbl -> _ClosedHandGrasp(This)

#define IBarretComp__IndexFingerPointing(This)	\
    (This)->lpVtbl -> _IndexFingerPointing(This)

#define IBarretComp_StopMotors(This)	\
    (This)->lpVtbl -> StopMotors(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_HandParamter_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_HandParamter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_HandParamter_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBarretComp_put_HandParamter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_StepSize_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_StepSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_StepSize_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBarretComp_put_StepSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_Open_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_Close_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_GoHome_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_GoHome_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_StepOpen_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_StepOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_StepClose_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_StepClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_Initialize_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_GoToPosition_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_GoToPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_GoToDefaultPosition_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_GoToDefaultPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_Velocity_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_Velocity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_Velocity_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBarretComp_put_Velocity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_StrainGauge_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_StrainGauge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_DefaultPosition_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_DefaultPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_DefaultPosition_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBarretComp_put_DefaultPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_ParameterFlag_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_ParameterFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_ParameterFlag_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBarretComp_put_ParameterFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_Get_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_Set_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_ParameterValue_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_ParameterValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_ParameterValue_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBarretComp_put_ParameterValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBarretComp_get_Position_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IBarretComp_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBarretComp_put_Position_Proxy( 
    IBarretComp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IBarretComp_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp__ThreeFingerGrasp_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp__ThreeFingerGrasp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp__ClosedHandGrasp_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp__ClosedHandGrasp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp__IndexFingerPointing_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp__IndexFingerPointing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBarretComp_StopMotors_Proxy( 
    IBarretComp __RPC_FAR * This);


void __RPC_STUB IBarretComp_StopMotors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBarretComp_INTERFACE_DEFINED__ */



#ifndef __IMA2_BARRETLIBLib_LIBRARY_DEFINED__
#define __IMA2_BARRETLIBLib_LIBRARY_DEFINED__

/* library IMA2_BARRETLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_BARRETLIBLib;

EXTERN_C const CLSID CLSID_BarretComp;

#ifdef __cplusplus

class DECLSPEC_UUID("EA74A33A-60F9-4CBE-828D-C13A9B700A33")
BarretComp;
#endif
#endif /* __IMA2_BARRETLIBLib_LIBRARY_DEFINED__ */

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
