/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Dec 04 12:20:53 2008
 */
/* Compiler settings for O:\Components\CameraComponents\IMA2_ColorSegmenterLib\IMA2_ColorSegmenterLib.idl:
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

#ifndef __IMA2_ColorSegmenterLib_h__
#define __IMA2_ColorSegmenterLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IColorSegmenter_FWD_DEFINED__
#define __IColorSegmenter_FWD_DEFINED__
typedef interface IColorSegmenter IColorSegmenter;
#endif 	/* __IColorSegmenter_FWD_DEFINED__ */


#ifndef __ColorSegmenter_FWD_DEFINED__
#define __ColorSegmenter_FWD_DEFINED__

#ifdef __cplusplus
typedef class ColorSegmenter ColorSegmenter;
#else
typedef struct ColorSegmenter ColorSegmenter;
#endif /* __cplusplus */

#endif 	/* __ColorSegmenter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IColorSegmenter_INTERFACE_DEFINED__
#define __IColorSegmenter_INTERFACE_DEFINED__

/* interface IColorSegmenter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IColorSegmenter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6D9415C2-3CB2-409A-B42C-49F67CE4E51F")
    IColorSegmenter : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColorModelFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColorModelFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_seg_NumOfStdDevs( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_seg_NumOfStdDevs( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColorModelName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_seg_SkipPixels( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_seg_SkipPixels( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowLeft( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowLeft( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowTop( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowTop( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowWidth( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowWidth( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowHeight( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WindowHeight( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_display_FilterOutputImage( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_display_FilterOutputImage( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_display_CrossMarker( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_display_CrossMarker( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_seg_NumSegmentedPixels( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_seg_NumSegmentedPixels( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_filter_StdDevGain( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_filter_StdDevGain( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_filter_NumIterations( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_filter_NumIterations( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stat_Average_X_BlobPosition( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_stat_Average_X_BlobPosition( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stat_StdDev_X_Blob( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_stat_StdDev_X_Blob( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stat_Average_Y_BlobPosition( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_stat_Average_Y_BlobPosition( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stat_StdDev_Y_Blob( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_stat_StdDev_Y_Blob( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoSegment( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadColorModel( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColorSegmenterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IColorSegmenter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IColorSegmenter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IColorSegmenter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorModelFileName )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColorModelFileName )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_seg_NumOfStdDevs )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_seg_NumOfStdDevs )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColorModelName )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_seg_SkipPixels )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_seg_SkipPixels )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowLeft )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowLeft )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowTop )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowTop )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowWidth )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowWidth )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowHeight )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowHeight )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_display_FilterOutputImage )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_display_FilterOutputImage )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_display_CrossMarker )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_display_CrossMarker )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_seg_NumSegmentedPixels )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_seg_NumSegmentedPixels )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filter_StdDevGain )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_filter_StdDevGain )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filter_NumIterations )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_filter_NumIterations )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stat_Average_X_BlobPosition )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_stat_Average_X_BlobPosition )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stat_StdDev_X_Blob )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_stat_StdDev_X_Blob )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stat_Average_Y_BlobPosition )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_stat_Average_Y_BlobPosition )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stat_StdDev_Y_Blob )( 
            IColorSegmenter __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_stat_StdDev_Y_Blob )( 
            IColorSegmenter __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IColorSegmenter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoSegment )( 
            IColorSegmenter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadColorModel )( 
            IColorSegmenter __RPC_FAR * This);
        
        END_INTERFACE
    } IColorSegmenterVtbl;

    interface IColorSegmenter
    {
        CONST_VTBL struct IColorSegmenterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColorSegmenter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColorSegmenter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColorSegmenter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColorSegmenter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IColorSegmenter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IColorSegmenter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IColorSegmenter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IColorSegmenter_get_ColorModelFileName(This,pVal)	\
    (This)->lpVtbl -> get_ColorModelFileName(This,pVal)

#define IColorSegmenter_put_ColorModelFileName(This,newVal)	\
    (This)->lpVtbl -> put_ColorModelFileName(This,newVal)

#define IColorSegmenter_get_seg_NumOfStdDevs(This,pVal)	\
    (This)->lpVtbl -> get_seg_NumOfStdDevs(This,pVal)

#define IColorSegmenter_put_seg_NumOfStdDevs(This,newVal)	\
    (This)->lpVtbl -> put_seg_NumOfStdDevs(This,newVal)

#define IColorSegmenter_get_ColorModelName(This,pVal)	\
    (This)->lpVtbl -> get_ColorModelName(This,pVal)

#define IColorSegmenter_get_seg_SkipPixels(This,pVal)	\
    (This)->lpVtbl -> get_seg_SkipPixels(This,pVal)

#define IColorSegmenter_put_seg_SkipPixels(This,newVal)	\
    (This)->lpVtbl -> put_seg_SkipPixels(This,newVal)

#define IColorSegmenter_get_WindowLeft(This,pVal)	\
    (This)->lpVtbl -> get_WindowLeft(This,pVal)

#define IColorSegmenter_put_WindowLeft(This,newVal)	\
    (This)->lpVtbl -> put_WindowLeft(This,newVal)

#define IColorSegmenter_get_WindowTop(This,pVal)	\
    (This)->lpVtbl -> get_WindowTop(This,pVal)

#define IColorSegmenter_put_WindowTop(This,newVal)	\
    (This)->lpVtbl -> put_WindowTop(This,newVal)

#define IColorSegmenter_get_WindowWidth(This,pVal)	\
    (This)->lpVtbl -> get_WindowWidth(This,pVal)

#define IColorSegmenter_put_WindowWidth(This,newVal)	\
    (This)->lpVtbl -> put_WindowWidth(This,newVal)

#define IColorSegmenter_get_WindowHeight(This,pVal)	\
    (This)->lpVtbl -> get_WindowHeight(This,pVal)

#define IColorSegmenter_put_WindowHeight(This,newVal)	\
    (This)->lpVtbl -> put_WindowHeight(This,newVal)

#define IColorSegmenter_get_display_FilterOutputImage(This,pVal)	\
    (This)->lpVtbl -> get_display_FilterOutputImage(This,pVal)

#define IColorSegmenter_put_display_FilterOutputImage(This,newVal)	\
    (This)->lpVtbl -> put_display_FilterOutputImage(This,newVal)

#define IColorSegmenter_get_display_CrossMarker(This,pVal)	\
    (This)->lpVtbl -> get_display_CrossMarker(This,pVal)

#define IColorSegmenter_put_display_CrossMarker(This,newVal)	\
    (This)->lpVtbl -> put_display_CrossMarker(This,newVal)

#define IColorSegmenter_get_seg_NumSegmentedPixels(This,pVal)	\
    (This)->lpVtbl -> get_seg_NumSegmentedPixels(This,pVal)

#define IColorSegmenter_put_seg_NumSegmentedPixels(This,newVal)	\
    (This)->lpVtbl -> put_seg_NumSegmentedPixels(This,newVal)

#define IColorSegmenter_get_filter_StdDevGain(This,pVal)	\
    (This)->lpVtbl -> get_filter_StdDevGain(This,pVal)

#define IColorSegmenter_put_filter_StdDevGain(This,newVal)	\
    (This)->lpVtbl -> put_filter_StdDevGain(This,newVal)

#define IColorSegmenter_get_filter_NumIterations(This,pVal)	\
    (This)->lpVtbl -> get_filter_NumIterations(This,pVal)

#define IColorSegmenter_put_filter_NumIterations(This,newVal)	\
    (This)->lpVtbl -> put_filter_NumIterations(This,newVal)

#define IColorSegmenter_get_stat_Average_X_BlobPosition(This,pVal)	\
    (This)->lpVtbl -> get_stat_Average_X_BlobPosition(This,pVal)

#define IColorSegmenter_put_stat_Average_X_BlobPosition(This,newVal)	\
    (This)->lpVtbl -> put_stat_Average_X_BlobPosition(This,newVal)

#define IColorSegmenter_get_stat_StdDev_X_Blob(This,pVal)	\
    (This)->lpVtbl -> get_stat_StdDev_X_Blob(This,pVal)

#define IColorSegmenter_put_stat_StdDev_X_Blob(This,newVal)	\
    (This)->lpVtbl -> put_stat_StdDev_X_Blob(This,newVal)

#define IColorSegmenter_get_stat_Average_Y_BlobPosition(This,pVal)	\
    (This)->lpVtbl -> get_stat_Average_Y_BlobPosition(This,pVal)

#define IColorSegmenter_put_stat_Average_Y_BlobPosition(This,newVal)	\
    (This)->lpVtbl -> put_stat_Average_Y_BlobPosition(This,newVal)

#define IColorSegmenter_get_stat_StdDev_Y_Blob(This,pVal)	\
    (This)->lpVtbl -> get_stat_StdDev_Y_Blob(This,pVal)

#define IColorSegmenter_put_stat_StdDev_Y_Blob(This,newVal)	\
    (This)->lpVtbl -> put_stat_StdDev_Y_Blob(This,newVal)

#define IColorSegmenter_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IColorSegmenter_DoSegment(This)	\
    (This)->lpVtbl -> DoSegment(This)

#define IColorSegmenter_LoadColorModel(This)	\
    (This)->lpVtbl -> LoadColorModel(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_ColorModelFileName_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_ColorModelFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_ColorModelFileName_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IColorSegmenter_put_ColorModelFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_seg_NumOfStdDevs_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_seg_NumOfStdDevs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_seg_NumOfStdDevs_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB IColorSegmenter_put_seg_NumOfStdDevs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_ColorModelName_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_ColorModelName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_seg_SkipPixels_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_seg_SkipPixels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_seg_SkipPixels_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_seg_SkipPixels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_WindowLeft_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_WindowLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_WindowLeft_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_WindowLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_WindowTop_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_WindowTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_WindowTop_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_WindowTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_WindowWidth_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_WindowWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_WindowWidth_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_WindowWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_WindowHeight_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_WindowHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_WindowHeight_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_WindowHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_display_FilterOutputImage_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_display_FilterOutputImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_display_FilterOutputImage_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_display_FilterOutputImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_display_CrossMarker_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_display_CrossMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_display_CrossMarker_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IColorSegmenter_put_display_CrossMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_seg_NumSegmentedPixels_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_seg_NumSegmentedPixels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_seg_NumSegmentedPixels_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IColorSegmenter_put_seg_NumSegmentedPixels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_filter_StdDevGain_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_filter_StdDevGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_filter_StdDevGain_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IColorSegmenter_put_filter_StdDevGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_filter_NumIterations_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_filter_NumIterations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_filter_NumIterations_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IColorSegmenter_put_filter_NumIterations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_stat_Average_X_BlobPosition_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_stat_Average_X_BlobPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_stat_Average_X_BlobPosition_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IColorSegmenter_put_stat_Average_X_BlobPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_stat_StdDev_X_Blob_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_stat_StdDev_X_Blob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_stat_StdDev_X_Blob_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IColorSegmenter_put_stat_StdDev_X_Blob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_stat_Average_Y_BlobPosition_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_stat_Average_Y_BlobPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_stat_Average_Y_BlobPosition_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IColorSegmenter_put_stat_Average_Y_BlobPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_get_stat_StdDev_Y_Blob_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IColorSegmenter_get_stat_StdDev_Y_Blob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_put_stat_StdDev_Y_Blob_Proxy( 
    IColorSegmenter __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IColorSegmenter_put_stat_StdDev_Y_Blob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_Initialize_Proxy( 
    IColorSegmenter __RPC_FAR * This);


void __RPC_STUB IColorSegmenter_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_DoSegment_Proxy( 
    IColorSegmenter __RPC_FAR * This);


void __RPC_STUB IColorSegmenter_DoSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IColorSegmenter_LoadColorModel_Proxy( 
    IColorSegmenter __RPC_FAR * This);


void __RPC_STUB IColorSegmenter_LoadColorModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColorSegmenter_INTERFACE_DEFINED__ */



#ifndef __IMA2_COLORSEGMENTERLIBLib_LIBRARY_DEFINED__
#define __IMA2_COLORSEGMENTERLIBLib_LIBRARY_DEFINED__

/* library IMA2_COLORSEGMENTERLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_COLORSEGMENTERLIBLib;

EXTERN_C const CLSID CLSID_ColorSegmenter;

#ifdef __cplusplus

class DECLSPEC_UUID("5B77B15E-47A3-4BDF-9763-61A93DDC7749")
ColorSegmenter;
#endif
#endif /* __IMA2_COLORSEGMENTERLIBLib_LIBRARY_DEFINED__ */

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
