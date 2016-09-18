/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 08 17:00:03 2006
 */
/* Compiler settings for O:\Components\Representations\IMA2_DynamicRepsLib\IMA2_DynamicRepsLib.idl:
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

const IID IID_IDynamicVector = {0xAC378F4C,0xC175,0x42C4,{0xBB,0xDE,0xF4,0xF3,0xE1,0x3A,0x62,0x36}};


const IID LIBID_IMA2_DYNAMICREPSLIBLib = {0xF145B219,0x03DE,0x4FD5,{0x91,0x6C,0x3C,0xF1,0x32,0x4C,0x99,0x44}};


const CLSID CLSID_DynamicVector = {0xFEAB28F2,0x03C5,0x4618,{0x83,0xA8,0xD5,0x16,0xE2,0x51,0x35,0xD5}};


#ifdef __cplusplus
}
#endif

