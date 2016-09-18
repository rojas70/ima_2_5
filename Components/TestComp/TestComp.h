/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 16 14:32:58 2006
 */
/* Compiler settings for O:\Components\TestComp\TestComp.idl:
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

#ifndef __TestComp_h__
#define __TestComp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITesting123_FWD_DEFINED__
#define __ITesting123_FWD_DEFINED__
typedef interface ITesting123 ITesting123;
#endif 	/* __ITesting123_FWD_DEFINED__ */


#ifndef __Testing123_FWD_DEFINED__
#define __Testing123_FWD_DEFINED__

#ifdef __cplusplus
typedef class Testing123 Testing123;
#else
typedef struct Testing123 Testing123;
#endif /* __cplusplus */

#endif 	/* __Testing123_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITesting123_INTERFACE_DEFINED__
#define __ITesting123_INTERFACE_DEFINED__

/* interface ITesting123 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITesting123;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("493FC2A5-FD98-451C-8740-94A8532AD281")
    ITesting123 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendDouble( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITesting123Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITesting123 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITesting123 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITesting123 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITesting123 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITesting123 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITesting123 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITesting123 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDouble )( 
            ITesting123 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * Data);
        
        END_INTERFACE
    } ITesting123Vtbl;

    interface ITesting123
    {
        CONST_VTBL struct ITesting123Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITesting123_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITesting123_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITesting123_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITesting123_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITesting123_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITesting123_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITesting123_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITesting123_SendDouble(This,Data)	\
    (This)->lpVtbl -> SendDouble(This,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITesting123_SendDouble_Proxy( 
    ITesting123 __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * Data);


void __RPC_STUB ITesting123_SendDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITesting123_INTERFACE_DEFINED__ */



#ifndef __TESTCOMPLib_LIBRARY_DEFINED__
#define __TESTCOMPLib_LIBRARY_DEFINED__

/* library TESTCOMPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TESTCOMPLib;

EXTERN_C const CLSID CLSID_Testing123;

#ifdef __cplusplus

class DECLSPEC_UUID("DF45426C-5436-4EB1-B01E-D1DB7235AC3E")
Testing123;
#endif
#endif /* __TESTCOMPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
