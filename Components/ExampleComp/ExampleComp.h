/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 20 14:50:14 2006
 */
/* Compiler settings for O:\Components\ExampleComp\ExampleComp.idl:
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

#ifndef __ExampleComp_h__
#define __ExampleComp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IExample_FWD_DEFINED__
#define __IExample_FWD_DEFINED__
typedef interface IExample IExample;
#endif 	/* __IExample_FWD_DEFINED__ */


#ifndef __Example_FWD_DEFINED__
#define __Example_FWD_DEFINED__

#ifdef __cplusplus
typedef class Example Example;
#else
typedef struct Example Example;
#endif /* __cplusplus */

#endif 	/* __Example_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IExample_INTERFACE_DEFINED__
#define __IExample_INTERFACE_DEFINED__

/* interface IExample */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F976D99B-D347-4DCD-A4F9-A266BA8AF739")
    IExample : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectingToComponent( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExample __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExample __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExample __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectingToComponent )( 
            IExample __RPC_FAR * This);
        
        END_INTERFACE
    } IExampleVtbl;

    interface IExample
    {
        CONST_VTBL struct IExampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExample_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExample_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExample_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExample_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExample_ConnectingToComponent(This)	\
    (This)->lpVtbl -> ConnectingToComponent(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IExample_ConnectingToComponent_Proxy( 
    IExample __RPC_FAR * This);


void __RPC_STUB IExample_ConnectingToComponent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExample_INTERFACE_DEFINED__ */



#ifndef __EXAMPLECOMPLib_LIBRARY_DEFINED__
#define __EXAMPLECOMPLib_LIBRARY_DEFINED__

/* library EXAMPLECOMPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EXAMPLECOMPLib;

EXTERN_C const CLSID CLSID_Example;

#ifdef __cplusplus

class DECLSPEC_UUID("BCB67108-F739-4B9C-BD9C-BAC1703A077D")
Example;
#endif
#endif /* __EXAMPLECOMPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
