/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 03 16:34:33 2008
 */
/* Compiler settings for O:\Components\CameraComponents\IMA2_ImageProcessingLib\IMA2_ImageProcessingLib.idl:
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

#ifndef __IMA2_ImageProcessingLib_h__
#define __IMA2_ImageProcessingLib_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IIntelIPL_FWD_DEFINED__
#define __IIntelIPL_FWD_DEFINED__
typedef interface IIntelIPL IIntelIPL;
#endif 	/* __IIntelIPL_FWD_DEFINED__ */


#ifndef __IIntelSPL_FWD_DEFINED__
#define __IIntelSPL_FWD_DEFINED__
typedef interface IIntelSPL IIntelSPL;
#endif 	/* __IIntelSPL_FWD_DEFINED__ */


#ifndef __IntelIPL_FWD_DEFINED__
#define __IntelIPL_FWD_DEFINED__

#ifdef __cplusplus
typedef class IntelIPL IntelIPL;
#else
typedef struct IntelIPL IntelIPL;
#endif /* __cplusplus */

#endif 	/* __IntelIPL_FWD_DEFINED__ */


#ifndef __IntelSPL_FWD_DEFINED__
#define __IntelSPL_FWD_DEFINED__

#ifdef __cplusplus
typedef class IntelSPL IntelSPL;
#else
typedef struct IntelSPL IntelSPL;
#endif /* __cplusplus */

#endif 	/* __IntelSPL_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IIntelIPL_INTERFACE_DEFINED__
#define __IIntelIPL_INTERFACE_DEFINED__

