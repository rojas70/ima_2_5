/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 18 21:56:32 2009
 */
/* Compiler settings for O:\Components\ControlBasis\IMA2_VirtualContactLib\IMA2_VirtualContactLib.idl:
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

#ifndef __IMA2_VirtualContactLib_h__
#define __IMA2_VirtualContactLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IISAC_Assembly_FWD_DEFINED__
#define __IISAC_Assembly_FWD_DEFINED__
typedef interface IISAC_Assembly IISAC_Assembly;
#endif 	/* __IISAC_Assembly_FWD_DEFINED__ */


#ifndef __ISAC_Assembly_FWD_DEFINED__
#define __ISAC_Assembly_FWD_DEFINED__

#ifdef __cplusplus
typedef class ISAC_Assembly ISAC_Assembly;
#else
typedef struct ISAC_Assembly ISAC_Assembly;
#endif /* __cplusplus */

#endif 	/* __ISAC_Assembly_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IISAC_Assembly_INTERFACE_DEFINED__
#define __IISAC_Assembly_INTERFACE_DEFINED__

/* interface IISAC_Assembly */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IISAC_Assembly;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33CCC6E1-9887-4140-8A2D-ADA138AA9DF0")
    IISAC_Assembly : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AverageValues( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IISAC_AssemblyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IISAC_Assembly __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IISAC_Assembly __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IISAC_Assembly __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IISAC_Assembly __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IISAC_Assembly __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IISAC_Assembly __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IISAC_Assembly __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AverageValues )( 
            IISAC_Assembly __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IISAC_Assembly __RPC_FAR * This);
        
        END_INTERFACE
    } IISAC_AssemblyVtbl;

    interface IISAC_Assembly
    {
        CONST_VTBL struct IISAC_AssemblyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IISAC_Assembly_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IISAC_Assembly_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IISAC_Assembly_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IISAC_Assembly_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IISAC_Assembly_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IISAC_Assembly_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IISAC_Assembly_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IISAC_Assembly_AverageValues(This)	\
    (This)->lpVtbl -> AverageValues(This)

#define IISAC_Assembly_Close(This)	\
    (This)->lpVtbl -> Close(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IISAC_Assembly_AverageValues_Proxy( 
    IISAC_Assembly __RPC_FAR * This);


void __RPC_STUB IISAC_Assembly_AverageValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IISAC_Assembly_Close_Proxy( 
    IISAC_Assembly __RPC_FAR * This);


void __RPC_STUB IISAC_Assembly_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IISAC_Assembly_INTERFACE_DEFINED__ */



#ifndef __IMA2_VIRTUALCONTACTLIBLib_LIBRARY_DEFINED__
#define __IMA2_VIRTUALCONTACTLIBLib_LIBRARY_DEFINED__

/* library IMA2_VIRTUALCONTACTLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_VIRTUALCONTACTLIBLib;

EXTERN_C const CLSID CLSID_ISAC_Assembly;

#ifdef __cplusplus

class DECLSPEC_UUID("74FEEC9C-4F27-44B7-B837-964E34201573")
ISAC_Assembly;
#endif
#endif /* __IMA2_VIRTUALCONTACTLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
