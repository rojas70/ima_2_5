/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 23 14:10:04 2008
 */
/* Compiler settings for O:\Components\ControlBasis\IMA2_ControlBasisLib\IMA2_ControlBasisLib.idl:
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

const IID IID_IControlBasis = {0x3FA17E2C,0x11C9,0x4460,{0x82,0x47,0xF7,0xCF,0xD8,0xFB,0xE8,0x86}};


const IID LIBID_IMA2_CONTROLBASISLIBLib = {0x2408BA3C,0x414E,0x44F8,{0x8F,0xD4,0xE9,0x1B,0x8F,0xC6,0x04,0xB3}};


const CLSID CLSID_ControlBasis = {0x2A43D57C,0x00F6,0x4054,{0x9B,0x0C,0xE8,0x31,0xA9,0x51,0x7C,0xB7}};


#ifdef __cplusplus
}
#endif

