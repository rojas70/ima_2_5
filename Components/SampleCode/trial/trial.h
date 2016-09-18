/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 07 15:45:55 2006
 */
/* Compiler settings for O:\Components\SampleCode\trial\trial.idl:
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

#ifndef __trial_h__
#define __trial_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __Itrialobj_FWD_DEFINED__
#define __Itrialobj_FWD_DEFINED__
typedef interface Itrialobj Itrialobj;
#endif 	/* __Itrialobj_FWD_DEFINED__ */


#ifndef __trialobj_FWD_DEFINED__
#define __trialobj_FWD_DEFINED__

#ifdef __cplusplus
typedef class trialobj trialobj;
#else
typedef struct trialobj trialobj;
#endif /* __cplusplus */

#endif 	/* __trialobj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __Itrialobj_INTERFACE_DEFINED__
#define __Itrialobj_INTERFACE_DEFINED__

/* interface Itrialobj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_Itrialobj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D12EFCCC-15DE-45A6-84D3-11EAD2A88327")
    Itrialobj : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ItrialobjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Itrialobj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Itrialobj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Itrialobj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Itrialobj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Itrialobj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Itrialobj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Itrialobj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ItrialobjVtbl;

    interface Itrialobj
    {
        CONST_VTBL struct ItrialobjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Itrialobj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Itrialobj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Itrialobj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Itrialobj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Itrialobj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Itrialobj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Itrialobj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Itrialobj_INTERFACE_DEFINED__ */



#ifndef __TRIALLib_LIBRARY_DEFINED__
#define __TRIALLib_LIBRARY_DEFINED__

/* library TRIALLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TRIALLib;

EXTERN_C const CLSID CLSID_trialobj;

#ifdef __cplusplus

class DECLSPEC_UUID("E2EC1480-F13E-4F16-8338-15495F3AE6BF")
trialobj;
#endif
#endif /* __TRIALLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
