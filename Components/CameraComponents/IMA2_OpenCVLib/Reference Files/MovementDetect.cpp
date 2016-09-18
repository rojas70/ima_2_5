/*
Movement Detector
This program allows for the detection of any object in the workspace environment for ISAC.
Methods such as optical flow, phase corrleation, and image slippage are used for this goal.
The program presents a bug not yet fixed. The bug pertains to Dlls.
Currently the code is functional but, if any modifications are done the following has to be done.
Comment all of the functions that relate to the image processing except for SegByDifference.
Rebuild and register.
Take the comments off the other functions and reubild. DO NOT REREGISTER.
- If you do so, you will not be able to use/find the dll.

 Juan Rojas, Oct. 2003
*/

// MovementDetect.cpp : Implementation of CMovementDetect
#include "stdafx.h"
#include "MovementDetector.h"
#include "MovementDetect.h"

/////////////////////////////////////////////////////////////////////////////
// CMovementDetect

STDMETHODIMP CMovementDetect::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMovementDetect,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


//
// Name		- MechanismActivate
// Purpose	- "Do it" method for IMA mechanisms.

ULONG CMovementDetect::MechanismActivate(ULONG flags, ULONG operation)
{
	// TODO: Implement the operations that this component supports.
	switch(operation)
	{
	case 1:
		SegByDifference();
		break;
	case 2:
		SegByOpticalFlowBM();
		break;
	case 3:
		SegByOpticalFlowHS();
		break;
	case 4:
		SegByOpticalFlowLK();
		break;
	case 5:
		SegByOpticalFlowBM2();
		break;

	case 6:
		SegByPhaseCorrelation();
		break;
	case 7:
		SegByOpticalFlowBM3();
		break;

	default:
		MessageBox(NULL, "This operation ID is not supported!", NULL, MB_OK);
		break;

	}
		
	return S_OK;
}


//
// Name		- MechanismReset
// Purpose	- Standard way for IMA components to 

HRESULT CMovementDetect::MechanismReset(ULONG flags)
{

	return S_OK;
}


//
// Name		- FinalComponentInitialization
// Purpose	- Called to do allow the component to do any final setup.
// *NOTE: This may be called more than once after a component is inserted!

HRESULT CMovementDetect::FinalComponentInitialization(ULONG ulFlags, IUnknown *pIUnkAManager)
{
	// setup the output image rep
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lWidth,lHeight,lDepth; 

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL ) 
		{
			// get the input image rep property
			pInput->get_Width( &lWidth );		// width 
			pInput->get_Height( &lHeight );		// height 
			pInput->get_Depth( &lDepth );		// depth 

			// release I/F 
			pInput->Release(); 

			// set values for member variables
			m_lWidth = lWidth;
			m_lHeight = lHeight;

			// set up the output image rep property
			if( lDepth == 3 ) // color image from PXC frame grabber
			{
				pOutput->put_Width( lWidth );	// width 
				pOutput->put_Height( lHeight );	// height
				pOutput->put_Depth( 1 );		// depth, gray scale image

				// initialize m_pbPreviousFrame
				m_pbPreviousFrame = new BYTE[m_lWidth*m_lHeight];

				// initialize phase correlation variables
				m_pfFFTPrevious = new float[m_lWidth*m_lHeight];
			}
			else
			{
				MessageBox(NULL, "The depth of input image is not 3!", NULL, MB_OK);
			}

			// release I/F 
			pOutput->Release();

		} // end if( pInput != NULL && pOutput != NULL )
		
	}	// end link present 
	else
	{
		return E_POINTER; 
	}

	return S_OK;
}


//
// Name		- SaveComponentToStream
// Purpose	- Save the state of this component from storage.

HRESULT CMovementDetect::SaveComponentToStream(LPSTREAM pStm)
{
	ULONG	ulBytes;

	// TODO: Save persistent to pStm
	pStm->Write(&m_bDifferenceThresh,sizeof(double),&ulBytes);
	return S_OK;
}


//
// Name		- InitComponentFromStream
// Purpose	- Initialize the state of this component from storage.

HRESULT CMovementDetect::InitComponentFromStream(LPSTREAM pStm)
{
	ULONG	ulBytes;
	
	// TODO: Load persistent state from pStm
	pStm->Read(&m_bDifferenceThresh,sizeof(double),&ulBytes);
	return S_OK;
}


//
// Name		-	GetMaxStreamSize
// Purpose	-	Return the size of the stream necessary to save this object.

ULONG	CMovementDetect::GetMaxStreamSize()
{
	// TODO: Return a count of the amount of memory bytes that you require for
	//		 storage.

	return S_OK;
}

STDMETHODIMP CMovementDetect::get_DifferenceThresh(BYTE *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bDifferenceThresh;
	return S_OK;
}

STDMETHODIMP CMovementDetect::put_DifferenceThresh(BYTE newVal)
{
	// TODO: Add your implementation code here
	m_bDifferenceThresh = newVal;
	return S_OK;
}

STDMETHODIMP CMovementDetect::get_HSlambda(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_dHSlambda;
	return S_OK;
}

STDMETHODIMP CMovementDetect::put_HSlambda(double newVal)
{
	// TODO: Add your implementation code here
	m_dHSlambda = newVal;
	return S_OK;
}

STDMETHODIMP CMovementDetect::get_ImageInput(BSTR *pVal)
{
	// TODO: Add your implementation code here
	GetComponentLinkName(&m_pIUnkImgInput,pVal);
	return S_OK;
}

STDMETHODIMP CMovementDetect::put_ImageInput(BSTR newVal)
{
	// TODO: Add your implementation code here
	UpdateComponentLinkName(&m_pIUnkImgInput,newVal);
	return S_OK;
}

STDMETHODIMP CMovementDetect::get_ImageOutput(BSTR *pVal)
{
	// TODO: Add your implementation code here
	GetComponentLinkName(&m_pIUnkImgOutput, pVal);
	return S_OK;
}

STDMETHODIMP CMovementDetect::put_ImageOutput(BSTR newVal)
{
	// TODO: Add your implementation code here
	UpdateComponentLinkName(&m_pIUnkImgOutput, newVal);
	return S_OK;
}

STDMETHODIMP CMovementDetect::get_PixelMotion(BYTE *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bPixelMotionThresh;
	return S_OK;
}

STDMETHODIMP CMovementDetect::put_PixelMotion(BYTE newVal)
{
	// TODO: Add your implementation code here
	m_bPixelMotionThresh = newVal;
	return S_OK;
}

STDMETHODIMP CMovementDetect::get_VSMotionPosition(BSTR *pVal)
{
	// TODO: Add your implementation code here
	GetComponentLinkName(&m_pIUnkVSpos, pVal);
	return S_OK;
}

STDMETHODIMP CMovementDetect::put_VSMotionPosition(BSTR newVal)
{
	// TODO: Add your implementation code here
	UpdateComponentLinkName(&m_pIUnkVSpos, newVal);
	return S_OK;
}

/*
// Added 02/04 to include get a threshold to validate differencing
STDMETHODIMP CMovementDetect::get_PixelThreshold(BSTR * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bPixelThreshold;
	return S_OK;
}	

STDMETHODIMP CMovementDetect::put_PixelThreshold(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bPixelThreshold = newVal;
	return S_OK;
}
*/

// This median filter comes from the: Pocket Handbook of Image Processing 
// Algorithms in C by Arthur Weeks.
// The reason:Intel IPL function iplMedianFilter does not support float data type
// which is needed when calculating bounds for Optical Flow functions.

void CMovementDetect::MedianFilter(float *image, float *image1, int N, int Height, int Width)
{
	long x, y, i, j, z, index;
	float ar[121], a;

	// first, clear the output image
	for (index=0; index<Height*Width; index++)
	{
		image1[index] = 0;
	}

	// median filtering
	for (y=N/2; y<Height-N/2; y++)
	{
		for (x=N/2; x<Width-N/2; x++)
		{
			z = 0;

			for (j=-N/2; j<=N/2; j++)
			{
				for (i=-N/2; i<=N/2; i++)
				{
					index = x+i + (y+j)*Width;
					ar[z] = image[index];
					z++;
				}
			}

			for (j=1; j<N*N; j++)
			{
				a = ar[j];
				i = j-1;
				while (i>=0 && ar[i]>a)
				{
					ar[i+1] = ar[i];
					i = i-1;
				}
				ar[i+1] = a;
			}

			image1[x+(long)y*Width] = ar[N*N/2];

		}
	}
}

