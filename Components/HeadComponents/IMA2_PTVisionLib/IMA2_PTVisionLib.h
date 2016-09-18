/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 28 15:33:51 2008
 */
/* Compiler settings for O:\Components\HeadComponents\IMA2_PTVisionLib\IMA2_PTVisionLib.idl:
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

#ifndef __IMA2_PTVisionLib_h__
#define __IMA2_PTVisionLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPTSmoothPursuit_FWD_DEFINED__
#define __IPTSmoothPursuit_FWD_DEFINED__
typedef interface IPTSmoothPursuit IPTSmoothPursuit;
#endif 	/* __IPTSmoothPursuit_FWD_DEFINED__ */


#ifndef __IVisualInputRepresentation_FWD_DEFINED__
#define __IVisualInputRepresentation_FWD_DEFINED__
typedef interface IVisualInputRepresentation IVisualInputRepresentation;
#endif 	/* __IVisualInputRepresentation_FWD_DEFINED__ */


#ifndef __ISaccade_FWD_DEFINED__
#define __ISaccade_FWD_DEFINED__
typedef interface ISaccade ISaccade;
#endif 	/* __ISaccade_FWD_DEFINED__ */


#ifndef __IEyeMotionCenter_FWD_DEFINED__
#define __IEyeMotionCenter_FWD_DEFINED__
typedef interface IEyeMotionCenter IEyeMotionCenter;
#endif 	/* __IEyeMotionCenter_FWD_DEFINED__ */


#ifndef __PTSmoothPursuit_FWD_DEFINED__
#define __PTSmoothPursuit_FWD_DEFINED__

#ifdef __cplusplus
typedef class PTSmoothPursuit PTSmoothPursuit;
#else
typedef struct PTSmoothPursuit PTSmoothPursuit;
#endif /* __cplusplus */

#endif 	/* __PTSmoothPursuit_FWD_DEFINED__ */


#ifndef __VisualInputRepresentation_FWD_DEFINED__
#define __VisualInputRepresentation_FWD_DEFINED__

#ifdef __cplusplus
typedef class VisualInputRepresentation VisualInputRepresentation;
#else
typedef struct VisualInputRepresentation VisualInputRepresentation;
#endif /* __cplusplus */

#endif 	/* __VisualInputRepresentation_FWD_DEFINED__ */


#ifndef __Saccade_FWD_DEFINED__
#define __Saccade_FWD_DEFINED__

#ifdef __cplusplus
typedef class Saccade Saccade;
#else
typedef struct Saccade Saccade;
#endif /* __cplusplus */

#endif 	/* __Saccade_FWD_DEFINED__ */


#ifndef __EyeMotionCenter_FWD_DEFINED__
#define __EyeMotionCenter_FWD_DEFINED__

#ifdef __cplusplus
typedef class EyeMotionCenter EyeMotionCenter;
#else
typedef struct EyeMotionCenter EyeMotionCenter;
#endif /* __cplusplus */

#endif 	/* __EyeMotionCenter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPTSmoothPursuit_INTERFACE_DEFINED__
#define __IPTSmoothPursuit_INTERFACE_DEFINED__

