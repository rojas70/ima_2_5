/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 10 08:55:46 2009
 */
/* Compiler settings for O:\Components\ControlBasis\IMA2_HP3JCAssemblyPositionLib\IMA2_HP3JCAssemblyPositionLib.idl:
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

const IID IID_IComputeGoalPos = {0x88117FAD,0x9D58,0x42AC,{0x97,0x78,0x12,0x9A,0xE2,0xD2,0x29,0x62}};


const IID LIBID_IMA2_HP3JCASSEMBLYPOSITIONLIBLib = {0x7C9FE133,0x88E0,0x4D2F,{0x8C,0x69,0x03,0x99,0xB7,0xA2,0x8F,0xA5}};


const CLSID CLSID_ComputeGoalPos = {0x121915AA,0x25E2,0x4592,{0x85,0x50,0x5E,0x35,0x11,0xF0,0xFB,0xAB}};


#ifdef __cplusplus
}
#endif

