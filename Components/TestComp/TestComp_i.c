/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 16 14:32:58 2006
 */
/* Compiler settings for O:\Components\TestComp\TestComp.idl:
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

const IID IID_ITesting123 = {0x493FC2A5,0xFD98,0x451C,{0x87,0x40,0x94,0xA8,0x53,0x2A,0xD2,0x81}};


const IID LIBID_TESTCOMPLib = {0xF17CDE57,0xD545,0x4CD3,{0xA8,0xE7,0x75,0xBC,0x66,0xAA,0x42,0x49}};


const CLSID CLSID_Testing123 = {0xDF45426C,0x5436,0x4EB1,{0xB0,0x1E,0xD1,0xDB,0x72,0x35,0xAC,0x3E}};


#ifdef __cplusplus
}
#endif

