/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 13 11:31:31 2008
 */
/* Compiler settings for O:\Components\MultiTypeComponents\IMA2_BasicComponentsLib\IMA2_BasicComponentsLib.idl:
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

const IID IID_IVectorSignal = {0x4EB79C6B,0xB32F,0x4834,{0x97,0xAE,0x82,0x9B,0x56,0xBB,0x3F,0xB1}};


const IID IID_IVSandFiles = {0x37712595,0x1EB7,0x48C0,{0xAA,0xFD,0x70,0x31,0xF5,0x35,0x7F,0x43}};


const IID LIBID_IMA2_BASICCOMPONENTSLIBLib = {0x08D47F9E,0x6A98,0x4B2C,{0x9A,0xAC,0xA9,0xEC,0x21,0x0F,0x3E,0x0F}};


const CLSID CLSID_VectorSignal = {0x7F58ABCE,0x1E9C,0x495F,{0x84,0x33,0x81,0xB3,0x04,0xA4,0x71,0x3B}};


const CLSID CLSID_VSandFiles = {0xEBB38638,0x88D2,0x44EF,{0xA1,0x42,0x8E,0x25,0x62,0x70,0x6B,0xEE}};


#ifdef __cplusplus
}
#endif

