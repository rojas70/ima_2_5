/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 23 14:10:04 2008
 */
/* Compiler settings for O:\Components\ControlBasis\IMA2_ControlBasisLib\IMA2_ControlBasisLib.idl:
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

#ifndef __IMA2_ControlBasisLib_h__
#define __IMA2_ControlBasisLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IControlBasis_FWD_DEFINED__
#define __IControlBasis_FWD_DEFINED__
typedef interface IControlBasis IControlBasis;
#endif 	/* __IControlBasis_FWD_DEFINED__ */


#ifndef __ControlBasis_FWD_DEFINED__
#define __ControlBasis_FWD_DEFINED__

#ifdef __cplusplus
typedef class ControlBasis ControlBasis;
#else
typedef struct ControlBasis ControlBasis;
#endif /* __cplusplus */

#endif 	/* __ControlBasis_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IControlBasis_INTERFACE_DEFINED__
#define __IControlBasis_INTERFACE_DEFINED__

/* interface IControlBasis */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IControlBasis;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3FA17E2C-11C9-4460-8247-F7CFD8FBE886")
    IControlBasis : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhatRobot( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WhatRobot( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cont_NumControllers( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_cont_NumControllers( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_PositionGain( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_PositionGain( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_ForceGain( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_ForceGain( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_MomentGain( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_MomentGain( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorMessage( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ErrorMessage( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dom_DesiredVector( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dom_DesiredVector( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dom_ActualVector( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dom_ActualVector( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dom_OutputVector( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dom_OutputVector( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dom_DesiredVectorIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dom_DesiredVectorIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dom_ActualVectorIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dom_ActualVectorIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dom_OutputVectorIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dom_OutputVectorIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sub_DesiredVector( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sub_DesiredVector( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sub_ActualVector( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sub_ActualVector( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sub_OutputVector( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sub_OutputVector( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sub_ActualVectorIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sub_ActualVectorIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sub_DesiredVectorIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sub_DesiredVectorIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_sub_OutputVectorIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_sub_OutputVectorIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cont_DomContType( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_cont_DomContType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cont_SubContType( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_cont_SubContType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_PositionGainIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_PositionGainIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_ForceGainIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_ForceGainIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_gain_MomentGainIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_gain_MomentGainIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ComputeControlBasis( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AveragingWeight_JointAngles( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AveragingWeight_JointAngles( 
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IControlBasisVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IControlBasis __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IControlBasis __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IControlBasis __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatRobot )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WhatRobot )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cont_NumControllers )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cont_NumControllers )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_PositionGain )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_PositionGain )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_ForceGain )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_ForceGain )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_MomentGain )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_MomentGain )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErrorMessage )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErrorMessage )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dom_DesiredVector )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dom_DesiredVector )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dom_ActualVector )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dom_ActualVector )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dom_OutputVector )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dom_OutputVector )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dom_DesiredVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dom_DesiredVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dom_ActualVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dom_ActualVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dom_OutputVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dom_OutputVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sub_DesiredVector )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sub_DesiredVector )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sub_ActualVector )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sub_ActualVector )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sub_OutputVector )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sub_OutputVector )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sub_ActualVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sub_ActualVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sub_DesiredVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sub_DesiredVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sub_OutputVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sub_OutputVectorIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cont_DomContType )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cont_DomContType )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cont_SubContType )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cont_SubContType )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_PositionGainIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_PositionGainIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_ForceGainIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_ForceGainIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_gain_MomentGainIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_gain_MomentGainIndex )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ComputeControlBasis )( 
            IControlBasis __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IControlBasis __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AveragingWeight_JointAngles )( 
            IControlBasis __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AveragingWeight_JointAngles )( 
            IControlBasis __RPC_FAR * This,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } IControlBasisVtbl;

    interface IControlBasis
    {
        CONST_VTBL struct IControlBasisVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IControlBasis_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IControlBasis_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IControlBasis_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IControlBasis_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IControlBasis_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IControlBasis_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IControlBasis_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IControlBasis_get_WhatRobot(This,pVal)	\
    (This)->lpVtbl -> get_WhatRobot(This,pVal)

#define IControlBasis_put_WhatRobot(This,newVal)	\
    (This)->lpVtbl -> put_WhatRobot(This,newVal)

#define IControlBasis_get_cont_NumControllers(This,pVal)	\
    (This)->lpVtbl -> get_cont_NumControllers(This,pVal)

#define IControlBasis_put_cont_NumControllers(This,newVal)	\
    (This)->lpVtbl -> put_cont_NumControllers(This,newVal)

#define IControlBasis_get_gain_PositionGain(This,pVal)	\
    (This)->lpVtbl -> get_gain_PositionGain(This,pVal)

#define IControlBasis_put_gain_PositionGain(This,newVal)	\
    (This)->lpVtbl -> put_gain_PositionGain(This,newVal)

#define IControlBasis_get_gain_ForceGain(This,pVal)	\
    (This)->lpVtbl -> get_gain_ForceGain(This,pVal)

#define IControlBasis_put_gain_ForceGain(This,newVal)	\
    (This)->lpVtbl -> put_gain_ForceGain(This,newVal)

#define IControlBasis_get_gain_MomentGain(This,pVal)	\
    (This)->lpVtbl -> get_gain_MomentGain(This,pVal)

#define IControlBasis_put_gain_MomentGain(This,newVal)	\
    (This)->lpVtbl -> put_gain_MomentGain(This,newVal)

#define IControlBasis_get_ErrorMessage(This,pVal)	\
    (This)->lpVtbl -> get_ErrorMessage(This,pVal)

#define IControlBasis_put_ErrorMessage(This,newVal)	\
    (This)->lpVtbl -> put_ErrorMessage(This,newVal)

#define IControlBasis_get_dom_DesiredVector(This,pVal)	\
    (This)->lpVtbl -> get_dom_DesiredVector(This,pVal)

#define IControlBasis_put_dom_DesiredVector(This,newVal)	\
    (This)->lpVtbl -> put_dom_DesiredVector(This,newVal)

#define IControlBasis_get_dom_ActualVector(This,pVal)	\
    (This)->lpVtbl -> get_dom_ActualVector(This,pVal)

#define IControlBasis_put_dom_ActualVector(This,newVal)	\
    (This)->lpVtbl -> put_dom_ActualVector(This,newVal)

#define IControlBasis_get_dom_OutputVector(This,pVal)	\
    (This)->lpVtbl -> get_dom_OutputVector(This,pVal)

#define IControlBasis_put_dom_OutputVector(This,newVal)	\
    (This)->lpVtbl -> put_dom_OutputVector(This,newVal)

#define IControlBasis_get_dom_DesiredVectorIndex(This,pVal)	\
    (This)->lpVtbl -> get_dom_DesiredVectorIndex(This,pVal)

#define IControlBasis_put_dom_DesiredVectorIndex(This,newVal)	\
    (This)->lpVtbl -> put_dom_DesiredVectorIndex(This,newVal)

#define IControlBasis_get_dom_ActualVectorIndex(This,pVal)	\
    (This)->lpVtbl -> get_dom_ActualVectorIndex(This,pVal)

#define IControlBasis_put_dom_ActualVectorIndex(This,newVal)	\
    (This)->lpVtbl -> put_dom_ActualVectorIndex(This,newVal)

#define IControlBasis_get_dom_OutputVectorIndex(This,pVal)	\
    (This)->lpVtbl -> get_dom_OutputVectorIndex(This,pVal)

#define IControlBasis_put_dom_OutputVectorIndex(This,newVal)	\
    (This)->lpVtbl -> put_dom_OutputVectorIndex(This,newVal)

#define IControlBasis_get_sub_DesiredVector(This,pVal)	\
    (This)->lpVtbl -> get_sub_DesiredVector(This,pVal)

#define IControlBasis_put_sub_DesiredVector(This,newVal)	\
    (This)->lpVtbl -> put_sub_DesiredVector(This,newVal)

#define IControlBasis_get_sub_ActualVector(This,pVal)	\
    (This)->lpVtbl -> get_sub_ActualVector(This,pVal)

#define IControlBasis_put_sub_ActualVector(This,newVal)	\
    (This)->lpVtbl -> put_sub_ActualVector(This,newVal)

#define IControlBasis_get_sub_OutputVector(This,pVal)	\
    (This)->lpVtbl -> get_sub_OutputVector(This,pVal)

#define IControlBasis_put_sub_OutputVector(This,newVal)	\
    (This)->lpVtbl -> put_sub_OutputVector(This,newVal)

#define IControlBasis_get_sub_ActualVectorIndex(This,pVal)	\
    (This)->lpVtbl -> get_sub_ActualVectorIndex(This,pVal)

#define IControlBasis_put_sub_ActualVectorIndex(This,newVal)	\
    (This)->lpVtbl -> put_sub_ActualVectorIndex(This,newVal)

#define IControlBasis_get_sub_DesiredVectorIndex(This,pVal)	\
    (This)->lpVtbl -> get_sub_DesiredVectorIndex(This,pVal)

#define IControlBasis_put_sub_DesiredVectorIndex(This,newVal)	\
    (This)->lpVtbl -> put_sub_DesiredVectorIndex(This,newVal)

#define IControlBasis_get_sub_OutputVectorIndex(This,pVal)	\
    (This)->lpVtbl -> get_sub_OutputVectorIndex(This,pVal)

#define IControlBasis_put_sub_OutputVectorIndex(This,newVal)	\
    (This)->lpVtbl -> put_sub_OutputVectorIndex(This,newVal)

#define IControlBasis_get_cont_DomContType(This,pVal)	\
    (This)->lpVtbl -> get_cont_DomContType(This,pVal)

#define IControlBasis_put_cont_DomContType(This,newVal)	\
    (This)->lpVtbl -> put_cont_DomContType(This,newVal)

#define IControlBasis_get_cont_SubContType(This,pVal)	\
    (This)->lpVtbl -> get_cont_SubContType(This,pVal)

#define IControlBasis_put_cont_SubContType(This,newVal)	\
    (This)->lpVtbl -> put_cont_SubContType(This,newVal)

#define IControlBasis_get_gain_PositionGainIndex(This,pVal)	\
    (This)->lpVtbl -> get_gain_PositionGainIndex(This,pVal)

#define IControlBasis_put_gain_PositionGainIndex(This,newVal)	\
    (This)->lpVtbl -> put_gain_PositionGainIndex(This,newVal)

#define IControlBasis_get_gain_ForceGainIndex(This,pVal)	\
    (This)->lpVtbl -> get_gain_ForceGainIndex(This,pVal)

#define IControlBasis_put_gain_ForceGainIndex(This,newVal)	\
    (This)->lpVtbl -> put_gain_ForceGainIndex(This,newVal)

#define IControlBasis_get_gain_MomentGainIndex(This,pVal)	\
    (This)->lpVtbl -> get_gain_MomentGainIndex(This,pVal)

#define IControlBasis_put_gain_MomentGainIndex(This,newVal)	\
    (This)->lpVtbl -> put_gain_MomentGainIndex(This,newVal)

#define IControlBasis_ComputeControlBasis(This)	\
    (This)->lpVtbl -> ComputeControlBasis(This)

#define IControlBasis_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IControlBasis_get_AveragingWeight_JointAngles(This,pVal)	\
    (This)->lpVtbl -> get_AveragingWeight_JointAngles(This,pVal)

#define IControlBasis_put_AveragingWeight_JointAngles(This,newVal)	\
    (This)->lpVtbl -> put_AveragingWeight_JointAngles(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_WhatRobot_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_WhatRobot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_WhatRobot_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IControlBasis_put_WhatRobot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_cont_NumControllers_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_cont_NumControllers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_cont_NumControllers_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_cont_NumControllers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_gain_PositionGain_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_gain_PositionGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_gain_PositionGain_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_gain_PositionGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_gain_ForceGain_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_gain_ForceGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_gain_ForceGain_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_gain_ForceGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_gain_MomentGain_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_gain_MomentGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_gain_MomentGain_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_gain_MomentGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_ErrorMessage_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_ErrorMessage_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IControlBasis_put_ErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_dom_DesiredVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_dom_DesiredVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_dom_DesiredVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_dom_DesiredVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_dom_ActualVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_dom_ActualVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_dom_ActualVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_dom_ActualVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_dom_OutputVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_dom_OutputVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_dom_OutputVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_dom_OutputVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_dom_DesiredVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_dom_DesiredVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_dom_DesiredVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_dom_DesiredVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_dom_ActualVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_dom_ActualVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_dom_ActualVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_dom_ActualVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_dom_OutputVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_dom_OutputVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_dom_OutputVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_dom_OutputVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_sub_DesiredVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_sub_DesiredVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_sub_DesiredVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_sub_DesiredVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_sub_ActualVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_sub_ActualVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_sub_ActualVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_sub_ActualVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_sub_OutputVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_sub_OutputVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_sub_OutputVector_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_sub_OutputVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_sub_ActualVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_sub_ActualVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_sub_ActualVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_sub_ActualVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_sub_DesiredVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_sub_DesiredVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_sub_DesiredVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_sub_DesiredVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_sub_OutputVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_sub_OutputVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_sub_OutputVectorIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_sub_OutputVectorIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_cont_DomContType_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_cont_DomContType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_cont_DomContType_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IControlBasis_put_cont_DomContType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_cont_SubContType_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_cont_SubContType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_cont_SubContType_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IControlBasis_put_cont_SubContType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_gain_PositionGainIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_gain_PositionGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_gain_PositionGainIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_gain_PositionGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_gain_ForceGainIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_gain_ForceGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_gain_ForceGainIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_gain_ForceGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_gain_MomentGainIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_gain_MomentGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_gain_MomentGainIndex_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IControlBasis_put_gain_MomentGainIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IControlBasis_ComputeControlBasis_Proxy( 
    IControlBasis __RPC_FAR * This);


void __RPC_STUB IControlBasis_ComputeControlBasis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IControlBasis_Initialize_Proxy( 
    IControlBasis __RPC_FAR * This);


void __RPC_STUB IControlBasis_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IControlBasis_get_AveragingWeight_JointAngles_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IControlBasis_get_AveragingWeight_JointAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IControlBasis_put_AveragingWeight_JointAngles_Proxy( 
    IControlBasis __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IControlBasis_put_AveragingWeight_JointAngles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IControlBasis_INTERFACE_DEFINED__ */



#ifndef __IMA2_CONTROLBASISLIBLib_LIBRARY_DEFINED__
#define __IMA2_CONTROLBASISLIBLib_LIBRARY_DEFINED__

/* library IMA2_CONTROLBASISLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_CONTROLBASISLIBLib;

EXTERN_C const CLSID CLSID_ControlBasis;

#ifdef __cplusplus

class DECLSPEC_UUID("2A43D57C-00F6-4054-9B0C-E831A9517CB7")
ControlBasis;
#endif
#endif /* __IMA2_CONTROLBASISLIBLib_LIBRARY_DEFINED__ */

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
