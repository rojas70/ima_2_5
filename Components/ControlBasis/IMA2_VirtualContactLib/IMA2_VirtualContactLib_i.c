/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 18 21:56:32 2009
 */
/* Compiler settings for O:\Components\ControlBasis\IMA2_VirtualContactLib\IMA2_VirtualContactLib.idl:
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

const IID IID_IISAC_Assembly = {0x33CCC6E1,0x9887,0x4140,{0x8A,0x2D,0xAD,0xA1,0x38,0xAA,0x9D,0xF0}};


const IID LIBID_IMA2_VIRTUALCONTACTLIBLib = {0x7733B835,0xADFA,0x44CC,{0xAF,0x23,0x3D,0x93,0xA2,0xAD,0xAE,0x01}};


const CLSID CLSID_ISAC_Assembly = {0x74FEEC9C,0x4F27,0x44B7,{0xB8,0x37,0x96,0x4E,0x34,0x20,0x15,0x73}};


#ifdef __cplusplus
}
#endif

