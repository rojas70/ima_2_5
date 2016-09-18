/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 08 16:06:30 2006
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_TrajectoryLib\IMA2_TrajectoryLib.idl:
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

#ifndef __IMA2_TrajectoryLib_h__
#define __IMA2_TrajectoryLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITrajectoryGen_FWD_DEFINED__
#define __ITrajectoryGen_FWD_DEFINED__
typedef interface ITrajectoryGen ITrajectoryGen;
#endif 	/* __ITrajectoryGen_FWD_DEFINED__ */


#ifndef __ITrajectoryPlayer_FWD_DEFINED__
#define __ITrajectoryPlayer_FWD_DEFINED__
typedef interface ITrajectoryPlayer ITrajectoryPlayer;
#endif 	/* __ITrajectoryPlayer_FWD_DEFINED__ */


#ifndef __TrajectoryGen_FWD_DEFINED__
#define __TrajectoryGen_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrajectoryGen TrajectoryGen;
#else
typedef struct TrajectoryGen TrajectoryGen;
#endif /* __cplusplus */

#endif 	/* __TrajectoryGen_FWD_DEFINED__ */


#ifndef __TrajectoryPlayer_FWD_DEFINED__
#define __TrajectoryPlayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrajectoryPlayer TrajectoryPlayer;
#else
typedef struct TrajectoryPlayer TrajectoryPlayer;
#endif /* __cplusplus */

#endif 	/* __TrajectoryPlayer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITrajectoryGen_INTERFACE_DEFINED__
#define __ITrajectoryGen_INTERFACE_DEFINED__