/* interface IPTSmoothPursuit */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPTSmoothPursuit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF9FC7F2-C451-48CE-AE8D-E37FA9583DBD")
    IPTSmoothPursuit : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LowPassFilterConstant( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LowPassFilterConstant( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SchemaWeights( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SchemaWeights( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUpdate( 
            SAFEARRAY __RPC_FAR * Value,
            short Method) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPTSmoothPursuitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPTSmoothPursuit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPTSmoothPursuit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LowPassFilterConstant )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LowPassFilterConstant )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SchemaWeights )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SchemaWeights )( 
            IPTSmoothPursuit __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUpdate )( 
            IPTSmoothPursuit __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * Value,
            short Method);
        
        END_INTERFACE
    } IPTSmoothPursuitVtbl;

    interface IPTSmoothPursuit
    {
        CONST_VTBL struct IPTSmoothPursuitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPTSmoothPursuit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPTSmoothPursuit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPTSmoothPursuit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPTSmoothPursuit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPTSmoothPursuit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPTSmoothPursuit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPTSmoothPursuit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPTSmoothPursuit_get_LowPassFilterConstant(This,pVal)	\
    (This)->lpVtbl -> get_LowPassFilterConstant(This,pVal)

#define IPTSmoothPursuit_put_LowPassFilterConstant(This,newVal)	\
    (This)->lpVtbl -> put_LowPassFilterConstant(This,newVal)

#define IPTSmoothPursuit_get_SchemaWeights(This,pVal)	\
    (This)->lpVtbl -> get_SchemaWeights(This,pVal)

#define IPTSmoothPursuit_put_SchemaWeights(This,newVal)	\
    (This)->lpVtbl -> put_SchemaWeights(This,newVal)

#define IPTSmoothPursuit_GetUpdate(This,Value,Method)	\
    (This)->lpVtbl -> GetUpdate(This,Value,Method)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTSmoothPursuit_get_LowPassFilterConstant_Proxy( 
    IPTSmoothPursuit __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPTSmoothPursuit_get_LowPassFilterConstant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTSmoothPursuit_put_LowPassFilterConstant_Proxy( 
    IPTSmoothPursuit __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPTSmoothPursuit_put_LowPassFilterConstant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTSmoothPursuit_get_SchemaWeights_Proxy( 
    IPTSmoothPursuit __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPTSmoothPursuit_get_SchemaWeights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTSmoothPursuit_put_SchemaWeights_Proxy( 
    IPTSmoothPursuit __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPTSmoothPursuit_put_SchemaWeights_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTSmoothPursuit_GetUpdate_Proxy( 
    IPTSmoothPursuit __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * Value,
    short Method);


void __RPC_STUB IPTSmoothPursuit_GetUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPTSmoothPursuit_INTERFACE_DEFINED__ */


#ifndef __IVisualInputRepresentation_INTERFACE_DEFINED__
#define __IVisualInputRepresentation_INTERFACE_DEFINED__

/* interface IVisualInputRepresentation */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVisualInputRepresentation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6604D381-1DFD-40C0-86ED-5BA4BD4EC093")
    IVisualInputRepresentation : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTargetLocation( 
            long CameraID,
            double __RPC_FAR *Location,
            long Length) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImage( 
            long ImageID,
            long __RPC_FAR *ImagePointer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTargetLocation( 
            long CameraID,
            double __RPC_FAR *Location,
            double Length) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEyeMovementStatus( 
            double __RPC_FAR *Status,
            double Length) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEyeMovementStatus( 
            double __RPC_FAR *Status,
            double Length) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ObtainTargetLoc( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisualInputRepresentationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisualInputRepresentation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisualInputRepresentation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisualInputRepresentation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVisualInputRepresentation __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVisualInputRepresentation __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVisualInputRepresentation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVisualInputRepresentation __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTargetLocation )( 
            IVisualInputRepresentation __RPC_FAR * This,
            long CameraID,
            double __RPC_FAR *Location,
            long Length);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImage )( 
            IVisualInputRepresentation __RPC_FAR * This,
            long ImageID,
            long __RPC_FAR *ImagePointer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTargetLocation )( 
            IVisualInputRepresentation __RPC_FAR * This,
            long CameraID,
            double __RPC_FAR *Location,
            double Length);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEyeMovementStatus )( 
            IVisualInputRepresentation __RPC_FAR * This,
            double __RPC_FAR *Status,
            double Length);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEyeMovementStatus )( 
            IVisualInputRepresentation __RPC_FAR * This,
            double __RPC_FAR *Status,
            double Length);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ObtainTargetLoc )( 
            IVisualInputRepresentation __RPC_FAR * This);
        
        END_INTERFACE
    } IVisualInputRepresentationVtbl;

    interface IVisualInputRepresentation
    {
        CONST_VTBL struct IVisualInputRepresentationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisualInputRepresentation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisualInputRepresentation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisualInputRepresentation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisualInputRepresentation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVisualInputRepresentation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVisualInputRepresentation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVisualInputRepresentation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVisualInputRepresentation_GetTargetLocation(This,CameraID,Location,Length)	\
    (This)->lpVtbl -> GetTargetLocation(This,CameraID,Location,Length)

#define IVisualInputRepresentation_GetImage(This,ImageID,ImagePointer)	\
    (This)->lpVtbl -> GetImage(This,ImageID,ImagePointer)

#define IVisualInputRepresentation_SetTargetLocation(This,CameraID,Location,Length)	\
    (This)->lpVtbl -> SetTargetLocation(This,CameraID,Location,Length)

#define IVisualInputRepresentation_GetEyeMovementStatus(This,Status,Length)	\
    (This)->lpVtbl -> GetEyeMovementStatus(This,Status,Length)

#define IVisualInputRepresentation_SetEyeMovementStatus(This,Status,Length)	\
    (This)->lpVtbl -> SetEyeMovementStatus(This,Status,Length)

#define IVisualInputRepresentation_ObtainTargetLoc(This)	\
    (This)->lpVtbl -> ObtainTargetLoc(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVisualInputRepresentation_GetTargetLocation_Proxy( 
    IVisualInputRepresentation __RPC_FAR * This,
    long CameraID,
    double __RPC_FAR *Location,
    long Length);


void __RPC_STUB IVisualInputRepresentation_GetTargetLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVisualInputRepresentation_GetImage_Proxy( 
    IVisualInputRepresentation __RPC_FAR * This,
    long ImageID,
    long __RPC_FAR *ImagePointer);


void __RPC_STUB IVisualInputRepresentation_GetImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVisualInputRepresentation_SetTargetLocation_Proxy( 
    IVisualInputRepresentation __RPC_FAR * This,
    long CameraID,
    double __RPC_FAR *Location,
    double Length);


void __RPC_STUB IVisualInputRepresentation_SetTargetLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVisualInputRepresentation_GetEyeMovementStatus_Proxy( 
    IVisualInputRepresentation __RPC_FAR * This,
    double __RPC_FAR *Status,
    double Length);


void __RPC_STUB IVisualInputRepresentation_GetEyeMovementStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVisualInputRepresentation_SetEyeMovementStatus_Proxy( 
    IVisualInputRepresentation __RPC_FAR * This,
    double __RPC_FAR *Status,
    double Length);


void __RPC_STUB IVisualInputRepresentation_SetEyeMovementStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVisualInputRepresentation_ObtainTargetLoc_Proxy( 
    IVisualInputRepresentation __RPC_FAR * This);


void __RPC_STUB IVisualInputRepresentation_ObtainTargetLoc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisualInputRepresentation_INTERFACE_DEFINED__ */


#ifndef __ISaccade_INTERFACE_DEFINED__
#define __ISaccade_INTERFACE_DEFINED__

/* interface ISaccade */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISaccade;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FB6BC121-8C4B-4E52-AEDA-3F80A1C944C4")
    ISaccade : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE aaSaccade( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUpdate( 
            long CameraID,
            double __RPC_FAR *Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaccadeFunction( 
            double __RPC_FAR *ImagePosition,
            double __RPC_FAR *MotorOutput) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISaccadeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISaccade __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISaccade __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISaccade __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISaccade __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISaccade __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISaccade __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISaccade __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *aaSaccade )( 
            ISaccade __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUpdate )( 
            ISaccade __RPC_FAR * This,
            long CameraID,
            double __RPC_FAR *Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaccadeFunction )( 
            ISaccade __RPC_FAR * This,
            double __RPC_FAR *ImagePosition,
            double __RPC_FAR *MotorOutput);
        
        END_INTERFACE
    } ISaccadeVtbl;

    interface ISaccade
    {
        CONST_VTBL struct ISaccadeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISaccade_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISaccade_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISaccade_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISaccade_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISaccade_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISaccade_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISaccade_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISaccade_aaSaccade(This)	\
    (This)->lpVtbl -> aaSaccade(This)

#define ISaccade_GetUpdate(This,CameraID,Value)	\
    (This)->lpVtbl -> GetUpdate(This,CameraID,Value)

#define ISaccade_SaccadeFunction(This,ImagePosition,MotorOutput)	\
    (This)->lpVtbl -> SaccadeFunction(This,ImagePosition,MotorOutput)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISaccade_aaSaccade_Proxy( 
    ISaccade __RPC_FAR * This);


void __RPC_STUB ISaccade_aaSaccade_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISaccade_GetUpdate_Proxy( 
    ISaccade __RPC_FAR * This,
    long CameraID,
    double __RPC_FAR *Value);


void __RPC_STUB ISaccade_GetUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISaccade_SaccadeFunction_Proxy( 
    ISaccade __RPC_FAR * This,
    double __RPC_FAR *ImagePosition,
    double __RPC_FAR *MotorOutput);


void __RPC_STUB ISaccade_SaccadeFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISaccade_INTERFACE_DEFINED__ */


#ifndef __IEyeMotionCenter_INTERFACE_DEFINED__
#define __IEyeMotionCenter_INTERFACE_DEFINED__

/* interface IEyeMotionCenter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEyeMotionCenter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7E050FD-F710-4005-B5E8-B14D1EF6C83A")
    IEyeMotionCenter : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeadZoneIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeadZoneIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PTTargetThresholdIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PTTargetThresholdIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeadZone( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeadZone( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PTTargetThreshold( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PTTargetThreshold( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CameraSpeedFactor( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CameraSpeedFactor( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HeadSample( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoProportionalTracking( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteMotorPositions( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEyeMotionCenterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEyeMotionCenter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEyeMotionCenter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeadZoneIndex )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeadZoneIndex )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PTTargetThresholdIndex )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PTTargetThresholdIndex )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeadZone )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeadZone )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PTTargetThreshold )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PTTargetThreshold )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CameraSpeedFactor )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CameraSpeedFactor )( 
            IEyeMotionCenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HeadSample )( 
            IEyeMotionCenter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoProportionalTracking )( 
            IEyeMotionCenter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteMotorPositions )( 
            IEyeMotionCenter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEyeMotionCenter __RPC_FAR * This);
        
        END_INTERFACE
    } IEyeMotionCenterVtbl;

    interface IEyeMotionCenter
    {
        CONST_VTBL struct IEyeMotionCenterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEyeMotionCenter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEyeMotionCenter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEyeMotionCenter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEyeMotionCenter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEyeMotionCenter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEyeMotionCenter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEyeMotionCenter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEyeMotionCenter_get_DeadZoneIndex(This,pVal)	\
    (This)->lpVtbl -> get_DeadZoneIndex(This,pVal)

#define IEyeMotionCenter_put_DeadZoneIndex(This,newVal)	\
    (This)->lpVtbl -> put_DeadZoneIndex(This,newVal)

#define IEyeMotionCenter_get_PTTargetThresholdIndex(This,pVal)	\
    (This)->lpVtbl -> get_PTTargetThresholdIndex(This,pVal)

#define IEyeMotionCenter_put_PTTargetThresholdIndex(This,newVal)	\
    (This)->lpVtbl -> put_PTTargetThresholdIndex(This,newVal)

#define IEyeMotionCenter_get_DeadZone(This,pVal)	\
    (This)->lpVtbl -> get_DeadZone(This,pVal)

#define IEyeMotionCenter_put_DeadZone(This,newVal)	\
    (This)->lpVtbl -> put_DeadZone(This,newVal)

#define IEyeMotionCenter_get_PTTargetThreshold(This,pVal)	\
    (This)->lpVtbl -> get_PTTargetThreshold(This,pVal)

#define IEyeMotionCenter_put_PTTargetThreshold(This,newVal)	\
    (This)->lpVtbl -> put_PTTargetThreshold(This,newVal)

#define IEyeMotionCenter_get_CameraSpeedFactor(This,pVal)	\
    (This)->lpVtbl -> get_CameraSpeedFactor(This,pVal)

#define IEyeMotionCenter_put_CameraSpeedFactor(This,newVal)	\
    (This)->lpVtbl -> put_CameraSpeedFactor(This,newVal)

#define IEyeMotionCenter_HeadSample(This)	\
    (This)->lpVtbl -> HeadSample(This)

#define IEyeMotionCenter_DoProportionalTracking(This)	\
    (This)->lpVtbl -> DoProportionalTracking(This)

#define IEyeMotionCenter_WriteMotorPositions(This)	\
    (This)->lpVtbl -> WriteMotorPositions(This)

#define IEyeMotionCenter_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_get_DeadZoneIndex_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEyeMotionCenter_get_DeadZoneIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_put_DeadZoneIndex_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IEyeMotionCenter_put_DeadZoneIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_get_PTTargetThresholdIndex_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEyeMotionCenter_get_PTTargetThresholdIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_put_PTTargetThresholdIndex_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IEyeMotionCenter_put_PTTargetThresholdIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_get_DeadZone_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IEyeMotionCenter_get_DeadZone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_put_DeadZone_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IEyeMotionCenter_put_DeadZone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_get_PTTargetThreshold_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IEyeMotionCenter_get_PTTargetThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_put_PTTargetThreshold_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IEyeMotionCenter_put_PTTargetThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_get_CameraSpeedFactor_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IEyeMotionCenter_get_CameraSpeedFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_put_CameraSpeedFactor_Proxy( 
    IEyeMotionCenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IEyeMotionCenter_put_CameraSpeedFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_HeadSample_Proxy( 
    IEyeMotionCenter __RPC_FAR * This);


void __RPC_STUB IEyeMotionCenter_HeadSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_DoProportionalTracking_Proxy( 
    IEyeMotionCenter __RPC_FAR * This);


void __RPC_STUB IEyeMotionCenter_DoProportionalTracking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_WriteMotorPositions_Proxy( 
    IEyeMotionCenter __RPC_FAR * This);


void __RPC_STUB IEyeMotionCenter_WriteMotorPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeMotionCenter_Initialize_Proxy( 
    IEyeMotionCenter __RPC_FAR * This);


void __RPC_STUB IEyeMotionCenter_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEyeMotionCenter_INTERFACE_DEFINED__ */



#ifndef __IMA2_PTVISIONLIBLib_LIBRARY_DEFINED__
#define __IMA2_PTVISIONLIBLib_LIBRARY_DEFINED__

/* library IMA2_PTVISIONLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_PTVISIONLIBLib;

EXTERN_C const CLSID CLSID_PTSmoothPursuit;

#ifdef __cplusplus

class DECLSPEC_UUID("781AAC54-EE77-4BDA-BAF2-B3CF413EEFB8")
PTSmoothPursuit;
#endif

EXTERN_C const CLSID CLSID_VisualInputRepresentation;

#ifdef __cplusplus

class DECLSPEC_UUID("C5044BD7-77C6-4B82-982D-89C63B15AF93")
VisualInputRepresentation;
#endif

EXTERN_C const CLSID CLSID_Saccade;

#ifdef __cplusplus

class DECLSPEC_UUID("4C169BF4-37A3-422A-BFC6-909E319949F2")
Saccade;
#endif

EXTERN_C const CLSID CLSID_EyeMotionCenter;

#ifdef __cplusplus

class DECLSPEC_UUID("ED3A5186-5F85-4EF1-BD31-20CA54C54632")
EyeMotionCenter;
#endif
#endif /* __IMA2_PTVISIONLIBLib_LIBRARY_DEFINED__ */

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
