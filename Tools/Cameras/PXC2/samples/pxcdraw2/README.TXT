
  ---------------------------------------------------------
  PXCDRAW Samples for Win32 Systems -
	     Win95, 98, Me, NT, 2000, and XP
  ---------------------------------------------------------

  The PXCDRAW samples are two programs that use the same 
	GDI mechanism for displaying video in a window. The 
	differences between the programs are in their use of the 
	queuing facility in the PXC library. See the program 
	descriptions below. You should feel free to use our 
	samples as starting points for your applications.  


  --------------
  The GDI Method 
  --------------
  These programs show you how to use the Windows GDI 
	facilities to display video in a window. As computers 
	become faster and faster, this becomes a very good way to 
	display video. It is much simpler than DirectDraw and does 
	not rely as heavily on the VGA drivers. 

  Windows provides three methods for drawing graphics on a 
	window: text, raster, and vector. These samples use the 
	raster method. An image is stored in an array called a 
	bitmap and then a call is made to a Windows function that 
	describes how to display the bitmap. A bitmap consists of a 
  header and an upside-down representation of an image. 

  In the following programs, we set the header with the 
	function SetBitMapHead().  We flip the image upside down 
	with the function GetImage(). And we send the image to the 
	screen with the Windows function SetDIBitsToDevice(). You 
	can also use StretchDIBits() but it is slower. Don't use 
	StretchDIBits unless the image and window are different 
	sizes. SetDIBitsToDevice() is the fastest way to move an 
	image to the VGA card when the image size does not need to 
	change. 

  The complete algorithm for grabbing and displaying an 
	image is as follows: 
    Grab(); 
    GetImage(); 
    SetDIBitsToDevice();
  The bitmap header is set during initialization and never 
	changed. After the grab, the image is flipped row by row 
	in GetImage() and displayed. The work is divided between 
	the functions AppPaint() and AppIdle(). 

  -------------
  PROJECT FILES
  -------------
  The PXCDRAW samples have project files for Microsoft 
	Visual C/C++ 6.0. If you have an older version or a 
	different compiler, you will need to make your own project 
	file.  Each subdirectory that contains a sample also 
	contains all of the files necessary to build the sample. 
	In other words, the header files and libraries are 
	duplicated with each sample.


  ----------
  PXCDRAW1.C
  ----------
  PXCDRAW1 is the simplest and slowest sample. It uses a 
	NON-QUEUED grab which means it wastes 33 ms waiting for the 
	grab to complete. Then it copies the image into it to a 
	window. This sample has a maximum theoretical speed of 20 
	frames a second if it can get the display done in 1 field 
	time (16 ms). That means it would grab a frame, skip a field, 
	grab a frame, etc. The tradeoff is that this method is 
	easier than the one shown in PXCDRAW2.C.

  When you run the program, make note of the "COMPOSITE" 
	and "SVIDEO" buttons. Make sure you press the button for 
	the type of video you have.


  ------------------------------
  S-VIDEO LIMITATIIONS PER BOARD
  ------------------------------
  PXC200L:  S-VIDEO must be on channel 1 of 0 thru 3.
  PXC200AL: S-VIDEO must be on channel 1 of 0 thru 3.
  PXC200F:  S-VIDEO can be on any or all channels.
  PXC200AF: S-VIDEO can be on any or all channels.


  ----------
  PXCDRAW2.C
  ----------
  PXCDRAW2 uses QUEUED frame grabs and DOUBLE BUFFERING. 
	It keeps the image buffers full by using 2 queued grabs. 
	It flips an image and requeues the next grab while it sends 
	the image to a window. If this sample can flip an image and 
	requeue the next one fast enough, it can achieve a speed of 
	30 frames per second. This sample should display 25 (CCIR) 
	or 30 (NTSC) frames per second, unless you are using an old 
	VGA card, or a very slow PC. 


  ----------------------
  A NOTE ON BOTH SAMPLES
  ----------------------
  Both sample progams use 24-bit RGB images by default. This 
	means that they will run better if the computer's display 
	adapter is in 24-bit or 32-bit color mode (sometimes called 
	True Color or 16 million color mode). The samples can be 
	recompiled to use 8-bit grayscale images by changing the 
	value of the PIXEL_TYPE constant near the top of the source 
	file. Note that the programs will only work with 8 or 
	24-bit frames.

