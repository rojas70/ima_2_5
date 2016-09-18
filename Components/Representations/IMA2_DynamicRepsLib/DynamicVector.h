/* ############################################################################ ++

	Filename:		DynamicVector.h : Declaration of the CDynamicVector

	Purpose:		Have a representation that you are able to add points to
					dynamically.		

	Classes:		CDynamicVector

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Tuesday, October 28, 1997

++ ############################################################################# */


#ifndef __DYNAMICVECTOR_H_
#define __DYNAMICVECTOR_H_

#include "resource.h"						// main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\components\msvbvm60.tlh"		// property bag dll

#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDynamicVector
class ATL_NO_VTABLE CDynamicVector : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDynamicVector, &CLSID_DynamicVector>,
	public IDispatchImpl<IDynamicVector, &IID_IDynamicVector, &LIBID_IMA2_DYNAMICREPSLIBLib>,
	public CComponentImpl 
{
public:
CDynamicVector():

		m_vecData( NULL ),
		m_dTime( 0 ),
		m_lNumVectors( 2 ),
		m_lVectorLength( 256 ),
		m_lPointsAdded( NULL ),
		m_lReadPointer( NULL ),
		m_lWritePointer( NULL ),
		m_bInitialSetup( FALSE )
	{
		ATLTRACE("*-- Created DynamicVector with %d Vectors and %d Points --*\n", m_lNumVectors, m_lVectorLength );
		m_iPointsAddedIndex = 0;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_DYNAMICVECTOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDynamicVector)
	COM_INTERFACE_ENTRY(IDynamicVector)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IDynamicVector
public:
	STDMETHOD(get_VectorLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_VectorLength)(/*[in]*/ long newVal);
	STDMETHOD(get_NumVectors)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumVectors)(/*[in]*/ long newVal);
	STDMETHOD(get_PointsAdded)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PointsAdded)(/*[in]*/ long newVal);
	STDMETHOD(get_PointsAddedIndex)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_PointsAddedIndex)(/*[in]*/ int newVal);
	
	STDMETHOD(GetRecentValue)(long buffer_index, long history_point, double* pVal);
	STDMETHOD(GetVector)(long index, SAFEARRAY* data);
	STDMETHOD(SetVector)(long index, SAFEARRAY* data);
	STDMETHOD(AddNewValue)(long buffer_index, double new_value);

	BOOL BufferIndexValid( long index );
	void AdvanceWritePointer( long Index );


private:

	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT

	void AdvanceReadPointer( long index );
	void ReallocateVectors( long numvectors, long vectorlength );
	long BufferEnd( long buffer_index ) const;
	long BufferStart( long buffer_index ) const;

	double*		m_vecData;			// the actual data.
	double		m_dTime;			// time of last update
	long		m_lNumVectors;		// how many vectors in this rep.
	long		m_lVectorLength;	// length of *EVERY* vector in this rep.
	long*		m_lPointsAdded;		// # points added to each vector

	// read/write pointer for each vector
	long*		m_lWritePointer;
	long*		m_lReadPointer;

	BOOL		m_bInitialSetup;

	// Indeces added for IMA2.5 purposes
	int			m_iPointsAddedIndex;		
};

#endif //__DYNAMICVECTOR_H_
