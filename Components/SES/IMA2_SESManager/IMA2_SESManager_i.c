/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 21 16:06:09 2006
 */
/* Compiler settings for O:\Components\SES\IMA2_SESManager\IMA2_SESManager.idl:
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

const IID IID_ISesManager = {0x2C82E557,0x68E3,0x470B,{0x9D,0x6A,0xD9,0xD8,0xA3,0x84,0x37,0xED}};


const IID LIBID_IMA2_SESMANAGERLib = {0x811951D3,0x639E,0x4C93,{0xAE,0xF8,0x0F,0xBA,0x60,0xB8,0x5A,0x24}};


const CLSID CLSID_SesManager = {0x6E17776E,0x8396,0x4F5A,{0xBA,0xDA,0x61,0xBC,0x13,0x60,0x8A,0x3D}};


#ifdef __cplusplus
}
#endif