/* interface IIntelIPL */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIntelIPL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B6D762F-3A73-4645-B0C0-4DE8E7DF8F3A")
    IIntelIPL : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FlipAxis( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FlipAxis( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConvKernel( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConvKernel( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initial( 
            int InputWidth,
            int InputHeight,
            int InputDepth) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mirror( 
            long Input,
            long Output,
            long FlipAxis) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Not( 
            long Input,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ColorToGray( 
            long Input,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Erode( 
            long Input,
            long Output,
            long Iteration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dilate( 
            long Input,
            long Output,
            long Iteration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            long Input,
            long Output,
            long Iteration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            long Input,
            long Output,
            long Iteration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Subtract( 
            long InputA,
            long InputB,
            long Output,
            long FlipAxis) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateConvolutionKernel( 
            long __RPC_FAR *Values,
            long Rows,
            long Columns,
            long AnchorX,
            long AnchorY,
            long nShiftR,
            long Number) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Convolve2D( 
            long Input,
            long Output,
            long nKernels,
            long combineMethod) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumberColumns( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumberColumns( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumberRows( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumberRows( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AnchorX( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AnchorX( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AnchorY( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AnchorY( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Blur( 
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MedianFilter( 
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MinFilter( 
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MaxFilter( 
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ThresholdValue( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ThresholdValue( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Threshold( 
            long Input,
            long Output,
            long threshold) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AND( 
            long InputA,
            long InputB,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OR( 
            long InputA,
            long InputB,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE XOR( 
            long InputA,
            long InputB,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Square( 
            long Input,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Multiply( 
            long Input,
            long Output,
            long value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MultiplyScale( 
            long Input,
            long Output,
            long value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MultiplyImage( 
            long InputA,
            long InputB,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MultiplyImageScale( 
            long InputA,
            long InputB,
            long Output) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RGBToHSV( 
            long InputRGB,
            long OutputHSV) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIntelIPLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIntelIPL __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIntelIPL __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIntelIPL __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputIndex )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputIndex )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FlipAxis )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FlipAxis )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConvKernel )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConvKernel )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initial )( 
            IIntelIPL __RPC_FAR * This,
            int InputWidth,
            int InputHeight,
            int InputDepth);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Mirror )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long FlipAxis);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Not )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ColorToGray )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erode )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long Iteration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Dilate )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long Iteration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long Iteration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long Iteration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subtract )( 
            IIntelIPL __RPC_FAR * This,
            long InputA,
            long InputB,
            long Output,
            long FlipAxis);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateConvolutionKernel )( 
            IIntelIPL __RPC_FAR * This,
            long __RPC_FAR *Values,
            long Rows,
            long Columns,
            long AnchorX,
            long AnchorY,
            long nShiftR,
            long Number);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Convolve2D )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long nKernels,
            long combineMethod);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberColumns )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumberColumns )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberRows )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumberRows )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AnchorX )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AnchorX )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AnchorY )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AnchorY )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Blur )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MedianFilter )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MinFilter )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MaxFilter )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long nRows,
            long nCols,
            long anchorX,
            long anchorY);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ThresholdValue )( 
            IIntelIPL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ThresholdValue )( 
            IIntelIPL __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Threshold )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long threshold);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AND )( 
            IIntelIPL __RPC_FAR * This,
            long InputA,
            long InputB,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OR )( 
            IIntelIPL __RPC_FAR * This,
            long InputA,
            long InputB,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *XOR )( 
            IIntelIPL __RPC_FAR * This,
            long InputA,
            long InputB,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Square )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Multiply )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MultiplyScale )( 
            IIntelIPL __RPC_FAR * This,
            long Input,
            long Output,
            long value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MultiplyImage )( 
            IIntelIPL __RPC_FAR * This,
            long InputA,
            long InputB,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MultiplyImageScale )( 
            IIntelIPL __RPC_FAR * This,
            long InputA,
            long InputB,
            long Output);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RGBToHSV )( 
            IIntelIPL __RPC_FAR * This,
            long InputRGB,
            long OutputHSV);
        
        END_INTERFACE
    } IIntelIPLVtbl;

    interface IIntelIPL
    {
        CONST_VTBL struct IIntelIPLVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIntelIPL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIntelIPL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIntelIPL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIntelIPL_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIntelIPL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIntelIPL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIntelIPL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIntelIPL_get_InputIndex(This,pVal)	\
    (This)->lpVtbl -> get_InputIndex(This,pVal)

#define IIntelIPL_put_InputIndex(This,newVal)	\
    (This)->lpVtbl -> put_InputIndex(This,newVal)

#define IIntelIPL_get_FlipAxis(This,pVal)	\
    (This)->lpVtbl -> get_FlipAxis(This,pVal)

#define IIntelIPL_put_FlipAxis(This,newVal)	\
    (This)->lpVtbl -> put_FlipAxis(This,newVal)

#define IIntelIPL_get_ConvKernel(This,pVal)	\
    (This)->lpVtbl -> get_ConvKernel(This,pVal)

#define IIntelIPL_put_ConvKernel(This,newVal)	\
    (This)->lpVtbl -> put_ConvKernel(This,newVal)

#define IIntelIPL_Initial(This,InputWidth,InputHeight,InputDepth)	\
    (This)->lpVtbl -> Initial(This,InputWidth,InputHeight,InputDepth)

#define IIntelIPL_Mirror(This,Input,Output,FlipAxis)	\
    (This)->lpVtbl -> Mirror(This,Input,Output,FlipAxis)

#define IIntelIPL_Not(This,Input,Output)	\
    (This)->lpVtbl -> Not(This,Input,Output)

#define IIntelIPL_ColorToGray(This,Input,Output)	\
    (This)->lpVtbl -> ColorToGray(This,Input,Output)

#define IIntelIPL_Erode(This,Input,Output,Iteration)	\
    (This)->lpVtbl -> Erode(This,Input,Output,Iteration)

#define IIntelIPL_Dilate(This,Input,Output,Iteration)	\
    (This)->lpVtbl -> Dilate(This,Input,Output,Iteration)

#define IIntelIPL_Open(This,Input,Output,Iteration)	\
    (This)->lpVtbl -> Open(This,Input,Output,Iteration)

#define IIntelIPL_Close(This,Input,Output,Iteration)	\
    (This)->lpVtbl -> Close(This,Input,Output,Iteration)

#define IIntelIPL_Subtract(This,InputA,InputB,Output,FlipAxis)	\
    (This)->lpVtbl -> Subtract(This,InputA,InputB,Output,FlipAxis)

#define IIntelIPL_CreateConvolutionKernel(This,Values,Rows,Columns,AnchorX,AnchorY,nShiftR,Number)	\
    (This)->lpVtbl -> CreateConvolutionKernel(This,Values,Rows,Columns,AnchorX,AnchorY,nShiftR,Number)

#define IIntelIPL_Convolve2D(This,Input,Output,nKernels,combineMethod)	\
    (This)->lpVtbl -> Convolve2D(This,Input,Output,nKernels,combineMethod)

#define IIntelIPL_get_NumberColumns(This,pVal)	\
    (This)->lpVtbl -> get_NumberColumns(This,pVal)

#define IIntelIPL_put_NumberColumns(This,newVal)	\
    (This)->lpVtbl -> put_NumberColumns(This,newVal)

#define IIntelIPL_get_NumberRows(This,pVal)	\
    (This)->lpVtbl -> get_NumberRows(This,pVal)

#define IIntelIPL_put_NumberRows(This,newVal)	\
    (This)->lpVtbl -> put_NumberRows(This,newVal)

#define IIntelIPL_get_AnchorX(This,pVal)	\
    (This)->lpVtbl -> get_AnchorX(This,pVal)

#define IIntelIPL_put_AnchorX(This,newVal)	\
    (This)->lpVtbl -> put_AnchorX(This,newVal)

#define IIntelIPL_get_AnchorY(This,pVal)	\
    (This)->lpVtbl -> get_AnchorY(This,pVal)

#define IIntelIPL_put_AnchorY(This,newVal)	\
    (This)->lpVtbl -> put_AnchorY(This,newVal)

#define IIntelIPL_Blur(This,Input,Output,nRows,nCols,anchorX,anchorY)	\
    (This)->lpVtbl -> Blur(This,Input,Output,nRows,nCols,anchorX,anchorY)

#define IIntelIPL_MedianFilter(This,Input,Output,nRows,nCols,anchorX,anchorY)	\
    (This)->lpVtbl -> MedianFilter(This,Input,Output,nRows,nCols,anchorX,anchorY)

#define IIntelIPL_MinFilter(This,Input,Output,nRows,nCols,anchorX,anchorY)	\
    (This)->lpVtbl -> MinFilter(This,Input,Output,nRows,nCols,anchorX,anchorY)

#define IIntelIPL_MaxFilter(This,Input,Output,nRows,nCols,anchorX,anchorY)	\
    (This)->lpVtbl -> MaxFilter(This,Input,Output,nRows,nCols,anchorX,anchorY)

#define IIntelIPL_get_ThresholdValue(This,pVal)	\
    (This)->lpVtbl -> get_ThresholdValue(This,pVal)

#define IIntelIPL_put_ThresholdValue(This,newVal)	\
    (This)->lpVtbl -> put_ThresholdValue(This,newVal)

#define IIntelIPL_Threshold(This,Input,Output,threshold)	\
    (This)->lpVtbl -> Threshold(This,Input,Output,threshold)

#define IIntelIPL_AND(This,InputA,InputB,Output)	\
    (This)->lpVtbl -> AND(This,InputA,InputB,Output)

#define IIntelIPL_OR(This,InputA,InputB,Output)	\
    (This)->lpVtbl -> OR(This,InputA,InputB,Output)

#define IIntelIPL_XOR(This,InputA,InputB,Output)	\
    (This)->lpVtbl -> XOR(This,InputA,InputB,Output)

#define IIntelIPL_Square(This,Input,Output)	\
    (This)->lpVtbl -> Square(This,Input,Output)

#define IIntelIPL_Multiply(This,Input,Output,value)	\
    (This)->lpVtbl -> Multiply(This,Input,Output,value)

#define IIntelIPL_MultiplyScale(This,Input,Output,value)	\
    (This)->lpVtbl -> MultiplyScale(This,Input,Output,value)

#define IIntelIPL_MultiplyImage(This,InputA,InputB,Output)	\
    (This)->lpVtbl -> MultiplyImage(This,InputA,InputB,Output)

#define IIntelIPL_MultiplyImageScale(This,InputA,InputB,Output)	\
    (This)->lpVtbl -> MultiplyImageScale(This,InputA,InputB,Output)

#define IIntelIPL_RGBToHSV(This,InputRGB,OutputHSV)	\
    (This)->lpVtbl -> RGBToHSV(This,InputRGB,OutputHSV)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_InputIndex_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_InputIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_InputIndex_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_InputIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_FlipAxis_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_FlipAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_FlipAxis_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_FlipAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_ConvKernel_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_ConvKernel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_ConvKernel_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_ConvKernel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Initial_Proxy( 
    IIntelIPL __RPC_FAR * This,
    int InputWidth,
    int InputHeight,
    int InputDepth);


void __RPC_STUB IIntelIPL_Initial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Mirror_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long FlipAxis);