STDMETHODIMP CMovementDetect::SegByDifference()
{
	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	double sum, xsum, ysum;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)  
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index;
			float r, g, b, y;
			if (m_FirstFrameReady == false)  // First frame is not ready
			{
				// fill the m_pbPreviousFrame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						m_pbPreviousFrame[index] = ( BYTE ) y;
					} 
				}

				// set the flag
				m_FirstFrameReady = true;

			} 
			else
			{
				// simple thresholding here
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// difference from the previous frame
						int delta = (int)y - (int)m_pbPreviousFrame[index];
						delta = abs(delta);

						// save it for next frame
						m_pbPreviousFrame[index] = (BYTE) y;

						// output
						if (delta >= m_bDifferenceThresh)
							pbOutput[index] = 255;
						else
							pbOutput[index] = 0;
					} 
				}

				// calculate pos_x & pos_y
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						if (pbOutput[index] == 255)
						{
							sum++;
							xsum += i;
							ysum += j;
						}
					}
				}

				int posx, posy;

				if (sum>100)
				{
					posx = xsum/sum;
					posy = ysum/sum;
				}
				else
				{
					posx = m_lWidth/2;		// center
					posy = m_lHeight/2;	// center
				}

				// send the result to vector signal
				// JJ's agent takes input as normalized between 0 and 1
				pdPos[0] = (double)posx/(double)m_lWidth;
				pdPos[1] = (double)posy/(double)m_lHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					pbOutput[index] = 255;
				}

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					pbOutput[index] = 255;
				}

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	return S_OK;
}

STDMETHODIMP CMovementDetect::SegByOpticalFlowBM()
{
/*


	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	// for holding image data
	LPBYTE pbPreviousFrame;
	LPBYTE pbCurrentFrame;
	float * pofX, * pofY;
	LPBYTE pbMIm;	// thresholded optical flow image

	IplImage *iplIm1, *iplIm2;
	IplImage *iplX, *iplY;

	// allocate memory for previous & current frames
	pbPreviousFrame = new BYTE[m_lHeight*m_lWidth];
	pbCurrentFrame = new BYTE[m_lHeight*m_lWidth];

	// blob match size is 5x5
	int blobSize = 5;
	int ofHeight = m_lHeight/blobSize;
	int ofWidth = m_lWidth/blobSize;

	// allocate memory for optical flow result
	pofX = new float[ofHeight*ofWidth];
	pofY = new float[ofHeight*ofWidth];
	pbMIm = new BYTE[ofHeight*ofWidth];

	// create ipl image header
	iplIm1 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplIm2 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplX = cvCreateImageHeader( cvSize(ofWidth, ofHeight), IPL_DEPTH_32F, 1);
	iplY = cvCreateImageHeader( cvSize(ofWidth, ofHeight), IPL_DEPTH_32F, 1);

	// variables declaration for median filtering
	float * pofFilteredX = new float[ofHeight*ofWidth];
	float * pofFilteredY = new float[ofHeight*ofWidth];
	IplImage * iplFilteredX = cvCreateImageHeader(
		cvSize(ofWidth, ofHeight), 
		IPL_DEPTH_32F, 
		1);
	IplImage * iplFilteredY = cvCreateImageHeader(
		cvSize(ofWidth, ofHeight), 
		IPL_DEPTH_32F, 
		1);

	cvSetImageData(iplFilteredX, pofFilteredX, ofWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFilteredY, pofFilteredY, ofWidth*sizeof(IPL_DEPTH_32F));

	double sum, xsum, ysum;
	double pos_x, pos_y;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index, index2;
			float r, g, b, y;
			if (m_FirstFrameReady == false)  // First frame is not ready
			{
				// fill the m_pbPreviousFrame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						m_pbPreviousFrame[index] = ( BYTE ) y;
					} 
				}

				// set the flag
				m_FirstFrameReady = true;

			} 
			else
			{
				// optical flow segmentaiton here
				//
				// first, convert RGB to gray-level, and fill the current frame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// fill the current frame
						pbCurrentFrame[index] = (BYTE)y;
					} 
				}

				// fill the previous frame
				memcpy(pbPreviousFrame, m_pbPreviousFrame, m_lHeight*m_lWidth);

				// set the image data
				cvSetImageData(iplIm1, pbPreviousFrame, m_lWidth);
				cvSetImageData(iplIm2, pbCurrentFrame, m_lWidth);
				cvSetImageData(iplX, pofX, ofWidth*sizeof(IPL_DEPTH_32F));
				cvSetImageData(iplY, pofY, ofWidth*sizeof(IPL_DEPTH_32F));

				// set ROI: region of interest
				//
				// CvRect struct is:
				//	typedef struct CvRect
				//	{
				//		int x;
				//		int y;
				//		int width;
				//		int height;
				//	} CvRect;
				CvRect roi;
				roi.x = 0;
				roi.y = 0;
				roi.width = m_lWidth;
				roi.height = m_lHeight;

				// set ROI
				cvSetImageROI(iplIm1, roi);
				cvSetImageROI(iplIm2, roi);

				// calculate optical flow
				CvSize blockSize, shiftSize, maxRange;
        
				blockSize.width = 5;
				blockSize.height = 5;
				shiftSize.width = 1;
				shiftSize.height = 1;
				maxRange.width = 8;
				maxRange.height = 8;

				// use_previous must be 0 for this OpenCV function!
	            cvCalcOpticalFlowBM(
					iplIm1, iplIm2, // input images
					blockSize, shiftSize, maxRange, // sizes
					0, // use_previous must be 0!
					iplX, iplY); // output result

				// copy the current frame to previous frame
				memcpy(m_pbPreviousFrame, pbCurrentFrame, m_lHeight*m_lWidth);

				// filter the iplX & iplY image using median filter
				// Since Intel IPL function iplMedianFilter does not support 
				// float data type, I write my own median filter according to
				// "the pocket handbook of image processing algorithms in c" by
				// Arthur Weeks

				MedianFilter(pofX, pofFilteredX, 5, ofHeight, ofWidth);
				MedianFilter(pofY, pofFilteredY, 5, ofHeight, ofWidth);

				// find out the background motion
				//
				// Method to find the background motion: Assume that the background area is bigger than 
				// the forground, then on the motion histogram, the highest peak is the background motion.
				//
				// calculate the motion histogram
				//
				int pDim[1] = {13};
				float ranges[1][14] = 
					{-100, -5.5, -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 100};

				// Pointer-to-a-two-dimensional-float-array is not the same as 
				// pointer-to-pointer-to-type-float.
				// Some tricks have to be used to do this.
				// I found the following code from C-faq
				//
				// int **array2 = (int **)malloc(nrows * sizeof(int *));
				// array2[0] = (int *)malloc(nrows * ncolumns * sizeof(int));
				// for(i = 1; i < nrows; i++)
				//     array2[i] = array2[0] + i * ncolumns;
				//

				float ** ppfRanges = (float **)malloc(1 * sizeof(float *));
				ppfRanges[0] = (float *)malloc(1 * 14 * sizeof(float));				

				for(j=0; j<14; j++)
					ppfRanges[0][j] = ranges[0][j];

				// create CvHistogram
				CvHistogram *pXHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				CvHistogram *pYHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				// calc hist
				cvCalcHist(&iplFilteredX, pXHist);
				cvCalcHist(&iplFilteredY, pYHist);

				// free memory
				free(ppfRanges[0]);
				free(ppfRanges);

				// find max in hist
				float minXVal[1], maxXVal[1];
				int minXIdx[1], maxXIdx[1];
				float minYVal[1], maxYVal[1];
				int minYIdx[1], maxYIdx[1];

				cvGetMinMaxHistValue(
					pXHist,		// X histogram
					minXVal,	// min val
					maxXVal,	// max val
					minXIdx,	// min index
					maxXIdx);	// max index
				cvGetMinMaxHistValue(
					pYHist,		// Y histogram
					minYVal,
					maxYVal,
					minYIdx,
					maxYIdx);

				// calc lower and upper bound
				 if (( ppfRanges == 0 || maxXIdx[0] >=14 ))
				{
					ATLTRACE("Pointer is out of range or undefined\n");	
					return S_OK;
				}
				//then throw exception
				
				float XLBound = ppfRanges[0][ maxXIdx[0] ] - (float)m_bPixelMotionThresh;
				float XUBound = ppfRanges[0][ maxXIdx[0] ] + (float)m_bPixelMotionThresh;
				float YLBound = ppfRanges[0][ maxYIdx[0] ] - (float)m_bPixelMotionThresh;
				float YUBound = ppfRanges[0][ maxYIdx[0] ] + (float)m_bPixelMotionThresh;

				// release cvHistogram
				cvReleaseHist(&pXHist);
				cvReleaseHist(&pYHist);

				// segment the motion image and find the centroid of motion
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;

				for( j = 4; j < ofHeight-4; j++ ) {
					for ( i = 4; i < ofWidth-4; i++ ) {
						index = j*ofWidth+i;
						if (pofFilteredX[index] > XLBound &&
							pofFilteredX[index] < XUBound &&
							pofFilteredY[index] > YLBound &&
							pofFilteredY[index] < YUBound )
						{
							pbMIm[index] = 0;	// background motion
						}
						else
						{
							pbMIm[index] = 255;
							sum++;
							xsum +=i;
							ysum +=j;
						}
					}
				}

				// calculate pos_x & pos_y in pbMIm
				if (sum>40 && sum<(ofHeight/2)*(ofWidth/2))
				{
					pos_x = xsum/sum;
					pos_y = ysum/sum;
					DispatchAgentEvent(100, 1);
				}
				else
				{
					pos_x = ofWidth/2;	// center of the image
					pos_y = ofHeight/2;
					DispatchAgentEvent(100, 2);
				}

				// send the result to vector signal
				// JJ's head agent takes input as normalized between 0 and 1
				pdPos[0] = pos_x/(double)ofWidth;
				pdPos[1] = pos_y/(double)ofHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw the output image
				for( j=0; j<m_lHeight; j++ )
				{
					for( i=0; i<m_lWidth; i++ )
					{
						index = j*m_lWidth+i;
						index2 = (j/blobSize)*ofWidth+(i/blobSize);
						pbOutput[index] = pbMIm[index2];
					}
				}

				int posx = (int)(pdPos[0] * (double)m_lWidth);
				int posy = (int)(pdPos[1] * (double)m_lHeight);
				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					index2 = (posy+1)*m_lWidth+i;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Horizontal line is drawn\n");

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					index2 = j*m_lWidth+posx+1;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Vertical line is drawn\n");

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	// release image header
	cvReleaseImageHeader(&iplIm1);
	cvReleaseImageHeader(&iplIm2);
	cvReleaseImageHeader(&iplX);
	cvReleaseImageHeader(&iplY);
	cvReleaseImageHeader(&iplFilteredX);
	cvReleaseImageHeader(&iplFilteredY);

	// release memory
	delete pbPreviousFrame;
	delete pbCurrentFrame;
	delete pofX;
	delete pofY;
	delete pbMIm;
	delete pofFilteredX;
	delete pofFilteredY;

*/
	return S_OK;

}

