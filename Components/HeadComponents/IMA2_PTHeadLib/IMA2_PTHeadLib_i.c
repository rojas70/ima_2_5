/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 26 12:28:11 2008
 */
/* Compiler settings for O:\Components\HeadComponents\IMA2_PTHeadLib\IMA2_PTHeadLib.idl:
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

const IID IID_IPTCatch = {0x868D647B,0xD30E,0x4A20,{0x89,0x91,0xD9,0x24,0x22,0x4B,0xE1,0xA2}};


const IID LIBID_IMA2_PTHEADLIBLib = {0x6B31DC86,0x3B53,0x40C3,{0x99,0xCB,0x40,0xB1,0xB4,0x9E,0x86,0xB9}};


const CLSID CLSID_PTCatch = {0x84638812,0xDA4D,0x445F,{0x8D,0x46,0x04,0xB2,0x96,0x1F,0x7A,0x1F}};


#ifdef __cplusplus
}
#endif

