/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 25 14:13:44 2008
 */
/* Compiler settings for O:\Components\CameraComponents\IMA2_OpenCVLib\IMA2_ImageProcessingLib.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID_IIntelIPL = {0x2B6D762F,0x3A73,0x4645,{0xB0,0xC0,0x4D,0xE8,0xE7,0xDF,0x8F,0x3A}};


const IID IID_IIntelSPL = {0x8398F1C1,0x5FD8,0x4078,{0x8A,0x0B,0xDE,0xDA,0xDB,0x72,0x1F,0x46}};


const IID LIBID_IMA2_IMAGEPROCESSINGLIBLib = {0x97C5FC94,0x57ED,0x4DC6,{0x8C,0xFD,0x48,0x4E,0x6F,0x75,0xC4,0x41}};


const CLSID CLSID_IntelIPL = {0x950C6005,0xDE09,0x4A09,{0x9E,0xC4,0xC0,0x79,0x8A,0x1A,0xA4,0x6D}};


const CLSID CLSID_IntelSPL = {0xF5F6D14E,0x4AB0,0x490C,{0xBB,0xD9,0x73,0xFF,0xAC,0x43,0xE3,0xBD}};


#ifdef __cplusplus
}
#endif