STDMETHODIMP CMovementDetect::SegByOpticalFlowHS()
{
/*


	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	// allocate memory for previous & current frame
	LPBYTE pbPreviousFrame = new BYTE[m_lHeight*m_lWidth];
	LPBYTE pbCurrentFrame = new BYTE[m_lHeight*m_lWidth];

	// allocate memory for optical flow result
	float * pofX = new float[m_lHeight*m_lWidth];
	float * pofY = new float[m_lHeight*m_lWidth];
	// thresholded optical flow image
	LPBYTE pbMIm = new BYTE[m_lHeight*m_lWidth];

	// create ipl image header
	IplImage * iplIm1 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	IplImage * iplIm2 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	IplImage * iplX = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);
	IplImage * iplY = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);

	// variables declaration for median filtering
	float * pofFilteredX = new float[m_lHeight*m_lWidth];
	float * pofFilteredY = new float[m_lHeight*m_lWidth];
	IplImage * iplFilteredX = cvCreateImageHeader(
		cvSize(m_lWidth, m_lHeight), 
		IPL_DEPTH_32F, 
		1);
	IplImage * iplFilteredY = cvCreateImageHeader(
		cvSize(m_lWidth, m_lHeight), 
		IPL_DEPTH_32F, 
		1);

	cvSetImageData(iplFilteredX, pofFilteredX, m_lWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFilteredY, pofFilteredY, m_lWidth*sizeof(IPL_DEPTH_32F));

	double sum, xsum, ysum;
	double pos_x, pos_y;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index, index2;
			float r, g, b, y;
			if (m_FirstFrameReady == false)  // First frame is not ready
			{
				// fill the m_pbPreviousFrame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						m_pbPreviousFrame[index] = ( BYTE ) y;
					} 
				}

				// set the flag
				m_FirstFrameReady = true;

			} 
			else
			{
				// optical flow segmentaiton here
				//
				// first, convert RGB to gray-level, and fill the current frame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// fill the current frame
						pbCurrentFrame[index] = (BYTE)y;
					} 
				}

				// fill the previous frame
				memcpy(pbPreviousFrame, m_pbPreviousFrame, m_lHeight*m_lWidth);

				// set the image data
				cvSetImageData(iplIm1, pbPreviousFrame, m_lWidth);
				cvSetImageData(iplIm2, pbCurrentFrame, m_lWidth);
				cvSetImageData(iplX, pofX, m_lWidth*sizeof(IPL_DEPTH_32F));
				cvSetImageData(iplY, pofY, m_lWidth*sizeof(IPL_DEPTH_32F));

				// set ROI: region of interest
				//
				// CvRect struct is:
				//	typedef struct CvRect
				//	{
				//		int x;
				//		int y;
				//		int width;
				//		int height;
				//	} CvRect;
				CvRect roi;
				roi.x = 0;
				roi.y = 0;
				roi.width = m_lWidth;
				roi.height = m_lHeight;

				// set ROI
				cvSetImageROI(iplIm1, roi);
				cvSetImageROI(iplIm2, roi);
*/
				// calculate optical flow using Horn & Schunk method
				/*
				void cvCalcOpticalFlowHS( IplImage* srcA, IplImage* srcB, int usePrevious,
					IplImage* velx, IplImage* vely, double lambda, CvTermCriteria criteria);

					imgA		First image.
					imgB		Second image.
					usePrevious Uses previous (input)velocity field.
					velx		Horizontal omponent of the optical flow.
					vely		Vertical omponent of the optical flow.
					lambda		Lagrangian multiplier.
					criteria	Criteria of termination of velocity computing.

				typedef struct CvTermCriteria
				{
					int   type;  // may be combination of
								 // CV_TERMCRIT_ITER
								 // CV_TERMCRIT_EPS
					int   maxIter;
					float epsilon;
				} CvTermCriteria;
				*/
/*
				CvTermCriteria criteria;
				criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
				criteria.maxIter = 1000;
				criteria.epsilon = 0.001f;
				
				// set use_previous to 1
	            cvCalcOpticalFlowHS(
					iplIm1, iplIm2, // input images
					1, // use previous
					iplX, iplY, // output result
					m_dHSlambda,	// lambda
					criteria);	// termination criteria

				// copy the current frame to previous frame
				memcpy(m_pbPreviousFrame, pbCurrentFrame, m_lHeight*m_lWidth);

				// filter the iplX & iplY image using median filter
				// Since Intel IPL function iplMedianFilter does not support 
				// float data type, I write my own median filter according to
				// "the pocket handbook of image processing algorithms in c" by
				// Arthur Weeks
				//
				//memcpy(pofFilteredX, pofX, ofHeight*ofWidth*sizeof(float));
				//memcpy(pofFilteredY, pofY, ofHeight*ofWidth*sizeof(float));
				//
				MedianFilter(pofX, pofFilteredX, 5, m_lHeight, m_lWidth);
				MedianFilter(pofY, pofFilteredY, 5, m_lHeight, m_lWidth);

				// find out the background motion
				//
				// Method to find the background motion: Assume that the background area is bigger than 
				// the forground, then on the motion histogram, the highest peak is the background motion.
				//
				// calculate the motion histogram
				//
				// motion histogram bin width is 1, and it is arranged as following:
				// (less than -5.5), (-5.5, -4.5), ... , (4.5, 5.5), and (bigger than 5.5)
				// totally 13 bins
				// OpenCV Histogram functions will be used here
				//
				// create histogram 
				int pDim[1] = {13};
				float ranges[1][14] = 
					{-100, -5.5, -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 100};

				// Pointer-to-a-two-dimensional-float-array is not the same as 
				// pointer-to-pointer-to-type-float.
				// Some tricks have to be used to do this.
				// I found the following code from C-faq
				//
				// int **array2 = (int **)malloc(nrows * sizeof(int *));
				// array2[0] = (int *)malloc(nrows * ncolumns * sizeof(int));
				// for(i = 1; i < nrows; i++)
				//     array2[i] = array2[0] + i * ncolumns;
				//

				float ** ppfRanges = (float **)malloc(1 * sizeof(float *));
				ppfRanges[0] = (float *)malloc(1 * 14 * sizeof(float));

				for(j=0; j<14; j++)
					ppfRanges[0][j] = ranges[0][j];

				CvHistogram *pXHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				CvHistogram *pYHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				// calc hist
				cvCalcHist(&iplFilteredX, pXHist);
				cvCalcHist(&iplFilteredY, pYHist);

				// free up the memory
				free(ppfRanges[0]);
				free(ppfRanges);

				// find max in hist
				float minXVal[1], maxXVal[1];
				int minXIdx[1], maxXIdx[1];
				float minYVal[1], maxYVal[1];
				int minYIdx[1], maxYIdx[1];

				cvGetMinMaxHistValue(
					pXHist,		// X histogram
					minXVal,	// min val
					maxXVal,	// max val
					minXIdx,	// min index
					maxXIdx);	// max index
				cvGetMinMaxHistValue(
					pYHist,		// Y histogram
					minYVal,
					maxYVal,
					minYIdx,
					maxYIdx);

				// calc lower and upper bound
				float XLBound = ppfRanges[0][ maxXIdx[0] ] - (float)m_bPixelMotionThresh;
				float XUBound = ppfRanges[0][ maxXIdx[0] ] + (float)m_bPixelMotionThresh;
				float YLBound = ppfRanges[0][ maxYIdx[0] ] - (float)m_bPixelMotionThresh;
				float YUBound = ppfRanges[0][ maxYIdx[0] ] + (float)m_bPixelMotionThresh;

				// release cvHistogram
				cvReleaseHist(&pXHist);
				cvReleaseHist(&pYHist);

				// segment the motion image and find the centroid of motion
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;

				for( j = 20; j < m_lHeight-20; j++ ) {
					for ( i = 20; i < m_lWidth-20; i++ ) {
						index = j*m_lWidth+i;
						if (pofX[index] > XLBound &&
							pofX[index] < XUBound &&
							pofY[index] > YLBound &&
							pofY[index] < YUBound )
						{
								pbMIm[index] = 0;	// background motion
						}
						else
						{
							pbMIm[index] = 255;
							sum++;
							xsum +=i;
							ysum +=j;
						}
					}
				}

				// calculate pos_x & pos_y in pbMIm
				if (sum>200)
				{
					pos_x = xsum/sum;
					pos_y = ysum/sum;
				}
				else
				{
					pos_x = m_lWidth/2;	// center
					pos_y = m_lHeight/2;	// center
				}

				// send the result to vector signal
				// JJ's agent takes input as normalized between 0 and 1
				pdPos[0] = pos_x/(double)m_lWidth;
				pdPos[1] = pos_y/(double)m_lHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw the output image
				for( j=0; j<m_lHeight; j++ )
				{
					for( i=0; i<m_lWidth; i++ )
					{
						index = j*m_lWidth+i;
						pbOutput[index] = pbMIm[index];
					}
				}

				int posx = (int)(pdPos[0] * (double)m_lWidth);
				int posy = (int)(pdPos[1] * (double)m_lHeight);
				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					index2 = (posy+1)*m_lWidth+i;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Horizontal line is drawn\n");

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					index2 = j*m_lWidth+posx+1;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Vertical line is drawn\n");

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	// release image header
	cvReleaseImageHeader(&iplIm1);
	cvReleaseImageHeader(&iplIm2);
	cvReleaseImageHeader(&iplX);
	cvReleaseImageHeader(&iplY);
	cvReleaseImageHeader(&iplFilteredX);
	cvReleaseImageHeader(&iplFilteredY);

	// release memory
	delete pbPreviousFrame;
	delete pbCurrentFrame;
	delete pofX;
	delete pofY;
	delete pbMIm;
	delete pofFilteredX;
	delete pofFilteredY;


*/
	return S_OK;
	
}

