/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jul 18 11:59:34 2008
 */
/* Compiler settings for O:\Components\FT Sensor\IMA2_JR3FTSensor\IMA2_JR3FTSensor.idl:
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

const IID IID_IJR3Sensor = {0xA884706D,0x7C76,0x498B,{0x99,0x6F,0x8D,0x3A,0x6D,0x7C,0x66,0xCE}};


const IID LIBID_IMA2_JR3FTSENSORLib = {0x1FCED051,0xC359,0x4168,{0x9E,0xC5,0xB9,0xD1,0x6E,0xC5,0xD7,0x30}};


const CLSID CLSID_JR3Sensor = {0x7B374970,0x0315,0x47DD,{0xB0,0x94,0x97,0x81,0x10,0x20,0xB3,0x01}};


#ifdef __cplusplus
}
#endif

