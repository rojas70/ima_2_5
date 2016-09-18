/////////////////////////////////////////////////////////////
// IntelIPL.cpp : Implementation of CIntelIPL
// Can perform a variety of image processing manipulations
// on an incoming image and output them to another.
/////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "IMA2_ImageProcessingLib.h"
#include "IntelIPL.h"
#include "O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.h"

/////////////////////////////////////////////////////////////////////////////
// CIntelIPL

CIntelIPL::CIntelIPL()
{
	// Masks
	int	maskH[9]		= { -1,-1,-1,2,2,2,-1,-1,-1 };
	int	maskV[9]		= { -1,2,-1,-1,2,-1,-1,2,-1 };
	int	maskDL[9]		= { -1,-1,2,-1,2,-1,2,-1,-1 };
	int	maskDR[9]		= { 2,-1,-1,-1,2,-1,-1,-1,2 };

	m_lInputIndex		= 0;			// IMA 2.5

	m_lCols				= 3;
	m_lRows				= 3;
	m_lAnchorX			= 1;
	m_lAnchorY			= 1;
	m_lThreshold		= 128;

	m_pIUnkImgOutput	= NULL;
	m_pImgOutput		= NULL;
	m_pImgOutputGray	= NULL;
	m_pImgOutputColor	= NULL;

	// Init
	for (int i=0; i<N; i++ ) {
		m_pIUnkImgInput[i]	= NULL;
		m_pImgInput[i]		= NULL;
		//SetupComponentLink( &IID_IImageRep , &m_pIUnkImgInput[i] );
	}

	m_lConvKernel		= 0;						// Default to horizontal edge kernel

	for( i=0; i < MAX_KERNELS; i++ ) 
		m_pConvKernel[i] = NULL;

	// Setup convolution kernels for edge detections
	m_pConvKernel[0] = iplCreateConvKernel(	3,3,	// 3x3 kernel
										1,1,		// anchor=center
										maskH,		// horizontal edges
										0 );		// no scaling
	m_pConvKernel[1] = iplCreateConvKernel(	3,3,	// 3x3 kernel
										1,1,		// anchor=center
										maskV,		// vertical edges
										0 );		// no scaling
	m_pConvKernel[2] = iplCreateConvKernel(	3,3,	// 3x3 kernel
										1,1,		// anchor=center
										maskDL,		// left diagonal edges
										0 );		// no scaling
	m_pConvKernel[3] = iplCreateConvKernel(	3,3,	// 3x3 kernel
										1,1,		// anchor=center
										maskDR,		// right diagonal edges
										0 );		// no scaling

	m_lFlipAxis	= 1;								// Vertical axis
	m_bInitialized = FALSE;

	// DEBUG
	ATLTRACE("CIntelIPL::constructor completed\n");

}

CIntelIPL::~CIntelIPL()
{
	// Cleanup

	// Delete our convolution kernels
	for( int i=0 ; i < MAX_KERNELS; i++ )
		if( m_pConvKernel[i] != NULL )
			iplDeleteConvKernel( m_pConvKernel[i] );
		
	// DEBUG
	ATLTRACE("CIntelIPL::destructor completed\n");

}