STDMETHODIMP CMovementDetect::SegByOpticalFlowLK()
{

/*

	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	// allocate memory for previous & current frame
	LPBYTE pbPreviousFrame = new BYTE[m_lHeight*m_lWidth];
	LPBYTE pbCurrentFrame = new BYTE[m_lHeight*m_lWidth];

	// allocate memory for optical flow result
	float * pofX = new float[m_lHeight*m_lWidth];
	float * pofY = new float[m_lHeight*m_lWidth];
	// thresholded optical flow image
	LPBYTE pbMIm = new BYTE[m_lHeight*m_lWidth];

	// create ipl image header
	IplImage * iplIm1 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	IplImage * iplIm2 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	IplImage * iplX = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);
	IplImage * iplY = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);

	// variables declaration for median filtering
	float * pofFilteredX = new float[m_lHeight*m_lWidth];
	float * pofFilteredY = new float[m_lHeight*m_lWidth];
	IplImage * iplFilteredX = cvCreateImageHeader(
		cvSize(m_lWidth, m_lHeight), 
		IPL_DEPTH_32F, 
		1);
	IplImage * iplFilteredY = cvCreateImageHeader(
		cvSize(m_lWidth, m_lHeight), 
		IPL_DEPTH_32F, 
		1);

	cvSetImageData(iplFilteredX, pofFilteredX, m_lWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFilteredY, pofFilteredY, m_lWidth*sizeof(IPL_DEPTH_32F));

	double sum, xsum, ysum;
	double pos_x, pos_y;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index, index2;
			float r, g, b, y;
			if (m_FirstFrameReady == false)  // First frame is not ready
			{
				// fill the m_pbPreviousFrame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						m_pbPreviousFrame[index] = ( BYTE ) y;
					} 
				}

				// set the flag
				m_FirstFrameReady = true;

			} 
			else
			{
				// optical flow segmentaiton here
				//
				// first, convert RGB to gray-level, and fill the current frame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// fill the current frame
						pbCurrentFrame[index] = (BYTE)y;
					} 
				}

				// fill the previous frame
				memcpy(pbPreviousFrame, m_pbPreviousFrame, m_lHeight*m_lWidth);

				// set the image data
				cvSetImageData(iplIm1, pbPreviousFrame, m_lWidth);
				cvSetImageData(iplIm2, pbCurrentFrame, m_lWidth);
				cvSetImageData(iplX, pofX, m_lWidth*sizeof(IPL_DEPTH_32F));
				cvSetImageData(iplY, pofY, m_lWidth*sizeof(IPL_DEPTH_32F));

				// set ROI: region of interest
				//
				// CvRect struct is:
				//	typedef struct CvRect
				//	{
				//		int x;
				//		int y;
				//		int width;
				//		int height;
				//	} CvRect;
				CvRect roi;
				roi.x = 0;
				roi.y = 0;
				roi.width = m_lWidth;
				roi.height = m_lHeight;

				// set ROI
				cvSetImageROI(iplIm1, roi);
				cvSetImageROI(iplIm2, roi);
*/
				// use Lucas & Kanade method
				/*
				void cvCalcOpticalFlowLK( IplImage* srcA, IplImage* srcB, CvSize winSize,
					IplImage* velx, IplImage* vely);

					imgA		First image.
					imgB		Second image.
					winSize		Size of the averaging window used for grouping pixels.
					velx		Horizontal component of the optical flow.
					vely		Vertical component of the optical flow.
				*/
/*				// use Lucas & Kanade method
				CvSize winSize;
				winSize.width = 5;
				winSize.height = 5;

				cvCalcOpticalFlowLK(
					iplIm1, iplIm2,	// input images
					winSize,		// averaging window
					iplX, iplY);	// result

				// copy the current frame to previous frame
				memcpy(m_pbPreviousFrame, pbCurrentFrame, m_lHeight*m_lWidth);

				// filter the iplX & iplY image using median filter
				// Since Intel IPL function iplMedianFilter does not support 
				// float data type, I write my own median filter according to
				// "the pocket handbook of image processing algorithms in c" by
				// Arthur Weeks
				//
				//memcpy(pofFilteredX, pofX, m_lHeight*m_lWidth*sizeof(float));
				//memcpy(pofFilteredY, pofY, m_lHeight*m_lWidth*sizeof(float));
				//
				MedianFilter(pofX, pofFilteredX, 5, m_lHeight, m_lWidth);
				MedianFilter(pofY, pofFilteredY, 5, m_lHeight, m_lWidth);

				// find out the background motion
				// create histogram 
				int pDim[1] = {13};
				float ranges[1][14] = 
					{-100, -5.5, -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 100};

				// Pointer-to-a-two-dimensional-float-array is not the same as 
				// pointer-to-pointer-to-type-float.
				// Some tricks have to be used to do this.
				// I found the following code from C-faq
				//
				// int **array2 = (int **)malloc(nrows * sizeof(int *));
				// array2[0] = (int *)malloc(nrows * ncolumns * sizeof(int));
				// for(i = 1; i < nrows; i++)
				//     array2[i] = array2[0] + i * ncolumns;
				//

				float ** ppfRanges = (float **)malloc(1 * sizeof(float *));
				ppfRanges[0] = (float *)malloc(1 * 14 * sizeof(float));

				for(j=0; j<14; j++)
					ppfRanges[0][j] = ranges[0][j];

				CvHistogram *pXHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				CvHistogram *pYHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				// calc hist
				cvCalcHist(&iplFilteredX, pXHist);
				cvCalcHist(&iplFilteredY, pYHist);

				// free up memory
				free(ppfRanges[0]);
				free(ppfRanges);

				// find max in hist
				float minXVal[1], maxXVal[1];
				int minXIdx[1], maxXIdx[1];
				float minYVal[1], maxYVal[1];
				int minYIdx[1], maxYIdx[1];

				cvGetMinMaxHistValue(
					pXHist,		// X histogram
					minXVal,	// min val
					maxXVal,	// max val
					minXIdx,	// min index
					maxXIdx);	// max index
				cvGetMinMaxHistValue(
					pYHist,		// Y histogram
					minYVal,
					maxYVal,
					minYIdx,
					maxYIdx);

				// calc lower and upper bound
				float XLBound = ppfRanges[0][ maxXIdx[0] ] - (float)m_bPixelMotionThresh;
				float XUBound = ppfRanges[0][ maxXIdx[0] ] + (float)m_bPixelMotionThresh;
				float YLBound = ppfRanges[0][ maxYIdx[0] ] - (float)m_bPixelMotionThresh;
				float YUBound = ppfRanges[0][ maxYIdx[0] ] + (float)m_bPixelMotionThresh;

				// release cvHistogram
				cvReleaseHist(&pXHist);
				cvReleaseHist(&pYHist);

				// segment the motion image and find the centroid of motion
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;

				for( j = 20; j < m_lHeight-20; j++ ) {
					for ( i = 20; i < m_lWidth-20; i++ ) {
						index = j*m_lWidth+i;
						if (pofX[index] > XLBound &&
							pofX[index] < XUBound &&
							pofY[index] > YLBound &&
							pofY[index] < YUBound )
						{
								pbMIm[index] = 0;	// background motion
						}
						else
						{
							pbMIm[index] = 255;
							sum++;
							xsum +=i;
							ysum +=j;
						}
					}
				}

				// calculate pos_x & pos_y in pbMIm
				if (sum>200)
				{
					pos_x = xsum/sum;
					pos_y = ysum/sum;
				}
				else
				{
					pos_x = m_lWidth/2;	// center
					pos_y = m_lHeight/2;	// center
				}

				// send the result to vector signal
				// JJ's agent takes input as normalized between 0 and 1
				pdPos[0] = pos_x/(double)m_lWidth;
				pdPos[1] = pos_y/(double)m_lHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw the output image
				for( j=0; j<m_lHeight; j++ )
				{
					for( i=0; i<m_lWidth; i++ )
					{
						index = j*m_lWidth+i;
						pbOutput[index] = pbMIm[index];
					}
				}

				int posx = (int)(pdPos[0] * (double)m_lWidth);
				int posy = (int)(pdPos[1] * (double)m_lHeight);
				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					index2 = (posy+1)*m_lWidth+i;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Horizontal line is drawn\n");

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					index2 = j*m_lWidth+posx+1;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Vertical line is drawn\n");

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	// release image header
	cvReleaseImageHeader(&iplIm1);
	cvReleaseImageHeader(&iplIm2);
	cvReleaseImageHeader(&iplX);
	cvReleaseImageHeader(&iplY);
	cvReleaseImageHeader(&iplFilteredX);
	cvReleaseImageHeader(&iplFilteredY);

	// release memory
	delete pbPreviousFrame;
	delete pbCurrentFrame;
	delete pofX;
	delete pofY;
	delete pbMIm;
	delete pofFilteredX;
	delete pofFilteredY;

*/

	return S_OK;
	
}

