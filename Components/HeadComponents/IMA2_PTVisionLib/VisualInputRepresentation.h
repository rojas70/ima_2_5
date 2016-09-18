// VisualInputRepresentation.h : Declaration of the CVisualInputRepresentation

#ifndef __VISUALINPUTREPRESENTATION_H_
#define __VISUALINPUTREPRESENTATION_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.h"
#include "O:\Components\MultiTypeComponents\IMA2_BasicComponentsLib\IMA2_BasicComponentsLib.h"

/////////////////////////////////////////////////////////////////////////////
// CVisualInputRepresentation
class ATL_NO_VTABLE CVisualInputRepresentation : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVisualInputRepresentation, &CLSID_VisualInputRepresentation>,
	public IDispatchImpl<IVisualInputRepresentation, &IID_IVisualInputRepresentation, &LIBID_IMA2_PTVISIONLIBLib>,
	public CComponentImpl 
{
public:
	CVisualInputRepresentation()
	{
		m_pIUnkLeftImage				 = NULL;
		m_pIUnkRightImage				 = NULL;
		m_pIUnkLeftTargetLocationVector  = NULL;
		m_pIUnkRightTargetLocationVector = NULL;
		m_pIUnkEyeMovementStatusVector   = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VISUALINPUTREPRESENTATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVisualInputRepresentation)
	COM_INTERFACE_ENTRY(IVisualInputRepresentation)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

public:

// IVisualInputRepresentation
	STDMETHOD(GetImage)(long ImageID, long* ImagePointer);
	STDMETHOD(GetTargetLocation)(long CameraID, double* Location, long Length);
	STDMETHOD(SetTargetLocation)(long CameraID, double* Location, double Length);
	STDMETHOD(SetEyeMovementStatus)(double* Status, double Length);
	STDMETHOD(GetEyeMovementStatus)(double* Status, double Length);
	STDMETHODIMP ObtainTargetLoc();
	
private:
	// Boolean functions
	BOOL GetImagePointer(IComponent *m_Image, long* ImagePointer);
	BOOL GetSignalInfo(IComponent *m_Vector, double* Value, long Length);
	BOOL SetSignalInfo(IComponent* m_Vector, double* Location, double Length);
	BOOL GetImageInfo(IComponent* m_Image, long *Width, long *Height, long *Depth);

	// Binding variables
	IComponent* m_pIUnkLeftImage;
	IComponent* m_pIUnkRightImage;
	IComponent* m_pIUnkLeftTargetLocationVector;
	IComponent* m_pIUnkRightTargetLocationVector;
	IComponent* m_pIUnkEyeMovementStatusVector;

	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__VISUALINPUTREPRESENTATION_H_
