/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 26 13:10:06 2008
 */
/* Compiler settings for O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.idl:
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

const IID IID_INetImgRep = {0x907053F1,0x3EC2,0x4402,{0xA5,0xD8,0x26,0x43,0x82,0xC3,0x4F,0xFE}};


const IID IID_IImageRep = {0x7FDA7758,0xCBF3,0x48D0,{0xAF,0xF1,0xA2,0x98,0xDA,0xF5,0x4B,0x9B}};


const IID IID_IFeatureInfo = {0x79DE6720,0x6D92,0x11d1,{0xBC,0x62,0x00,0x20,0xAF,0xF1,0x2F,0xB6}};


const IID LIBID_IMA2_IMAGEREPLIBLib = {0x7481AFA4,0x383D,0x4148,{0xB8,0xFA,0x86,0x0C,0x8E,0xE9,0x27,0xC1}};


const CLSID CLSID_NetImgRep = {0xC37B8632,0x9581,0x4FB1,{0xB0,0xE1,0x4B,0x95,0xF4,0x72,0xA7,0xD3}};


#ifdef __cplusplus
}
#endif

