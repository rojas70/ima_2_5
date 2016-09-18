/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Nov 29 14:22:27 2008
 */
/* Compiler settings for O:\Components\CameraComponents\IMA2_FrameGrabberLib\IMA2_FrameGrabberLib.idl:
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

const IID IID_IPXC_FG = {0x608CC024,0x05D3,0x4BEB,{0x81,0xED,0x73,0x57,0x11,0x75,0xC6,0xA3}};


const IID LIBID_IMA2_FRAMEGRABBERLIBLib = {0x5102A4A0,0x3418,0x488A,{0x87,0xC9,0x7C,0xA4,0x02,0xDB,0x51,0xBD}};


const CLSID CLSID_PXC_FG = {0x103A665D,0xAC59,0x412E,{0xAE,0xFD,0x01,0x64,0xEF,0x9C,0xB5,0x82}};


#ifdef __cplusplus
}
#endif

