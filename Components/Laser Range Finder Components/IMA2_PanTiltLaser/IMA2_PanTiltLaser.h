/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 16 14:05:56 2006
 */
/* Compiler settings for O:\Components\Lase Range Finder Components\IMA2_PanTiltLaser\IMA2_PanTiltLaser.idl:
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

#ifndef __IMA2_PanTiltLaser_h__
#define __IMA2_PanTiltLaser_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPanTiltUnit_FWD_DEFINED__
#define __IPanTiltUnit_FWD_DEFINED__
typedef interface IPanTiltUnit IPanTiltUnit;
#endif 	/* __IPanTiltUnit_FWD_DEFINED__ */


#ifndef __PanTiltUnit_FWD_DEFINED__
#define __PanTiltUnit_FWD_DEFINED__

#ifdef __cplusplus
typedef class PanTiltUnit PanTiltUnit;
#else
typedef struct PanTiltUnit PanTiltUnit;
#endif /* __cplusplus */

#endif 	/* __PanTiltUnit_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPanTiltUnit_INTERFACE_DEFINED__
#define __IPanTiltUnit_INTERFACE_DEFINED__

/* interface IPanTiltUnit */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPanTiltUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4AB809D-38CB-439D-AE91-93CB6C1AEC46")
    IPanTiltUnit : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitLaser( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HomeLaser( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetLaser( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Scan( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPanTiltUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPanTiltUnit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPanTiltUnit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPanTiltUnit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPanTiltUnit __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPanTiltUnit __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPanTiltUnit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPanTiltUnit __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitLaser )( 
            IPanTiltUnit __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HomeLaser )( 
            IPanTiltUnit __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetLaser )( 
            IPanTiltUnit __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scan )( 
            IPanTiltUnit __RPC_FAR * This);
        
        END_INTERFACE
    } IPanTiltUnitVtbl;

    interface IPanTiltUnit
    {
        CONST_VTBL struct IPanTiltUnitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPanTiltUnit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPanTiltUnit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPanTiltUnit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPanTiltUnit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPanTiltUnit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPanTiltUnit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPanTiltUnit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPanTiltUnit_InitLaser(This)	\
    (This)->lpVtbl -> InitLaser(This)

#define IPanTiltUnit_HomeLaser(This)	\
    (This)->lpVtbl -> HomeLaser(This)

#define IPanTiltUnit_ResetLaser(This)	\
    (This)->lpVtbl -> ResetLaser(This)

#define IPanTiltUnit_Scan(This)	\
    (This)->lpVtbl -> Scan(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPanTiltUnit_InitLaser_Proxy( 
    IPanTiltUnit __RPC_FAR * This);


void __RPC_STUB IPanTiltUnit_InitLaser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPanTiltUnit_HomeLaser_Proxy( 
    IPanTiltUnit __RPC_FAR * This);


void __RPC_STUB IPanTiltUnit_HomeLaser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPanTiltUnit_ResetLaser_Proxy( 
    IPanTiltUnit __RPC_FAR * This);


void __RPC_STUB IPanTiltUnit_ResetLaser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPanTiltUnit_Scan_Proxy( 
    IPanTiltUnit __RPC_FAR * This);


void __RPC_STUB IPanTiltUnit_Scan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPanTiltUnit_INTERFACE_DEFINED__ */



#ifndef __IMA2_PANTILTLASERLib_LIBRARY_DEFINED__
#define __IMA2_PANTILTLASERLib_LIBRARY_DEFINED__

/* library IMA2_PANTILTLASERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_PANTILTLASERLib;

EXTERN_C const CLSID CLSID_PanTiltUnit;

#ifdef __cplusplus

class DECLSPEC_UUID("B87BF833-C75F-494C-B44A-67ABD75840E2")
PanTiltUnit;
#endif
#endif /* __IMA2_PANTILTLASERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
