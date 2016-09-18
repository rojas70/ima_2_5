/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 21 10:25:02 2006
 */
/* Compiler settings for O:\Components\SES\IMA2_SESInterface\IMA2_SESInterface.idl:
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

const IID IID_ISESInterface = {0xEE72C810,0xB8A2,0x415C,{0xA8,0xBD,0x68,0x68,0x4D,0x2C,0x02,0x1A}};


const IID LIBID_IMA2_SESINTERFACELib = {0xA99ABE6C,0x363D,0x40B1,{0x8C,0x47,0x8B,0xE0,0x0B,0x57,0x80,0x03}};


const CLSID CLSID_SESInterface = {0xE57C703D,0x7019,0x4637,{0x8A,0x46,0x9A,0xFE,0x80,0x51,0x83,0x48}};


#ifdef __cplusplus
}
#endif

