/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 23 12:13:37 2008
 */
/* Compiler settings for O:\Components\ControlBasis\Matlab_test\Matlab_test.idl:
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

const IID IID_IMEngine = {0x03F54F4B,0xFB32,0x469B,{0xB8,0x7B,0x98,0xEB,0x9F,0xE1,0xE2,0xB9}};


const IID LIBID_MATLAB_TESTLib = {0x4AE26227,0x0B1A,0x4C3F,{0x83,0xCF,0x6E,0x03,0x80,0x22,0xA6,0xA7}};


const CLSID CLSID_MEngine = {0xC8FD3D73,0xDB1C,0x40F4,{0xAB,0x53,0x25,0x7E,0x9B,0x10,0x9D,0xE7}};


#ifdef __cplusplus
}
#endif

