/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 03 15:10:12 2009
 */
/* Compiler settings for O:\Components\FT Sensor\IMA2_FTSensorLib\IMA2_FTSensorLib.idl:
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

const IID IID_IFTSensorCom = {0xAE08C1B6,0x9B59,0x4131,{0x8C,0x78,0x71,0x4B,0x03,0x6B,0xEC,0x38}};


const IID LIBID_IMA2_FTSENSORLIBLib = {0x6A8400B2,0xA349,0x4AFA,{0x9D,0x26,0x21,0x81,0x20,0xF3,0xD4,0xBD}};


const CLSID CLSID_FTSensorCom = {0xB76D0DD9,0xD211,0x43FB,{0xAF,0x30,0x0B,0x1A,0x6D,0xF3,0x2C,0xB3}};


#ifdef __cplusplus
}
#endif

