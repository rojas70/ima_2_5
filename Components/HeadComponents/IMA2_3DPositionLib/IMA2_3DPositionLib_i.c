/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 03 13:17:44 2008
 */
/* Compiler settings for O:\Components\HeadComponents\IMA2_3DPositionLib\IMA2_3DPositionLib.idl:
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

const IID IID_IComputePosition = {0xCF19C9A8,0x1DB2,0x45A2,{0x9A,0x5E,0x15,0xCC,0x78,0x74,0xDC,0xE0}};


const IID LIBID_IMA2_3DPOSITIONLIBLib = {0x2C811921,0x6395,0x4376,{0x86,0x4A,0xEF,0x04,0x8F,0xBC,0x1C,0xA6}};


const CLSID CLSID_ComputePosition = {0x152A576E,0xB530,0x4321,{0x9D,0x15,0xCC,0xE5,0x0B,0xA2,0x56,0x6F}};


#ifdef __cplusplus
}
#endif

