/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 17 16:08:37 2006
 */
/* Compiler settings for O:\Components\Representations\IMA2_TextQueueLib\IMA2_TextQueueLib.idl:
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

#ifndef __IMA2_TextQueueLib_h__
#define __IMA2_TextQueueLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITextQueue_FWD_DEFINED__
#define __ITextQueue_FWD_DEFINED__
typedef interface ITextQueue ITextQueue;
#endif 	/* __ITextQueue_FWD_DEFINED__ */


#ifndef __TextQueue_FWD_DEFINED__
#define __TextQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextQueue TextQueue;
#else
typedef struct TextQueue TextQueue;
#endif /* __cplusplus */

#endif 	/* __TextQueue_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITextQueue_INTERFACE_DEFINED__
#define __ITextQueue_INTERFACE_DEFINED__

/* interface ITextQueue */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D5132BF-D5C2-4916-9E56-603D987D486C")
    ITextQueue : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ long index,
            /* [out] */ BSTR __RPC_FAR *text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetText( 
            /* [in] */ long index,
            /* [in] */ BSTR text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentText( 
            /* [out] */ BSTR __RPC_FAR *text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentText( 
            /* [in] */ BSTR text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateManager( 
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StringIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StringIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentText( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QueueLength( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QueueLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ThrowEvent( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ThrowEvent( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SaveData( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SaveData( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITextQueue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITextQueue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITextQueue __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetText )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ long index,
            /* [out] */ BSTR __RPC_FAR *text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetText )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ BSTR text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentText )( 
            ITextQueue __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentText )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ BSTR text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateManager )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StringIndex )( 
            ITextQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StringIndex )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentText )( 
            ITextQueue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentText )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_QueueLength )( 
            ITextQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_QueueLength )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ThrowEvent )( 
            ITextQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ThrowEvent )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SaveData )( 
            ITextQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SaveData )( 
            ITextQueue __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } ITextQueueVtbl;

    interface ITextQueue
    {
        CONST_VTBL struct ITextQueueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextQueue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextQueue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextQueue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextQueue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextQueue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextQueue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextQueue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextQueue_GetText(This,index,text)	\
    (This)->lpVtbl -> GetText(This,index,text)

#define ITextQueue_SetText(This,index,text)	\
    (This)->lpVtbl -> SetText(This,index,text)

#define ITextQueue_GetCurrentText(This,text)	\
    (This)->lpVtbl -> GetCurrentText(This,text)

#define ITextQueue_SetCurrentText(This,text)	\
    (This)->lpVtbl -> SetCurrentText(This,text)

#define ITextQueue_UpdateManager(This,Interface,Data)	\
    (This)->lpVtbl -> UpdateManager(This,Interface,Data)

#define ITextQueue_get_StringIndex(This,pVal)	\
    (This)->lpVtbl -> get_StringIndex(This,pVal)

#define ITextQueue_put_StringIndex(This,newVal)	\
    (This)->lpVtbl -> put_StringIndex(This,newVal)

#define ITextQueue_get_CurrentText(This,pVal)	\
    (This)->lpVtbl -> get_CurrentText(This,pVal)

#define ITextQueue_put_CurrentText(This,newVal)	\
    (This)->lpVtbl -> put_CurrentText(This,newVal)

#define ITextQueue_get_QueueLength(This,pVal)	\
    (This)->lpVtbl -> get_QueueLength(This,pVal)

#define ITextQueue_put_QueueLength(This,newVal)	\
    (This)->lpVtbl -> put_QueueLength(This,newVal)

#define ITextQueue_get_ThrowEvent(This,pVal)	\
    (This)->lpVtbl -> get_ThrowEvent(This,pVal)

#define ITextQueue_put_ThrowEvent(This,newVal)	\
    (This)->lpVtbl -> put_ThrowEvent(This,newVal)

#define ITextQueue_get_SaveData(This,pVal)	\
    (This)->lpVtbl -> get_SaveData(This,pVal)

#define ITextQueue_put_SaveData(This,newVal)	\
    (This)->lpVtbl -> put_SaveData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextQueue_GetText_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ long index,
    /* [out] */ BSTR __RPC_FAR *text);


void __RPC_STUB ITextQueue_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextQueue_SetText_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ BSTR text);


void __RPC_STUB ITextQueue_SetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextQueue_GetCurrentText_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *text);


void __RPC_STUB ITextQueue_GetCurrentText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextQueue_SetCurrentText_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ BSTR text);


void __RPC_STUB ITextQueue_SetCurrentText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextQueue_UpdateManager_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ BSTR Interface,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB ITextQueue_UpdateManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextQueue_get_StringIndex_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITextQueue_get_StringIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextQueue_put_StringIndex_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITextQueue_put_StringIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextQueue_get_CurrentText_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITextQueue_get_CurrentText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextQueue_put_CurrentText_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITextQueue_put_CurrentText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextQueue_get_QueueLength_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITextQueue_get_QueueLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextQueue_put_QueueLength_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITextQueue_put_QueueLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextQueue_get_ThrowEvent_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITextQueue_get_ThrowEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextQueue_put_ThrowEvent_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITextQueue_put_ThrowEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextQueue_get_SaveData_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITextQueue_get_SaveData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextQueue_put_SaveData_Proxy( 
    ITextQueue __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITextQueue_put_SaveData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextQueue_INTERFACE_DEFINED__ */



#ifndef __IMA2_TEXTQUEUELIBLib_LIBRARY_DEFINED__
#define __IMA2_TEXTQUEUELIBLib_LIBRARY_DEFINED__

/* library IMA2_TEXTQUEUELIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_TEXTQUEUELIBLib;

EXTERN_C const CLSID CLSID_TextQueue;

#ifdef __cplusplus

class DECLSPEC_UUID("65D465D7-FE9B-4972-B460-8BDEF913F790")
TextQueue;
#endif
#endif /* __IMA2_TEXTQUEUELIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
