/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 26 13:10:06 2008
 */
/* Compiler settings for O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.idl:
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

#ifndef __IMA2_ImageRepLib_h__
#define __IMA2_ImageRepLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INetImgRep_FWD_DEFINED__
#define __INetImgRep_FWD_DEFINED__
typedef interface INetImgRep INetImgRep;
#endif 	/* __INetImgRep_FWD_DEFINED__ */


#ifndef __IImageRep_FWD_DEFINED__
#define __IImageRep_FWD_DEFINED__
typedef interface IImageRep IImageRep;
#endif 	/* __IImageRep_FWD_DEFINED__ */


#ifndef __IFeatureInfo_FWD_DEFINED__
#define __IFeatureInfo_FWD_DEFINED__
typedef interface IFeatureInfo IFeatureInfo;
#endif 	/* __IFeatureInfo_FWD_DEFINED__ */


#ifndef __NetImgRep_FWD_DEFINED__
#define __NetImgRep_FWD_DEFINED__

#ifdef __cplusplus
typedef class NetImgRep NetImgRep;
#else
typedef struct NetImgRep NetImgRep;
#endif /* __cplusplus */

#endif 	/* __NetImgRep_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INetImgRep_INTERFACE_DEFINED__
#define __INetImgRep_INTERFACE_DEFINED__