/*************************************************
* Interface Properties
*************************************************/
STDMETHODIMP CIntelIPL::get_InputIndex(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lInputIndex;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_InputIndex(long newVal)
{
	// TODO: Add your implementation code here
	m_lInputIndex = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_NumberColumns(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lCols;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_NumberColumns(long newVal)
{
	// TODO: Add your implementation code here
	m_lCols = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_NumberRows(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lRows;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_NumberRows(long newVal)
{
	// TODO: Add your implementation code here
	m_lRows = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_AnchorX(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lAnchorX;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_AnchorX(long newVal)
{
	// TODO: Add your implementation code here
	m_lAnchorX = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_AnchorY(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lAnchorY;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_AnchorY(long newVal)
{
	// TODO: Add your implementation code here
	m_lAnchorY = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_ThresholdValue(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lThreshold;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_ThresholdValue(long newVal)
{
	// TODO: Add your implementation code here
	m_lThreshold = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_ConvKernel(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lConvKernel;
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_ConvKernel(long newVal)
{
	// TODO: Add your implementation code here
	m_lConvKernel = newVal;
	return S_OK;
}

STDMETHODIMP CIntelIPL::get_FlipAxis(long * pVal)
{
	// TODO: Add your implementation code here
	*pVal = static_cast<long>(m_lFlipAxis);
	return S_OK;
}

STDMETHODIMP CIntelIPL::put_FlipAxis(long newVal)
{
	// TODO: Add your implementation code here
	m_lFlipAxis = static_cast<int>(newVal);
	return S_OK;
}


/*************************************************
* Main Interface Callable Functions
*************************************************/
STDMETHODIMP CIntelIPL::aaThreshold(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 	::MessageBox(NULL, "Could not bind to output image", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData		= (char*) pDataOut;

			iplThreshold(   m_pImgInput[0],	// Src
						m_pImgOutput,
						m_lThreshold// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to output image", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaMaxFilter(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn, pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 	::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData		= (char*) pDataOut;

			iplMaxFilter(m_pImgInput[0],	// Src 
					m_pImgOutput,    // Dst
					m_lRows,
					m_lCols,
					m_lAnchorX,
					m_lAnchorY
						   //ulFlags// flip A-B or B-A 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaMinFilter(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn, pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 	::MessageBox(NULL, "Could not bind to output image", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData		= (char*) pDataOut;

			iplMinFilter(m_pImgInput[0],	// Src 
					m_pImgOutput,    // Dst
					m_lRows,
					m_lCols,
					m_lAnchorX,
					m_lAnchorY
						   //ulFlags// flip A-B or B-A 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind  to output image", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaMedianFilter(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn, pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to input image", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return ::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 	::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData		= (char*) pDataOut;

			iplMedianFilter(m_pImgInput[0],	// Src 
					m_pImgOutput,    // Dst
					m_lRows,
					m_lCols,
					m_lAnchorX,
					m_lAnchorY
						   //ulFlags// flip A-B or B-A 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind to output image", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaBlur(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn, pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return ::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return ::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 	::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData		= (char*) pDataOut;

			iplMedianFilter(m_pImgInput[0],	// Src 
					m_pImgOutput,    // Dst
					m_lRows,
					m_lCols,
					m_lAnchorX,
					m_lAnchorY
						   //ulFlags// flip A-B or B-A 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind to output image", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaSubtract(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataInSrcA, pDataInSrcB ,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataInSrcA );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);
	
	if( m_pIUnkImgInput[1] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[1] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[1]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataInSrcB );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgInput[1] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataInSrcA;
			m_pImgInput[1]->imageData	= (char*) pDataInSrcB;
			m_pImgOutput->imageData		= (char*) pDataOut;

			iplSubtract(   m_pImgInput[0],	// Src A
						   m_pImgInput[1],  // Src B	
						   m_pImgOutput    // Dst
						   //ulFlags// flip A-B or B-A 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaClose(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplClose(   m_pImgInput[0],	// Src
						m_pImgOutput,
						ulFlags// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaOpen(ULONG ulFlags)
{
	// TODO: Add your implementation code here
	
	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);
	
	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplOpen(   m_pImgInput[0],	// Src
						m_pImgOutput,
						ulFlags// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaDilate(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return 	::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplDilate(   m_pImgInput[0],	// Src
						m_pImgOutput,
						ulFlags// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaErode(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[0]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[0] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[0]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplErode(   m_pImgInput[0],	// Src
						m_pImgOutput,
						ulFlags// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaColortoGray(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[ulFlags]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[ulFlags] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[0] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[ulFlags]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( 0, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			long lDepth = 1;
			pOutput->put_Depth( lDepth );
			pOutput->Data( 0, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[0] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[0]->imageData	= (char*) pDataIn;
			m_pImgOutputGray->imageData			= (char*) pDataOut;

			iplColorToGray(		m_pImgInput[0],	// Src
						m_pImgOutputGray			// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaConvolve2D(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[ulFlags]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	// DEBUG
	ATLTRACE("CIntelIPL::Convolve2D entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;
	IplConvKernel*	pKernel;

	// Do Convolve2Dhing if Convolve2D initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Convolve2D says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[ulFlags] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[ulFlags] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[ulFlags]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( ulFlags, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( ulFlags, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[ulFlags] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[ulFlags]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			// Setup kernel
			pKernel = m_pConvKernel[m_lConvKernel];

			iplConvolve2D(	m_pImgInput[ulFlags],// input image	
							m_pImgOutput,	// output image
							&pKernel,	// ptr to address of our one kernel
							1,			// #kernels
							IPL_SUM	// ignored for 1 kernel
							);		// no tiling info
			
			// DEBUG
			ATLTRACE("CIntelIPL::Convolve2D completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaDecimate(ULONG ulFlags)
{

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[ulFlags]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	// DEBUG
	ATLTRACE("CIntelIPL::Decimate entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;

	long		pDataIn,pDataOut;
	long		lWidthIn,lHeightIn;
	long		lWidthOut,lHeightOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Decimate says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[ulFlags] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[ulFlags] != NULL\n");

		// Get pointer to interface
		// Retrieve input
		m_pIUnkImgInput[ulFlags]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( ulFlags, &pDataIn );	// get address of image data
			
			// image dimensions
			pInput->get_Width( &lWidthIn );
			pInput->get_Height( &lHeightIn );
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( ulFlags, &pDataOut );	// get address of image data
			
			// image dimensions
			pOutput->get_Width( &lWidthOut );
			pOutput->get_Height( &lHeightOut );
					
			// Check for image headers set up?
			if( m_pImgInput[ulFlags] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[ulFlags]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplDecimate(	m_pImgInput[ulFlags],	// Src
							m_pImgOutput,			// Dest 	
							lWidthOut,lWidthIn,		// Dest W, Src W
							lHeightOut,lHeightIn,	// Dest H, Src H
							IPL_INTER_NN			// Linear interpolation
							);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Decimate completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaCopy(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[ulFlags]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);


	ATLTRACE("CIntelIPL::Copy entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// Input link present?
	if( m_pIUnkImgInput[ulFlags] != NULL )
	{
		// retrieve input
		m_pIUnkImgInput[ulFlags]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( ulFlags, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( ulFlags, &pDataOut );	// get address of image data
								
			// Check for image headers set up?
			if( m_pImgInput[ulFlags] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[ulFlags]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplCopy(	m_pImgInput[ulFlags],	// Src
						m_pImgOutput			// Dest
						);					// No map

			// DEBUG
			ATLTRACE("CIntelIPL::Copy completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update 
			pOutput->Update(0);
			
			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	return S_OK;
}

STDMETHODIMP CIntelIPL::aaNot(ULONG ulFlags)
{
	// TODO: Add your implementation code here
	
	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[ulFlags]);
	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	// DEBUG
	ATLTRACE("CIntelIPL::Not entered\n");

	IImageRep*	pInput = NULL;
	IImageRep*	pOutput= NULL;
	long		pDataIn,pDataOut;

	// Do nothing if not initialized
	if( !m_bInitialized ) aaInitialize(0);

	// DEBUG
	ATLTRACE("CIntelIPL::Not says IPL init\n");

	// Input link present?
	if( m_pIUnkImgInput[ulFlags] != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgInput[ulFlags] != NULL\n");

		// retrieve input
		m_pIUnkImgInput[ulFlags]->QueryInterface( IID_IImageRep, (void**)&pInput );
		
		// Pointer check
		assert( pInput );	

		// successful query interface?
		if( pInput != NULL )
		{
			pInput->Data( ulFlags, &pDataIn );	// get address of image data
			
			// release I/F
			pInput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

	// Output link present?
	if( m_pIUnkImgOutput != NULL )
	{
		// DEBUG
		ATLTRACE("m_pIUnkImgOutput != NULL\n");

		// retrieve input
		m_pIUnkImgOutput->QueryInterface( IID_IImageRep, (void**)&pOutput );
		
		// Pointer check
		assert( pOutput );	

		if( pOutput != NULL )
		{
			pOutput->Data( ulFlags, &pDataOut );	// get address of image data
					
			// Check for image headers set up?
			if( m_pImgInput[ulFlags] == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;
			if( m_pImgOutput == NULL ) return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;

			// Set IPL image data ptrs to our image data
			m_pImgInput[ulFlags]->imageData	= (char*) pDataIn;
			m_pImgOutput->imageData			= (char*) pDataOut;

			iplNot(		m_pImgInput[ulFlags],	// Src
						m_pImgOutput			// Dest 	
						);					// No tiling info

			// DEBUG
			ATLTRACE("CIntelIPL::Not completed\n");

			// Set completion time
			pOutput->put_Time( ulFlags, 0.0 /*GetAgentTime()*/ );

			// Update
			pOutput->Update(0);

			// release I/F
			pOutput->Release();
		}
	}
	else return 		::MessageBox(NULL, "Could not bind", "Error", MB_ICONERROR);;


	return S_OK;
}

STDMETHODIMP CIntelIPL::aaInitialize(ULONG ulFlags)
{
	// TODO: Add your implementation code here

	IImageRep*	pImage = NULL;
	long		lWidth,lHeight,lDepth;

	// Get pointer to output image object
	m_Bindings->get_Pointers(SysAllocString(L"OututImage"),&m_pIUnkImgOutput);

	// Input images (2 images for some operations)
	for(int i = 0; i < N; i++ )
	{

	// Get pointer to input image object
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgInput[i]);

		// get input image from image rep
		if( m_pIUnkImgInput[i] != NULL )
		{
			m_pIUnkImgInput[i]->QueryInterface(IID_IImageRep,(void**)&pImage );
		
			// Pointer check
			assert( pImage );	

			if( pImage != NULL )
			{
				pImage->get_Width( &lWidth );
				pImage->get_Height( &lHeight );
				pImage->get_Depth( &lDepth );

				pImage->Release();

				// If header exists, deallocate before creating a new one
				if( m_pImgInput[i] != NULL ) iplDeallocate( m_pImgInput[i], IPL_IMAGE_HEADER );

				switch(lDepth)
				{
				// create img header for 24-bit color RGB
				case 3: m_pImgInput[i] = iplCreateImageHeader(3,	// 3 channels
									0,								// alpha = 0
									IPL_DEPTH_8U,	
									"RGB",
									"RGB",
									IPL_DATA_ORDER_PIXEL,			// ?
									IPL_ORIGIN_TL,					// origin @ bottom-left
									IPL_ALIGN_DWORD,				// mmx optimized
									lWidth,							// img width		
									lHeight,						// img height
									NULL,NULL,NULL,NULL);
					break;
				// create image head for gray-scale
				case 1: m_pImgInput[i] = iplCreateImageHeader(1,	// 1 channels
									0,								// alpha = 0
									IPL_DEPTH_8U,	
									"GRAY",
									"GRAY",
									IPL_DATA_ORDER_PIXEL,			// ?
									IPL_ORIGIN_TL,					// origin @ bottom-left
									IPL_ALIGN_DWORD,				// mmx optimized
									lWidth,							// img width
									lHeight,						// img height
									NULL,NULL,NULL,NULL);
					break;
				}
				// create ROI structure

				// Setup input image size
				m_pImgInput[i]->imageSize = lHeight*lWidth*lDepth;
			}	
		}
	}

	// Output image (depend on input image except ColorToGray and GrayToColor)
	if( m_pIUnkImgOutput != NULL )
	{
		m_pIUnkImgOutput->QueryInterface(IID_IImageRep,(void**)&pImage );

		// Pointer check
		assert( pImage );	

		if( pImage != NULL )
		{
			// same dimension as input image
			pImage->get_Width( &lWidth );
			pImage->get_Height( &lHeight );
			pImage->get_Depth( &lDepth );

			pImage->Release();

			// If header exists, deallocate before creating a new one
			if( m_pImgOutput != NULL ) iplDeallocate( m_pImgOutput, IPL_IMAGE_HEADER );

			switch(lDepth)
			{
			// create image header for 24-bit color RGB
			case 3: m_pImgOutput = iplCreateImageHeader(3,	// 3 channels
								0,							// alpha = 0
								IPL_DEPTH_8U,	
								"RGB",
								"RGB",
								IPL_DATA_ORDER_PIXEL,		// ?
								IPL_ORIGIN_TL,				// origin @ top-left
								IPL_ALIGN_DWORD,			// mmx optimized
								lWidth,						// img width
								lHeight,					// img height
								NULL,NULL,NULL,NULL);
				break;
			// create image header for gray-scale image
			case 1: m_pImgOutput = iplCreateImageHeader(1,	// 3 channels
								0,							// alpha = 0
								IPL_DEPTH_8U,	
								"GRAY",
								"GRAY",
								IPL_DATA_ORDER_PIXEL,		// ?
								IPL_ORIGIN_TL,				// origin @ top-left
								IPL_ALIGN_DWORD,			// mmx optimized
								lWidth,						// img width
								lHeight,					// img height
								NULL,NULL,NULL,NULL);
				break;

			}
			// create ROI structure

			// Setup image size
			m_pImgOutput->imageSize = lHeight*lWidth*lDepth;

			/********************************************
					for gray-scale header
			this is use specificly for ColorToGray function
			 ********************************************/
			// If header exists, deallocate before creating a new one
			if( m_pImgOutputGray != NULL ) iplDeallocate( m_pImgOutputGray, IPL_IMAGE_HEADER );

			// create img header fo 24-bit color RGB
			m_pImgOutputGray = iplCreateImageHeader(1,	// 3 channels
								0,						// alpha = 0
								IPL_DEPTH_8U,	
								"GRAY",
								"GRAY",
								IPL_DATA_ORDER_PIXEL,	// ?
								IPL_ORIGIN_TL,			// origin @ top-left
								IPL_ALIGN_DWORD,		// mmx optimized
								lWidth,					// img width
								lHeight,				// img height
								NULL,NULL,NULL,NULL);

			// create ROI structure

			// Setup image size
			m_pImgOutputGray->imageSize = lHeight*lWidth;

			/********************************************
					for color header
			 ********************************************/
			// If header exists, deallocate before creating a new one
			if( m_pImgOutputColor != NULL ) iplDeallocate( m_pImgOutputColor, IPL_IMAGE_HEADER );

			// create img header fo 24-bit color RGB
			m_pImgOutputColor = iplCreateImageHeader(3,	// 3 channels
								0,						// alpha = 0
								IPL_DEPTH_8U,	
								"RGB",
								"RGB",
								IPL_DATA_ORDER_PIXEL,	// ?
								IPL_ORIGIN_TL,			// origin @ top-left
								IPL_ALIGN_DWORD,		// mmx optimized
								lWidth,					// img width
								lHeight,				// img height
								NULL,NULL,NULL,NULL);

			// create ROI structure

			// Setup image size
			m_pImgOutputColor->imageSize = lHeight*lWidth*lDepth;
		}	
	}


	m_bInitialized = TRUE;

	return S_OK;
}



/*********************************************
* Initial(width, height, depth)
*
* Create Image headers for images.
* Do so for two input images and two output images. 
*
* N = 2, for left and right.
*********************************************/
STDMETHODIMP CIntelIPL::Initial(int InputWidth, int InputHeight, int InputDepth)
{
	/************ we have N IPL header here **********/
	/***** to handle N image *************************/
	for(int i = 0; i < N; i++ )
	{
		/******** clear header *********/
		if( m_pImgInput[i] != NULL ) iplDeallocate( m_pImgInput[i], IPL_IMAGE_HEADER );
		/******** create img header for 24-bit color (3 channels) RGB **********/
		switch(InputDepth)
		{
			// Monochrome image
			case 1: m_pImgInput[i] = iplCreateImageHeader(1,	// number of channels
								0,								// alpha = 0
								IPL_DEPTH_8U,					// 8 bytes = 255 levels of intesity
								"GRAY",							// Grayscale image
								"GRAY",
								IPL_DATA_ORDER_PIXEL,			// 0,1,2,3....
								IPL_ORIGIN_TL,					// origin @ bottom-left
								IPL_ALIGN_DWORD,				// mmx optimized
								InputWidth,						// img width		
								InputHeight,					// img height
								NULL,NULL,NULL,NULL);
					
					m_pImgInput[i]->imageSize = InputHeight*InputWidth;
				break;

			// Color image
			case 3: m_pImgInput[i] = iplCreateImageHeader(3,	// number of channels
								0,								// alpha = 0
								IPL_DEPTH_8U,	
								"RGB",
								"RGB",
								IPL_DATA_ORDER_PIXEL,			// ?
								IPL_ORIGIN_TL,					// origin @ bottom-left
								IPL_ALIGN_DWORD,				// mmx optimized
								InputWidth,						// img width		
								InputHeight,					// img height
								NULL,NULL,NULL,NULL);
					
					m_pImgInput[i]->imageSize = InputHeight*InputWidth*InputDepth;
				break;
		}
	}
	
	/******** creat output image corresponding to input **********/
	if( m_pImgOutput != NULL ) iplDeallocate( m_pImgOutput, IPL_IMAGE_HEADER );
	switch(InputDepth)
	{
	case 3: m_pImgOutput = iplCreateImageHeader(3,	// number of channels
						0,		// alpha = 0
						IPL_DEPTH_8U,	
						"RGB",
						"RGB",
						IPL_DATA_ORDER_PIXEL,	// ?
						IPL_ORIGIN_TL,	// origin @ bottom-left
						IPL_ALIGN_DWORD, // mmx optimized
						InputWidth,	// img width		
						InputHeight,// img height
						NULL,NULL,NULL,NULL);
			
			m_pImgOutput->imageSize = InputHeight*InputWidth*InputDepth;
		break;
	case 1: m_pImgOutput = iplCreateImageHeader(1,	// number of channels
						0,		// alpha = 0
						IPL_DEPTH_8U,	
						"GRAY",
						"GRAY",
						IPL_DATA_ORDER_PIXEL,	// ?
						IPL_ORIGIN_TL,	// origin @ bottom-left
						IPL_ALIGN_DWORD, // mmx optimized
						InputWidth,	// img width		
						InputHeight,// img height
						NULL,NULL,NULL,NULL);
			
			m_pImgOutput->imageSize = InputHeight*InputWidth;
		break;
	}

	/*********** special header to handle color and gray image **********/
	/********************************************
			for gray-scale header
	this is use specificly for ColorToGray function
	 ********************************************/
	/**** If header exists, deallocate before creating a new one ****/
	if( m_pImgOutputGray != NULL ) iplDeallocate( m_pImgOutputGray, IPL_IMAGE_HEADER );
	// create img header for gray output image
	m_pImgOutputGray = iplCreateImageHeader(1,	// 1 channels
							0,		// alpha = 0
							IPL_DEPTH_8U,	
							"GRAY",
							"GRAY",
							IPL_DATA_ORDER_PIXEL,	// ?
							IPL_ORIGIN_TL,	// origin @ top-left
							IPL_ALIGN_DWORD, // mmx optimized
							InputWidth,	// img width
							InputHeight,// img height
							NULL,NULL,NULL,NULL);
	/*** Setup image size ***/
	m_pImgOutputGray->imageSize = InputHeight*InputWidth;

	/********************************************
				for color header
	********************************************/
	/*** If header exists, deallocate before creating a new one ***/
	if( m_pImgOutputColor != NULL ) iplDeallocate( m_pImgOutputColor, IPL_IMAGE_HEADER );

	/***  create img header fo 24-bit color RGB ****/
	m_pImgOutputColor = iplCreateImageHeader(3,	// 3 channels
							0,		// alpha = 0
							IPL_DEPTH_8U,	
							"RGB",
							"RGB",
							IPL_DATA_ORDER_PIXEL,	// ?
							IPL_ORIGIN_TL,	// origin @ top-left
							IPL_ALIGN_DWORD, // mmx optimized
							InputWidth,	// img width
							InputHeight,// img height
							NULL,NULL,NULL,NULL);

	/***  Setup image size ***/
	m_pImgOutputColor->imageSize = InputHeight*InputWidth*InputDepth;

	// Set the flag
    m_bInitialized = TRUE;

	return S_OK;
}


STDMETHODIMP CIntelIPL::Mirror(long Input, long Output, long FlipAxis)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplMirror(	m_pImgInput[0],	// Src
				m_pImgOutput,			// Dest
				FlipAxis			// Flip flag
				);					// No tile info

	return S_OK;
}

STDMETHODIMP CIntelIPL::Not(long Input, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplNot(	m_pImgInput[0],	// Src
			m_pImgOutput			// Dest
			);					// No tile info

	return S_OK;
}

STDMETHODIMP CIntelIPL::ColorToGray(long Input, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutputGray->imageData	= (char*) Output;

	iplColorToGray(	m_pImgInput[0],	// Src
					m_pImgOutputGray			// Dest 	
						);					// No tiling info
	return S_OK;
}


STDMETHODIMP CIntelIPL::Erode(long Input, long Output, long Iteration)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplErode(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 Iteration
			 );					// No tile info

	return S_OK;
}

STDMETHODIMP CIntelIPL::Dilate(long Input, long Output, long Iteration)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplDilate(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 Iteration
			 );					// No tile info	
	return S_OK;
}

STDMETHODIMP CIntelIPL::Open(long Input, long Output, long Iteration)
{
	// Copy incoming input image data to private member variable
	m_pImgInput[0]->imageData	= (char*)Input;

	// Copy incoming output image data to private member variable
	m_pImgOutput->imageData		= (char*)Output;

	// Call the OpenCV "OPEN" morphological operator
	iplOpen(m_pImgInput[0],		// Input image
			 m_pImgOutput,		// Output image
			 Iteration			// Number of iterations or steps
			 );			
		
	return S_OK;
}

STDMETHODIMP CIntelIPL::Close(long Input, long Output, long Iteration)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplClose(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 Iteration
			 );					// No tile info
	return S_OK;
}

STDMETHODIMP CIntelIPL::Subtract(long InputA, long InputB, long Output, long FlipAxis)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)InputA;
	m_pImgInput[1]->imageData	= (char*)InputB;
	m_pImgOutput->imageData		= (char*)Output;
	if(FlipAxis==0)
	 iplSubtract(m_pImgInput[0],	// Src A
	 			m_pImgInput[1],		// Src B
	 		    m_pImgOutput		// Dest			A-B
			   );				
	else
	 iplSubtract(m_pImgInput[1],	// Src A
	 			m_pImgInput[0],		// Src B
	 		    m_pImgOutput		// Dest			B-A
			   );				

	return S_OK;
}

STDMETHODIMP CIntelIPL::CreateConvolutionKernel(long* Values, long Rows, long Columns, long AnchorX, long AnchorY, long nShiftR, long Number)
{
	// TODO: Add your implementation code here
	m_pConvKernel[Number] = iplCreateConvKernel(Rows, Columns, AnchorX, AnchorY, (int*)Values, nShiftR);
	return S_OK;
}

STDMETHODIMP CIntelIPL::Convolve2D(long Input, long Output, long nKernels, long combineMethod)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplConvolve2D(m_pImgInput[0],m_pImgOutput, m_pConvKernel, nKernels, combineMethod);

	return S_OK;
}

STDMETHODIMP CIntelIPL::Blur(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplBlur(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 nRows, nCols, anchorX, anchorY
			 );					
	return S_OK;
}

STDMETHODIMP CIntelIPL::MedianFilter(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplMedianFilter(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 nRows, nCols, anchorX, anchorY
			 );					
	return S_OK;
}

STDMETHODIMP CIntelIPL::MinFilter(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplMinFilter(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 nRows, nCols, anchorX, anchorY
			 );	
	return S_OK;
}

STDMETHODIMP CIntelIPL::MaxFilter(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplMaxFilter(m_pImgInput[0],	// Src
			 m_pImgOutput,		// Dest
			 nRows, nCols, anchorX, anchorY
			 );	
	return S_OK;
}

STDMETHODIMP CIntelIPL::Threshold(long Input, long Output, long threshold)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplThreshold(m_pImgInput[0],	// Src
				 m_pImgOutput,		// Dest
			     threshold
			    );					// No tile info
	return S_OK;
}

STDMETHODIMP CIntelIPL::AND(long InputA, long InputB, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)InputA;
	m_pImgInput[1]->imageData	= (char*)InputB;
	m_pImgOutput->imageData		= (char*)Output;
	iplAnd(m_pImgInput[0],	// SrcA
		   m_pImgInput[1],  // SrcB
		   m_pImgOutput		// Dest
		   );					
	return S_OK;
}

STDMETHODIMP CIntelIPL::OR(long InputA, long InputB, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)InputA;
	m_pImgInput[1]->imageData	= (char*)InputB;
	m_pImgOutput->imageData		= (char*)Output;
	iplOr(m_pImgInput[0],	// SrcA
		   m_pImgInput[1],  // SrcB
		   m_pImgOutput		// Dest
		   );					
	return S_OK;
}

STDMETHODIMP CIntelIPL::XOR(long InputA, long InputB, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)InputA;
	m_pImgInput[1]->imageData	= (char*)InputB;
	m_pImgOutput->imageData		= (char*)Output;
	iplXor(m_pImgInput[0],	// SrcA
		   m_pImgInput[1],  // SrcB
		   m_pImgOutput		// Dest
		   );					
	return S_OK;
}

STDMETHODIMP CIntelIPL::Square(long Input, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData	= (char*)Input;
	m_pImgOutput->imageData		= (char*)Output;
	iplSquare(m_pImgInput[0],	// Src
				 m_pImgOutput		// Dest
			    );					// No tile info
	return S_OK;
}

STDMETHODIMP CIntelIPL::Multiply(long Input, long Output, long value)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData = (char*)Input;
	m_pImgOutput->imageData   = (char*)Output;
	iplMultiplyS(m_pImgInput[0], m_pImgOutput, value);
	return S_OK;
}

STDMETHODIMP CIntelIPL::MultiplyScale(long Input, long Output, long value)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData = (char*)Input;
	m_pImgOutput->imageData   = (char*)Output;
	iplMultiplySScale(m_pImgInput[0], m_pImgOutput, value);
	return S_OK;
}

STDMETHODIMP CIntelIPL::MultiplyImage(long InputA, long InputB, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData = (char*)InputA;
	m_pImgInput[1]->imageData = (char*)InputB;
	m_pImgOutput->imageData   = (char*)Output;
	iplMultiply(m_pImgInput[0], m_pImgInput[1], m_pImgOutput);
	return S_OK;
}

STDMETHODIMP CIntelIPL::MultiplyImageScale(long InputA, long InputB, long Output)
{
	// TODO: Add your implementation code here
	m_pImgInput[0]->imageData = (char*)InputA;
	m_pImgInput[1]->imageData = (char*)InputB;
	m_pImgOutput->imageData   = (char*)Output;
	iplMultiplyScale(m_pImgInput[0], m_pImgInput[1], m_pImgOutput);
	return S_OK;
}

STDMETHODIMP CIntelIPL::RGBToHSV(long InputRGB, long OutputHSV)
{
	// TODO: Add your implementation code here
	m_pImgInput[0] ->imageData = (char*)InputRGB;
	m_pImgOutput ->imageData = (char*)OutputHSV;
	iplRGB2HSV(m_pImgInput[0], m_pImgOutput);

	return S_OK;
}

/*********************************************
* Internal Constructors and Serializing
*********************************************/
// The OnConstruct Function sets all the bindings for the component, and \
// also replaces FinalComponentInitialization
STDMETHODIMP CIntelIPL::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 
	int numiids=1;
	long x[1];
	IMA2_BindingInfo	m_Binding;
	x[0]=0;

	// Input Image
	m_Binding.Name		= SysAllocString(L"InputImage");						// Assign name to object
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IImageRep"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);

	// Output Image
	m_Binding.Name		= SysAllocString(L"OutputImage");						// Assign name to object
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IImageRep"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);
	
	return S_OK;
}

STDMETHODIMP CIntelIPL::OnDestruct() { return S_OK; }

STDMETHODIMP CIntelIPL::Load(VARIANT Data) {
	

	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	variant_t				*Var;

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		// hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Variable 1
		// Define strings
		ItemName	= SysAllocString(L"FlipAxis");
		Var			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lFlipAxis	= (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		ItemName	= SysAllocString(L"Rows");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lRows		= (long)*Var;
				// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 3
		ItemName	= SysAllocString(L"Cols");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lCols		= (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 4
		ItemName	= SysAllocString(L"anchorX");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lAnchorX	= (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 5
		ItemName	= SysAllocString(L"anchorY");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lAnchorY	= (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;


		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
		
		// FinalComponentInitialization
		// Init component here
		if( !m_bInitialized )
			aaInitialize(0);

	return S_OK;
}

STDMETHODIMP CIntelIPL::Save(VARIANT *pData) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*Var;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// Variable 1
		// Create string names for items to be saved
		ItemName = SysAllocString(L"FlipAxis");
		// Store the data and the type of data into a variant_t type
		Var = new variant_t(m_lFlipAxis, VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		ItemName = SysAllocString(L"Rows");
		Var = new variant_t(m_lRows, VT_I4);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 3
		ItemName = SysAllocString(L"Cols");
		Var = new variant_t(m_lCols, VT_I4);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 4
		ItemName = SysAllocString(L"anchorX");
		Var = new variant_t(m_lAnchorX, VT_I4);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 5
		ItemName = SysAllocString(L"anchorY");
		Var = new variant_t(m_lAnchorY, VT_I4);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;


		// Returns a pointer to the PropertyBag as a VARIANT
		hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Copy the contents of the property bag to the pData VARIANT
		VariantCopy(pData, &m_VBPropertyBag);

		// Save the size of the data 
		m_lDataSize = pData->parray->rgsabound[0].cElements;		

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);

		// Release
		pIPB->Release();

	return S_OK;
}