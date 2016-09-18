/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 03 13:17:44 2008
 */
/* Compiler settings for O:\Components\HeadComponents\IMA2_3DPositionLib\IMA2_3DPositionLib.idl:
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

#ifndef __IMA2_3DPositionLib_h__
#define __IMA2_3DPositionLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IComputePosition_FWD_DEFINED__
#define __IComputePosition_FWD_DEFINED__
typedef interface IComputePosition IComputePosition;
#endif 	/* __IComputePosition_FWD_DEFINED__ */


#ifndef __ComputePosition_FWD_DEFINED__
#define __ComputePosition_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComputePosition ComputePosition;
#else
typedef struct ComputePosition ComputePosition;
#endif /* __cplusplus */

#endif 	/* __ComputePosition_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IComputePosition_INTERFACE_DEFINED__
#define __IComputePosition_INTERFACE_DEFINED__

/* interface IComputePosition */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IComputePosition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF19C9A8-1DB2-45A2-9A5E-15CC7874DCE0")
    IComputePosition : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindCartesianCoordinates( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComputePositionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IComputePosition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IComputePosition __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IComputePosition __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IComputePosition __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IComputePosition __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IComputePosition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IComputePosition __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindCartesianCoordinates )( 
            IComputePosition __RPC_FAR * This);
        
        END_INTERFACE
    } IComputePositionVtbl;

    interface IComputePosition
    {
        CONST_VTBL struct IComputePositionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComputePosition_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComputePosition_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComputePosition_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComputePosition_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComputePosition_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComputePosition_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComputePosition_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComputePosition_FindCartesianCoordinates(This)	\
    (This)->lpVtbl -> FindCartesianCoordinates(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComputePosition_FindCartesianCoordinates_Proxy( 
    IComputePosition __RPC_FAR * This);


void __RPC_STUB IComputePosition_FindCartesianCoordinates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComputePosition_INTERFACE_DEFINED__ */



#ifndef __IMA2_3DPOSITIONLIBLib_LIBRARY_DEFINED__
#define __IMA2_3DPOSITIONLIBLib_LIBRARY_DEFINED__

/* library IMA2_3DPOSITIONLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_3DPOSITIONLIBLib;

EXTERN_C const CLSID CLSID_ComputePosition;

#ifdef __cplusplus

class DECLSPEC_UUID("152A576E-B530-4321-9D15-CCE50BA2566F")
ComputePosition;
#endif
#endif /* __IMA2_3DPOSITIONLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