STDMETHODIMP CMovementDetect::SegByOpticalFlowBM2()
{

/*

	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	// for holding image data
	LPBYTE pbPreviousFrame;
	LPBYTE pbCurrentFrame;
	float * pofX, * pofY;
	LPBYTE pbMIm;	// thresholded optical flow image

	IplImage *iplIm1, *iplIm2;
	IplImage *iplX, *iplY;

	// allocate memory for previous & current frame
	pbPreviousFrame = new BYTE[m_lHeight*m_lWidth];
	pbCurrentFrame = new BYTE[m_lHeight*m_lWidth];

	// blob match size is 5x5
	int blobSize = 5;
	int ofHeight = m_lHeight/blobSize;
	int ofWidth = m_lWidth/blobSize;

	// allocate memory for optical flow result
	pofX = new float[ofHeight*ofWidth];
	pofY = new float[ofHeight*ofWidth];
	pbMIm = new BYTE[ofHeight*ofWidth];

	// create ipl image header
	iplIm1 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplIm2 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplX = cvCreateImageHeader( cvSize(ofWidth, ofHeight), IPL_DEPTH_32F, 1);
	iplY = cvCreateImageHeader( cvSize(ofWidth, ofHeight), IPL_DEPTH_32F, 1);

	// variables declaration for median filtering
	float * pofFilteredX = new float[ofHeight*ofWidth];
	float * pofFilteredY = new float[ofHeight*ofWidth];
	IplImage * iplFilteredX = cvCreateImageHeader(
		cvSize(ofWidth, ofHeight), 
		IPL_DEPTH_32F, 
		1);
	IplImage * iplFilteredY = cvCreateImageHeader(
		cvSize(ofWidth, ofHeight), 
		IPL_DEPTH_32F, 
		1);

	cvSetImageData(iplFilteredX, pofFilteredX, ofWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFilteredY, pofFilteredY, ofWidth*sizeof(IPL_DEPTH_32F));

	double sum, xsum, ysum;
	double pos_x, pos_y;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index, index2;
			float r, g, b, y;
			if (m_FirstFrameReady == false)  // First frame is not ready
			{
				// fill the m_pbPreviousFrame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						m_pbPreviousFrame[index] = ( BYTE ) y;
					} 
				}

				// set the flag
				m_FirstFrameReady = true;

			} 
			else
			{
				// optical flow segmentaiton here
				//
				// first, convert RGB to gray-level, and fill the current frame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// fill the current frame
						pbCurrentFrame[index] = (BYTE)y;
					} 
				}

				// fill the previous frame
				memcpy(pbPreviousFrame, m_pbPreviousFrame, m_lHeight*m_lWidth);

				// set the image data
				cvSetImageData(iplIm1, pbPreviousFrame, m_lWidth);
				cvSetImageData(iplIm2, pbCurrentFrame, m_lWidth);
				cvSetImageData(iplX, pofX, ofWidth*sizeof(IPL_DEPTH_32F));
				cvSetImageData(iplY, pofY, ofWidth*sizeof(IPL_DEPTH_32F));

				// set ROI: region of interest
				//
				// CvRect struct is:
				//	typedef struct CvRect
				//	{
				//		int x;
				//		int y;
				//		int width;
				//		int height;
				//	} CvRect;
				CvRect roi;
				roi.x = 0;
				roi.y = 0;
				roi.width = m_lWidth;
				roi.height = m_lHeight;

				// set ROI
				cvSetImageROI(iplIm1, roi);
				cvSetImageROI(iplIm2, roi);

				// calculate optical flow
				CvSize blockSize, shiftSize, maxRange;
        
				blockSize.width = 5;
				blockSize.height = 5;
				shiftSize.width = 1;
				shiftSize.height = 1;
				maxRange.width = 8;
				maxRange.height = 8;

				// use_previous must be 0 for this OpenCV function!
	            cvCalcOpticalFlowBM(
					iplIm1, iplIm2, // input images
					blockSize, shiftSize, maxRange, // sizes
					0, // use_previous must be 0!
					iplX, iplY); // output result

				// copy the current frame to previous frame
				memcpy(m_pbPreviousFrame, pbCurrentFrame, m_lHeight*m_lWidth);

				// filter the iplX & iplY image using median filter
				// Since Intel IPL function iplMedianFilter does not support 
				// float data type, I write my own median filter according to
				// "the pocket handbook of image processing algorithms in c" by
				// Arthur Weeks

				MedianFilter(pofX, pofFilteredX, 5, ofHeight, ofWidth);
				MedianFilter(pofY, pofFilteredY, 5, ofHeight, ofWidth);

				float * pofVel = new float[ofHeight*ofWidth];
				IplImage * iplofVel = cvCreateImageHeader(
					cvSize(ofWidth, ofHeight), 
					IPL_DEPTH_32F, 
					1);
				cvSetImageData(iplofVel, pofVel, ofWidth*sizeof(IPL_DEPTH_32F));

				// Calculate the composite velocity
				for( j = 0; j < ofHeight; j++ ) {
					for ( i = 0; i < ofWidth; i++ ) {
						index = j*ofWidth+i;
						pofVel[index] = sqrt(pofFilteredX[index]*pofFilteredX[index]+pofFilteredY[index]*pofFilteredY[index]);
					}
				}
				
				// find out the background motion
				//
				// Method to find the background motion: Assume that the background area is bigger than 
				// the forground, then on the motion histogram, the highest peak is the background motion.
				//
				// calculate the motion histogram
				//
				int pDim[1] = {13};
				float ranges[1][14] = 
					{-100, -5.5, -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 100};

				// Pointer-to-a-two-dimensional-float-array is not the same as 
				// pointer-to-pointer-to-type-float.
				// Some tricks have to be used to do this.
				// I found the following code from C-faq
				//
				// int **array2 = (int **)malloc(nrows * sizeof(int *));
				// array2[0] = (int *)malloc(nrows * ncolumns * sizeof(int));
				// for(i = 1; i < nrows; i++)
				//     array2[i] = array2[0] + i * ncolumns;
				//

				float ** ppfRanges = (float **)malloc(1 * sizeof(float *));
				ppfRanges[0] = (float *)malloc(1 * 14 * sizeof(float));				

				for(j=0; j<14; j++)
					ppfRanges[0][j] = ranges[0][j];

				// create CvHistogram
				CvHistogram *pHist = cvCreateHist(
					1,		// histogram dimension
					pDim,		// bins in each dimension
					CV_HIST_ARRAY,	// histogram type
					ppfRanges,	// ranges for each bin
					0);		// non-uniform bin size

				// calc hist
				cvCalcHist(&iplofVel, pHist);
				//cvCalcHist(&iplFilteredY, pYHist);

				// free memory
				free(ppfRanges[0]);
				free(ppfRanges);

				// find max in hist
				float minVal[1], maxVal[1];
				int minIdx[1], maxIdx[1];

				cvGetMinMaxHistValue(
					pHist,		// histogram
					minVal,		// min val
					maxVal,		// max val
					minIdx,		// min index
					maxIdx);	// max index

				// calc lower and upper bound
				float LBound = ranges[0][ maxIdx[0] ] - (float)m_bPixelMotionThresh;
				float UBound = ranges[0][ maxIdx[0] ] + (float)m_bPixelMotionThresh;

				// release cvHistogram
				cvReleaseHist(&pHist);

				// free memory
				cvReleaseImageHeader(&iplofVel);
				delete pofVel;

				// segment the motion image and find the centroid of motion
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;

				for( j = 4; j < ofHeight-4; j++ ) {
					for ( i = 4; i < ofWidth-4; i++ ) {
						index = j*ofWidth+i;
						if (pofVel[index] > LBound &&  
							pofVel[index] < UBound ) 
						{
							pbMIm[index] = 0;	// background motion
						}
						else
						{
							pbMIm[index] = 255;
							sum++;
							xsum +=i;
							ysum +=j;
						}
					}
				}


				// calculate pos_x & pos_y in pbMIm
				if (sum>40 && sum<(ofHeight/2)*(ofWidth/2))
				{
					pos_x = xsum/sum;
					pos_y = ysum/sum;
				}
				else
				{
					pos_x = ofWidth/2;
					pos_y = ofHeight/2;
				}

				// send the result to vector signal
				// JJ's head agent takes input as normalized between 0 and 1
				pdPos[0] = pos_x/(double)ofWidth;
				pdPos[1] = pos_y/(double)ofHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw the output image
				for( j=0; j<m_lHeight; j++ )
				{
					for( i=0; i<m_lWidth; i++ )
					{
						index = j*m_lWidth+i;
						index2 = (j/blobSize)*ofWidth+(i/blobSize);
						pbOutput[index] = pbMIm[index2];
					}
				}

				int posx = (int)(pdPos[0] * (double)m_lWidth);
				int posy = (int)(pdPos[1] * (double)m_lHeight);
				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					index2 = (posy+1)*m_lWidth+i;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Horizontal line is drawn\n");

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					index2 = j*m_lWidth+posx+1;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Vertical line is drawn\n");

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	// release image header
	cvReleaseImageHeader(&iplIm1);
	cvReleaseImageHeader(&iplIm2);
	cvReleaseImageHeader(&iplX);
	cvReleaseImageHeader(&iplY);
	cvReleaseImageHeader(&iplFilteredX);
	cvReleaseImageHeader(&iplFilteredY);

	// release memory
	delete pbPreviousFrame;
	delete pbCurrentFrame;
	delete pofX;
	delete pofY;
	delete pbMIm;
	delete pofFilteredX;
	delete pofFilteredY;

*/
  
	return S_OK;

}

