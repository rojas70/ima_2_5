/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 21 19:20:32 2005
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_ArmComponent\IMA2_ArmComponent.idl:
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

const IID IID_IArmMech = {0xDBEC1F89,0x7AE2,0x449A,{0x88,0x8D,0x34,0x92,0x21,0x1B,0x08,0xED}};


const IID LIBID_IMA2_ARMCOMPONENTLib = {0xA51B77F0,0xCFA0,0x4903,{0x8F,0x95,0x61,0x62,0x86,0x4E,0x25,0x5D}};


const CLSID CLSID_ArmMech = {0x182973A0,0x8D57,0x4A47,{0x95,0x40,0x40,0xBD,0x20,0x23,0x86,0x85}};


#ifdef __cplusplus
}
#endif

