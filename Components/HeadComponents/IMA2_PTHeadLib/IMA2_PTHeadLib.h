/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 26 12:28:11 2008
 */
/* Compiler settings for O:\Components\HeadComponents\IMA2_PTHeadLib\IMA2_PTHeadLib.idl:
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

#ifndef __IMA2_PTHeadLib_h__
#define __IMA2_PTHeadLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPTCatch_FWD_DEFINED__
#define __IPTCatch_FWD_DEFINED__
typedef interface IPTCatch IPTCatch;
#endif 	/* __IPTCatch_FWD_DEFINED__ */


#ifndef __PTCatch_FWD_DEFINED__
#define __PTCatch_FWD_DEFINED__

#ifdef __cplusplus
typedef class PTCatch PTCatch;
#else
typedef struct PTCatch PTCatch;
#endif /* __cplusplus */

#endif 	/* __PTCatch_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPTCatch_INTERFACE_DEFINED__
#define __IPTCatch_INTERFACE_DEFINED__

/* interface IPTCatch */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPTCatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("868D647B-D30E-4A20-8991-D924224BE1A2")
    IPTCatch : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceFilename1( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeviceFilename1( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceFilename2( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeviceFilename2( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftPanSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftPanSpeed( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RightPanSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RightPanSpeed( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftTiltSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftTiltSpeed( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RightTiltSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RightTiltSpeed( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftPanAccel( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftPanAccel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RightPanAccel( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RightPanAccel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftTiltAccel( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftTiltAccel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RightTiltAccel( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RightTiltAccel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisOffset( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisOffsetIndex( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisOffsetIndex( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CommParams1( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CommParams1( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CommParams2( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CommParams2( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisGain( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisGain( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisGainIndex( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisGainIndex( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisThreshold( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisThreshold( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AxisThresholdIndex( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AxisThresholdIndex( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SampleHead( 
            /* [out][in] */ SAFEARRAY __RPC_FAR * Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CommandHeadAbsolute( 
            /* [in] */ SAFEARRAY __RPC_FAR * Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE aaHeadCommand( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE aaHeadSample( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPTCatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPTCatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPTCatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPTCatch __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceFilename1 )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeviceFilename1 )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceFilename2 )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeviceFilename2 )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftPanSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftPanSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RightPanSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RightPanSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftTiltSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftTiltSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RightTiltSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RightTiltSpeed )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftPanAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftPanAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RightPanAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RightPanAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftTiltAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftTiltAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RightTiltAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RightTiltAccel )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisOffset )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisOffset )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisOffsetIndex )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisOffsetIndex )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommParams1 )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CommParams1 )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommParams2 )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CommParams2 )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisGain )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisGain )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisGainIndex )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisGainIndex )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisThreshold )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisThreshold )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AxisThresholdIndex )( 
            IPTCatch __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AxisThresholdIndex )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SampleHead )( 
            IPTCatch __RPC_FAR * This,
            /* [out][in] */ SAFEARRAY __RPC_FAR * Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CommandHeadAbsolute )( 
            IPTCatch __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IPTCatch __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IPTCatch __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *aaHeadCommand )( 
            IPTCatch __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *aaHeadSample )( 
            IPTCatch __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IPTCatch __RPC_FAR * This);
        
        END_INTERFACE
    } IPTCatchVtbl;

    interface IPTCatch
    {
        CONST_VTBL struct IPTCatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPTCatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPTCatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPTCatch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPTCatch_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPTCatch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPTCatch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPTCatch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPTCatch_get_DeviceFilename1(This,pVal)	\
    (This)->lpVtbl -> get_DeviceFilename1(This,pVal)

#define IPTCatch_put_DeviceFilename1(This,newVal)	\
    (This)->lpVtbl -> put_DeviceFilename1(This,newVal)

#define IPTCatch_get_DeviceFilename2(This,pVal)	\
    (This)->lpVtbl -> get_DeviceFilename2(This,pVal)

#define IPTCatch_put_DeviceFilename2(This,newVal)	\
    (This)->lpVtbl -> put_DeviceFilename2(This,newVal)

#define IPTCatch_get_LeftPanSpeed(This,pVal)	\
    (This)->lpVtbl -> get_LeftPanSpeed(This,pVal)

#define IPTCatch_put_LeftPanSpeed(This,newVal)	\
    (This)->lpVtbl -> put_LeftPanSpeed(This,newVal)

#define IPTCatch_get_RightPanSpeed(This,pVal)	\
    (This)->lpVtbl -> get_RightPanSpeed(This,pVal)

#define IPTCatch_put_RightPanSpeed(This,newVal)	\
    (This)->lpVtbl -> put_RightPanSpeed(This,newVal)

#define IPTCatch_get_LeftTiltSpeed(This,pVal)	\
    (This)->lpVtbl -> get_LeftTiltSpeed(This,pVal)

#define IPTCatch_put_LeftTiltSpeed(This,newVal)	\
    (This)->lpVtbl -> put_LeftTiltSpeed(This,newVal)

#define IPTCatch_get_RightTiltSpeed(This,pVal)	\
    (This)->lpVtbl -> get_RightTiltSpeed(This,pVal)

#define IPTCatch_put_RightTiltSpeed(This,newVal)	\
    (This)->lpVtbl -> put_RightTiltSpeed(This,newVal)

#define IPTCatch_get_LeftPanAccel(This,pVal)	\
    (This)->lpVtbl -> get_LeftPanAccel(This,pVal)

#define IPTCatch_put_LeftPanAccel(This,newVal)	\
    (This)->lpVtbl -> put_LeftPanAccel(This,newVal)

#define IPTCatch_get_RightPanAccel(This,pVal)	\
    (This)->lpVtbl -> get_RightPanAccel(This,pVal)

#define IPTCatch_put_RightPanAccel(This,newVal)	\
    (This)->lpVtbl -> put_RightPanAccel(This,newVal)

#define IPTCatch_get_LeftTiltAccel(This,pVal)	\
    (This)->lpVtbl -> get_LeftTiltAccel(This,pVal)

#define IPTCatch_put_LeftTiltAccel(This,newVal)	\
    (This)->lpVtbl -> put_LeftTiltAccel(This,newVal)

#define IPTCatch_get_RightTiltAccel(This,pVal)	\
    (This)->lpVtbl -> get_RightTiltAccel(This,pVal)

#define IPTCatch_put_RightTiltAccel(This,newVal)	\
    (This)->lpVtbl -> put_RightTiltAccel(This,newVal)

#define IPTCatch_get_AxisOffset(This,pVal)	\
    (This)->lpVtbl -> get_AxisOffset(This,pVal)

#define IPTCatch_put_AxisOffset(This,newVal)	\
    (This)->lpVtbl -> put_AxisOffset(This,newVal)

#define IPTCatch_get_AxisOffsetIndex(This,pVal)	\
    (This)->lpVtbl -> get_AxisOffsetIndex(This,pVal)

#define IPTCatch_put_AxisOffsetIndex(This,newVal)	\
    (This)->lpVtbl -> put_AxisOffsetIndex(This,newVal)

#define IPTCatch_get_CommParams1(This,pVal)	\
    (This)->lpVtbl -> get_CommParams1(This,pVal)

#define IPTCatch_put_CommParams1(This,newVal)	\
    (This)->lpVtbl -> put_CommParams1(This,newVal)

#define IPTCatch_get_CommParams2(This,pVal)	\
    (This)->lpVtbl -> get_CommParams2(This,pVal)

#define IPTCatch_put_CommParams2(This,newVal)	\
    (This)->lpVtbl -> put_CommParams2(This,newVal)

#define IPTCatch_get_AxisGain(This,pVal)	\
    (This)->lpVtbl -> get_AxisGain(This,pVal)

#define IPTCatch_put_AxisGain(This,newVal)	\
    (This)->lpVtbl -> put_AxisGain(This,newVal)

#define IPTCatch_get_AxisGainIndex(This,pVal)	\
    (This)->lpVtbl -> get_AxisGainIndex(This,pVal)

#define IPTCatch_put_AxisGainIndex(This,newVal)	\
    (This)->lpVtbl -> put_AxisGainIndex(This,newVal)

#define IPTCatch_get_AxisThreshold(This,pVal)	\
    (This)->lpVtbl -> get_AxisThreshold(This,pVal)

#define IPTCatch_put_AxisThreshold(This,newVal)	\
    (This)->lpVtbl -> put_AxisThreshold(This,newVal)

#define IPTCatch_get_AxisThresholdIndex(This,pVal)	\
    (This)->lpVtbl -> get_AxisThresholdIndex(This,pVal)

#define IPTCatch_put_AxisThresholdIndex(This,newVal)	\
    (This)->lpVtbl -> put_AxisThresholdIndex(This,newVal)

#define IPTCatch_SampleHead(This,Val)	\
    (This)->lpVtbl -> SampleHead(This,Val)

#define IPTCatch_CommandHeadAbsolute(This,Val)	\
    (This)->lpVtbl -> CommandHeadAbsolute(This,Val)

#define IPTCatch_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IPTCatch_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IPTCatch_aaHeadCommand(This)	\
    (This)->lpVtbl -> aaHeadCommand(This)

#define IPTCatch_aaHeadSample(This)	\
    (This)->lpVtbl -> aaHeadSample(This)

#define IPTCatch_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_DeviceFilename1_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_DeviceFilename1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_DeviceFilename1_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPTCatch_put_DeviceFilename1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_DeviceFilename2_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_DeviceFilename2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_DeviceFilename2_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPTCatch_put_DeviceFilename2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_LeftPanSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_LeftPanSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_LeftPanSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_LeftPanSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_RightPanSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_RightPanSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_RightPanSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_RightPanSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_LeftTiltSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_LeftTiltSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_LeftTiltSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_LeftTiltSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_RightTiltSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_RightTiltSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_RightTiltSpeed_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_RightTiltSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_LeftPanAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_LeftPanAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_LeftPanAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_LeftPanAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_RightPanAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_RightPanAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_RightPanAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_RightPanAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_LeftTiltAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_LeftTiltAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_LeftTiltAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_LeftTiltAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_RightTiltAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_RightTiltAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_RightTiltAccel_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_RightTiltAccel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_AxisOffset_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_AxisOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_AxisOffset_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPTCatch_put_AxisOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_AxisOffsetIndex_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_AxisOffsetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_AxisOffsetIndex_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IPTCatch_put_AxisOffsetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_CommParams1_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_CommParams1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_CommParams1_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPTCatch_put_CommParams1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_CommParams2_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_CommParams2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_CommParams2_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPTCatch_put_CommParams2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_AxisGain_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_AxisGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_AxisGain_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPTCatch_put_AxisGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_AxisGainIndex_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_AxisGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_AxisGainIndex_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IPTCatch_put_AxisGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_AxisThreshold_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_AxisThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_AxisThreshold_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IPTCatch_put_AxisThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPTCatch_get_AxisThresholdIndex_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IPTCatch_get_AxisThresholdIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPTCatch_put_AxisThresholdIndex_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IPTCatch_put_AxisThresholdIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_SampleHead_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [out][in] */ SAFEARRAY __RPC_FAR * Val);


void __RPC_STUB IPTCatch_SampleHead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_CommandHeadAbsolute_Proxy( 
    IPTCatch __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * Val);


void __RPC_STUB IPTCatch_CommandHeadAbsolute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_Stop_Proxy( 
    IPTCatch __RPC_FAR * This);


void __RPC_STUB IPTCatch_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_Reset_Proxy( 
    IPTCatch __RPC_FAR * This);


void __RPC_STUB IPTCatch_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_aaHeadCommand_Proxy( 
    IPTCatch __RPC_FAR * This);


void __RPC_STUB IPTCatch_aaHeadCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_aaHeadSample_Proxy( 
    IPTCatch __RPC_FAR * This);


void __RPC_STUB IPTCatch_aaHeadSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPTCatch_Initialize_Proxy( 
    IPTCatch __RPC_FAR * This);


void __RPC_STUB IPTCatch_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPTCatch_INTERFACE_DEFINED__ */



#ifndef __IMA2_PTHEADLIBLib_LIBRARY_DEFINED__
#define __IMA2_PTHEADLIBLib_LIBRARY_DEFINED__

/* library IMA2_PTHEADLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_PTHEADLIBLib;

EXTERN_C const CLSID CLSID_PTCatch;

#ifdef __cplusplus

class DECLSPEC_UUID("84638812-DA4D-445F-8D46-04B2961F7A1F")
PTCatch;
#endif
#endif /* __IMA2_PTHEADLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
