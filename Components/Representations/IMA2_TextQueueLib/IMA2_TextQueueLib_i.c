/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 17 16:08:37 2006
 */
/* Compiler settings for O:\Components\Representations\IMA2_TextQueueLib\IMA2_TextQueueLib.idl:
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

const IID IID_ITextQueue = {0x1D5132BF,0xD5C2,0x4916,{0x9E,0x56,0x60,0x3D,0x98,0x7D,0x48,0x6C}};


const IID LIBID_IMA2_TEXTQUEUELIBLib = {0x14E7DF59,0x7A6D,0x4DBE,{0x98,0x42,0x37,0xE5,0xB9,0xD0,0x3D,0x58}};


const CLSID CLSID_TextQueue = {0x65D465D7,0xFE9B,0x4972,{0xB4,0x60,0x8B,0xDE,0xF9,0x13,0xF7,0x90}};


#ifdef __cplusplus
}
#endif

