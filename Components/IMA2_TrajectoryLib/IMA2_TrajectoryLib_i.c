/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 08 16:06:30 2006
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_TrajectoryLib\IMA2_TrajectoryLib.idl:
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

const IID IID_ITrajectoryGen = {0x54E33F6C,0xB988,0x44FE,{0xAE,0xEF,0x4E,0x23,0x3D,0xAF,0xD3,0x1B}};


const IID IID_ITrajectoryPlayer = {0x0049F005,0x9129,0x4E2D,{0x8B,0x0B,0x1F,0x95,0xF4,0x09,0xA3,0x1B}};


const IID LIBID_IMA2_TRAJECTORYLIBLib = {0x28F40331,0x1E2F,0x4F50,{0x8A,0xD2,0x7F,0xEC,0x3E,0xAD,0xF7,0x1C}};


const CLSID CLSID_TrajectoryGen = {0xA8F3D778,0x0ABA,0x44A3,{0x89,0xE2,0x07,0x5F,0x8E,0xEA,0x04,0x8B}};


const CLSID CLSID_TrajectoryPlayer = {0x928A762F,0xF18E,0x4447,{0x91,0xC4,0x71,0xB2,0xE1,0x33,0x8A,0x3B}};


#ifdef __cplusplus
}
#endif

