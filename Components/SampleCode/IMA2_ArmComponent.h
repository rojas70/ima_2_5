/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 21 19:20:32 2005
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_ArmComponent\IMA2_ArmComponent.idl:
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

#ifndef __IMA2_ArmComponent_h__
#define __IMA2_ArmComponent_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IArmMech_FWD_DEFINED__
#define __IArmMech_FWD_DEFINED__
typedef interface IArmMech IArmMech;
#endif 	/* __IArmMech_FWD_DEFINED__ */


#ifndef __ArmMech_FWD_DEFINED__
#define __ArmMech_FWD_DEFINED__

#ifdef __cplusplus
typedef class ArmMech ArmMech;
#else
typedef struct ArmMech ArmMech;
#endif /* __cplusplus */

#endif 	/* __ArmMech_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IArmMech_INTERFACE_DEFINED__
#define __IArmMech_INTERFACE_DEFINED__

/* interface IArmMech */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IArmMech;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DBEC1F89-7AE2-449A-888D-3492211B08ED")
    IArmMech : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunArm( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArmMechVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IArmMech __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IArmMech __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IArmMech __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IArmMech __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IArmMech __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IArmMech __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IArmMech __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunArm )( 
            IArmMech __RPC_FAR * This);
        
        END_INTERFACE
    } IArmMechVtbl;

    interface IArmMech
    {
        CONST_VTBL struct IArmMechVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArmMech_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IArmMech_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IArmMech_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IArmMech_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IArmMech_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IArmMech_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IArmMech_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IArmMech_RunArm(This)	\
    (This)->lpVtbl -> RunArm(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IArmMech_RunArm_Proxy( 
    IArmMech __RPC_FAR * This);


void __RPC_STUB IArmMech_RunArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IArmMech_INTERFACE_DEFINED__ */



#ifndef __IMA2_ARMCOMPONENTLib_LIBRARY_DEFINED__
#define __IMA2_ARMCOMPONENTLib_LIBRARY_DEFINED__

/* library IMA2_ARMCOMPONENTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_ARMCOMPONENTLib;

EXTERN_C const CLSID CLSID_ArmMech;

#ifdef __cplusplus

class DECLSPEC_UUID("182973A0-8D57-4A47-9540-40BD20238685")
ArmMech;
#endif
#endif /* __IMA2_ARMCOMPONENTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
