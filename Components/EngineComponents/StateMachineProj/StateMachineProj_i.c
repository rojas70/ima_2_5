/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 21 14:50:29 2006
 */
/* Compiler settings for O:\Components\EngineComponents\StateMachineProj\StateMachineProj.idl:
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

const IID IID_IStateMachine = {0x039B6487,0xB7C1,0x403F,{0xA0,0x49,0x1E,0x41,0x88,0xEE,0x7D,0x29}};


const IID LIBID_STATEMACHINEPROJLib = {0xF2F61FE1,0xFC37,0x4367,{0x8E,0x54,0x49,0xA8,0x58,0xE1,0xAD,0x6B}};


const CLSID CLSID_StateMachine = {0x8355FDFD,0x0EBC,0x47F4,{0xB0,0xB2,0xD7,0x14,0x04,0x54,0x70,0x22}};


#ifdef __cplusplus
}
#endif

