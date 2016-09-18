/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 08 17:00:03 2006
 */
/* Compiler settings for O:\Components\Representations\IMA2_DynamicRepsLib\IMA2_DynamicRepsLib.idl:
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

#ifndef __IMA2_DynamicRepsLib_h__
#define __IMA2_DynamicRepsLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDynamicVector_FWD_DEFINED__
#define __IDynamicVector_FWD_DEFINED__
typedef interface IDynamicVector IDynamicVector;
#endif 	/* __IDynamicVector_FWD_DEFINED__ */


#ifndef __DynamicVector_FWD_DEFINED__
#define __DynamicVector_FWD_DEFINED__

#ifdef __cplusplus
typedef class DynamicVector DynamicVector;
#else
typedef struct DynamicVector DynamicVector;
#endif /* __cplusplus */

#endif 	/* __DynamicVector_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDynamicVector_INTERFACE_DEFINED__
#define __IDynamicVector_INTERFACE_DEFINED__

/* interface IDynamicVector */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDynamicVector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC378F4C-C175-42C4-BBDE-F4F3E13A6236")
    IDynamicVector : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PointsAdded( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PointsAdded( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumVectors( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumVectors( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VectorLength( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VectorLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PointsAddedIndex( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PointsAddedIndex( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddNewValue( 
            long buffer_index,
            double new_value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVector( 
            long index,
            SAFEARRAY __RPC_FAR * data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVector( 
            long index,
            SAFEARRAY __RPC_FAR * data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecentValue( 
            long buffer_index,
            long history_point,
            double __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDynamicVectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDynamicVector __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDynamicVector __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDynamicVector __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PointsAdded )( 
            IDynamicVector __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PointsAdded )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumVectors )( 
            IDynamicVector __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumVectors )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VectorLength )( 
            IDynamicVector __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VectorLength )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PointsAddedIndex )( 
            IDynamicVector __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PointsAddedIndex )( 
            IDynamicVector __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddNewValue )( 
            IDynamicVector __RPC_FAR * This,
            long buffer_index,
            double new_value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVector )( 
            IDynamicVector __RPC_FAR * This,
            long index,
            SAFEARRAY __RPC_FAR * data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVector )( 
            IDynamicVector __RPC_FAR * This,
            long index,
            SAFEARRAY __RPC_FAR * data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRecentValue )( 
            IDynamicVector __RPC_FAR * This,
            long buffer_index,
            long history_point,
            double __RPC_FAR *pVal);
        
        END_INTERFACE
    } IDynamicVectorVtbl;

    interface IDynamicVector
    {
        CONST_VTBL struct IDynamicVectorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDynamicVector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDynamicVector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDynamicVector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDynamicVector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDynamicVector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDynamicVector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDynamicVector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDynamicVector_get_PointsAdded(This,pVal)	\
    (This)->lpVtbl -> get_PointsAdded(This,pVal)

#define IDynamicVector_put_PointsAdded(This,newVal)	\
    (This)->lpVtbl -> put_PointsAdded(This,newVal)

#define IDynamicVector_get_NumVectors(This,pVal)	\
    (This)->lpVtbl -> get_NumVectors(This,pVal)

#define IDynamicVector_put_NumVectors(This,newVal)	\
    (This)->lpVtbl -> put_NumVectors(This,newVal)

#define IDynamicVector_get_VectorLength(This,pVal)	\
    (This)->lpVtbl -> get_VectorLength(This,pVal)

#define IDynamicVector_put_VectorLength(This,newVal)	\
    (This)->lpVtbl -> put_VectorLength(This,newVal)

#define IDynamicVector_get_PointsAddedIndex(This,pVal)	\
    (This)->lpVtbl -> get_PointsAddedIndex(This,pVal)

#define IDynamicVector_put_PointsAddedIndex(This,newVal)	\
    (This)->lpVtbl -> put_PointsAddedIndex(This,newVal)

#define IDynamicVector_AddNewValue(This,buffer_index,new_value)	\
    (This)->lpVtbl -> AddNewValue(This,buffer_index,new_value)

#define IDynamicVector_SetVector(This,index,data)	\
    (This)->lpVtbl -> SetVector(This,index,data)

#define IDynamicVector_GetVector(This,index,data)	\
    (This)->lpVtbl -> GetVector(This,index,data)

#define IDynamicVector_GetRecentValue(This,buffer_index,history_point,pVal)	\
    (This)->lpVtbl -> GetRecentValue(This,buffer_index,history_point,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDynamicVector_get_PointsAdded_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDynamicVector_get_PointsAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDynamicVector_put_PointsAdded_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDynamicVector_put_PointsAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDynamicVector_get_NumVectors_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDynamicVector_get_NumVectors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDynamicVector_put_NumVectors_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDynamicVector_put_NumVectors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDynamicVector_get_VectorLength_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDynamicVector_get_VectorLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDynamicVector_put_VectorLength_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDynamicVector_put_VectorLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDynamicVector_get_PointsAddedIndex_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IDynamicVector_get_PointsAddedIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDynamicVector_put_PointsAddedIndex_Proxy( 
    IDynamicVector __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IDynamicVector_put_PointsAddedIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicVector_AddNewValue_Proxy( 
    IDynamicVector __RPC_FAR * This,
    long buffer_index,
    double new_value);


void __RPC_STUB IDynamicVector_AddNewValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicVector_SetVector_Proxy( 
    IDynamicVector __RPC_FAR * This,
    long index,
    SAFEARRAY __RPC_FAR * data);


void __RPC_STUB IDynamicVector_SetVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicVector_GetVector_Proxy( 
    IDynamicVector __RPC_FAR * This,
    long index,
    SAFEARRAY __RPC_FAR * data);


void __RPC_STUB IDynamicVector_GetVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicVector_GetRecentValue_Proxy( 
    IDynamicVector __RPC_FAR * This,
    long buffer_index,
    long history_point,
    double __RPC_FAR *pVal);


void __RPC_STUB IDynamicVector_GetRecentValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDynamicVector_INTERFACE_DEFINED__ */



#ifndef __IMA2_DYNAMICREPSLIBLib_LIBRARY_DEFINED__
#define __IMA2_DYNAMICREPSLIBLib_LIBRARY_DEFINED__

/* library IMA2_DYNAMICREPSLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_DYNAMICREPSLIBLib;

EXTERN_C const CLSID CLSID_DynamicVector;

#ifdef __cplusplus

class DECLSPEC_UUID("FEAB28F2-03C5-4618-83A8-D516E25135D5")
DynamicVector;
#endif
#endif /* __IMA2_DYNAMICREPSLIBLib_LIBRARY_DEFINED__ */

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