void __RPC_STUB IIntelIPL_Mirror_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Not_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output);


void __RPC_STUB IIntelIPL_Not_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_ColorToGray_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output);


void __RPC_STUB IIntelIPL_ColorToGray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Erode_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long Iteration);


void __RPC_STUB IIntelIPL_Erode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Dilate_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long Iteration);


void __RPC_STUB IIntelIPL_Dilate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Open_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long Iteration);


void __RPC_STUB IIntelIPL_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Close_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long Iteration);


void __RPC_STUB IIntelIPL_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Subtract_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputA,
    long InputB,
    long Output,
    long FlipAxis);


void __RPC_STUB IIntelIPL_Subtract_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_CreateConvolutionKernel_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long __RPC_FAR *Values,
    long Rows,
    long Columns,
    long AnchorX,
    long AnchorY,
    long nShiftR,
    long Number);


void __RPC_STUB IIntelIPL_CreateConvolutionKernel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Convolve2D_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long nKernels,
    long combineMethod);


void __RPC_STUB IIntelIPL_Convolve2D_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_NumberColumns_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_NumberColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_NumberColumns_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_NumberColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_NumberRows_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_NumberRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_NumberRows_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_NumberRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_AnchorX_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_AnchorX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_AnchorX_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_AnchorX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_AnchorY_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_AnchorY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_AnchorY_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_AnchorY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Blur_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long nRows,
    long nCols,
    long anchorX,
    long anchorY);


void __RPC_STUB IIntelIPL_Blur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_MedianFilter_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long nRows,
    long nCols,
    long anchorX,
    long anchorY);


void __RPC_STUB IIntelIPL_MedianFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_MinFilter_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long nRows,
    long nCols,
    long anchorX,
    long anchorY);


void __RPC_STUB IIntelIPL_MinFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_MaxFilter_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long nRows,
    long nCols,
    long anchorX,
    long anchorY);


void __RPC_STUB IIntelIPL_MaxFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIntelIPL_get_ThresholdValue_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIntelIPL_get_ThresholdValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIntelIPL_put_ThresholdValue_Proxy( 
    IIntelIPL __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IIntelIPL_put_ThresholdValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Threshold_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long threshold);


void __RPC_STUB IIntelIPL_Threshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_AND_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputA,
    long InputB,
    long Output);


void __RPC_STUB IIntelIPL_AND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_OR_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputA,
    long InputB,
    long Output);


void __RPC_STUB IIntelIPL_OR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_XOR_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputA,
    long InputB,
    long Output);


void __RPC_STUB IIntelIPL_XOR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Square_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output);


void __RPC_STUB IIntelIPL_Square_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_Multiply_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long value);


void __RPC_STUB IIntelIPL_Multiply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_MultiplyScale_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long Input,
    long Output,
    long value);


void __RPC_STUB IIntelIPL_MultiplyScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_MultiplyImage_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputA,
    long InputB,
    long Output);


void __RPC_STUB IIntelIPL_MultiplyImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_MultiplyImageScale_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputA,
    long InputB,
    long Output);


void __RPC_STUB IIntelIPL_MultiplyImageScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelIPL_RGBToHSV_Proxy( 
    IIntelIPL __RPC_FAR * This,
    long InputRGB,
    long OutputHSV);


void __RPC_STUB IIntelIPL_RGBToHSV_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIntelIPL_INTERFACE_DEFINED__ */


#ifndef __IIntelSPL_INTERFACE_DEFINED__
#define __IIntelSPL_INTERFACE_DEFINED__

