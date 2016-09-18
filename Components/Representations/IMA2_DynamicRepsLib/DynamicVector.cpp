// DynamicVector.cpp : Implementation of CDynamicVector
#include "stdafx.h"
#include "IMA2_DynamicRepsLib.h"
#include "DynamicVector.h"
#include <assert.h>
#include "O:\components\msvbvm60.tlh" // property bag dll
/////////////////////////////////////////////////////////////////////////////
// CDynamicVector
/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::AdvanceReadPointer()

	Purpose:		

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/
void CDynamicVector::AdvanceWritePointer(long Index) {

	if ( BufferIndexValid ( Index ) ) {
		m_lWritePointer[ Index ] ++;
		// circular buffer semantics.
		m_lWritePointer[ Index ] %= BufferEnd( Index );

		if ( m_lWritePointer[ Index ] < BufferStart( Index ) )
			m_lWritePointer += BufferStart( Index );
		
	}
}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::AdvanceReadPointer()

	Purpose:		

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/

void CDynamicVector::AdvanceReadPointer	(long index) {
	
	// IN: buffer you're interested in.
	if ( BufferIndexValid ( index ) ) {
		m_lReadPointer[ index ] ++;
		// circular buffer semantics.
		m_lReadPointer[ index ] %= BufferEnd( index );

		if ( m_lReadPointer[ index ] < BufferStart( index ) )
			m_lReadPointer += BufferStart( index );
		
	}
}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::BufferIndexValid()

	Purpose:		See if the user is referring to a proper buffer #.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/
BOOL CDynamicVector::BufferIndexValid(long index) {
	
	if ( ( index >= 0 ) && ( index < m_lNumVectors ) )
		return TRUE;
	
	else
		return FALSE;
}

STDMETHODIMP CDynamicVector::SetVector(long index, SAFEARRAY* data) {
	
	
	// TODO: Add your implementation code here

	long veclen;
	double * pVal;

	pVal = (double*)data->pvData;
	veclen = data->rgsabound->cElements;

	if ( pVal != NULL ){
		if ( BufferIndexValid( index ) ) {
			Lock();

			if ( veclen <= m_lVectorLength ) {
				// Now copy their vector into yours.

				for ( long buf_ptr = BufferStart( index ); buf_ptr <= BufferEnd( index ); buf_ptr++ )
					m_vecData[ buf_ptr ] = pVal[ buf_ptr - BufferStart( index ) ];

				m_lPointsAdded[ index ] = m_lVectorLength;

				Unlock();

				//SendProxyUpdates();			// Tell any proxies about this	
				//NotifyCMNewVisualState(0);	// Pump callbacks into manager objects		
			} 
			else
				return E_INVALIDARG;
		} 
		else
			return E_INVALIDARG;
	} 
	else
		return E_POINTER;
	return S_OK;
}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::GetVector()

	Purpose:		This function assumes that you're sending the correct length.
					Perhaps not a good assumption. :>~

 	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/
STDMETHODIMP CDynamicVector::GetVector(long index, SAFEARRAY* data) {
	
	long length;
	double* pVal;

	pVal = (double*)data->pvData;
	length = data->rgsabound->cElements;

	// TODO: Add your implementation code here
	if ( pVal != NULL ) {
		if ( BufferIndexValid( index ) ) {
			if ( m_vecData != NULL ) {
				Lock();

				// Now copy your vector into theirs.
				for ( long buf_ptr = BufferStart( index ); buf_ptr <= BufferEnd( index ); buf_ptr++ )	
					pVal[ buf_ptr - BufferStart( index ) ] = m_vecData[ buf_ptr ];
				
				Unlock();
			}

		} 
		else
			return E_INVALIDARG;
	} 
	else
		return E_POINTER;

	return S_OK;
}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::GetRecentValue()

	Purpose:		

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/
STDMETHODIMP CDynamicVector::GetRecentValue(long buffer_index, long history_point, double *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )	{
		if ( BufferIndexValid( buffer_index	) ) {
			if ( history_point >= 0 ) {
				// set a max value for the request. you don't want to request beyond the
				//	# points in the vector.
				history_point = ( history_point >= m_lVectorLength ) ? m_lVectorLength - 1 : history_point;
				long new_index = m_lWritePointer[ buffer_index ] - history_point - 1;	// (write pointer is on uninitialized data)

				if ( new_index < BufferStart( buffer_index ) ) {
					// wrap-around.
					new_index += m_lVectorLength;
					
					// now extract the value.
					*pVal = m_vecData[ new_index ];
				} 
				else {
					// here you can take the value directly.
					*pVal = m_vecData[ new_index ];
				//	ATLTRACE("CDYNAMICVECTOR::GETRECENTVALUE() pVal = %.2f\n", *pVal );
				}
			}
			else
				return E_INVALIDARG;
		}
		else
			return E_INVALIDARG;
	}
	else 
		return E_POINTER;

	return S_OK;
}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::get_PointsAddedIndex()

	Purpose:		Get the index for the respective function

	Created By:		Juan Rojas, Juan.Rojas@Vanderbilt.edu
	Date Modified:	June 2005
