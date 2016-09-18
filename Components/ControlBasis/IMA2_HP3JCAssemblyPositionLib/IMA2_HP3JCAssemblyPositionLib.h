/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 10 08:55:46 2009
 */
/* Compiler settings for O:\Components\ControlBasis\IMA2_HP3JCAssemblyPositionLib\IMA2_HP3JCAssemblyPositionLib.idl:
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

#ifndef __IMA2_HP3JCAssemblyPositionLib_h__
#define __IMA2_HP3JCAssemblyPositionLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IComputeGoalPos_FWD_DEFINED__
#define __IComputeGoalPos_FWD_DEFINED__
typedef interface IComputeGoalPos IComputeGoalPos;
#endif 	/* __IComputeGoalPos_FWD_DEFINED__ */


#ifndef __ComputeGoalPos_FWD_DEFINED__
#define __ComputeGoalPos_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComputeGoalPos ComputeGoalPos;
#else
typedef struct ComputeGoalPos ComputeGoalPos;
#endif /* __cplusplus */

#endif 	/* __ComputeGoalPos_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IComputeGoalPos_INTERFACE_DEFINED__
#define __IComputeGoalPos_INTERFACE_DEFINED__

/* interface IComputeGoalPos */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IComputeGoalPos;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88117FAD-9D58-42AC-9778-129AE2D22962")
    IComputeGoalPos : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ComputeGoalPosition( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComputeGoalPosVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IComputeGoalPos __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IComputeGoalPos __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IComputeGoalPos __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IComputeGoalPos __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IComputeGoalPos __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IComputeGoalPos __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IComputeGoalPos __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ComputeGoalPosition )( 
            IComputeGoalPos __RPC_FAR * This);
        
        END_INTERFACE
    } IComputeGoalPosVtbl;

    interface IComputeGoalPos
    {
        CONST_VTBL struct IComputeGoalPosVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComputeGoalPos_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComputeGoalPos_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComputeGoalPos_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComputeGoalPos_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComputeGoalPos_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComputeGoalPos_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComputeGoalPos_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComputeGoalPos_ComputeGoalPosition(This)	\
    (This)->lpVtbl -> ComputeGoalPosition(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComputeGoalPos_ComputeGoalPosition_Proxy( 
    IComputeGoalPos __RPC_FAR * This);


void __RPC_STUB IComputeGoalPos_ComputeGoalPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComputeGoalPos_INTERFACE_DEFINED__ */



#ifndef __IMA2_HP3JCASSEMBLYPOSITIONLIBLib_LIBRARY_DEFINED__
#define __IMA2_HP3JCASSEMBLYPOSITIONLIBLib_LIBRARY_DEFINED__

/* library IMA2_HP3JCASSEMBLYPOSITIONLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_HP3JCASSEMBLYPOSITIONLIBLib;

EXTERN_C const CLSID CLSID_ComputeGoalPos;

#ifdef __cplusplus

class DECLSPEC_UUID("121915AA-25E2-4592-8550-5E3511F0FBAB")
ComputeGoalPos;
#endif
#endif /* __IMA2_HP3JCASSEMBLYPOSITIONLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