/* interface ITrajectoryGen */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITrajectoryGen;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54E33F6C-B988-44FE-AEEF-4E233DAFD31B")
    ITrajectoryGen : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumElements( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumElements( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumSteps( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumSteps( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TravelPeriod( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TravelPeriod( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumberTrajectoryPoints( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumberTrajectoryPoints( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartTime( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TravelPeriodIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TravelPeriodIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumStepsIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumStepsIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateTrajectory( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckForObject( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SegmentedPixelThreshold( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SegmentedPixelThreshold( 
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrajectoryGenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrajectoryGen __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrajectoryGen __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumElements )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumElements )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumSteps )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumSteps )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TravelPeriod )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TravelPeriod )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberTrajectoryPoints )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumberTrajectoryPoints )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartTime )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputFile )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputFile )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TravelPeriodIndex )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TravelPeriodIndex )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumStepsIndex )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumStepsIndex )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateTrajectory )( 
            ITrajectoryGen __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckForObject )( 
            ITrajectoryGen __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SegmentedPixelThreshold )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SegmentedPixelThreshold )( 
            ITrajectoryGen __RPC_FAR * This,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } ITrajectoryGenVtbl;

    interface ITrajectoryGen
    {
        CONST_VTBL struct ITrajectoryGenVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrajectoryGen_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrajectoryGen_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrajectoryGen_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrajectoryGen_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITrajectoryGen_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITrajectoryGen_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITrajectoryGen_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITrajectoryGen_get_NumElements(This,pVal)	\
    (This)->lpVtbl -> get_NumElements(This,pVal)

#define ITrajectoryGen_put_NumElements(This,newVal)	\
    (This)->lpVtbl -> put_NumElements(This,newVal)

#define ITrajectoryGen_get_NumSteps(This,pVal)	\
    (This)->lpVtbl -> get_NumSteps(This,pVal)

#define ITrajectoryGen_put_NumSteps(This,newVal)	\
    (This)->lpVtbl -> put_NumSteps(This,newVal)

#define ITrajectoryGen_get_TravelPeriod(This,pVal)	\
    (This)->lpVtbl -> get_TravelPeriod(This,pVal)

#define ITrajectoryGen_put_TravelPeriod(This,newVal)	\
    (This)->lpVtbl -> put_TravelPeriod(This,newVal)

#define ITrajectoryGen_get_NumberTrajectoryPoints(This,pVal)	\
    (This)->lpVtbl -> get_NumberTrajectoryPoints(This,pVal)

#define ITrajectoryGen_put_NumberTrajectoryPoints(This,newVal)	\
    (This)->lpVtbl -> put_NumberTrajectoryPoints(This,newVal)

#define ITrajectoryGen_get_StartTime(This,pVal)	\
    (This)->lpVtbl -> get_StartTime(This,pVal)

#define ITrajectoryGen_put_StartTime(This,newVal)	\
    (This)->lpVtbl -> put_StartTime(This,newVal)

#define ITrajectoryGen_get_OutputFile(This,pVal)	\
    (This)->lpVtbl -> get_OutputFile(This,pVal)

#define ITrajectoryGen_put_OutputFile(This,newVal)	\
    (This)->lpVtbl -> put_OutputFile(This,newVal)

#define ITrajectoryGen_get_TravelPeriodIndex(This,pVal)	\
    (This)->lpVtbl -> get_TravelPeriodIndex(This,pVal)

#define ITrajectoryGen_put_TravelPeriodIndex(This,newVal)	\
    (This)->lpVtbl -> put_TravelPeriodIndex(This,newVal)

#define ITrajectoryGen_get_NumStepsIndex(This,pVal)	\
    (This)->lpVtbl -> get_NumStepsIndex(This,pVal)

#define ITrajectoryGen_put_NumStepsIndex(This,newVal)	\
    (This)->lpVtbl -> put_NumStepsIndex(This,newVal)

#define ITrajectoryGen_GenerateTrajectory(This)	\
    (This)->lpVtbl -> GenerateTrajectory(This)

#define ITrajectoryGen_CheckForObject(This)	\
    (This)->lpVtbl -> CheckForObject(This)

#define ITrajectoryGen_get_SegmentedPixelThreshold(This,pVal)	\
    (This)->lpVtbl -> get_SegmentedPixelThreshold(This,pVal)

#define ITrajectoryGen_put_SegmentedPixelThreshold(This,newVal)	\
    (This)->lpVtbl -> put_SegmentedPixelThreshold(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_NumElements_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_NumElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_NumElements_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITrajectoryGen_put_NumElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_NumSteps_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_NumSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_NumSteps_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITrajectoryGen_put_NumSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_TravelPeriod_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_TravelPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_TravelPeriod_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ITrajectoryGen_put_TravelPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_NumberTrajectoryPoints_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_NumberTrajectoryPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_NumberTrajectoryPoints_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITrajectoryGen_put_NumberTrajectoryPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_StartTime_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_StartTime_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ITrajectoryGen_put_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_OutputFile_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_OutputFile_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITrajectoryGen_put_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_TravelPeriodIndex_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_TravelPeriodIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_TravelPeriodIndex_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ITrajectoryGen_put_TravelPeriodIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_NumStepsIndex_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_NumStepsIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_NumStepsIndex_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ITrajectoryGen_put_NumStepsIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_GenerateTrajectory_Proxy( 
    ITrajectoryGen __RPC_FAR * This);


void __RPC_STUB ITrajectoryGen_GenerateTrajectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_CheckForObject_Proxy( 
    ITrajectoryGen __RPC_FAR * This);


void __RPC_STUB ITrajectoryGen_CheckForObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_get_SegmentedPixelThreshold_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryGen_get_SegmentedPixelThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryGen_put_SegmentedPixelThreshold_Proxy( 
    ITrajectoryGen __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB ITrajectoryGen_put_SegmentedPixelThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrajectoryGen_INTERFACE_DEFINED__ */


#ifndef __ITrajectoryPlayer_INTERFACE_DEFINED__
#define __ITrajectoryPlayer_INTERFACE_DEFINED__

/* interface ITrajectoryPlayer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITrajectoryPlayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0049F005-9129-4E2D-8B0B-1F95F409A31B")
    ITrajectoryPlayer : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OutputTrajectory( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumAxes( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumAxes( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrajectoryPlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrajectoryPlayer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrajectoryPlayer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OutputTrajectory )( 
            ITrajectoryPlayer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ITrajectoryPlayer __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumAxes )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumAxes )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            ITrajectoryPlayer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ITrajectoryPlayerVtbl;

    interface ITrajectoryPlayer
    {
        CONST_VTBL struct ITrajectoryPlayerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrajectoryPlayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrajectoryPlayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrajectoryPlayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrajectoryPlayer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITrajectoryPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITrajectoryPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITrajectoryPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITrajectoryPlayer_OutputTrajectory(This)	\
    (This)->lpVtbl -> OutputTrajectory(This)

#define ITrajectoryPlayer_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define ITrajectoryPlayer_get_NumAxes(This,pVal)	\
    (This)->lpVtbl -> get_NumAxes(This,pVal)

#define ITrajectoryPlayer_put_NumAxes(This,newVal)	\
    (This)->lpVtbl -> put_NumAxes(This,newVal)

#define ITrajectoryPlayer_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define ITrajectoryPlayer_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITrajectoryPlayer_OutputTrajectory_Proxy( 
    ITrajectoryPlayer __RPC_FAR * This);


void __RPC_STUB ITrajectoryPlayer_OutputTrajectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITrajectoryPlayer_Initialize_Proxy( 
    ITrajectoryPlayer __RPC_FAR * This);


void __RPC_STUB ITrajectoryPlayer_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryPlayer_get_NumAxes_Proxy( 
    ITrajectoryPlayer __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryPlayer_get_NumAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryPlayer_put_NumAxes_Proxy( 
    ITrajectoryPlayer __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITrajectoryPlayer_put_NumAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITrajectoryPlayer_get_FileName_Proxy( 
    ITrajectoryPlayer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITrajectoryPlayer_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITrajectoryPlayer_put_FileName_Proxy( 
    ITrajectoryPlayer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITrajectoryPlayer_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrajectoryPlayer_INTERFACE_DEFINED__ */



#ifndef __IMA2_TRAJECTORYLIBLib_LIBRARY_DEFINED__
#define __IMA2_TRAJECTORYLIBLib_LIBRARY_DEFINED__

/* library IMA2_TRAJECTORYLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_TRAJECTORYLIBLib;

EXTERN_C const CLSID CLSID_TrajectoryGen;

#ifdef __cplusplus

class DECLSPEC_UUID("A8F3D778-0ABA-44A3-89E2-075F8EEA048B")
TrajectoryGen;
#endif

EXTERN_C const CLSID CLSID_TrajectoryPlayer;

#ifdef __cplusplus

class DECLSPEC_UUID("928A762F-F18E-4447-91C4-71B2E1338A3B")
TrajectoryPlayer;
#endif
#endif /* __IMA2_TRAJECTORYLIBLib_LIBRARY_DEFINED__ */

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
