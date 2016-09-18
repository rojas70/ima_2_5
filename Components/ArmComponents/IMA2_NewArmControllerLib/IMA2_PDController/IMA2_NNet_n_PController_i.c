/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Nov 17 12:07:18 2008
 */
/* Compiler settings for O:\Components\ArmComponents\IMA2_NewArmControllerLib\IMA2_PDController\IMA2_NNet_n_PController.idl:
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

const IID IID_INewValveController = {0xB53073D1,0x1C5C,0x4916,{0x8A,0x27,0x92,0xA5,0xB7,0x40,0x2F,0x17}};


const IID LIBID_IMA2_NNET_N_PCONTROLLERLib = {0x72A62003,0x8AA6,0x4EA1,{0x95,0xC4,0xC3,0xE5,0x65,0x6F,0x88,0x7D}};


const CLSID CLSID_NewValveController = {0x71645483,0xB459,0x4EEA,{0xA3,0x55,0xB3,0xF3,0xD8,0xA5,0x74,0x8D}};


#ifdef __cplusplus
}
#endif

