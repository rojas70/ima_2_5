/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 25 16:24:26 2006
 */
/* Compiler settings for O:\Components\FT Sensor\PressureAndForctTorqueCharacterization\PressureAndForctTorqueCharacterization.idl:
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

#ifndef __PressureAndForctTorqueCharacterization_h__
#define __PressureAndForctTorqueCharacterization_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPressureForceCharacterization_FWD_DEFINED__
#define __IPressureForceCharacterization_FWD_DEFINED__
typedef interface IPressureForceCharacterization IPressureForceCharacterization;
#endif 	/* __IPressureForceCharacterization_FWD_DEFINED__ */


#ifndef __PressureForceCharacterization_FWD_DEFINED__
#define __PressureForceCharacterization_FWD_DEFINED__

#ifdef __cplusplus
typedef class PressureForceCharacterization PressureForceCharacterization;
#else
typedef struct PressureForceCharacterization PressureForceCharacterization;
#endif /* __cplusplus */

#endif 	/* __PressureForceCharacterization_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPressureForceCharacterization_INTERFACE_DEFINED__
#define __IPressureForceCharacterization_INTERFACE_DEFINED__

/* interface IPressureForceCharacterization */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPressureForceCharacterization;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("94F541B1-0CC5-4F4B-8B07-4397ED7F3DC5")
    IPressureForceCharacterization : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMinIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMinIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMaxIndex( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMaxIndex( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMin( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputMax( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HomingSteps( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HomingSteps( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftArm( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftArm( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureForRubbertuatorPair1( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureForRubbertuatorPair1( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureForRubbertuatorPair2( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureForRubbertuatorPair2( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureForRubbertuatorPair3( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureForRubbertuatorPair3( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureForRubbertuatorPair4( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureForRubbertuatorPair4( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureForRubbertuatorPair5( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureForRubbertuatorPair5( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PressureForRubbertuatorPair6( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PressureForRubbertuatorPair6( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartCharacerizationProcess( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerticalPush1( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteDataToFile( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePressure( 
            short whatjoint,
            double basepressure,
            double pressurechange,
            short numberofsteps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoToHomePosition( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPressureForceCharacterizationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMinIndex )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMinIndex )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMaxIndex )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMaxIndex )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMin )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMin )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputMax )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputMax )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HomingSteps )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HomingSteps )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeftArm )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeftArm )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureForRubbertuatorPair1 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureForRubbertuatorPair1 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureForRubbertuatorPair2 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureForRubbertuatorPair2 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureForRubbertuatorPair3 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureForRubbertuatorPair3 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureForRubbertuatorPair4 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureForRubbertuatorPair4 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureForRubbertuatorPair5 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureForRubbertuatorPair5 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PressureForRubbertuatorPair6 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PressureForRubbertuatorPair6 )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            IPressureForceCharacterization __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartCharacerizationProcess )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VerticalPush1 )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteDataToFile )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangePressure )( 
            IPressureForceCharacterization __RPC_FAR * This,
            short whatjoint,
            double basepressure,
            double pressurechange,
            short numberofsteps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoToHomePosition )( 
            IPressureForceCharacterization __RPC_FAR * This);
        
        END_INTERFACE
    } IPressureForceCharacterizationVtbl;

    interface IPressureForceCharacterization
    {
        CONST_VTBL struct IPressureForceCharacterizationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPressureForceCharacterization_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPressureForceCharacterization_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPressureForceCharacterization_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPressureForceCharacterization_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPressureForceCharacterization_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPressureForceCharacterization_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPressureForceCharacterization_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPressureForceCharacterization_get_OutputMinIndex(This,pVal)	\
    (This)->lpVtbl -> get_OutputMinIndex(This,pVal)

#define IPressureForceCharacterization_put_OutputMinIndex(This,newVal)	\
    (This)->lpVtbl -> put_OutputMinIndex(This,newVal)

#define IPressureForceCharacterization_get_OutputMaxIndex(This,pVal)	\
    (This)->lpVtbl -> get_OutputMaxIndex(This,pVal)

#define IPressureForceCharacterization_put_OutputMaxIndex(This,newVal)	\
    (This)->lpVtbl -> put_OutputMaxIndex(This,newVal)

#define IPressureForceCharacterization_get_OutputMin(This,pVal)	\
    (This)->lpVtbl -> get_OutputMin(This,pVal)

#define IPressureForceCharacterization_put_OutputMin(This,newVal)	\
    (This)->lpVtbl -> put_OutputMin(This,newVal)

#define IPressureForceCharacterization_get_OutputMax(This,pVal)	\
    (This)->lpVtbl -> get_OutputMax(This,pVal)

#define IPressureForceCharacterization_put_OutputMax(This,newVal)	\
    (This)->lpVtbl -> put_OutputMax(This,newVal)

#define IPressureForceCharacterization_get_HomingSteps(This,pVal)	\
    (This)->lpVtbl -> get_HomingSteps(This,pVal)

#define IPressureForceCharacterization_put_HomingSteps(This,newVal)	\
    (This)->lpVtbl -> put_HomingSteps(This,newVal)

#define IPressureForceCharacterization_get_LeftArm(This,pVal)	\
    (This)->lpVtbl -> get_LeftArm(This,pVal)

#define IPressureForceCharacterization_put_LeftArm(This,newVal)	\
    (This)->lpVtbl -> put_LeftArm(This,newVal)

#define IPressureForceCharacterization_get_PressureForRubbertuatorPair1(This,pVal)	\
    (This)->lpVtbl -> get_PressureForRubbertuatorPair1(This,pVal)

#define IPressureForceCharacterization_put_PressureForRubbertuatorPair1(This,newVal)	\
    (This)->lpVtbl -> put_PressureForRubbertuatorPair1(This,newVal)

#define IPressureForceCharacterization_get_PressureForRubbertuatorPair2(This,pVal)	\
    (This)->lpVtbl -> get_PressureForRubbertuatorPair2(This,pVal)

#define IPressureForceCharacterization_put_PressureForRubbertuatorPair2(This,newVal)	\
    (This)->lpVtbl -> put_PressureForRubbertuatorPair2(This,newVal)

#define IPressureForceCharacterization_get_PressureForRubbertuatorPair3(This,pVal)	\
    (This)->lpVtbl -> get_PressureForRubbertuatorPair3(This,pVal)

#define IPressureForceCharacterization_put_PressureForRubbertuatorPair3(This,newVal)	\
    (This)->lpVtbl -> put_PressureForRubbertuatorPair3(This,newVal)

#define IPressureForceCharacterization_get_PressureForRubbertuatorPair4(This,pVal)	\
    (This)->lpVtbl -> get_PressureForRubbertuatorPair4(This,pVal)

#define IPressureForceCharacterization_put_PressureForRubbertuatorPair4(This,newVal)	\
    (This)->lpVtbl -> put_PressureForRubbertuatorPair4(This,newVal)

#define IPressureForceCharacterization_get_PressureForRubbertuatorPair5(This,pVal)	\
    (This)->lpVtbl -> get_PressureForRubbertuatorPair5(This,pVal)

#define IPressureForceCharacterization_put_PressureForRubbertuatorPair5(This,newVal)	\
    (This)->lpVtbl -> put_PressureForRubbertuatorPair5(This,newVal)

#define IPressureForceCharacterization_get_PressureForRubbertuatorPair6(This,pVal)	\
    (This)->lpVtbl -> get_PressureForRubbertuatorPair6(This,pVal)

#define IPressureForceCharacterization_put_PressureForRubbertuatorPair6(This,newVal)	\
    (This)->lpVtbl -> put_PressureForRubbertuatorPair6(This,newVal)

#define IPressureForceCharacterization_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IPressureForceCharacterization_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IPressureForceCharacterization_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IPressureForceCharacterization_StartCharacerizationProcess(This)	\
    (This)->lpVtbl -> StartCharacerizationProcess(This)

#define IPressureForceCharacterization_VerticalPush1(This)	\
    (This)->lpVtbl -> VerticalPush1(This)

#define IPressureForceCharacterization_WriteDataToFile(This)	\
    (This)->lpVtbl -> WriteDataToFile(This)

#define IPressureForceCharacterization_ChangePressure(This,whatjoint,basepressure,pressurechange,numberofsteps)	\
    (This)->lpVtbl -> ChangePressure(This,whatjoint,basepressure,pressurechange,numberofsteps)

#define IPressureForceCharacterization_GoToHomePosition(This)	\
    (This)->lpVtbl -> GoToHomePosition(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_OutputMinIndex_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_OutputMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_OutputMinIndex_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPressureForceCharacterization_put_OutputMinIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_OutputMaxIndex_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_OutputMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_OutputMaxIndex_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPressureForceCharacterization_put_OutputMaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_OutputMin_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_OutputMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_OutputMin_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_OutputMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_OutputMax_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_OutputMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_OutputMax_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_OutputMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_HomingSteps_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_HomingSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_HomingSteps_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IPressureForceCharacterization_put_HomingSteps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_LeftArm_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_LeftArm_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IPressureForceCharacterization_put_LeftArm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_PressureForRubbertuatorPair1_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_PressureForRubbertuatorPair1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_PressureForRubbertuatorPair1_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_PressureForRubbertuatorPair1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_PressureForRubbertuatorPair2_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_PressureForRubbertuatorPair2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_PressureForRubbertuatorPair2_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_PressureForRubbertuatorPair2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_PressureForRubbertuatorPair3_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_PressureForRubbertuatorPair3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_PressureForRubbertuatorPair3_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_PressureForRubbertuatorPair3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_PressureForRubbertuatorPair4_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_PressureForRubbertuatorPair4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_PressureForRubbertuatorPair4_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_PressureForRubbertuatorPair4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_PressureForRubbertuatorPair5_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_PressureForRubbertuatorPair5_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_PressureForRubbertuatorPair5_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_PressureForRubbertuatorPair5_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_PressureForRubbertuatorPair6_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_PressureForRubbertuatorPair6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_PressureForRubbertuatorPair6_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IPressureForceCharacterization_put_PressureForRubbertuatorPair6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_get_FileName_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPressureForceCharacterization_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_put_FileName_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPressureForceCharacterization_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_Initialize_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This);


void __RPC_STUB IPressureForceCharacterization_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_StartCharacerizationProcess_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This);


void __RPC_STUB IPressureForceCharacterization_StartCharacerizationProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_VerticalPush1_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This);


void __RPC_STUB IPressureForceCharacterization_VerticalPush1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_WriteDataToFile_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This);


void __RPC_STUB IPressureForceCharacterization_WriteDataToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_ChangePressure_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This,
    short whatjoint,
    double basepressure,
    double pressurechange,
    short numberofsteps);


void __RPC_STUB IPressureForceCharacterization_ChangePressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPressureForceCharacterization_GoToHomePosition_Proxy( 
    IPressureForceCharacterization __RPC_FAR * This);


void __RPC_STUB IPressureForceCharacterization_GoToHomePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPressureForceCharacterization_INTERFACE_DEFINED__ */



#ifndef __PRESSUREANDFORCTTORQUECHARACTERIZATIONLib_LIBRARY_DEFINED__
#define __PRESSUREANDFORCTTORQUECHARACTERIZATIONLib_LIBRARY_DEFINED__

/* library PRESSUREANDFORCTTORQUECHARACTERIZATIONLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PRESSUREANDFORCTTORQUECHARACTERIZATIONLib;

EXTERN_C const CLSID CLSID_PressureForceCharacterization;

#ifdef __cplusplus

class DECLSPEC_UUID("4717FCEF-8FD4-40EB-997F-9B905D66D5E9")
PressureForceCharacterization;
#endif
#endif /* __PRESSUREANDFORCTTORQUECHARACTERIZATIONLib_LIBRARY_DEFINED__ */

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
