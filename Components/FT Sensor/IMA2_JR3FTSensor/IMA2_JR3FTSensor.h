/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jul 18 11:59:34 2008
 */
/* Compiler settings for O:\Components\FT Sensor\IMA2_JR3FTSensor\IMA2_JR3FTSensor.idl:
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

#ifndef __IMA2_JR3FTSensor_h__
#define __IMA2_JR3FTSensor_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IJR3Sensor_FWD_DEFINED__
#define __IJR3Sensor_FWD_DEFINED__
typedef interface IJR3Sensor IJR3Sensor;
#endif 	/* __IJR3Sensor_FWD_DEFINED__ */


#ifndef __JR3Sensor_FWD_DEFINED__
#define __JR3Sensor_FWD_DEFINED__

#ifdef __cplusplus
typedef class JR3Sensor JR3Sensor;
#else
typedef struct JR3Sensor JR3Sensor;
#endif /* __cplusplus */

#endif 	/* __JR3Sensor_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IJR3Sensor_INTERFACE_DEFINED__
#define __IJR3Sensor_INTERFACE_DEFINED__

/* interface IJR3Sensor */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IJR3Sensor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A884706D-7C76-498B-996F-8D3A6D7C66CE")
    IJR3Sensor : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FullScales( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FullScales( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetData( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetData( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FTData( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FTDataIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FTDataIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetDataIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetDataIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxMinPeakIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxMinPeakIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxMinPeakData( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxMinValue( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxMinValue( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_FullScales( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set_FullScales( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_RecommendedMaxScales( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_RecommendedMinScales( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AveragingWeight_FTData( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AveragingWeight_FTData( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_status( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_Offsets( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetOffsets( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_FTMax_or_MinPeaks( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_FTData( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJR3SensorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IJR3Sensor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IJR3Sensor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IJR3Sensor __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScales )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScales )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OffsetData )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OffsetData )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FTData )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FTDataIndex )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FTDataIndex )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OffsetDataIndex )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OffsetDataIndex )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxMinPeakIndex )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxMinPeakIndex )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxMinPeakData )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxMinValue )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxMinValue )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_FullScales )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set_FullScales )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_RecommendedMaxScales )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_RecommendedMinScales )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AveragingWeight_FTData )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AveragingWeight_FTData )( 
            IJR3Sensor __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_status )( 
            IJR3Sensor __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_Offsets )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetOffsets )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_FTMax_or_MinPeaks )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IJR3Sensor __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read_FTData )( 
            IJR3Sensor __RPC_FAR * This);
        
        END_INTERFACE
    } IJR3SensorVtbl;

    interface IJR3Sensor
    {
        CONST_VTBL struct IJR3SensorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJR3Sensor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IJR3Sensor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IJR3Sensor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IJR3Sensor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IJR3Sensor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IJR3Sensor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IJR3Sensor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IJR3Sensor_get_FullScales(This,pVal)	\
    (This)->lpVtbl -> get_FullScales(This,pVal)

#define IJR3Sensor_put_FullScales(This,newVal)	\
    (This)->lpVtbl -> put_FullScales(This,newVal)

#define IJR3Sensor_get_OffsetData(This,pVal)	\
    (This)->lpVtbl -> get_OffsetData(This,pVal)

#define IJR3Sensor_put_OffsetData(This,newVal)	\
    (This)->lpVtbl -> put_OffsetData(This,newVal)

#define IJR3Sensor_get_FTData(This,pVal)	\
    (This)->lpVtbl -> get_FTData(This,pVal)

#define IJR3Sensor_get_FTDataIndex(This,pVal)	\
    (This)->lpVtbl -> get_FTDataIndex(This,pVal)

#define IJR3Sensor_put_FTDataIndex(This,newVal)	\
    (This)->lpVtbl -> put_FTDataIndex(This,newVal)

#define IJR3Sensor_get_OffsetDataIndex(This,pVal)	\
    (This)->lpVtbl -> get_OffsetDataIndex(This,pVal)

#define IJR3Sensor_put_OffsetDataIndex(This,newVal)	\
    (This)->lpVtbl -> put_OffsetDataIndex(This,newVal)

#define IJR3Sensor_get_MaxMinPeakIndex(This,pVal)	\
    (This)->lpVtbl -> get_MaxMinPeakIndex(This,pVal)

#define IJR3Sensor_put_MaxMinPeakIndex(This,newVal)	\
    (This)->lpVtbl -> put_MaxMinPeakIndex(This,newVal)

#define IJR3Sensor_get_MaxMinPeakData(This,pVal)	\
    (This)->lpVtbl -> get_MaxMinPeakData(This,pVal)

#define IJR3Sensor_get_MaxMinValue(This,pVal)	\
    (This)->lpVtbl -> get_MaxMinValue(This,pVal)

#define IJR3Sensor_put_MaxMinValue(This,newVal)	\
    (This)->lpVtbl -> put_MaxMinValue(This,newVal)

#define IJR3Sensor_Read_FullScales(This)	\
    (This)->lpVtbl -> Read_FullScales(This)

#define IJR3Sensor_Set_FullScales(This)	\
    (This)->lpVtbl -> Set_FullScales(This)

#define IJR3Sensor_Read_RecommendedMaxScales(This)	\
    (This)->lpVtbl -> Read_RecommendedMaxScales(This)

#define IJR3Sensor_Read_RecommendedMinScales(This)	\
    (This)->lpVtbl -> Read_RecommendedMinScales(This)

#define IJR3Sensor_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IJR3Sensor_get_AveragingWeight_FTData(This,pVal)	\
    (This)->lpVtbl -> get_AveragingWeight_FTData(This,pVal)

#define IJR3Sensor_put_AveragingWeight_FTData(This,newVal)	\
    (This)->lpVtbl -> put_AveragingWeight_FTData(This,newVal)

#define IJR3Sensor_get_status(This,pVal)	\
    (This)->lpVtbl -> get_status(This,pVal)

#define IJR3Sensor_Read_Offsets(This)	\
    (This)->lpVtbl -> Read_Offsets(This)

#define IJR3Sensor_ResetOffsets(This)	\
    (This)->lpVtbl -> ResetOffsets(This)

#define IJR3Sensor_Read_FTMax_or_MinPeaks(This)	\
    (This)->lpVtbl -> Read_FTMax_or_MinPeaks(This)

#define IJR3Sensor_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IJR3Sensor_Read_FTData(This)	\
    (This)->lpVtbl -> Read_FTData(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_FullScales_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_FullScales_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_FullScales_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IJR3Sensor_put_FullScales_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_OffsetData_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_OffsetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_OffsetData_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IJR3Sensor_put_OffsetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_FTData_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_FTData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_FTDataIndex_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_FTDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_FTDataIndex_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IJR3Sensor_put_FTDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_OffsetDataIndex_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_OffsetDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_OffsetDataIndex_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IJR3Sensor_put_OffsetDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_MaxMinPeakIndex_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_MaxMinPeakIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_MaxMinPeakIndex_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IJR3Sensor_put_MaxMinPeakIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_MaxMinPeakData_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_MaxMinPeakData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_MaxMinValue_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_MaxMinValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_MaxMinValue_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IJR3Sensor_put_MaxMinValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Read_FullScales_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Read_FullScales_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Set_FullScales_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Set_FullScales_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Read_RecommendedMaxScales_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Read_RecommendedMaxScales_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Read_RecommendedMinScales_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Read_RecommendedMinScales_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Close_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_AveragingWeight_FTData_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_AveragingWeight_FTData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_put_AveragingWeight_FTData_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IJR3Sensor_put_AveragingWeight_FTData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_get_status_Proxy( 
    IJR3Sensor __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IJR3Sensor_get_status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Read_Offsets_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Read_Offsets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_ResetOffsets_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_ResetOffsets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Read_FTMax_or_MinPeaks_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Read_FTMax_or_MinPeaks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Initialize_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IJR3Sensor_Read_FTData_Proxy( 
    IJR3Sensor __RPC_FAR * This);


void __RPC_STUB IJR3Sensor_Read_FTData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJR3Sensor_INTERFACE_DEFINED__ */



#ifndef __IMA2_JR3FTSENSORLib_LIBRARY_DEFINED__
#define __IMA2_JR3FTSENSORLib_LIBRARY_DEFINED__

/* library IMA2_JR3FTSENSORLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_JR3FTSENSORLib;

EXTERN_C const CLSID CLSID_JR3Sensor;

#ifdef __cplusplus

class DECLSPEC_UUID("7B374970-0315-47DD-B094-97811020B301")
JR3Sensor;
#endif
#endif /* __IMA2_JR3FTSENSORLib_LIBRARY_DEFINED__ */

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