-------------------------------------------------------------------------------*/
STDMETHODIMP CDynamicVector::get_PointsAddedIndex(int *pVal) {
	// TODO: Add your implementation code here
	*pVal = m_iPointsAddedIndex;
	return S_OK;
}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::put_PointsAddedIndex()

	Purpose:		Put a new value at the index 

	Created By:		Juan Rojas, Juan.Rojas@Vanderbilt.edu
	Date Modified:	June 2005
-------------------------------------------------------------------------------*/
STDMETHODIMP CDynamicVector::put_PointsAddedIndex(int newVal) {
	// TODO: Add your implementation code here
	m_iPointsAddedIndex = newVal;
	return S_OK;
}
/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::get_PointsAdded()

	Purpose:		Find out how many points have been added to this buffer.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/
STDMETHODIMP CDynamicVector::get_PointsAdded(long *pVal) {
	// TODO: Add your implementation code here
	if ( pVal != NULL )	{
		if ( BufferIndexValid( m_iPointsAddedIndex ) )		{
			// if it's safe, give it out to the user.
			*pVal = m_lPointsAdded[ m_iPointsAddedIndex ];
		} 
		else
			return E_INVALIDARG;
	} 
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CDynamicVector::put_PointsAdded(long newVal) {	return E_NOTIMPL;}

/*-------------------------------------------------------------------------------
	Name:			CDynamicVector::AddNewValue()

	Purpose:		

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997
-------------------------------------------------------------------------------*/
STDMETHODIMP CDynamicVector::AddNewValue(long buffer_index, double new_value) {

	// TODO: Add your implementation code here
	if ( BufferIndexValid( buffer_index ) ) {
		Lock();
		
		// add a point to the required buffer.
		m_vecData[ m_lWritePointer[ buffer_index ] ] = new_value;

		AdvanceWritePointer( buffer_index );

		if ( m_lPointsAdded[ buffer_index ] < m_lVectorLength )
			m_lPointsAdded[ buffer_index ]++;

		Unlock();
		//SendProxyUpdates();			// Tell any proxies about this... not for ima 2.5
		//NotifyCMNewVisualState(0);		// Pump callbacks into manager objects		

	}
	else {
		ATLTRACE("CDYNAMICVECTOR::ADDNEWVALUE() == BUFFER INDEXVALID ERROR!\n");
		return E_INVALIDARG;
	}

	return S_OK;
}

STDMETHODIMP CDynamicVector::get_NumVectors(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )
		*pVal = m_lNumVectors;

	else
		return E_POINTER;
	return S_OK;
}

STDMETHODIMP CDynamicVector::put_NumVectors(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal >= 0 )
		ReallocateVectors( newVal, m_lVectorLength );	// reallocate vectors under a lock.
		
	else
		return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CDynamicVector::get_VectorLength(long *pVal)
{
	// TODO: Add your implementation code here

	if ( pVal != NULL )	
		*pVal = m_lVectorLength;
	
	else 
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CDynamicVector::put_VectorLength(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal >= 0 )
		ReallocateVectors( m_lNumVectors, newVal );	// reallocate vectors under a lock.
	
	else
		return E_INVALIDARG;
	return S_OK;
}

/*-------------------------------------------------------------------------------

	Name:			CDynamicVector::BufferStart()

	Purpose:		Find the beginning of the requested buffer.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997

-------------------------------------------------------------------------------*/

