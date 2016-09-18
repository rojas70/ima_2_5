/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 10 12:32:59 2006
 */
/* Compiler settings for O:\Components\SES\IMA2_SESLib\IMA2_SESLib.idl:
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

const IID IID_ISES = {0xAAC834AD,0xCEB8,0x42A1,{0x84,0x8A,0xF7,0x4B,0xCF,0xED,0x51,0xDD}};


const IID LIBID_IMA2_SESLIBLib = {0xB3425986,0x44F8,0x42A4,{0x8C,0xDA,0x03,0xDD,0xF0,0x05,0x61,0x0E}};


const CLSID CLSID_SES = {0x180E794B,0x3C04,0x42D6,{0xA7,0xF5,0x5E,0x9F,0xC6,0x61,0xD1,0x68}};


#ifdef __cplusplus
}
#endif

