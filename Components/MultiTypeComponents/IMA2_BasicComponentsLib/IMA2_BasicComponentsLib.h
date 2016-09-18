/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 13 11:31:31 2008
 */
/* Compiler settings for O:\Components\MultiTypeComponents\IMA2_BasicComponentsLib\IMA2_BasicComponentsLib.idl:
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

#ifndef __IMA2_BasicComponentsLib_h__
#define __IMA2_BasicComponentsLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVectorSignal_FWD_DEFINED__
#define __IVectorSignal_FWD_DEFINED__
typedef interface IVectorSignal IVectorSignal;
#endif 	/* __IVectorSignal_FWD_DEFINED__ */


#ifndef __IVSandFiles_FWD_DEFINED__
#define __IVSandFiles_FWD_DEFINED__
typedef interface IVSandFiles IVSandFiles;
#endif 	/* __IVSandFiles_FWD_DEFINED__ */


#ifndef __VectorSignal_FWD_DEFINED__
#define __VectorSignal_FWD_DEFINED__

#ifdef __cplusplus
typedef class VectorSignal VectorSignal;
#else
typedef struct VectorSignal VectorSignal;
#endif /* __cplusplus */

#endif 	/* __VectorSignal_FWD_DEFINED__ */


#ifndef __VSandFiles_FWD_DEFINED__
#define __VSandFiles_FWD_DEFINED__

#ifdef __cplusplus
typedef class VSandFiles VSandFiles;
#else
typedef struct VSandFiles VSandFiles;
#endif /* __cplusplus */

#endif 	/* __VSandFiles_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IVectorSignal_INTERFACE_DEFINED__
#define __IVectorSignal_INTERFACE_DEFINED__