long CDynamicVector::BufferStart(long buffer_index) const {
	// IN: which buffer you want to find the beginning of
	return ( buffer_index * m_lVectorLength );
}


/*-------------------------------------------------------------------------------

	Name:			CDynamicVector::BufferEnd()

	Purpose:		Find the end of the requested buffer

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997

-------------------------------------------------------------------------------*/

long CDynamicVector::BufferEnd(long	buffer_index) const {
	// IN: which buffer you want to find the end of
	// because indices for each buffer go from 0..VECTOR_LENGTH - 1
	return ( buffer_index * m_lVectorLength + m_lVectorLength - 1 );
}

/*-------------------------------------------------------------------------------

	Name:			CDynamicVector::ReallocateVectors()

	Purpose:		Change the size of the current set of vectors we're managing.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Wednesday, October 29, 1997

-------------------------------------------------------------------------------*/

void CDynamicVector::ReallocateVectors(long	numvectors, long vectorlength) {
	
	ATLTRACE("ENTERED REALLOCATEVECTORS\n");
	// don't need to reallocate if you're giving the same length as the
	//  current vectors OR if you haven't setup at all yet.
	if ( ( !m_bInitialSetup) || ( numvectors != m_lNumVectors ) || ( vectorlength != m_lVectorLength ) )
	{
		Lock();

		m_bInitialSetup = TRUE;

		// delete your existing buffer
		delete [] m_vecData;
		// and delete your housekeeping data
		delete [] m_lPointsAdded;
		delete [] m_lReadPointer;
		delete [] m_lWritePointer;

		m_lVectorLength = vectorlength;
		m_lNumVectors	= numvectors;

		// create your new buffer using the new sizes
		// you will lose the old data. bummer.
		m_vecData = new double[ numvectors * vectorlength ];

		// now make your new housekeeping data storage
		m_lPointsAdded = new long[ m_lNumVectors ];

		// setup read/write pointers for each vector
		m_lReadPointer	= new long[ m_lNumVectors ];
		m_lWritePointer = new long[ m_lNumVectors ];

		// zero this guy out
		memset( m_vecData, 0, sizeof( double ) * vectorlength * numvectors );

		ATLTRACE("ReallocateVectors -- Allocating %d * %d vectors\n", vectorlength, numvectors );

		for ( long index = 0; index < m_lNumVectors; index++ ) {
			m_lPointsAdded[ index ] = 0;
		
			// set the read and write pointers to the front of each
			//  vector, currently
			m_lReadPointer[ index ] = BufferStart( index );
			m_lWritePointer[ index ] = BufferStart( index );
		}

		Unlock();
	} 
	ATLTRACE("EXITING REALLOCATEVECTORS\n");
}


STDMETHODIMP CDynamicVector::OnConstruct() {

	// Final Component Initzialization
	// ULONG ulFlags;
	// IUnknown* pIUnkAManager;
	if ( m_vecData == NULL )		// b/c this function could be called more than once.
	{
		ReallocateVectors( m_lNumVectors, m_lVectorLength );
	}
	// let's see how this puppy graphs.	
	
	return S_OK; 
}

STDMETHODIMP CDynamicVector::OnDestruct() {
	
	// Deallocate storage
	delete [] m_vecData;
	delete [] m_lPointsAdded;
	delete [] m_lWritePointer;
	delete [] m_lReadPointer;
	
	return S_OK; 
}

STDMETHODIMP CDynamicVector::Load(VARIANT Data) {
	

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
		//hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Variable 1
		// Define string name
		ItemName		= SysAllocString(L"NumVectors");
		Var				= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, Var);  //2nd argument is return value (look retval for help)
		// Assign loaded value to member variable
		m_lNumVectors	= (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		// Define string name
		ItemName		= SysAllocString(L"VectorLength");
		Var				= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, Var);  //2nd argument is return value (look retval for help)
		// Assign loaded value to member variable
		m_lVectorLength = (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

STDMETHODIMP CDynamicVector::Save(VARIANT *pData) {
	
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
		ItemName = SysAllocString(L"NumVectors");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_lNumVectors,VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		// Create string names for items to be saved
		ItemName = SysAllocString(L"VectorLength");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_lVectorLength,VT_I4);
		// Add an item to the property bag via the wrapper class.
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