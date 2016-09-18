/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 16 14:05:56 2006
 */
/* Compiler settings for O:\Components\Lase Range Finder Components\IMA2_PanTiltLaser\IMA2_PanTiltLaser.idl:
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

const IID IID_IPanTiltUnit = {0xA4AB809D,0x38CB,0x439D,{0xAE,0x91,0x93,0xCB,0x6C,0x1A,0xEC,0x46}};


const IID LIBID_IMA2_PANTILTLASERLib = {0xEF31C770,0x95E5,0x4A6F,{0x9F,0x31,0x88,0x7E,0xA6,0x37,0x63,0x04}};


const CLSID CLSID_PanTiltUnit = {0xB87BF833,0xC75F,0x494C,{0xB4,0x4A,0x67,0xAB,0xD7,0x58,0x40,0xE2}};


#ifdef __cplusplus
}
#endif