/* interface IVectorSignal */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVectorSignal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4EB79C6B-B32F-4834-97AE-829B56BB3FB1")
    IVectorSignal : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Index( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IndexValue( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IndexValue( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowVector( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowVector( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignalLength( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignalLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VectorLength( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VectorLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TestSetup( 
            long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentVector( 
            /* [out][in] */ SAFEARRAY __RPC_FAR * data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVector( 
            /* [in] */ long index,
            /* [out][in] */ SAFEARRAY __RPC_FAR * data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentVector( 
            /* [in] */ SAFEARRAY __RPC_FAR * data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVector( 
            /* [in] */ long index,
            /* [in] */ SAFEARRAY __RPC_FAR * data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateManager( 
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVectorSignalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVectorSignal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVectorSignal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVectorSignal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            IVectorSignal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Index )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IndexValue )( 
            IVectorSignal __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IndexValue )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RowVector )( 
            IVectorSignal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RowVector )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SignalLength )( 
            IVectorSignal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SignalLength )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VectorLength )( 
            IVectorSignal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VectorLength )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TestSetup )( 
            IVectorSignal __RPC_FAR * This,
            long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentVector )( 
            IVectorSignal __RPC_FAR * This,
            /* [out][in] */ SAFEARRAY __RPC_FAR * data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVector )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ long index,
            /* [out][in] */ SAFEARRAY __RPC_FAR * data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentVector )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVector )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ SAFEARRAY __RPC_FAR * data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateManager )( 
            IVectorSignal __RPC_FAR * This,
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        END_INTERFACE
    } IVectorSignalVtbl;

    interface IVectorSignal
    {
        CONST_VTBL struct IVectorSignalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVectorSignal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVectorSignal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVectorSignal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVectorSignal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVectorSignal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVectorSignal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVectorSignal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVectorSignal_get_Index(This,pVal)	\
    (This)->lpVtbl -> get_Index(This,pVal)

#define IVectorSignal_put_Index(This,newVal)	\
    (This)->lpVtbl -> put_Index(This,newVal)

#define IVectorSignal_get_IndexValue(This,pVal)	\
    (This)->lpVtbl -> get_IndexValue(This,pVal)

#define IVectorSignal_put_IndexValue(This,newVal)	\
    (This)->lpVtbl -> put_IndexValue(This,newVal)

#define IVectorSignal_get_RowVector(This,pVal)	\
    (This)->lpVtbl -> get_RowVector(This,pVal)

#define IVectorSignal_put_RowVector(This,newVal)	\
    (This)->lpVtbl -> put_RowVector(This,newVal)

#define IVectorSignal_get_SignalLength(This,pVal)	\
    (This)->lpVtbl -> get_SignalLength(This,pVal)

#define IVectorSignal_put_SignalLength(This,newVal)	\
    (This)->lpVtbl -> put_SignalLength(This,newVal)

#define IVectorSignal_get_VectorLength(This,pVal)	\
    (This)->lpVtbl -> get_VectorLength(This,pVal)

#define IVectorSignal_put_VectorLength(This,newVal)	\
    (This)->lpVtbl -> put_VectorLength(This,newVal)

#define IVectorSignal_TestSetup(This,Index)	\
    (This)->lpVtbl -> TestSetup(This,Index)

#define IVectorSignal_GetCurrentVector(This,data)	\
    (This)->lpVtbl -> GetCurrentVector(This,data)

#define IVectorSignal_GetVector(This,index,data)	\
    (This)->lpVtbl -> GetVector(This,index,data)

#define IVectorSignal_SetCurrentVector(This,data)	\
    (This)->lpVtbl -> SetCurrentVector(This,data)

#define IVectorSignal_SetVector(This,index,data)	\
    (This)->lpVtbl -> SetVector(This,index,data)

#define IVectorSignal_UpdateManager(This,Interface,Data)	\
    (This)->lpVtbl -> UpdateManager(This,Interface,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVectorSignal_get_Index_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVectorSignal_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVectorSignal_put_Index_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVectorSignal_put_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVectorSignal_get_IndexValue_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVectorSignal_get_IndexValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVectorSignal_put_IndexValue_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IVectorSignal_put_IndexValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVectorSignal_get_RowVector_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVectorSignal_get_RowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVectorSignal_put_RowVector_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVectorSignal_put_RowVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVectorSignal_get_SignalLength_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVectorSignal_get_SignalLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVectorSignal_put_SignalLength_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVectorSignal_put_SignalLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVectorSignal_get_VectorLength_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVectorSignal_get_VectorLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVectorSignal_put_VectorLength_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVectorSignal_put_VectorLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVectorSignal_TestSetup_Proxy( 
    IVectorSignal __RPC_FAR * This,
    long Index);


void __RPC_STUB IVectorSignal_TestSetup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVectorSignal_GetCurrentVector_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [out][in] */ SAFEARRAY __RPC_FAR * data);


void __RPC_STUB IVectorSignal_GetCurrentVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVectorSignal_GetVector_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ long index,
    /* [out][in] */ SAFEARRAY __RPC_FAR * data);


void __RPC_STUB IVectorSignal_GetVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVectorSignal_SetCurrentVector_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * data);


void __RPC_STUB IVectorSignal_SetCurrentVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVectorSignal_SetVector_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ SAFEARRAY __RPC_FAR * data);


void __RPC_STUB IVectorSignal_SetVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVectorSignal_UpdateManager_Proxy( 
    IVectorSignal __RPC_FAR * This,
    /* [in] */ BSTR Interface,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB IVectorSignal_UpdateManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVectorSignal_INTERFACE_DEFINED__ */


#ifndef __IVSandFiles_INTERFACE_DEFINED__
#define __IVSandFiles_INTERFACE_DEFINED__

/* interface IVSandFiles */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSandFiles;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("37712595-1EB7-48C0-AAFD-7031F5357F43")
    IVSandFiles : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Write2VS( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumAxes( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumAxes( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Write2File( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSandFilesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSandFiles __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSandFiles __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSandFiles __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSandFiles __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSandFiles __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSandFiles __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSandFiles __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write2VS )( 
            IVSandFiles __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumAxes )( 
            IVSandFiles __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumAxes )( 
            IVSandFiles __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IVSandFiles __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            IVSandFiles __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVSandFiles __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write2File )( 
            IVSandFiles __RPC_FAR * This);
        
        END_INTERFACE
    } IVSandFilesVtbl;

    interface IVSandFiles
    {
        CONST_VTBL struct IVSandFilesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSandFiles_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSandFiles_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSandFiles_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSandFiles_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSandFiles_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSandFiles_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSandFiles_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSandFiles_Write2VS(This)	\
    (This)->lpVtbl -> Write2VS(This)

#define IVSandFiles_get_NumAxes(This,pVal)	\
    (This)->lpVtbl -> get_NumAxes(This,pVal)

#define IVSandFiles_put_NumAxes(This,newVal)	\
    (This)->lpVtbl -> put_NumAxes(This,newVal)

#define IVSandFiles_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IVSandFiles_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IVSandFiles_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IVSandFiles_Write2File(This)	\
    (This)->lpVtbl -> Write2File(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSandFiles_Write2VS_Proxy( 
    IVSandFiles __RPC_FAR * This);


void __RPC_STUB IVSandFiles_Write2VS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSandFiles_get_NumAxes_Proxy( 
    IVSandFiles __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVSandFiles_get_NumAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSandFiles_put_NumAxes_Proxy( 
    IVSandFiles __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVSandFiles_put_NumAxes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSandFiles_get_FileName_Proxy( 
    IVSandFiles __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVSandFiles_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSandFiles_put_FileName_Proxy( 
    IVSandFiles __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IVSandFiles_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSandFiles_Initialize_Proxy( 
    IVSandFiles __RPC_FAR * This);


void __RPC_STUB IVSandFiles_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSandFiles_Write2File_Proxy( 
    IVSandFiles __RPC_FAR * This);


void __RPC_STUB IVSandFiles_Write2File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSandFiles_INTERFACE_DEFINED__ */



#ifndef __IMA2_BASICCOMPONENTSLIBLib_LIBRARY_DEFINED__
#define __IMA2_BASICCOMPONENTSLIBLib_LIBRARY_DEFINED__

/* library IMA2_BASICCOMPONENTSLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_BASICCOMPONENTSLIBLib;

EXTERN_C const CLSID CLSID_VectorSignal;

#ifdef __cplusplus

class DECLSPEC_UUID("7F58ABCE-1E9C-495F-8433-81B304A4713B")
VectorSignal;
#endif

EXTERN_C const CLSID CLSID_VSandFiles;

#ifdef __cplusplus

class DECLSPEC_UUID("EBB38638-88D2-44EF-A142-8E2562706BEE")
VSandFiles;
#endif
#endif /* __IMA2_BASICCOMPONENTSLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
