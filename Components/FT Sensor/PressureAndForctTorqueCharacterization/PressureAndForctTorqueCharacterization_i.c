/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 25 16:24:26 2006
 */
/* Compiler settings for O:\Components\FT Sensor\PressureAndForctTorqueCharacterization\PressureAndForctTorqueCharacterization.idl:
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

const IID IID_IPressureForceCharacterization = {0x94F541B1,0x0CC5,0x4F4B,{0x8B,0x07,0x43,0x97,0xED,0x7F,0x3D,0xC5}};


const IID LIBID_PRESSUREANDFORCTTORQUECHARACTERIZATIONLib = {0xB2E54CF7,0xA7D6,0x434F,{0xBD,0x1F,0x2B,0xC0,0xDF,0x03,0x0F,0xB7}};


const CLSID CLSID_PressureForceCharacterization = {0x4717FCEF,0x8FD4,0x40EB,{0x99,0x7F,0x9B,0x90,0x5D,0x66,0xD5,0xE9}};


#ifdef __cplusplus
}
#endif