/* interface IIntelSPL */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIntelSPL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8398F1C1-5FD8-4078-8A0B-DEDADB721F46")
    IIntelSPL : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fCopy( 
            float __RPC_FAR *src,
            float __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dCopy( 
            double __RPC_FAR *src,
            double __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sCopy( 
            short __RPC_FAR *src,
            short __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fSet( 
            float val,
            float __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dSet( 
            double val,
            double __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sSet( 
            short val,
            short __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fZero( 
            float __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dZero( 
            double __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sZero( 
            short __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fMax( 
            float __RPC_FAR *vec,
            int n,
            float __RPC_FAR *outval,
            int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dMax( 
            double __RPC_FAR *vec,
            int n,
            double __RPC_FAR *outval,
            int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sMax( 
            short __RPC_FAR *vec,
            int n,
            short __RPC_FAR *outval,
            int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fMin( 
            float __RPC_FAR *vec,
            int n,
            float __RPC_FAR *outval,
            int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dMin( 
            double __RPC_FAR *vec,
            int n,
            double __RPC_FAR *outval,
            int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sMin( 
            short __RPC_FAR *vec,
            int n,
            short __RPC_FAR *outval,
            int __RPC_FAR *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fMean( 
            float __RPC_FAR *vec,
            int n,
            float __RPC_FAR *outval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dMean( 
            double __RPC_FAR *vec,
            int n,
            double __RPC_FAR *outval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sMean( 
            short __RPC_FAR *vec,
            int n,
            short __RPC_FAR *outval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fNorm( 
            float __RPC_FAR *srcA,
            float __RPC_FAR *srcB,
            int n,
            int flag,
            float __RPC_FAR *outval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dNorm( 
            double __RPC_FAR *srcA,
            double __RPC_FAR *srcB,
            int n,
            int flag,
            double __RPC_FAR *outval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sNorm( 
            short __RPC_FAR *srcA,
            short __RPC_FAR *srcB,
            int n,
            int flag,
            float __RPC_FAR *outval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fAutoCorr( 
            float __RPC_FAR *src,
            int len,
            float __RPC_FAR *dst,
            int nLags,
            int flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dAutoCorr( 
            double __RPC_FAR *src,
            int len,
            double __RPC_FAR *dst,
            int nLags,
            int flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sAutoCorr( 
            short __RPC_FAR *src,
            int len,
            short __RPC_FAR *dst,
            int nLags,
            int flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fCrossCorr( 
            float __RPC_FAR *srcA,
            int lenA,
            float __RPC_FAR *srcB,
            int lenB,
            float __RPC_FAR *dst,
            int loLag,
            int hiLag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dCrossCorr( 
            double __RPC_FAR *srcA,
            int lenA,
            double __RPC_FAR *srcB,
            int lenB,
            double __RPC_FAR *dst,
            int loLag,
            int hiLag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sCrossCorr( 
            short __RPC_FAR *srcA,
            int lenA,
            short __RPC_FAR *srcB,
            int lenB,
            short __RPC_FAR *dst,
            int loLag,
            int hiLag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fRealFFT( 
            float __RPC_FAR *samps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fRealFFTip( 
            float __RPC_FAR *inSamps,
            float __RPC_FAR *outSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dRealFFT( 
            double __RPC_FAR *samps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dRealFFTip( 
            double __RPC_FAR *inSamps,
            double __RPC_FAR *outSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sRealFFT( 
            short __RPC_FAR *samps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sRealFFTip( 
            short __RPC_FAR *inSamps,
            short __RPC_FAR *outSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fRealInvFFT( 
            float __RPC_FAR *samps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fRealInvFFTip( 
            float __RPC_FAR *inSamps,
            float __RPC_FAR *outSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dRealInvFFT( 
            double __RPC_FAR *samps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dRealInvFFTip( 
            double __RPC_FAR *inSamps,
            double __RPC_FAR *outSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sRealInvFFT( 
            short __RPC_FAR *samps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sRealInvFFTip( 
            short __RPC_FAR *inSamps,
            short __RPC_FAR *outSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fReal2FFT( 
            float __RPC_FAR *xSamps,
            float __RPC_FAR *ySamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fReal2FFTip( 
            float __RPC_FAR *xInSamps,
            float __RPC_FAR *xOutSamps,
            float __RPC_FAR *yInSamps,
            float __RPC_FAR *yOutSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dReal2FFT( 
            double __RPC_FAR *xSamps,
            double __RPC_FAR *ySamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dReal2FFTip( 
            double __RPC_FAR *xInSamps,
            double __RPC_FAR *xOutSamps,
            double __RPC_FAR *yInSamps,
            double __RPC_FAR *yOutSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sReal2FFT( 
            short __RPC_FAR *xSamps,
            short __RPC_FAR *ySamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sReal2FFTip( 
            short __RPC_FAR *xInSamps,
            short __RPC_FAR *xOutSamps,
            short __RPC_FAR *yInSamps,
            short __RPC_FAR *yOutSamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fReal2InvFFT( 
            float __RPC_FAR *xSamps,
            float __RPC_FAR *ySamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dReal2InvFFT( 
            double __RPC_FAR *xSamps,
            double __RPC_FAR *ySamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sReal2InvFFT( 
            short __RPC_FAR *xSamps,
            short __RPC_FAR *ySamps,
            int order) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE dScalarMultiply( 
            double val,
            double __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fScalarMultiply( 
            float val,
            float __RPC_FAR *dst,
            int n) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sScalarMultiply( 
            short val,
            short __RPC_FAR *dst,
            int n) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIntelSPLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIntelSPL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIntelSPL __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIntelSPL __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIntelSPL __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIntelSPL __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIntelSPL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIntelSPL __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fCopy )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *src,
            float __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dCopy )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *src,
            double __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sCopy )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *src,
            short __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fSet )( 
            IIntelSPL __RPC_FAR * This,
            float val,
            float __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dSet )( 
            IIntelSPL __RPC_FAR * This,
            double val,
            double __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sSet )( 
            IIntelSPL __RPC_FAR * This,
            short val,
            short __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fZero )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dZero )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sZero )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fMax )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *vec,
            int n,
            float __RPC_FAR *outval,
            int __RPC_FAR *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dMax )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *vec,
            int n,
            double __RPC_FAR *outval,
            int __RPC_FAR *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sMax )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *vec,
            int n,
            short __RPC_FAR *outval,
            int __RPC_FAR *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fMin )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *vec,
            int n,
            float __RPC_FAR *outval,
            int __RPC_FAR *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dMin )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *vec,
            int n,
            double __RPC_FAR *outval,
            int __RPC_FAR *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sMin )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *vec,
            int n,
            short __RPC_FAR *outval,
            int __RPC_FAR *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fMean )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *vec,
            int n,
            float __RPC_FAR *outval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dMean )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *vec,
            int n,
            double __RPC_FAR *outval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sMean )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *vec,
            int n,
            short __RPC_FAR *outval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fNorm )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *srcA,
            float __RPC_FAR *srcB,
            int n,
            int flag,
            float __RPC_FAR *outval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dNorm )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *srcA,
            double __RPC_FAR *srcB,
            int n,
            int flag,
            double __RPC_FAR *outval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sNorm )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *srcA,
            short __RPC_FAR *srcB,
            int n,
            int flag,
            float __RPC_FAR *outval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fAutoCorr )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *src,
            int len,
            float __RPC_FAR *dst,
            int nLags,
            int flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dAutoCorr )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *src,
            int len,
            double __RPC_FAR *dst,
            int nLags,
            int flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sAutoCorr )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *src,
            int len,
            short __RPC_FAR *dst,
            int nLags,
            int flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fCrossCorr )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *srcA,
            int lenA,
            float __RPC_FAR *srcB,
            int lenB,
            float __RPC_FAR *dst,
            int loLag,
            int hiLag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dCrossCorr )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *srcA,
            int lenA,
            double __RPC_FAR *srcB,
            int lenB,
            double __RPC_FAR *dst,
            int loLag,
            int hiLag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sCrossCorr )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *srcA,
            int lenA,
            short __RPC_FAR *srcB,
            int lenB,
            short __RPC_FAR *dst,
            int loLag,
            int hiLag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fRealFFT )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *samps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fRealFFTip )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *inSamps,
            float __RPC_FAR *outSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dRealFFT )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *samps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dRealFFTip )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *inSamps,
            double __RPC_FAR *outSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sRealFFT )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *samps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sRealFFTip )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *inSamps,
            short __RPC_FAR *outSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fRealInvFFT )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *samps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fRealInvFFTip )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *inSamps,
            float __RPC_FAR *outSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dRealInvFFT )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *samps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dRealInvFFTip )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *inSamps,
            double __RPC_FAR *outSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sRealInvFFT )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *samps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sRealInvFFTip )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *inSamps,
            short __RPC_FAR *outSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fReal2FFT )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *xSamps,
            float __RPC_FAR *ySamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fReal2FFTip )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *xInSamps,
            float __RPC_FAR *xOutSamps,
            float __RPC_FAR *yInSamps,
            float __RPC_FAR *yOutSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dReal2FFT )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *xSamps,
            double __RPC_FAR *ySamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dReal2FFTip )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *xInSamps,
            double __RPC_FAR *xOutSamps,
            double __RPC_FAR *yInSamps,
            double __RPC_FAR *yOutSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sReal2FFT )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *xSamps,
            short __RPC_FAR *ySamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sReal2FFTip )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *xInSamps,
            short __RPC_FAR *xOutSamps,
            short __RPC_FAR *yInSamps,
            short __RPC_FAR *yOutSamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fReal2InvFFT )( 
            IIntelSPL __RPC_FAR * This,
            float __RPC_FAR *xSamps,
            float __RPC_FAR *ySamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dReal2InvFFT )( 
            IIntelSPL __RPC_FAR * This,
            double __RPC_FAR *xSamps,
            double __RPC_FAR *ySamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sReal2InvFFT )( 
            IIntelSPL __RPC_FAR * This,
            short __RPC_FAR *xSamps,
            short __RPC_FAR *ySamps,
            int order);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *dScalarMultiply )( 
            IIntelSPL __RPC_FAR * This,
            double val,
            double __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *fScalarMultiply )( 
            IIntelSPL __RPC_FAR * This,
            float val,
            float __RPC_FAR *dst,
            int n);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sScalarMultiply )( 
            IIntelSPL __RPC_FAR * This,
            short val,
            short __RPC_FAR *dst,
            int n);
        
        END_INTERFACE
    } IIntelSPLVtbl;

    interface IIntelSPL
    {
        CONST_VTBL struct IIntelSPLVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIntelSPL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIntelSPL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIntelSPL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIntelSPL_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIntelSPL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIntelSPL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIntelSPL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIntelSPL_fCopy(This,src,dst,n)	\
    (This)->lpVtbl -> fCopy(This,src,dst,n)

#define IIntelSPL_dCopy(This,src,dst,n)	\
    (This)->lpVtbl -> dCopy(This,src,dst,n)

#define IIntelSPL_sCopy(This,src,dst,n)	\
    (This)->lpVtbl -> sCopy(This,src,dst,n)

#define IIntelSPL_fSet(This,val,dst,n)	\
    (This)->lpVtbl -> fSet(This,val,dst,n)

#define IIntelSPL_dSet(This,val,dst,n)	\
    (This)->lpVtbl -> dSet(This,val,dst,n)

#define IIntelSPL_sSet(This,val,dst,n)	\
    (This)->lpVtbl -> sSet(This,val,dst,n)

#define IIntelSPL_fZero(This,dst,n)	\
    (This)->lpVtbl -> fZero(This,dst,n)

#define IIntelSPL_dZero(This,dst,n)	\
    (This)->lpVtbl -> dZero(This,dst,n)

#define IIntelSPL_sZero(This,dst,n)	\
    (This)->lpVtbl -> sZero(This,dst,n)

#define IIntelSPL_fMax(This,vec,n,outval,index)	\
    (This)->lpVtbl -> fMax(This,vec,n,outval,index)

#define IIntelSPL_dMax(This,vec,n,outval,index)	\
    (This)->lpVtbl -> dMax(This,vec,n,outval,index)

#define IIntelSPL_sMax(This,vec,n,outval,index)	\
    (This)->lpVtbl -> sMax(This,vec,n,outval,index)

#define IIntelSPL_fMin(This,vec,n,outval,index)	\
    (This)->lpVtbl -> fMin(This,vec,n,outval,index)

#define IIntelSPL_dMin(This,vec,n,outval,index)	\
    (This)->lpVtbl -> dMin(This,vec,n,outval,index)

#define IIntelSPL_sMin(This,vec,n,outval,index)	\
    (This)->lpVtbl -> sMin(This,vec,n,outval,index)

#define IIntelSPL_fMean(This,vec,n,outval)	\
    (This)->lpVtbl -> fMean(This,vec,n,outval)

#define IIntelSPL_dMean(This,vec,n,outval)	\
    (This)->lpVtbl -> dMean(This,vec,n,outval)

#define IIntelSPL_sMean(This,vec,n,outval)	\
    (This)->lpVtbl -> sMean(This,vec,n,outval)

#define IIntelSPL_fNorm(This,srcA,srcB,n,flag,outval)	\
    (This)->lpVtbl -> fNorm(This,srcA,srcB,n,flag,outval)

#define IIntelSPL_dNorm(This,srcA,srcB,n,flag,outval)	\
    (This)->lpVtbl -> dNorm(This,srcA,srcB,n,flag,outval)

#define IIntelSPL_sNorm(This,srcA,srcB,n,flag,outval)	\
    (This)->lpVtbl -> sNorm(This,srcA,srcB,n,flag,outval)

#define IIntelSPL_fAutoCorr(This,src,len,dst,nLags,flag)	\
    (This)->lpVtbl -> fAutoCorr(This,src,len,dst,nLags,flag)

#define IIntelSPL_dAutoCorr(This,src,len,dst,nLags,flag)	\
    (This)->lpVtbl -> dAutoCorr(This,src,len,dst,nLags,flag)

#define IIntelSPL_sAutoCorr(This,src,len,dst,nLags,flag)	\
    (This)->lpVtbl -> sAutoCorr(This,src,len,dst,nLags,flag)

#define IIntelSPL_fCrossCorr(This,srcA,lenA,srcB,lenB,dst,loLag,hiLag)	\
    (This)->lpVtbl -> fCrossCorr(This,srcA,lenA,srcB,lenB,dst,loLag,hiLag)

#define IIntelSPL_dCrossCorr(This,srcA,lenA,srcB,lenB,dst,loLag,hiLag)	\
    (This)->lpVtbl -> dCrossCorr(This,srcA,lenA,srcB,lenB,dst,loLag,hiLag)

#define IIntelSPL_sCrossCorr(This,srcA,lenA,srcB,lenB,dst,loLag,hiLag)	\
    (This)->lpVtbl -> sCrossCorr(This,srcA,lenA,srcB,lenB,dst,loLag,hiLag)

#define IIntelSPL_fRealFFT(This,samps,order)	\
    (This)->lpVtbl -> fRealFFT(This,samps,order)

#define IIntelSPL_fRealFFTip(This,inSamps,outSamps,order)	\
    (This)->lpVtbl -> fRealFFTip(This,inSamps,outSamps,order)

#define IIntelSPL_dRealFFT(This,samps,order)	\
    (This)->lpVtbl -> dRealFFT(This,samps,order)

#define IIntelSPL_dRealFFTip(This,inSamps,outSamps,order)	\
    (This)->lpVtbl -> dRealFFTip(This,inSamps,outSamps,order)

#define IIntelSPL_sRealFFT(This,samps,order)	\
    (This)->lpVtbl -> sRealFFT(This,samps,order)

#define IIntelSPL_sRealFFTip(This,inSamps,outSamps,order)	\
    (This)->lpVtbl -> sRealFFTip(This,inSamps,outSamps,order)

#define IIntelSPL_fRealInvFFT(This,samps,order)	\
    (This)->lpVtbl -> fRealInvFFT(This,samps,order)

#define IIntelSPL_fRealInvFFTip(This,inSamps,outSamps,order)	\
    (This)->lpVtbl -> fRealInvFFTip(This,inSamps,outSamps,order)

#define IIntelSPL_dRealInvFFT(This,samps,order)	\
    (This)->lpVtbl -> dRealInvFFT(This,samps,order)

#define IIntelSPL_dRealInvFFTip(This,inSamps,outSamps,order)	\
    (This)->lpVtbl -> dRealInvFFTip(This,inSamps,outSamps,order)

#define IIntelSPL_sRealInvFFT(This,samps,order)	\
    (This)->lpVtbl -> sRealInvFFT(This,samps,order)

#define IIntelSPL_sRealInvFFTip(This,inSamps,outSamps,order)	\
    (This)->lpVtbl -> sRealInvFFTip(This,inSamps,outSamps,order)

#define IIntelSPL_fReal2FFT(This,xSamps,ySamps,order)	\
    (This)->lpVtbl -> fReal2FFT(This,xSamps,ySamps,order)

#define IIntelSPL_fReal2FFTip(This,xInSamps,xOutSamps,yInSamps,yOutSamps,order)	\
    (This)->lpVtbl -> fReal2FFTip(This,xInSamps,xOutSamps,yInSamps,yOutSamps,order)

#define IIntelSPL_dReal2FFT(This,xSamps,ySamps,order)	\
    (This)->lpVtbl -> dReal2FFT(This,xSamps,ySamps,order)

#define IIntelSPL_dReal2FFTip(This,xInSamps,xOutSamps,yInSamps,yOutSamps,order)	\
    (This)->lpVtbl -> dReal2FFTip(This,xInSamps,xOutSamps,yInSamps,yOutSamps,order)

#define IIntelSPL_sReal2FFT(This,xSamps,ySamps,order)	\
    (This)->lpVtbl -> sReal2FFT(This,xSamps,ySamps,order)

#define IIntelSPL_sReal2FFTip(This,xInSamps,xOutSamps,yInSamps,yOutSamps,order)	\
    (This)->lpVtbl -> sReal2FFTip(This,xInSamps,xOutSamps,yInSamps,yOutSamps,order)

#define IIntelSPL_fReal2InvFFT(This,xSamps,ySamps,order)	\
    (This)->lpVtbl -> fReal2InvFFT(This,xSamps,ySamps,order)

#define IIntelSPL_dReal2InvFFT(This,xSamps,ySamps,order)	\
    (This)->lpVtbl -> dReal2InvFFT(This,xSamps,ySamps,order)

#define IIntelSPL_sReal2InvFFT(This,xSamps,ySamps,order)	\
    (This)->lpVtbl -> sReal2InvFFT(This,xSamps,ySamps,order)

#define IIntelSPL_dScalarMultiply(This,val,dst,n)	\
    (This)->lpVtbl -> dScalarMultiply(This,val,dst,n)

#define IIntelSPL_fScalarMultiply(This,val,dst,n)	\
    (This)->lpVtbl -> fScalarMultiply(This,val,dst,n)

#define IIntelSPL_sScalarMultiply(This,val,dst,n)	\
    (This)->lpVtbl -> sScalarMultiply(This,val,dst,n)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fCopy_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *src,
    float __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_fCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dCopy_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *src,
    double __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_dCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sCopy_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *src,
    short __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_sCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fSet_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float val,
    float __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_fSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dSet_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double val,
    double __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_dSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sSet_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short val,
    short __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_sSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fZero_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_fZero_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dZero_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_dZero_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sZero_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_sZero_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fMax_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *vec,
    int n,
    float __RPC_FAR *outval,
    int __RPC_FAR *index);


void __RPC_STUB IIntelSPL_fMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dMax_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *vec,
    int n,
    double __RPC_FAR *outval,
    int __RPC_FAR *index);


void __RPC_STUB IIntelSPL_dMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sMax_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *vec,
    int n,
    short __RPC_FAR *outval,
    int __RPC_FAR *index);


