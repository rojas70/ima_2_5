/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 03 15:10:12 2009
 */
/* Compiler settings for O:\Components\FT Sensor\IMA2_FTSensorLib\IMA2_FTSensorLib.idl:
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

#ifndef __IMA2_FTSensorLib_h__
#define __IMA2_FTSensorLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IFTSensorCom_FWD_DEFINED__
#define __IFTSensorCom_FWD_DEFINED__
typedef interface IFTSensorCom IFTSensorCom;
#endif 	/* __IFTSensorCom_FWD_DEFINED__ */


#ifndef __FTSensorCom_FWD_DEFINED__
#define __FTSensorCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class FTSensorCom FTSensorCom;
#else
typedef struct FTSensorCom FTSensorCom;
#endif /* __cplusplus */

#endif 	/* __FTSensorCom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IFTSensorCom_INTERFACE_DEFINED__
#define __IFTSensorCom_INTERFACE_DEFINED__

/* interface IFTSensorCom */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFTSensorCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE08C1B6-9B59-4131-8C78-714B036BEC38")
    IFTSensorCom : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SampleFTData( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentFrame( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentFrame( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentFrameIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentFrameIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AverageLength( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AverageLength( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceFilename( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeviceFilename( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FTWristSide( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FTWristSide( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ErrorMessage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BiasSensor( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnablePeaks( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFTSensorComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFTSensorCom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFTSensorCom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFTSensorCom __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SampleFTData )( 
            IFTSensorCom __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentFrame )( 
            IFTSensorCom __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentFrame )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentFrameIndex )( 
            IFTSensorCom __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentFrameIndex )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AverageLength )( 
            IFTSensorCom __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AverageLength )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceFilename )( 
            IFTSensorCom __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeviceFilename )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FTWristSide )( 
            IFTSensorCom __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FTWristSide )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IFTSensorCom __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorMessage )( 
            IFTSensorCom __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErrorMessage )( 
            IFTSensorCom __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BiasSensor )( 
            IFTSensorCom __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnablePeaks )( 
            IFTSensorCom __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IFTSensorCom __RPC_FAR * This);
        
        END_INTERFACE
    } IFTSensorComVtbl;

    interface IFTSensorCom
    {
        CONST_VTBL struct IFTSensorComVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFTSensorCom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFTSensorCom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFTSensorCom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFTSensorCom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFTSensorCom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFTSensorCom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFTSensorCom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFTSensorCom_SampleFTData(This)	\
    (This)->lpVtbl -> SampleFTData(This)

#define IFTSensorCom_get_CurrentFrame(This,pVal)	\
    (This)->lpVtbl -> get_CurrentFrame(This,pVal)

#define IFTSensorCom_put_CurrentFrame(This,newVal)	\
    (This)->lpVtbl -> put_CurrentFrame(This,newVal)

#define IFTSensorCom_get_CurrentFrameIndex(This,pVal)	\
    (This)->lpVtbl -> get_CurrentFrameIndex(This,pVal)

#define IFTSensorCom_put_CurrentFrameIndex(This,newVal)	\
    (This)->lpVtbl -> put_CurrentFrameIndex(This,newVal)

#define IFTSensorCom_get_AverageLength(This,pVal)	\
    (This)->lpVtbl -> get_AverageLength(This,pVal)

#define IFTSensorCom_put_AverageLength(This,newVal)	\
    (This)->lpVtbl -> put_AverageLength(This,newVal)

#define IFTSensorCom_get_DeviceFilename(This,pVal)	\
    (This)->lpVtbl -> get_DeviceFilename(This,pVal)

#define IFTSensorCom_put_DeviceFilename(This,newVal)	\
    (This)->lpVtbl -> put_DeviceFilename(This,newVal)

#define IFTSensorCom_get_FTWristSide(This,pVal)	\
    (This)->lpVtbl -> get_FTWristSide(This,pVal)

#define IFTSensorCom_put_FTWristSide(This,newVal)	\
    (This)->lpVtbl -> put_FTWristSide(This,newVal)

#define IFTSensorCom_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IFTSensorCom_get_ErrorMessage(This,pVal)	\
    (This)->lpVtbl -> get_ErrorMessage(This,pVal)

#define IFTSensorCom_put_ErrorMessage(This,newVal)	\
    (This)->lpVtbl -> put_ErrorMessage(This,newVal)

#define IFTSensorCom_BiasSensor(This)	\
    (This)->lpVtbl -> BiasSensor(This)

#define IFTSensorCom_EnablePeaks(This)	\
    (This)->lpVtbl -> EnablePeaks(This)

#define IFTSensorCom_Close(This)	\
    (This)->lpVtbl -> Close(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_SampleFTData_Proxy( 
    IFTSensorCom __RPC_FAR * This);


void __RPC_STUB IFTSensorCom_SampleFTData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_get_CurrentFrame_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IFTSensorCom_get_CurrentFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_put_CurrentFrame_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IFTSensorCom_put_CurrentFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_get_CurrentFrameIndex_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IFTSensorCom_get_CurrentFrameIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_put_CurrentFrameIndex_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IFTSensorCom_put_CurrentFrameIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_get_AverageLength_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFTSensorCom_get_AverageLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_put_AverageLength_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IFTSensorCom_put_AverageLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_get_DeviceFilename_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFTSensorCom_get_DeviceFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_put_DeviceFilename_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTSensorCom_put_DeviceFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_get_FTWristSide_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFTSensorCom_get_FTWristSide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_put_FTWristSide_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTSensorCom_put_FTWristSide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_Initialize_Proxy( 
    IFTSensorCom __RPC_FAR * This);


void __RPC_STUB IFTSensorCom_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_get_ErrorMessage_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFTSensorCom_get_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_put_ErrorMessage_Proxy( 
    IFTSensorCom __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFTSensorCom_put_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_BiasSensor_Proxy( 
    IFTSensorCom __RPC_FAR * This);


void __RPC_STUB IFTSensorCom_BiasSensor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_EnablePeaks_Proxy( 
    IFTSensorCom __RPC_FAR * This);


void __RPC_STUB IFTSensorCom_EnablePeaks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFTSensorCom_Close_Proxy( 
    IFTSensorCom __RPC_FAR * This);


void __RPC_STUB IFTSensorCom_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFTSensorCom_INTERFACE_DEFINED__ */



#ifndef __IMA2_FTSENSORLIBLib_LIBRARY_DEFINED__
#define __IMA2_FTSENSORLIBLib_LIBRARY_DEFINED__

/* library IMA2_FTSENSORLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_FTSENSORLIBLib;

EXTERN_C const CLSID CLSID_FTSensorCom;

#ifdef __cplusplus

class DECLSPEC_UUID("B76D0DD9-D211-43FB-AF30-0B1A6DF32CB3")
FTSensorCom;
#endif
#endif /* __IMA2_FTSENSORLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
