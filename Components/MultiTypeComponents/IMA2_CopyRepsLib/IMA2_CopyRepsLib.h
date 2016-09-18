/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 02 10:34:45 2009
 */
/* Compiler settings for O:\Components\MultiTypeComponents\IMA2_CopyRepsLib\IMA2_CopyRepsLib.idl:
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

#ifndef __IMA2_CopyRepsLib_h__
#define __IMA2_CopyRepsLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICopyVS_FWD_DEFINED__
#define __ICopyVS_FWD_DEFINED__
typedef interface ICopyVS ICopyVS;
#endif 	/* __ICopyVS_FWD_DEFINED__ */


#ifndef __CopyVS_FWD_DEFINED__
#define __CopyVS_FWD_DEFINED__

#ifdef __cplusplus
typedef class CopyVS CopyVS;
#else
typedef struct CopyVS CopyVS;
#endif /* __cplusplus */

#endif 	/* __CopyVS_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICopyVS_INTERFACE_DEFINED__
#define __ICopyVS_INTERFACE_DEFINED__

/* interface ICopyVS */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICopyVS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1BA00A2-E646-457F-B391-04C988B00B67")
    ICopyVS : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyVectorSignal( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyRowVector( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputRowVector( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputRowVector( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputRowVector( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputRowVector( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyCurrentVector( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICopyVSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICopyVS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICopyVS __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICopyVS __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICopyVS __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICopyVS __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICopyVS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICopyVS __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyVectorSignal )( 
            ICopyVS __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyRowVector )( 
            ICopyVS __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputRowVector )( 
            ICopyVS __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputRowVector )( 
            ICopyVS __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputRowVector )( 
            ICopyVS __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputRowVector )( 
            ICopyVS __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyCurrentVector )( 
            ICopyVS __RPC_FAR * This);
        
        END_INTERFACE
    } ICopyVSVtbl;

    interface ICopyVS
    {
        CONST_VTBL struct ICopyVSVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICopyVS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICopyVS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICopyVS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICopyVS_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICopyVS_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICopyVS_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICopyVS_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICopyVS_CopyVectorSignal(This)	\
    (This)->lpVtbl -> CopyVectorSignal(This)

#define ICopyVS_CopyRowVector(This)	\
    (This)->lpVtbl -> CopyRowVector(This)

#define ICopyVS_get_InputRowVector(This,pVal)	\
    (This)->lpVtbl -> get_InputRowVector(This,pVal)

#define ICopyVS_put_InputRowVector(This,newVal)	\
    (This)->lpVtbl -> put_InputRowVector(This,newVal)

#define ICopyVS_get_OutputRowVector(This,pVal)	\
    (This)->lpVtbl -> get_OutputRowVector(This,pVal)

#define ICopyVS_put_OutputRowVector(This,newVal)	\
    (This)->lpVtbl -> put_OutputRowVector(This,newVal)

#define ICopyVS_CopyCurrentVector(This)	\
    (This)->lpVtbl -> CopyCurrentVector(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICopyVS_CopyVectorSignal_Proxy( 
    ICopyVS __RPC_FAR * This);


void __RPC_STUB ICopyVS_CopyVectorSignal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICopyVS_CopyRowVector_Proxy( 
    ICopyVS __RPC_FAR * This);


void __RPC_STUB ICopyVS_CopyRowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICopyVS_get_InputRowVector_Proxy( 
    ICopyVS __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ICopyVS_get_InputRowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICopyVS_put_InputRowVector_Proxy( 
    ICopyVS __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ICopyVS_put_InputRowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICopyVS_get_OutputRowVector_Proxy( 
    ICopyVS __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ICopyVS_get_OutputRowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICopyVS_put_OutputRowVector_Proxy( 
    ICopyVS __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB ICopyVS_put_OutputRowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICopyVS_CopyCurrentVector_Proxy( 
    ICopyVS __RPC_FAR * This);


void __RPC_STUB ICopyVS_CopyCurrentVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICopyVS_INTERFACE_DEFINED__ */



#ifndef __IMA2_COPYREPSLIBLib_LIBRARY_DEFINED__
#define __IMA2_COPYREPSLIBLib_LIBRARY_DEFINED__

/* library IMA2_COPYREPSLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_COPYREPSLIBLib;

EXTERN_C const CLSID CLSID_CopyVS;

#ifdef __cplusplus

class DECLSPEC_UUID("2B5BD3BD-6332-47DF-A73E-A80A486E5567")
CopyVS;
#endif
#endif /* __IMA2_COPYREPSLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