void __RPC_STUB IIntelSPL_sMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fMin_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *vec,
    int n,
    float __RPC_FAR *outval,
    int __RPC_FAR *index);


void __RPC_STUB IIntelSPL_fMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dMin_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *vec,
    int n,
    double __RPC_FAR *outval,
    int __RPC_FAR *index);


void __RPC_STUB IIntelSPL_dMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sMin_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *vec,
    int n,
    short __RPC_FAR *outval,
    int __RPC_FAR *index);


void __RPC_STUB IIntelSPL_sMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fMean_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *vec,
    int n,
    float __RPC_FAR *outval);


void __RPC_STUB IIntelSPL_fMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dMean_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *vec,
    int n,
    double __RPC_FAR *outval);


void __RPC_STUB IIntelSPL_dMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sMean_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *vec,
    int n,
    short __RPC_FAR *outval);


void __RPC_STUB IIntelSPL_sMean_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fNorm_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *srcA,
    float __RPC_FAR *srcB,
    int n,
    int flag,
    float __RPC_FAR *outval);


void __RPC_STUB IIntelSPL_fNorm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dNorm_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *srcA,
    double __RPC_FAR *srcB,
    int n,
    int flag,
    double __RPC_FAR *outval);


void __RPC_STUB IIntelSPL_dNorm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sNorm_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *srcA,
    short __RPC_FAR *srcB,
    int n,
    int flag,
    float __RPC_FAR *outval);