STDMETHODIMP CMovementDetect::SegByPhaseCorrelation()
{
/*
	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	// for holding image data
	LPBYTE pbPrevious;
	LPBYTE pbCurrent;
	LPBYTE pbResult;
	float * pfFFTPrevious;
	float * pfFFTCurrent;
	float * pfFFTResult;

	IplImage * iplPrevious, * iplCurrent, * iplResult;
	IplImage * iplFFTPrevious, * iplFFTCurrent, * iplFFTResult;

	int row, col;
	BYTE peak;

	// allocate memory for previous and current frames
	pbPrevious = new BYTE[m_lHeight*m_lWidth];
	pbCurrent = new BYTE[m_lHeight*m_lWidth];
	pbResult = new BYTE[m_lHeight*m_lWidth];
	pfFFTPrevious = new float[m_lHeight*m_lWidth];
	pfFFTCurrent = new float[m_lHeight*m_lWidth];
	pfFFTResult = new float[m_lHeight*m_lWidth];

	// create ipl image header
	iplPrevious = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplCurrent = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplResult = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplFFTPrevious = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);
	iplFFTCurrent = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);
	iplFFTResult = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_32F, 1);

	// set image data
	cvSetImageData(iplPrevious, pbPrevious, m_lWidth);
	cvSetImageData(iplCurrent, pbCurrent, m_lWidth);
	cvSetImageData(iplResult, pbResult, m_lWidth);
	cvSetImageData(iplFFTPrevious, pfFFTPrevious, m_lWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFFTCurrent, pfFFTCurrent, m_lWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFFTResult, pfFFTResult, m_lWidth*sizeof(IPL_DEPTH_32F));

	double sum, xsum, ysum;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)  
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index;
			float r, g, b, y;
			if (m_FCFirstFrameReady == false)  // First frame is not ready
			{
				// fill the pbPrevious
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						pbPrevious[index] = ( BYTE ) y;
					} 
				}

				// FFT
				iplRealFft2D(iplPrevious, iplFFTPrevious, IPL_FFT_Forw);

				// copy to m_pbPreviousFrame from pbPrevious, with a total size of height * width
				memcpy(m_pbPreviousFrame, pbPrevious, m_lHeight*m_lWidth);
				// copy to m_pfFFTPrevious
				memcpy(m_pfFFTPrevious, pfFFTPrevious, m_lHeight*m_lWidth*sizeof(float));

				// set the flag
				m_FCFirstFrameReady = true;

			} 
			else
			{
				// first, convert RGB to gray-level, and fill the current frame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// fill the current frame
						pbCurrent[index] = (BYTE)y;
					} 
				}

				// FFT
				iplRealFft2D(iplCurrent, iplFFTCurrent, IPL_FFT_Forw);

				// get previous frame
				memcpy(pbPrevious, m_pbPreviousFrame, m_lHeight*m_lWidth);
				// get previous frame FFT
				memcpy(pfFFTPrevious, m_pfFFTPrevious, m_lHeight*m_lWidth*sizeof(float));

				// get the conjugate of FFT of previous frame
				Conjugate(pfFFTPrevious, m_lHeight, m_lWidth);
				// multiply
				iplMpyRCPack2D(iplFFTCurrent, iplFFTPrevious, iplFFTResult);
				// normalize
				Normalize(pfFFTResult, m_lHeight, m_lWidth);
				// inverse FFT
				iplCcsFft2D(iplFFTResult, iplResult, IPL_FFT_Inv);
				// release memory for FFT
				iplRealFft2D(NULL, NULL, IPL_FFT_Free);
				// find peak
				FindPeak(pbResult, m_lHeight, m_lWidth, peak, row, col);

				// move row & col accordingly
				if ( row > m_lHeight/2) row -= m_lHeight;
				if ( col > m_lWidth/2) col -= m_lWidth;

				// for debugging
				ATLTRACE("movement is peak, row, col: %d %d %d\n", int(peak), row, col);

				// Now row & col indicate how far away the current frame is 
				// from the previous frame
				// Difference these two frames
				for ( j = 20; j < m_lHeight-20; j++ )
				{
					for ( i = 20; i < m_lWidth-20; i++ )
					{
						long ix1, ix2;
						ix2 = j*m_lWidth+i;	// index for current frame
						ix1 = (j+row)*m_lWidth+(i+col); // index for corresponding previous frame
						int delta;
						delta = (int)pbCurrent[ix1]-(int)pbPrevious[ix2];
						delta = abs(delta);

						if (delta >= m_bDifferenceThresh)
							pbOutput[ix1] = 255;
						else
							pbOutput[ix1] = 0;
					}
				}

				// save the current frame for the next frame
				memcpy(m_pbPreviousFrame, pbCurrent, m_lHeight*m_lWidth);
				memcpy(m_pfFFTPrevious, pfFFTCurrent, m_lHeight*m_lWidth*sizeof(float));

				// calculate pos_x & pos_y
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;
				for ( j = 0; j < m_lHeight; j++ ) 

				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						if (pbOutput[index] == 255)
						{
							sum++;
							xsum += i;
							ysum += j;
						}
					}
				}

				int posx, posy;

				if (sum>100)
				{
					posx = xsum/sum;
					posy = ysum/sum;
				}
				else
				{
					posx = m_lWidth/2;		// center
					posy = m_lHeight/2;	// center
				}

				// send the result to vector signal
				// JJ's agent takes input as normalized between 0 and 1
				pdPos[0] = (double)posx/(double)m_lWidth;
				pdPos[1] = (double)posy/(double)m_lHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					pbOutput[index] = 255;
				}

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					pbOutput[index] = 255;
				}

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	delete pbPrevious;
	delete pbCurrent;
	delete pbResult;
	delete pfFFTPrevious;
	delete pfFFTCurrent;
	delete pfFFTResult;

	cvReleaseImageHeader(&iplPrevious);
	cvReleaseImageHeader(&iplCurrent);
	cvReleaseImageHeader(&iplResult);
	cvReleaseImageHeader(&iplFFTPrevious);
	cvReleaseImageHeader(&iplFFTCurrent);
	cvReleaseImageHeader(&iplResult);
*/
	return S_OK;

}



