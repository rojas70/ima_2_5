/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 02 10:34:45 2009
 */
/* Compiler settings for O:\Components\MultiTypeComponents\IMA2_CopyRepsLib\IMA2_CopyRepsLib.idl:
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

const IID IID_ICopyVS = {0xC1BA00A2,0xE646,0x457F,{0xB3,0x91,0x04,0xC9,0x88,0xB0,0x0B,0x67}};


const IID LIBID_IMA2_COPYREPSLIBLib = {0x3B6C7D50,0x0501,0x42AD,{0xA2,0x9E,0xA4,0x84,0x3C,0x3A,0x2C,0x4D}};


const CLSID CLSID_CopyVS = {0x2B5BD3BD,0x6332,0x47DF,{0xA7,0x3E,0xA8,0x0A,0x48,0x6E,0x55,0x67}};


#ifdef __cplusplus
}
#endif