void __RPC_STUB IIntelSPL_sNorm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fAutoCorr_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *src,
    int len,
    float __RPC_FAR *dst,
    int nLags,
    int flag);


void __RPC_STUB IIntelSPL_fAutoCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dAutoCorr_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *src,
    int len,
    double __RPC_FAR *dst,
    int nLags,
    int flag);


void __RPC_STUB IIntelSPL_dAutoCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sAutoCorr_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *src,
    int len,
    short __RPC_FAR *dst,
    int nLags,
    int flag);


void __RPC_STUB IIntelSPL_sAutoCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fCrossCorr_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *srcA,
    int lenA,
    float __RPC_FAR *srcB,
    int lenB,
    float __RPC_FAR *dst,
    int loLag,
    int hiLag);


void __RPC_STUB IIntelSPL_fCrossCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dCrossCorr_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *srcA,
    int lenA,
    double __RPC_FAR *srcB,
    int lenB,
    double __RPC_FAR *dst,
    int loLag,
    int hiLag);


void __RPC_STUB IIntelSPL_dCrossCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sCrossCorr_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *srcA,
    int lenA,
    short __RPC_FAR *srcB,
    int lenB,
    short __RPC_FAR *dst,
    int loLag,
    int hiLag);


void __RPC_STUB IIntelSPL_sCrossCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fRealFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *samps,
    int order);