// This function gets the conjugate of IPL Real-Complex Packed (RCPack2D)
// array, in-place, i.e., it returns the result using the array passed in.
// See IPL manual 7-3 for more detail on RCPack2D format
void CMovementDetect::Conjugate(float * RCPack2D, const int height, const int width)
{

/*
	int i, j;
	long ix;

	// first column
	for (j = 2; j < height-1; j += 2)
	{
		ix = j*width;
		RCPack2D[ix] = -RCPack2D[ix];
	}

	// last column
	for (j = 2; j < height-1; j += 2)
	{
		ix = j*width + width - 1;
		RCPack2D[ix] = -RCPack2D[ix];
	}

	// middle part
	for (j = 0; j < height; j++)
	{
		for (i = 2; i < width; i += 2)
		{
			ix = j*width+i;
			RCPack2D[ix] = -RCPack2D[ix];
		}
	}

*/
}



void CMovementDetect::Normalize(float *RCPack2D, const int height, const int width)
{
/*
	int i, j;
	long ix1, ix2;
	float re, im, mag;

	// first column
	// first element
	RCPack2D[0] = 1.0;
	// middle
	for ( j = 1; j < height-2; j += 2)
	{
		ix1 = j*width;
		ix2 = (j+1)*width;
		re = RCPack2D[ix1];
		im = RCPack2D[ix2];
		mag = sqrt(re*re+im*im);
		RCPack2D[ix1] = re/mag;
		RCPack2D[ix2] = im/mag;
	}
	// last element
	RCPack2D[ (height-1)*width ] = 1.0;

	// last column
	// frist element
	RCPack2D[ width-1 ] = 1.0;
	// middle
	for ( j = 1; j < height-2; j+=2)
	{
		ix1 = (j+1)*width-1;
		ix2 = (j+2)*width-1;
		re = RCPack2D[ix1];
		im = RCPack2D[ix2];
		mag = sqrt(re*re+im*im);
		RCPack2D[ix1] = re/mag;
		RCPack2D[ix2] = im/mag;
	}
	// last element
	RCPack2D[ height*width-1 ] = 1.0;

	// middle
	for ( j = 0; j < height; j++ )
	{
		for ( i = 1; i < width-1; i+=2 )
		{
			ix1 = j*width+i;
			ix2 = ix1+1;
			re = RCPack2D[ix1];
			im = RCPack2D[ix2];
			mag = sqrt(re*re+im*im);
			RCPack2D[ix1] = re/mag;
			RCPack2D[ix2] = im/mag;
		}
	}
*/
}

void CMovementDetect::FindPeak(BYTE *pArray, const int height, const int width, 
							 BYTE &peak, int &row, int &col)
{
/*
	BYTE tmp;
	int i, j, r, c;
	long ix;

	tmp = 0;
	r = 0;
	c = 0;
	for ( j = 0; j < height; j++ )
	{
		for ( i = 0; i < width; i++ )
		{
			ix = j*width+i;
			if (tmp < pArray[ix])
			{
				tmp = pArray[ix];
				r = j;
				c = i;
			}
		}
	}

	peak = tmp;
	row = r;  
	col = c;
*/
}  



