/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 02 15:08:18 2006
 */
/* Compiler settings for O:\Components\Hand\IMA2_BarretLib\IMA2_BarretLib.idl:
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

const IID IID_IBarretComp = {0x5F38AA5F,0x6EDF,0x4841,{0x88,0x09,0xB4,0x20,0x56,0xB8,0xB9,0xFE}};


const IID LIBID_IMA2_BARRETLIBLib = {0x1DAE7BC7,0x0BE4,0x4375,{0xB5,0x0B,0x10,0xFC,0x23,0x0D,0x51,0x3B}};


const CLSID CLSID_BarretComp = {0xEA74A33A,0x60F9,0x4CBE,{0x82,0x8D,0xC1,0x3A,0x9B,0x70,0x0A,0x33}};


#ifdef __cplusplus
}
#endif