void __RPC_STUB IIntelSPL_fRealFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fRealFFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *inSamps,
    float __RPC_FAR *outSamps,
    int order);


void __RPC_STUB IIntelSPL_fRealFFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dRealFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *samps,
    int order);


void __RPC_STUB IIntelSPL_dRealFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dRealFFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *inSamps,
    double __RPC_FAR *outSamps,
    int order);


void __RPC_STUB IIntelSPL_dRealFFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sRealFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *samps,
    int order);


void __RPC_STUB IIntelSPL_sRealFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sRealFFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *inSamps,
    short __RPC_FAR *outSamps,
    int order);


void __RPC_STUB IIntelSPL_sRealFFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fRealInvFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *samps,
    int order);


void __RPC_STUB IIntelSPL_fRealInvFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fRealInvFFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *inSamps,
    float __RPC_FAR *outSamps,
    int order);


void __RPC_STUB IIntelSPL_fRealInvFFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dRealInvFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *samps,
    int order);


void __RPC_STUB IIntelSPL_dRealInvFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dRealInvFFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *inSamps,
    double __RPC_FAR *outSamps,
    int order);


void __RPC_STUB IIntelSPL_dRealInvFFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sRealInvFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *samps,
    int order);


void __RPC_STUB IIntelSPL_sRealInvFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sRealInvFFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *inSamps,
    short __RPC_FAR *outSamps,
    int order);


