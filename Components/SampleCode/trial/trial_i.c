/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 07 15:45:55 2006
 */
/* Compiler settings for O:\Components\SampleCode\trial\trial.idl:
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

const IID IID_Itrialobj = {0xD12EFCCC,0x15DE,0x45A6,{0x84,0xD3,0x11,0xEA,0xD2,0xA8,0x83,0x27}};


const IID LIBID_TRIALLib = {0xF50D985F,0x0B86,0x43E1,{0x84,0xBA,0xEE,0xC4,0x28,0xEC,0x88,0xD4}};


const CLSID CLSID_trialobj = {0xE2EC1480,0xF13E,0x4F16,{0x83,0x38,0x15,0x49,0x5F,0x3A,0xE6,0xBF}};


#ifdef __cplusplus
}
#endif