STDMETHODIMP CMovementDetect::SegByOpticalFlowBM3()
{ 

/*

	// TODO: Add your implementation code here
	// variable daclaration
	IImageRep*	pInput = NULL; 
	IImageRep*	pOutput = NULL; 
	long	lData, lData2; 

	LPBYTE	pbInput = NULL; 
	LPBYTE	pbOutput= NULL; 

	// for motion position vector signal
	IVectorSignal* pIVSpos = NULL;

	// for holding image data
	LPBYTE pbPreviousFrame;
	LPBYTE pbCurrentFrame;
	float * pofX, * pofY;
	LPBYTE pbMIm;	// thresholded optical flow image

	IplImage *iplIm1, *iplIm2;
	IplImage *iplX, *iplY;

	// allocate memory for previous & current frame
	pbPreviousFrame = new BYTE[m_lHeight*m_lWidth];
	pbCurrentFrame = new BYTE[m_lHeight*m_lWidth];

	// blob match size is 5x5
	int blobSize = 5;
	int ofHeight = m_lHeight/blobSize;
	int ofWidth = m_lWidth/blobSize;

	// allocate memory for optical flow result
	pofX = new float[ofHeight*ofWidth];
	pofY = new float[ofHeight*ofWidth];
	pbMIm = new BYTE[ofHeight*ofWidth];

	// create ipl image header
	iplIm1 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplIm2 = cvCreateImageHeader( cvSize(m_lWidth, m_lHeight), IPL_DEPTH_8U, 1);
	iplX = cvCreateImageHeader( cvSize(ofWidth, ofHeight), IPL_DEPTH_32F, 1);
	iplY = cvCreateImageHeader( cvSize(ofWidth, ofHeight), IPL_DEPTH_32F, 1);

	// variables declaration for median filtering
	float * pofFilteredX = new float[ofHeight*ofWidth];
	float * pofFilteredY = new float[ofHeight*ofWidth];
	IplImage * iplFilteredX = cvCreateImageHeader(
		cvSize(ofWidth, ofHeight), 
		IPL_DEPTH_32F, 
		1);
	IplImage * iplFilteredY = cvCreateImageHeader(		
		cvSize(ofWidth, ofHeight), 
		IPL_DEPTH_32F, 
		1);

	cvSetImageData(iplFilteredX, pofFilteredX, ofWidth*sizeof(IPL_DEPTH_32F));
	cvSetImageData(iplFilteredY, pofFilteredY, ofWidth*sizeof(IPL_DEPTH_32F));

	double sum, xsum, ysum;
	double pos_x, pos_y;
	double pdPos[2];

	// Input and output link present? 
	if( m_pIUnkImgInput != NULL 
		&& m_pIUnkImgOutput != NULL 
		&& m_pIUnkVSpos != NULL)
	{ 
		// retrieve input 
		m_pIUnkImgInput->QueryInterface( IID_IImageRep, (void**)&pInput ); 
		// retrieve output 
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput ); 
		// retrieve vector signal
		m_pIUnkVSpos->QueryInterface( IID_IVectorSignal, (void**)&pIVSpos);

		// successful query interface? 
		if( pInput != NULL && pOutput != NULL && pIVSpos != NULL) 
		{ 
			// Because we know from FinalComponentInitialization that image is
			// in color and its dimensions, I don't retrieve them any more.
			
			// get address of image data 
			pInput->Data( 0, &lData );

			// cast returned image data address to BYTE ptr 
			pbInput = ( LPBYTE ) lData; 

			// get address of image data
			pOutput->Data( 0, &lData2 ); 

			// cast image data address to BYTE type
			pbOutput = ( LPBYTE ) lData2;

			int i, j;
			long index, index2;
			float r, g, b, y;
			if (m_FirstFrameReady == false)  // First frame is not ready
			{
				// fill the m_pbPreviousFrame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];
						y = 0.3*r + 0.6*g + 0.1*b;
						m_pbPreviousFrame[index] = ( BYTE ) y;
					} 
				}

				// set the flag
				m_FirstFrameReady = true;

			} 
			else
			{
				// optical flow segmentaiton here
				//
				// first, convert RGB to gray-level, and fill the current frame
				for( j = 0; j < m_lHeight; j++ ) 
				{
					for ( i = 0; i < m_lWidth; i++)
					{
						index = j*m_lWidth+i;
						b = (float)pbInput[3*index];
						g = (float)pbInput[3*index+1];
						r = (float)pbInput[3*index+2];

						// get the luminance
						y = 0.3*r + 0.6*g + 0.1*b;

						// fill the current frame
						pbCurrentFrame[index] = (BYTE)y;
					} 
				}

				// fill the previous frame
				memcpy(pbPreviousFrame, m_pbPreviousFrame, m_lHeight*m_lWidth);

				// set the image data
				cvSetImageData(iplIm1, pbPreviousFrame, m_lWidth);
				cvSetImageData(iplIm2, pbCurrentFrame, m_lWidth);
				cvSetImageData(iplX, pofX, ofWidth*sizeof(IPL_DEPTH_32F));
				cvSetImageData(iplY, pofY, ofWidth*sizeof(IPL_DEPTH_32F));

				// set ROI: region of interest
				//
				// CvRect struct is:
				//	typedef struct CvRect
				//	{
				//		int x;
				//		int y;
				//		int width;
				//		int height;
				//	} CvRect;
				CvRect roi;
				roi.x = 0;
				roi.y = 0;
				roi.width = m_lWidth;
				roi.height = m_lHeight;

				// set ROI
				cvSetImageROI(iplIm1, roi);
				cvSetImageROI(iplIm2, roi);

				// calculate optical flow
				CvSize blockSize, shiftSize, maxRange;
        
				blockSize.width = 5;
				blockSize.height = 5;
				shiftSize.width = 1;
				shiftSize.height = 1;
				maxRange.width = 8;
				maxRange.height = 8;

				// use_previous must be 0 for this OpenCV function!
	            cvCalcOpticalFlowBM(
					iplIm1, iplIm2, // input images
					blockSize, shiftSize, maxRange, // sizes
					0, // use_previous must be 0!
					iplX, iplY); // output result

				// copy the current frame to previous frame
				memcpy(m_pbPreviousFrame, pbCurrentFrame, m_lHeight*m_lWidth);

				// filter the iplX & iplY image using median filter
				// Since Intel IPL function iplMedianFilter does not support 
				// float data type, I write my own median filter according to
				// "the pocket handbook of image processing algorithms in c" by
				// Arthur Weeks

				MedianFilter(pofX, pofFilteredX, 5, ofHeight, ofWidth);
				MedianFilter(pofY, pofFilteredY, 5, ofHeight, ofWidth);

				float * pofVel = new float[ofHeight*ofWidth];
				IplImage * iplofVel = cvCreateImageHeader(
					cvSize(ofWidth, ofHeight), 
					IPL_DEPTH_32F, 
					1);
				cvSetImageData(iplofVel, pofVel, ofWidth*sizeof(IPL_DEPTH_32F));

				// Calculate the composite velocity
				for( j = 0; j < ofHeight; j++ ) {
					for ( i = 0; i < ofWidth; i++ ) {
						index = j*ofWidth+i;
						pofVel[index] = sqrt(pofFilteredX[index]*pofFilteredX[index]+pofFilteredY[index]*pofFilteredY[index]);
					}
				}
				
				// find out the background motion
				//
				// This time I assume that the camera doesn't move very fast,
				// so the background motion is less than 3 pixels.
				// segment the motion image and find the centroid of motion
				sum = 0.0;
				xsum = 0.0;
				ysum = 0.0;

				for( j = 4; j < ofHeight-4; j++ ) {
					for ( i = 4; i < ofWidth-4; i++ ) {
						index = j*ofWidth+i;
						if (pofVel[index] > -3 &&
							pofVel[index] < 3 )
						{
							pbMIm[index] = 0;	// background motion
						}
						else
						{
							pbMIm[index] = 255;
							sum++;
							xsum +=i;
							ysum +=j;
						}
					}
				}

				// calculate pos_x & pos_y in pbMIm
				if (sum>30 && sum<(ofHeight/2)*(ofWidth/2))
				{
					pos_x = xsum/sum;
					pos_y = ysum/sum;
					DispatchAgentEvent(500, 1);
				}
				else
				{
					pos_x = ofWidth/2;
					pos_y = ofHeight/2;
					DispatchAgentEvent(500, 0);
				}

				// send the result to vector signal
				// JJ's head agent takes input as normalized between 0 and 1
				pdPos[0] = pos_x/(double)ofWidth;
				pdPos[1] = pos_y/(double)ofHeight;
				pIVSpos->SetCurrentVector(2, pdPos);

				// draw the output image
				for( j=0; j<m_lHeight; j++ )
				{
					for( i=0; i<m_lWidth; i++ )
					{
						index = j*m_lWidth+i;
						index2 = (j/blobSize)*ofWidth+(i/blobSize);
						pbOutput[index] = pbMIm[index2];
					}
				}

				int posx = (int)(pdPos[0] * (double)m_lWidth);
				int posy = (int)(pdPos[1] * (double)m_lHeight);
				// draw a cross on the output image
				// horizontal line
				for ( i = 0; i < m_lWidth; i++)
				{
					index = posy*m_lWidth+i;
					index2 = (posy+1)*m_lWidth+i;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Horizontal line is drawn\n");

				// vertical line
				for ( j = 0; j < m_lHeight; j++)
				{
					index = j*m_lWidth+posx;
					index2 = j*m_lWidth+posx+1;
					pbOutput[index] = 255;
					pbOutput[index2] = 255;
				}

				ATLTRACE("Vertical line is drawn\n");

			} // end if(...) else

			// release I/F 
			pInput->Release(); 

			// release I/F 
			pOutput->Release(); 
			
			// release I/F
			pIVSpos->Release();

		}	// end if( pInput != NULL && pOutput != NULL ) 
	
	}	// end if( m_pIUnkImgInput != NULL && m_pIUnkImgOutput != NULL ) 
	else
	{
		return E_POINTER; 
	}

	// release image header
	cvReleaseImageHeader(&iplIm1);
	cvReleaseImageHeader(&iplIm2);
	cvReleaseImageHeader(&iplX);
	cvReleaseImageHeader(&iplY);
	cvReleaseImageHeader(&iplFilteredX);
	cvReleaseImageHeader(&iplFilteredY);

	// release memory
	delete pbPreviousFrame;
	delete pbCurrentFrame;
	delete pofX;
	delete pofY;
	delete pbMIm;
	delete pofFilteredX;
	delete pofFilteredY;

*/
	return S_OK;

}

  