void __RPC_STUB IIntelSPL_sRealInvFFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fReal2FFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *xSamps,
    float __RPC_FAR *ySamps,
    int order);


void __RPC_STUB IIntelSPL_fReal2FFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fReal2FFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *xInSamps,
    float __RPC_FAR *xOutSamps,
    float __RPC_FAR *yInSamps,
    float __RPC_FAR *yOutSamps,
    int order);


void __RPC_STUB IIntelSPL_fReal2FFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dReal2FFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *xSamps,
    double __RPC_FAR *ySamps,
    int order);


void __RPC_STUB IIntelSPL_dReal2FFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dReal2FFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *xInSamps,
    double __RPC_FAR *xOutSamps,
    double __RPC_FAR *yInSamps,
    double __RPC_FAR *yOutSamps,
    int order);


void __RPC_STUB IIntelSPL_dReal2FFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sReal2FFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *xSamps,
    short __RPC_FAR *ySamps,
    int order);


void __RPC_STUB IIntelSPL_sReal2FFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sReal2FFTip_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *xInSamps,
    short __RPC_FAR *xOutSamps,
    short __RPC_FAR *yInSamps,
    short __RPC_FAR *yOutSamps,
    int order);


void __RPC_STUB IIntelSPL_sReal2FFTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fReal2InvFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float __RPC_FAR *xSamps,
    float __RPC_FAR *ySamps,
    int order);


void __RPC_STUB IIntelSPL_fReal2InvFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dReal2InvFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double __RPC_FAR *xSamps,
    double __RPC_FAR *ySamps,
    int order);


void __RPC_STUB IIntelSPL_dReal2InvFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sReal2InvFFT_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short __RPC_FAR *xSamps,
    short __RPC_FAR *ySamps,
    int order);


void __RPC_STUB IIntelSPL_sReal2InvFFT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_dScalarMultiply_Proxy( 
    IIntelSPL __RPC_FAR * This,
    double val,
    double __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_dScalarMultiply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_fScalarMultiply_Proxy( 
    IIntelSPL __RPC_FAR * This,
    float val,
    float __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_fScalarMultiply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIntelSPL_sScalarMultiply_Proxy( 
    IIntelSPL __RPC_FAR * This,
    short val,
    short __RPC_FAR *dst,
    int n);


void __RPC_STUB IIntelSPL_sScalarMultiply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIntelSPL_INTERFACE_DEFINED__ */



#ifndef __IMA2_IMAGEPROCESSINGLIBLib_LIBRARY_DEFINED__
#define __IMA2_IMAGEPROCESSINGLIBLib_LIBRARY_DEFINED__

/* library IMA2_IMAGEPROCESSINGLIBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMA2_IMAGEPROCESSINGLIBLib;

EXTERN_C const CLSID CLSID_IntelIPL;

#ifdef __cplusplus

class DECLSPEC_UUID("950C6005-DE09-4A09-9EC4-C0798A1AA46D")
IntelIPL;
#endif

EXTERN_C const CLSID CLSID_IntelSPL;

#ifdef __cplusplus

class DECLSPEC_UUID("F5F6D14E-4AB0-490C-BBD9-73FFAC43E3BD")
IntelSPL;
#endif
#endif /* __IMA2_IMAGEPROCESSINGLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
