/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 27 14:45:50 2005
 */
/* Compiler settings for O:\Components\CameraComponents\IMA2_FrameGrabberLib\IMA2_FrameGrabberLib.idl:
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

#ifndef __IMA2_FrameGrabberLib_h__
#define __IMA2_FrameGrabberLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPXC_FG_FWD_DEFINED__
#define __IPXC_FG_FWD_DEFINED__
typedef interface IPXC_FG IPXC_FG;
#endif 	/* __IPXC_FG_FWD_DEFINED__ */


#ifndef __PXC_FG_FWD_DEFINED__
#define __PXC_FG_FWD_DEFINED__

#ifdef __cplusplus
typedef class PXC_FG PXC_FG;
#else
typedef struct PXC_FG PXC_FG;
#endif /* __cplusplus */

#endif 	/* __PXC_FG_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPXC_FG_INTERFACE_DEFINED__
#define __IPXC_FG_INTERFACE_DEFINED__

/* interface IPXC_FG */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPXC_FG;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("608CC024-05D3-4BEB-81ED-73571175C6A3")
    IPXC_FG : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Chroma( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Chroma( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FrameCount( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Saturation( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Saturation( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Hue( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Hue( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FieldCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FieldCount( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Contrast( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Contrast( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Camera( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Camera( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Brightness( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Brightness( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameGrabberID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FrameGrabberID( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageTop( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageTop( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageLeft( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageLeft( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageDepth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageHeight( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageWidth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ObtainImage( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPXC_FGVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPXC_FG __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPXC_FG __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPXC_FG __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Chroma )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Chroma )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameCount )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FrameCount )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Saturation )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Saturation )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hue )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Hue )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FieldCount )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FieldCount )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Contrast )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Contrast )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Camera )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Camera )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Brightness )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Brightness )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameGrabberID )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FrameGrabberID )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImageTop )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImageTop )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImageLeft )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImageLeft )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImageDepth )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImageHeight )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImageHeight )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImageWidth )( 
            IPXC_FG __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImageWidth )( 
            IPXC_FG __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IPXC_FG __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ObtainImage )( 
            IPXC_FG __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IPXC_FG __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IPXC_FG __RPC_FAR * This);
        
        END_INTERFACE
    } IPXC_FGVtbl;

    interface IPXC_FG
    {
        CONST_VTBL struct IPXC_FGVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPXC_FG_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPXC_FG_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPXC_FG_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPXC_FG_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPXC_FG_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPXC_FG_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPXC_FG_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPXC_FG_get_Chroma(This,pVal)	\
    (This)->lpVtbl -> get_Chroma(This,pVal)

#define IPXC_FG_put_Chroma(This,newVal)	\
    (This)->lpVtbl -> put_Chroma(This,newVal)

#define IPXC_FG_get_FrameCount(This,pVal)	\
    (This)->lpVtbl -> get_FrameCount(This,pVal)

#define IPXC_FG_put_FrameCount(This,newVal)	\
    (This)->lpVtbl -> put_FrameCount(This,newVal)

#define IPXC_FG_get_Saturation(This,pVal)	\
    (This)->lpVtbl -> get_Saturation(This,pVal)

#define IPXC_FG_put_Saturation(This,newVal)	\
    (This)->lpVtbl -> put_Saturation(This,newVal)

#define IPXC_FG_get_Hue(This,pVal)	\
    (This)->lpVtbl -> get_Hue(This,pVal)

#define IPXC_FG_put_Hue(This,newVal)	\
    (This)->lpVtbl -> put_Hue(This,newVal)

#define IPXC_FG_get_FieldCount(This,pVal)	\
    (This)->lpVtbl -> get_FieldCount(This,pVal)

#define IPXC_FG_put_FieldCount(This,newVal)	\
    (This)->lpVtbl -> put_FieldCount(This,newVal)

#define IPXC_FG_get_Contrast(This,pVal)	\
    (This)->lpVtbl -> get_Contrast(This,pVal)

#define IPXC_FG_put_Contrast(This,newVal)	\
    (This)->lpVtbl -> put_Contrast(This,newVal)

#define IPXC_FG_get_Camera(This,pVal)	\
    (This)->lpVtbl -> get_Camera(This,pVal)

#define IPXC_FG_put_Camera(This,newVal)	\
    (This)->lpVtbl -> put_Camera(This,newVal)

#define IPXC_FG_get_Brightness(This,pVal)	\
    (This)->lpVtbl -> get_Brightness(This,pVal)

#define IPXC_FG_put_Brightness(This,newVal)	\
    (This)->lpVtbl -> put_Brightness(This,newVal)

#define IPXC_FG_get_FrameGrabberID(This,pVal)	\
    (This)->lpVtbl -> get_FrameGrabberID(This,pVal)

#define IPXC_FG_put_FrameGrabberID(This,newVal)	\
    (This)->lpVtbl -> put_FrameGrabberID(This,newVal)

#define IPXC_FG_get_ImageTop(This,pVal)	\
    (This)->lpVtbl -> get_ImageTop(This,pVal)

#define IPXC_FG_put_ImageTop(This,newVal)	\
    (This)->lpVtbl -> put_ImageTop(This,newVal)

#define IPXC_FG_get_ImageLeft(This,pVal)	\
    (This)->lpVtbl -> get_ImageLeft(This,pVal)

#define IPXC_FG_put_ImageLeft(This,newVal)	\
    (This)->lpVtbl -> put_ImageLeft(This,newVal)

#define IPXC_FG_get_ImageDepth(This,pVal)	\
    (This)->lpVtbl -> get_ImageDepth(This,pVal)

#define IPXC_FG_get_ImageHeight(This,pVal)	\
    (This)->lpVtbl -> get_ImageHeight(This,pVal)

#define IPXC_FG_put_ImageHeight(This,newVal)	\
    (This)->lpVtbl -> put_ImageHeight(This,newVal)

#define IPXC_FG_get_ImageWidth(This,pVal)	\
    (This)->lpVtbl -> get_ImageWidth(This,pVal)

#define IPXC_FG_put_ImageWidth(This,newVal)	\
    (This)->lpVtbl -> put_ImageWidth(This,newVal)

#define IPXC_FG_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IPXC_FG_ObtainImage(This)	\
    (This)->lpVtbl -> ObtainImage(This)

#define IPXC_FG_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IPXC_FG_Close(This)	\
    (This)->lpVtbl -> Close(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_Chroma_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_Chroma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_Chroma_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPXC_FG_put_Chroma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_FrameCount_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_FrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_FrameCount_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_FrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_Saturation_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_Saturation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_Saturation_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPXC_FG_put_Saturation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_Hue_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_Hue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_Hue_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPXC_FG_put_Hue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_FieldCount_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_FieldCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_FieldCount_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_FieldCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_Contrast_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_Contrast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_Contrast_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPXC_FG_put_Contrast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_Camera_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_Camera_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_Camera_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPXC_FG_put_Camera_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_Brightness_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_Brightness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_Brightness_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPXC_FG_put_Brightness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_FrameGrabberID_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_FrameGrabberID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_FrameGrabberID_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_FrameGrabberID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_ImageTop_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_ImageTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_ImageTop_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_ImageTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_ImageLeft_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_ImageLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_ImageLeft_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_ImageLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_ImageDepth_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_ImageDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_ImageHeight_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_ImageHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_ImageHeight_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_ImageHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPXC_FG_get_ImageWidth_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPXC_FG_get_ImageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPXC_FG_put_ImageWidth_Proxy( 
    IPXC_FG __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPXC_FG_put_ImageWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPXC_FG_Initialize_Proxy( 
    IPXC_FG __RPC_FAR * This);


void __RPC_STUB IPXC_FG_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPXC_FG_ObtainImage_Proxy( 
    IPXC_FG __RPC_FAR * This);


void __RPC_STUB IPXC_FG_ObtainImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPXC_FG_Reset_Proxy( 
    IPXC_FG __RPC_FAR * This);


void __RPC_STUB IPXC_FG_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPXC_FG_Close_Proxy( 
    IPXC_FG __RPC_FAR * This);


void __RPC_STUB IPXC_FG_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPXC_FG_INTERFACE_DEFINED__ */



#ifndef __IMA2_FRAMEGRABBERLIBLib_LIBRARY_DEFINED__
#define __IMA2_FRAMEGRABBERLIBLib_LIBRARY_DEFINED__

/* library IMA2_FRAMEGRABBERLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_FRAMEGRABBERLIBLib;

EXTERN_C const CLSID CLSID_PXC_FG;

#ifdef __cplusplus

class DECLSPEC_UUID("103A665D-AC59-412E-AEFD-0164EF9CB582")
PXC_FG;
#endif
#endif /* __IMA2_FRAMEGRABBERLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
