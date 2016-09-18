/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Dec 04 12:20:53 2008
 */
/* Compiler settings for O:\Components\CameraComponents\IMA2_ColorSegmenterLib\IMA2_ColorSegmenterLib.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IColorSegmenter = {0x6D9415C2,0x3CB2,0x409A,{0xB4,0x2C,0x49,0xF6,0x7C,0xE4,0xE5,0x1F}};


const IID LIBID_IMA2_COLORSEGMENTERLIBLib = {0xDE6046B8,0x5C92,0x48D1,{0xAD,0x92,0xDD,0xB4,0x96,0xCB,0x23,0x21}};


const CLSID CLSID_ColorSegmenter = {0x5B77B15E,0x47A3,0x4BDF,{0x97,0x63,0x61,0xA9,0x3D,0xDC,0x77,0x49}};


#ifdef __cplusplus
}
#endif

