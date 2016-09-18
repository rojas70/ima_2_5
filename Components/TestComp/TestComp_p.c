/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 16 14:32:58 2006
 */
/* Compiler settings for O:\Components\TestComp\TestComp.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "TestComp.h"

#define TYPE_FORMAT_STRING_SIZE   967                               
#define PROC_FORMAT_STRING_SIZE   29                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ITesting123, ver. 0.0,
   GUID={0x493FC2A5,0xFD98,0x451C,{0x87,0x40,0x94,0xA8,0x53,0x2A,0xD2,0x81}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITesting123_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short ITesting123_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_SERVER_INFO ITesting123_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITesting123_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ITesting123_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITesting123_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(8) _ITesting123ProxyVtbl = 
{
    &ITesting123_ProxyInfo,
    &IID_ITesting123,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* ITesting123::SendDouble */
};


static const PRPC_STUB_FUNCTION ITesting123_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _ITesting123StubVtbl =
{
    &IID_ITesting123,
    &ITesting123_ServerInfo,
    8,
    &ITesting123_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1] = 
        {
            
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SendDouble */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter Data */

/* 16 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	NdrFcShort( 0x3bc ),	/* Type Offset=956 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x13, 0x10,	/* FC_OP */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0x3a2 ),	/* Offset= 930 (938) */
/* 10 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 12 */	NdrFcShort( 0x18 ),	/* 24 */
/* 14 */	NdrFcShort( 0xa ),	/* 10 */
/* 16 */	NdrFcLong( 0x8 ),	/* 8 */
/* 20 */	NdrFcShort( 0x6c ),	/* Offset= 108 (128) */
/* 22 */	NdrFcLong( 0xd ),	/* 13 */
/* 26 */	NdrFcShort( 0x9e ),	/* Offset= 158 (184) */
/* 28 */	NdrFcLong( 0x9 ),	/* 9 */
/* 32 */	NdrFcShort( 0xcc ),	/* Offset= 204 (236) */
/* 34 */	NdrFcLong( 0xc ),	/* 12 */
/* 38 */	NdrFcShort( 0x292 ),	/* Offset= 658 (696) */
/* 40 */	NdrFcLong( 0x24 ),	/* 36 */
/* 44 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (742) */
/* 46 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 50 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (776) */
/* 52 */	NdrFcLong( 0x10 ),	/* 16 */
/* 56 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (806) */
/* 58 */	NdrFcLong( 0x2 ),	/* 2 */
/* 62 */	NdrFcShort( 0x306 ),	/* Offset= 774 (836) */
/* 64 */	NdrFcLong( 0x3 ),	/* 3 */
/* 68 */	NdrFcShort( 0x31e ),	/* Offset= 798 (866) */
/* 70 */	NdrFcLong( 0x14 ),	/* 20 */
/* 74 */	NdrFcShort( 0x336 ),	/* Offset= 822 (896) */
/* 76 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (75) */
/* 78 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 80 */	NdrFcShort( 0x2 ),	/* 2 */
/* 82 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 84 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 86 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 88 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 90 */	NdrFcShort( 0x8 ),	/* 8 */
/* 92 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (78) */
/* 94 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 96 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 98 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 100 */	NdrFcShort( 0x4 ),	/* 4 */
/* 102 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 108 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 110 */	NdrFcShort( 0x4 ),	/* 4 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x1 ),	/* 1 */
/* 116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	0x13, 0x0,	/* FC_OP */
/* 122 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (88) */
/* 124 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 126 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 128 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 130 */	NdrFcShort( 0x8 ),	/* 8 */
/* 132 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 134 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 136 */	NdrFcShort( 0x4 ),	/* 4 */
/* 138 */	NdrFcShort( 0x4 ),	/* 4 */
/* 140 */	0x11, 0x0,	/* FC_RP */
/* 142 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (98) */
/* 144 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 146 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 148 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 150 */	NdrFcLong( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 160 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 162 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 164 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 166 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 170 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 174 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 178 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 180 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (148) */
/* 182 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 184 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x6 ),	/* Offset= 6 (196) */
/* 192 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 194 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 196 */	
			0x11, 0x0,	/* FC_RP */
/* 198 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (166) */
/* 200 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 202 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 212 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 214 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 216 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 218 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 222 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 226 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 230 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 232 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (200) */
/* 234 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 236 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x6 ),	/* Offset= 6 (248) */
/* 244 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 246 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 248 */	
			0x11, 0x0,	/* FC_RP */
/* 250 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (218) */
/* 252 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 254 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 256 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 258 */	NdrFcShort( 0x2 ),	/* Offset= 2 (260) */
/* 260 */	NdrFcShort( 0x10 ),	/* 16 */
/* 262 */	NdrFcShort( 0x2b ),	/* 43 */
/* 264 */	NdrFcLong( 0x3 ),	/* 3 */
/* 268 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 270 */	NdrFcLong( 0x11 ),	/* 17 */
/* 274 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 276 */	NdrFcLong( 0x2 ),	/* 2 */
/* 280 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 282 */	NdrFcLong( 0x4 ),	/* 4 */
/* 286 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 288 */	NdrFcLong( 0x5 ),	/* 5 */
/* 292 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 294 */	NdrFcLong( 0xb ),	/* 11 */
/* 298 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 300 */	NdrFcLong( 0xa ),	/* 10 */
/* 304 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 306 */	NdrFcLong( 0x6 ),	/* 6 */
/* 310 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (524) */
/* 312 */	NdrFcLong( 0x7 ),	/* 7 */
/* 316 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 318 */	NdrFcLong( 0x8 ),	/* 8 */
/* 322 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (530) */
/* 324 */	NdrFcLong( 0xd ),	/* 13 */
/* 328 */	NdrFcShort( 0xffffff4c ),	/* Offset= -180 (148) */
/* 330 */	NdrFcLong( 0x9 ),	/* 9 */
/* 334 */	NdrFcShort( 0xffffff7a ),	/* Offset= -134 (200) */
/* 336 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 340 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (534) */
/* 342 */	NdrFcLong( 0x24 ),	/* 36 */
/* 346 */	NdrFcShort( 0xc0 ),	/* Offset= 192 (538) */
/* 348 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 352 */	NdrFcShort( 0xba ),	/* Offset= 186 (538) */
/* 354 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 358 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (590) */
/* 360 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 364 */	NdrFcShort( 0xe6 ),	/* Offset= 230 (594) */
/* 366 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 370 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (598) */
/* 372 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 376 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (602) */
/* 378 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 382 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (606) */
/* 384 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 388 */	NdrFcShort( 0xce ),	/* Offset= 206 (594) */
/* 390 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 394 */	NdrFcShort( 0xcc ),	/* Offset= 204 (598) */
/* 396 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 400 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (610) */
/* 402 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 406 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (606) */
/* 408 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 412 */	NdrFcShort( 0xca ),	/* Offset= 202 (614) */
/* 414 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 418 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (618) */
/* 420 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 424 */	NdrFcShort( 0xc6 ),	/* Offset= 198 (622) */
/* 426 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 430 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (626) */
/* 432 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 436 */	NdrFcShort( 0xbe ),	/* Offset= 190 (626) */
/* 438 */	NdrFcLong( 0x10 ),	/* 16 */
/* 442 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 444 */	NdrFcLong( 0x12 ),	/* 18 */
/* 448 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 450 */	NdrFcLong( 0x13 ),	/* 19 */
/* 454 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 456 */	NdrFcLong( 0x16 ),	/* 22 */
/* 460 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 462 */	NdrFcLong( 0x17 ),	/* 23 */
/* 466 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 468 */	NdrFcLong( 0xe ),	/* 14 */
/* 472 */	NdrFcShort( 0x9e ),	/* Offset= 158 (630) */
/* 474 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 478 */	NdrFcShort( 0xa4 ),	/* Offset= 164 (642) */
/* 480 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 484 */	NdrFcShort( 0x6a ),	/* Offset= 106 (590) */
/* 486 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 490 */	NdrFcShort( 0x68 ),	/* Offset= 104 (594) */
/* 492 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 496 */	NdrFcShort( 0x66 ),	/* Offset= 102 (598) */
/* 498 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 502 */	NdrFcShort( 0x60 ),	/* Offset= 96 (598) */
/* 504 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 508 */	NdrFcShort( 0x5a ),	/* Offset= 90 (598) */
/* 510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 514 */	NdrFcShort( 0x0 ),	/* Offset= 0 (514) */
/* 516 */	NdrFcLong( 0x1 ),	/* 1 */
/* 520 */	NdrFcShort( 0x0 ),	/* Offset= 0 (520) */
/* 522 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (521) */
/* 524 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 526 */	NdrFcShort( 0x8 ),	/* 8 */
/* 528 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 530 */	
			0x13, 0x0,	/* FC_OP */
/* 532 */	NdrFcShort( 0xfffffe44 ),	/* Offset= -444 (88) */
/* 534 */	
			0x13, 0x0,	/* FC_OP */
/* 536 */	NdrFcShort( 0x192 ),	/* Offset= 402 (938) */
/* 538 */	
			0x13, 0x0,	/* FC_OP */
/* 540 */	NdrFcShort( 0x1e ),	/* Offset= 30 (570) */
/* 542 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 544 */	NdrFcLong( 0x2f ),	/* 47 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 554 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 556 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 558 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 560 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 562 */	NdrFcShort( 0x1 ),	/* 1 */
/* 564 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 566 */	NdrFcShort( 0x4 ),	/* 4 */
/* 568 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 570 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 572 */	NdrFcShort( 0x10 ),	/* 16 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0xa ),	/* Offset= 10 (586) */
/* 578 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 580 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 582 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (542) */
/* 584 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 586 */	
			0x13, 0x0,	/* FC_OP */
/* 588 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (560) */
/* 590 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 592 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 594 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 596 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 598 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 600 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 602 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 604 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 606 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 608 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 610 */	
			0x13, 0x0,	/* FC_OP */
/* 612 */	NdrFcShort( 0xffffffa8 ),	/* Offset= -88 (524) */
/* 614 */	
			0x13, 0x10,	/* FC_OP */
/* 616 */	NdrFcShort( 0xffffffaa ),	/* Offset= -86 (530) */
/* 618 */	
			0x13, 0x10,	/* FC_OP */
/* 620 */	NdrFcShort( 0xfffffe28 ),	/* Offset= -472 (148) */
/* 622 */	
			0x13, 0x10,	/* FC_OP */
/* 624 */	NdrFcShort( 0xfffffe58 ),	/* Offset= -424 (200) */
/* 626 */	
			0x13, 0x10,	/* FC_OP */
/* 628 */	NdrFcShort( 0xffffffa2 ),	/* Offset= -94 (534) */
/* 630 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 632 */	NdrFcShort( 0x10 ),	/* 16 */
/* 634 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 636 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 638 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 640 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 642 */	
			0x13, 0x0,	/* FC_OP */
/* 644 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (630) */
/* 646 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 648 */	NdrFcShort( 0x20 ),	/* 32 */
/* 650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 652 */	NdrFcShort( 0x0 ),	/* Offset= 0 (652) */
/* 654 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 656 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 658 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 660 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 662 */	NdrFcShort( 0xfffffe66 ),	/* Offset= -410 (252) */
/* 664 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 666 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 668 */	NdrFcShort( 0x4 ),	/* 4 */
/* 670 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 676 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 678 */	NdrFcShort( 0x4 ),	/* 4 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	NdrFcShort( 0x1 ),	/* 1 */
/* 684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 688 */	0x13, 0x0,	/* FC_OP */
/* 690 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (646) */
/* 692 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 694 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 696 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 698 */	NdrFcShort( 0x8 ),	/* 8 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 702 */	NdrFcShort( 0x6 ),	/* Offset= 6 (708) */
/* 704 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 706 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 708 */	
			0x11, 0x0,	/* FC_RP */
/* 710 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (666) */
/* 712 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 714 */	NdrFcShort( 0x4 ),	/* 4 */
/* 716 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 720 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 722 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	0x13, 0x0,	/* FC_OP */
/* 736 */	NdrFcShort( 0xffffff5a ),	/* Offset= -166 (570) */
/* 738 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 740 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 742 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 744 */	NdrFcShort( 0x8 ),	/* 8 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0x6 ),	/* Offset= 6 (754) */
/* 750 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 752 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 754 */	
			0x11, 0x0,	/* FC_RP */
/* 756 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (712) */
/* 758 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 760 */	NdrFcShort( 0x8 ),	/* 8 */
/* 762 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 764 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x10 ),	/* 16 */
/* 768 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 770 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 772 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (758) */
			0x5b,		/* FC_END */
/* 776 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 778 */	NdrFcShort( 0x18 ),	/* 24 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0xa ),	/* Offset= 10 (792) */
/* 784 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 786 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 788 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (764) */
/* 790 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 792 */	
			0x11, 0x0,	/* FC_RP */
/* 794 */	NdrFcShort( 0xfffffd8c ),	/* Offset= -628 (166) */
/* 796 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 798 */	NdrFcShort( 0x1 ),	/* 1 */
/* 800 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 806 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 808 */	NdrFcShort( 0x8 ),	/* 8 */
/* 810 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 812 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 814 */	NdrFcShort( 0x4 ),	/* 4 */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	0x13, 0x0,	/* FC_OP */
/* 820 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (796) */
/* 822 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 824 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 826 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 828 */	NdrFcShort( 0x2 ),	/* 2 */
/* 830 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 836 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 838 */	NdrFcShort( 0x8 ),	/* 8 */
/* 840 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 842 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 844 */	NdrFcShort( 0x4 ),	/* 4 */
/* 846 */	NdrFcShort( 0x4 ),	/* 4 */
/* 848 */	0x13, 0x0,	/* FC_OP */
/* 850 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (826) */
/* 852 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 854 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 856 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 858 */	NdrFcShort( 0x4 ),	/* 4 */
/* 860 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 864 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 866 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 868 */	NdrFcShort( 0x8 ),	/* 8 */
/* 870 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 872 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 874 */	NdrFcShort( 0x4 ),	/* 4 */
/* 876 */	NdrFcShort( 0x4 ),	/* 4 */
/* 878 */	0x13, 0x0,	/* FC_OP */
/* 880 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (856) */
/* 882 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 884 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 886 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 888 */	NdrFcShort( 0x8 ),	/* 8 */
/* 890 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 894 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 896 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 898 */	NdrFcShort( 0x8 ),	/* 8 */
/* 900 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 902 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 904 */	NdrFcShort( 0x4 ),	/* 4 */
/* 906 */	NdrFcShort( 0x4 ),	/* 4 */
/* 908 */	0x13, 0x0,	/* FC_OP */
/* 910 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (886) */
/* 912 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 914 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 916 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 920 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 922 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 924 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 930 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 932 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 934 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (916) */
/* 936 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 938 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 940 */	NdrFcShort( 0x28 ),	/* 40 */
/* 942 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (924) */
/* 944 */	NdrFcShort( 0x0 ),	/* Offset= 0 (944) */
/* 946 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 948 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 950 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 952 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc51 ),	/* Offset= -943 (10) */
			0x5b,		/* FC_END */
/* 956 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 960 */	NdrFcShort( 0x4 ),	/* 4 */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0xfffffc3e ),	/* Offset= -962 (2) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _TestComp_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ITesting123ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _TestComp_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ITesting123StubVtbl,
    0
};

PCInterfaceName const _TestComp_InterfaceNamesList[] = 
{
    "ITesting123",
    0
};

const IID *  _TestComp_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _TestComp_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _TestComp, pIID, n)

int __stdcall _TestComp_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_TestComp_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo TestComp_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _TestComp_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _TestComp_StubVtblList,
    (const PCInterfaceName * ) & _TestComp_InterfaceNamesList,
    (const IID ** ) & _TestComp_BaseIIDList,
    & _TestComp_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
