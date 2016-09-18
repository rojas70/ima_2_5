/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 09 22:55:31 2009
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_Motoman\IMA2_MotomanLib\IMA2_MotomanLib.idl:
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

const IID IID_IHP3JC = {0x0BF23BE8,0xDE51,0x4716,{0xB3,0xDE,0xCC,0xDF,0x0F,0x35,0xAD,0xEC}};


const IID LIBID_IMA2_MOTOMANLIBLib = {0xAFDC39ED,0xB97C,0x46C6,{0xB9,0x13,0x09,0xA2,0x8A,0xA9,0x52,0xD3}};


const CLSID CLSID_HP3JC = {0x898C35A9,0xD83C,0x4354,{0xB2,0xFE,0x4E,0x9F,0xDE,0x00,0xC4,0x64}};


#ifdef __cplusplus
}
#endif