/* interface INetImgRep */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INetImgRep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("907053F1-3EC2-4402-A5D8-264382C34FFE")
    INetImgRep : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyDelay( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyDelay( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImgWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImgWidth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImgHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImgHeight( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImgDepth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImgDepth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Point( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Point( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PointIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PointIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateManager( 
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INetImgRepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INetImgRep __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INetImgRep __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INetImgRep __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyDelay )( 
            INetImgRep __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyDelay )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImgWidth )( 
            INetImgRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImgWidth )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImgHeight )( 
            INetImgRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImgHeight )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImgDepth )( 
            INetImgRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImgDepth )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Point )( 
            INetImgRep __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Point )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PointIndex )( 
            INetImgRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PointIndex )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateManager )( 
            INetImgRep __RPC_FAR * This,
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        END_INTERFACE
    } INetImgRepVtbl;

    interface INetImgRep
    {
        CONST_VTBL struct INetImgRepVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INetImgRep_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INetImgRep_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INetImgRep_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INetImgRep_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INetImgRep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INetImgRep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INetImgRep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INetImgRep_get_ProxyDelay(This,pVal)	\
    (This)->lpVtbl -> get_ProxyDelay(This,pVal)

#define INetImgRep_put_ProxyDelay(This,newVal)	\
    (This)->lpVtbl -> put_ProxyDelay(This,newVal)

#define INetImgRep_get_ImgWidth(This,pVal)	\
    (This)->lpVtbl -> get_ImgWidth(This,pVal)

#define INetImgRep_put_ImgWidth(This,newVal)	\
    (This)->lpVtbl -> put_ImgWidth(This,newVal)

#define INetImgRep_get_ImgHeight(This,pVal)	\
    (This)->lpVtbl -> get_ImgHeight(This,pVal)

#define INetImgRep_put_ImgHeight(This,newVal)	\
    (This)->lpVtbl -> put_ImgHeight(This,newVal)

#define INetImgRep_get_ImgDepth(This,pVal)	\
    (This)->lpVtbl -> get_ImgDepth(This,pVal)

#define INetImgRep_put_ImgDepth(This,newVal)	\
    (This)->lpVtbl -> put_ImgDepth(This,newVal)

#define INetImgRep_get_Point(This,pVal)	\
    (This)->lpVtbl -> get_Point(This,pVal)

#define INetImgRep_put_Point(This,newVal)	\
    (This)->lpVtbl -> put_Point(This,newVal)

#define INetImgRep_get_PointIndex(This,pVal)	\
    (This)->lpVtbl -> get_PointIndex(This,pVal)

#define INetImgRep_put_PointIndex(This,newVal)	\
    (This)->lpVtbl -> put_PointIndex(This,newVal)

#define INetImgRep_UpdateManager(This,Interface,Data)	\
    (This)->lpVtbl -> UpdateManager(This,Interface,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INetImgRep_get_ProxyDelay_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INetImgRep_get_ProxyDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INetImgRep_put_ProxyDelay_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INetImgRep_put_ProxyDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INetImgRep_get_ImgWidth_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INetImgRep_get_ImgWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INetImgRep_put_ImgWidth_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB INetImgRep_put_ImgWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INetImgRep_get_ImgHeight_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INetImgRep_get_ImgHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INetImgRep_put_ImgHeight_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB INetImgRep_put_ImgHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INetImgRep_get_ImgDepth_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INetImgRep_get_ImgDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INetImgRep_put_ImgDepth_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB INetImgRep_put_ImgDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INetImgRep_get_Point_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INetImgRep_get_Point_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INetImgRep_put_Point_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB INetImgRep_put_Point_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INetImgRep_get_PointIndex_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INetImgRep_get_PointIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INetImgRep_put_PointIndex_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB INetImgRep_put_PointIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INetImgRep_UpdateManager_Proxy( 
    INetImgRep __RPC_FAR * This,
    /* [in] */ BSTR Interface,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB INetImgRep_UpdateManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INetImgRep_INTERFACE_DEFINED__ */


#ifndef __IImageRep_INTERFACE_DEFINED__
#define __IImageRep_INTERFACE_DEFINED__

/* interface IImageRep */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IImageRep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7FDA7758-CBF3-48D0-AFF1-A298DAF54B9B")
    IImageRep : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Depth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Depth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            long m_lTimeFlag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Time( 
            long m_lTimeFlag,
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Data( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ BYTE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateManager( 
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageRepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageRep __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageRep __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageRep __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IImageRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IImageRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IImageRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IImageRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Depth )( 
            IImageRep __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Depth )( 
            IImageRep __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Time )( 
            IImageRep __RPC_FAR * This,
            long m_lTimeFlag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Time )( 
            IImageRep __RPC_FAR * This,
            long m_lTimeFlag,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Data )( 
            IImageRep __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IImageRep __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateManager )( 
            IImageRep __RPC_FAR * This,
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        END_INTERFACE
    } IImageRepVtbl;

    interface IImageRep
    {
        CONST_VTBL struct IImageRepVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageRep_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageRep_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageRep_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageRep_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IImageRep_put_Width(This,newVal)	\
    (This)->lpVtbl -> put_Width(This,newVal)

#define IImageRep_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IImageRep_put_Height(This,newVal)	\
    (This)->lpVtbl -> put_Height(This,newVal)

#define IImageRep_get_Depth(This,pVal)	\
    (This)->lpVtbl -> get_Depth(This,pVal)

#define IImageRep_put_Depth(This,newVal)	\
    (This)->lpVtbl -> put_Depth(This,newVal)

#define IImageRep_get_Time(This,m_lTimeFlag,pVal)	\
    (This)->lpVtbl -> get_Time(This,m_lTimeFlag,pVal)

#define IImageRep_put_Time(This,m_lTimeFlag,newVal)	\
    (This)->lpVtbl -> put_Time(This,m_lTimeFlag,newVal)

#define IImageRep_Data(This,lIndex,pVal)	\
    (This)->lpVtbl -> Data(This,lIndex,pVal)

#define IImageRep_Update(This,pVal)	\
    (This)->lpVtbl -> Update(This,pVal)

#define IImageRep_UpdateManager(This,Interface,Data)	\
    (This)->lpVtbl -> UpdateManager(This,Interface,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageRep_get_Width_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IImageRep_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageRep_put_Width_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IImageRep_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageRep_get_Height_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IImageRep_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageRep_put_Height_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IImageRep_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageRep_get_Depth_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IImageRep_get_Depth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageRep_put_Depth_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IImageRep_put_Depth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageRep_get_Time_Proxy( 
    IImageRep __RPC_FAR * This,
    long m_lTimeFlag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IImageRep_get_Time_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageRep_put_Time_Proxy( 
    IImageRep __RPC_FAR * This,
    long m_lTimeFlag,
    /* [in] */ double newVal);


void __RPC_STUB IImageRep_put_Time_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageRep_Data_Proxy( 
    IImageRep __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IImageRep_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageRep_Update_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pVal);


void __RPC_STUB IImageRep_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageRep_UpdateManager_Proxy( 
    IImageRep __RPC_FAR * This,
    /* [in] */ BSTR Interface,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB IImageRep_UpdateManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageRep_INTERFACE_DEFINED__ */


#ifndef __IFeatureInfo_INTERFACE_DEFINED__
#define __IFeatureInfo_INTERFACE_DEFINED__

/* interface IFeatureInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFeatureInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79DE6720-6D92-11d1-BC62-0020AFF12FB6")
    IFeatureInfo : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureWidth( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureWidth( 
            long lIndex,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureHeight( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureHeight( 
            long lIndex,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureArea( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureArea( 
            long lIndex,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureLabel( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureLabel( 
            long lIndex,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureIndex( 
            long lFeatureLabel,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureIndex( 
            long lFeatureLabel,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureOrientation( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureOrientation( 
            long lIndex,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureName( 
            long lIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureName( 
            long lIndex,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeatureLength( 
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeatureLength( 
            long lIndex,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_FeatureCentroid( 
            long lIndex,
            /* [out] */ long __RPC_FAR *pX,
            /* [out] */ long __RPC_FAR *pY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE put_FeatureCentroid( 
            long lIndex,
            /* [in] */ long newX,
            /* [in] */ long newY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_FeatureLocation( 
            long lIndex,
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE put_FeatureLocation( 
            long lIndex,
            /* [in] */ long newLeft,
            /* [in] */ long newTop) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFeature( 
            long lFeatureLabel,
            /* [out] */ long __RPC_FAR *plFeatureIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearFeatures( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NumFeatures( 
            long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateManager( 
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFeatureInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFeatureInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFeatureInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFeatureInfo __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureWidth )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureWidth )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureHeight )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureHeight )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureArea )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureArea )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureLabel )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureLabel )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureIndex )( 
            IFeatureInfo __RPC_FAR * This,
            long lFeatureLabel,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureIndex )( 
            IFeatureInfo __RPC_FAR * This,
            long lFeatureLabel,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureOrientation )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureOrientation )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureName )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureName )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureLength )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureLength )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureCentroid )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [out] */ long __RPC_FAR *pX,
            /* [out] */ long __RPC_FAR *pY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureCentroid )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newX,
            /* [in] */ long newY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FeatureLocation )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FeatureLocation )( 
            IFeatureInfo __RPC_FAR * This,
            long lIndex,
            /* [in] */ long newLeft,
            /* [in] */ long newTop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFeature )( 
            IFeatureInfo __RPC_FAR * This,
            long lFeatureLabel,
            /* [out] */ long __RPC_FAR *plFeatureIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearFeatures )( 
            IFeatureInfo __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NumFeatures )( 
            IFeatureInfo __RPC_FAR * This,
            long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateManager )( 
            IFeatureInfo __RPC_FAR * This,
            /* [in] */ BSTR Interface,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        END_INTERFACE
    } IFeatureInfoVtbl;

    interface IFeatureInfo
    {
        CONST_VTBL struct IFeatureInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFeatureInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFeatureInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFeatureInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFeatureInfo_get_FeatureWidth(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureWidth(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureWidth(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureWidth(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureHeight(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureHeight(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureHeight(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureHeight(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureArea(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureArea(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureArea(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureArea(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureLabel(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureLabel(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureLabel(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureLabel(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureIndex(This,lFeatureLabel,pVal)	\
    (This)->lpVtbl -> get_FeatureIndex(This,lFeatureLabel,pVal)

#define IFeatureInfo_put_FeatureIndex(This,lFeatureLabel,newVal)	\
    (This)->lpVtbl -> put_FeatureIndex(This,lFeatureLabel,newVal)

#define IFeatureInfo_get_FeatureOrientation(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureOrientation(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureOrientation(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureOrientation(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureName(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureName(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureName(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureName(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureLength(This,lIndex,pVal)	\
    (This)->lpVtbl -> get_FeatureLength(This,lIndex,pVal)

#define IFeatureInfo_put_FeatureLength(This,lIndex,newVal)	\
    (This)->lpVtbl -> put_FeatureLength(This,lIndex,newVal)

#define IFeatureInfo_get_FeatureCentroid(This,lIndex,pX,pY)	\
    (This)->lpVtbl -> get_FeatureCentroid(This,lIndex,pX,pY)

#define IFeatureInfo_put_FeatureCentroid(This,lIndex,newX,newY)	\
    (This)->lpVtbl -> put_FeatureCentroid(This,lIndex,newX,newY)

#define IFeatureInfo_get_FeatureLocation(This,lIndex,pLeft,pTop)	\
    (This)->lpVtbl -> get_FeatureLocation(This,lIndex,pLeft,pTop)

#define IFeatureInfo_put_FeatureLocation(This,lIndex,newLeft,newTop)	\
    (This)->lpVtbl -> put_FeatureLocation(This,lIndex,newLeft,newTop)

#define IFeatureInfo_AddFeature(This,lFeatureLabel,plFeatureIndex)	\
    (This)->lpVtbl -> AddFeature(This,lFeatureLabel,plFeatureIndex)

#define IFeatureInfo_ClearFeatures(This)	\
    (This)->lpVtbl -> ClearFeatures(This)

#define IFeatureInfo_NumFeatures(This,pVal)	\
    (This)->lpVtbl -> NumFeatures(This,pVal)

#define IFeatureInfo_UpdateManager(This,Interface,Data)	\
    (This)->lpVtbl -> UpdateManager(This,Interface,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureWidth_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureWidth_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureHeight_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureHeight_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureArea_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureArea_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureLabel_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureLabel_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureIndex_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lFeatureLabel,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureIndex_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lFeatureLabel,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureOrientation_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureOrientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureOrientation_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureOrientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureName_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureName_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFeatureInfo_put_FeatureName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureLength_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_get_FeatureLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureLength_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newVal);


void __RPC_STUB IFeatureInfo_put_FeatureLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureCentroid_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [out] */ long __RPC_FAR *pX,
    /* [out] */ long __RPC_FAR *pY);


void __RPC_STUB IFeatureInfo_get_FeatureCentroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureCentroid_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newX,
    /* [in] */ long newY);


void __RPC_STUB IFeatureInfo_put_FeatureCentroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_get_FeatureLocation_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [out] */ long __RPC_FAR *pLeft,
    /* [out] */ long __RPC_FAR *pTop);


void __RPC_STUB IFeatureInfo_get_FeatureLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_put_FeatureLocation_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lIndex,
    /* [in] */ long newLeft,
    /* [in] */ long newTop);


void __RPC_STUB IFeatureInfo_put_FeatureLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_AddFeature_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long lFeatureLabel,
    /* [out] */ long __RPC_FAR *plFeatureIndex);


void __RPC_STUB IFeatureInfo_AddFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_ClearFeatures_Proxy( 
    IFeatureInfo __RPC_FAR * This);


void __RPC_STUB IFeatureInfo_ClearFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_NumFeatures_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    long __RPC_FAR *pVal);


void __RPC_STUB IFeatureInfo_NumFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFeatureInfo_UpdateManager_Proxy( 
    IFeatureInfo __RPC_FAR * This,
    /* [in] */ BSTR Interface,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB IFeatureInfo_UpdateManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFeatureInfo_INTERFACE_DEFINED__ */



#ifndef __IMA2_IMAGEREPLIBLib_LIBRARY_DEFINED__
#define __IMA2_IMAGEREPLIBLib_LIBRARY_DEFINED__

/* library IMA2_IMAGEREPLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_IMAGEREPLIBLib;

EXTERN_C const CLSID CLSID_NetImgRep;

#ifdef __cplusplus

class DECLSPEC_UUID("C37B8632-9581-4FB1-B0E1-4B95F472A7D3")
NetImgRep;
#endif
#endif /* __IMA2_IMAGEREPLIBLib_LIBRARY_DEFINED__ */

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
