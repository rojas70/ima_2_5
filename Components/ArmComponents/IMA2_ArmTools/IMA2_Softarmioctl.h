// Softarm Device Driver IOCTL Interface File

// By providing different hexadecimal commands/locations to the IOCTL 
// interface, different HW functions can be used.
// One can find more help on IOCTL at www.msdn.com


#define	SOFTARM_DEVICE_TYPE		61800

// These IOCTL's expose the driver's most basic functionality.
#define IOCTL_SOFTARM_READ_ENCODERS \
    CTL_CODE( SOFTARM_DEVICE_TYPE, 0x900, METHOD_BUFFERED, FILE_READ_ACCESS )

#define IOCTL_SOFTARM_WRITE_VALVES \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x901, METHOD_BUFFERED, FILE_WRITE_ACCESS )

#define IOCTL_SOFTARM_WRITE_DIGITAL_OUT \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x902, METHOD_BUFFERED, FILE_WRITE_ACCESS )

#define IOCTL_SOFTARM_READ_DIGITAL_IN \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x903, METHOD_BUFFERED, FILE_READ_ACCESS )

#define IOCTL_SOFTARM_READ_ZFLAGS \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x904, METHOD_BUFFERED, FILE_READ_ACCESS )

#define IOCTL_SOFTARM_RESET_ZFLAGS \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x905, METHOD_BUFFERED, FILE_READ_ACCESS )

#define	IOCTL_SOFTARM_WRITE_ZMASK \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x906, METHOD_BUFFERED, FILE_WRITE_ACCESS )

// These IOCTL's are for the devices timer / sampling interrupt control.
#define	IOCTL_ENABLE_SAMPLING_MODE \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x907, METHOD_BUFFERED, FILE_WRITE_ACCESS )

#define IOCTL_SOFTARM_SAMPLE \
	CTL_CODE( SOFTARM_DEVICE_TYPE, 0x908, METHOD_BUFFERED, FILE_WRITE_ACCESS | FILE_READ_ACCESS)


// These structures define the input and output parameters for the reads and writes
// above and are specific to this device only, of course.
typedef struct _SoftarmEncoders {
		USHORT	Encoder[6];		// 6, 16-bit encoder inputs.
} SoftarmEncoders, *pSoftarmEncoders;

typedef struct _SoftarmValves {
		USHORT	Valve[12];		// 12, 12-bit output valves.
} SoftarmValves, *pSoftarmValves;

// These structures define the input and output parameters for the sampling control.
typedef struct _SoftarmSamplingInfo {
	BOOLEAN	EnableSampling;		// Allows enable / disable of sampling control
	ULONG	SamplingPeriod;		// Millisecond sampling time value.
} SoftarmSamplingInfo, *pSoftarmSamplingInfo;