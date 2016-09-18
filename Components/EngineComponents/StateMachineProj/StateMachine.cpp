// StateMachine.cpp : Implementation of CStateMachine

/******************************************************** 
/********************* PLEASE READ *********************/
/********************************************************
* This code is designed to work with Matlab R2007 or earlier.
* The R2008 versions write the state machine under a different format.
* The state machine component will not run. 
* The difference is small and could be easily fixed. When Matlab 2008
* writes the text file representing the statemachine in state flow,
* all the calls to different routines are found in the same line of text.
* In earlier versions each call would be in a new line. 
* Compare the text file between how a new state machine would look like and
* how an old one would look like. 
**********************************************************/

#include "stdafx.h"
#include "StateMachineProj.h"
#include "StateMachine.h"

state::~state()
{
	int i;
	for(i=0;i<transitions.GetSize();i++)
		delete transitions.GetAt(i);
	transitions.RemoveAll();
	for(i=0;i<commands.GetSize();i++)
		delete commands.GetAt(i);
	commands.RemoveAll();
}

state::state(CString inname, int id)
{
	conn* trans;
	shapeid=id;
	if(inname!="Stop")
	{
		trans=new conn;
		trans->shapeid=-1;
		trans->trigger="Stop";
		trans->startnum=id;
		transitions.Add(trans);
		trans=new conn;
		trans->shapeid=-1;
		trans->trigger="Reset";
		trans->startnum=id;
		transitions.Add(trans);
	}
	commands.RemoveAll();
	name=inname;
}

state::state(conn* intrans, int id)
{
	conn* trans;
	shapeid=id;
	trans=new conn;
	trans->shapeid=-1;
	trans->trigger="Stop";
	trans->startnum=id;
	transitions.Add(trans);
	trans=new conn;
	trans->shapeid=-1;
	trans->trigger="Reset";
	trans->startnum=id;
	transitions.Add(trans);
	if(intrans->trigger.Find("Stop")==0)
		transitions[0]->trigger=intrans->trigger;
	else if(intrans->trigger.Find("Reset")==0)
		transitions[1]->trigger=intrans->trigger;
	else
		transitions.Add(intrans);
	commands.RemoveAll();
	name="";
}

command::command(CString txt)
{
	if(txt[0]=='\\')
		componentname="\\"+txt.SpanExcluding(".");
	else
		componentname="\\\\"+txt.SpanExcluding(".");
	function=txt.Mid(txt.Find(".")+1);
	fnname=function.SpanExcluding("(");
}

command::~command()
{
	//do something???
}

/////////////////////////////////////////////////////////////////////////////
// CStateMachine

STDMETHODIMP CStateMachine::OnConstruct()
{

	m_currstate=-1;
	m_reset=FALSE;
	m_wait=FALSE;
	m_vars=new CMapStringToPtr;
	m_idxs=new int[1];
	m_firstconn=new conn;
	m_stopstate=-1;
	m_signal="";

	return S_OK;
}

STDMETHODIMP CStateMachine::OnDestruct()
{
	int i;

	DeleteVars();

	m_filename.Empty();
	for(i=0;i<m_fsm.GetSize();i++)
		delete m_fsm.GetAt(i);
	m_fsm.RemoveAll();
	delete m_firstconn;

	delete[] m_idxs;


	return S_OK;
}

void CStateMachine::DeleteVars()
{
	POSITION t;
	CString key;
	variant_t *val;

	t=m_vars->GetStartPosition();
	while(t!=NULL)
	{
		m_vars->GetNextAssoc(t,key,(void *&)val);
		DeleteInternal(val);
	}
	m_vars->RemoveAll();

	delete m_vars;
}

void CStateMachine::DeleteInternal(VARIANTARG *val)
{
	if(val->vt==(VT_BSTR))
		SysFreeString(val->bstrVal);
	else if(val->vt>=VT_BYREF)
	{
		switch(val->vt)
		{
		case VT_BYREF|VT_I2:
			delete val->piVal;
			break;
		case VT_BYREF|VT_I4:
			delete val->plVal;
			break;
		case VT_BYREF|VT_R4:
			delete val->pfltVal;
			break;
		case VT_BYREF|VT_R8:
			delete val->pdblVal;
			break;
		}
	}
}

void CStateMachine::DeleteOneVar(VARIANTARG* val, CString key)
{
	variant_t *val1;
	CString key1;

	if(key.Find("_arraycount")!=-1)
	{
		delete val;
		m_vars->RemoveKey(key);
		return;
	}

	key1=key+"_arraycount";
	if(m_vars->Lookup(key1,(void*&)val1))
	{
		delete val1;
		m_vars->RemoveKey(key1);
	}

	DeleteInternal(val);
	delete val;

	m_vars->RemoveKey(key);
}

STDMETHODIMP CStateMachine::Load(VARIANT Data)
{
			BSTR					ItemName1 = NULL;	// Holds the name of a given item to be writen into a PropertyBag
			_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
			HRESULT					hRes;			// The HRESULT value we get back from COM calls.
			variant_t*				var;
			bstr_t					temp;

			// (1) Create the property bag wrapper class
			// (2) Have the class point to the interface 
			hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);
			{
				var=new variant_t;
				if (pIPB == NULL)	
					return !S_OK;
				
				// Pass Data to PropertyBag
				hRes = pIPB->SetPropertyBag(&Data);

				// Define strings
				// State Machine File Path
				ItemName1 = SysAllocString(L"StateMachineFile");	// Assign to Item1 the name of your variable

				// Read Data from the property bag
				hRes = pIPB->GetFromPropertyBag(&ItemName1,var);
				m_filename=((bstr_t)(*var)).copy();

				// Manual String
				ItemName1 = SysAllocString(L"ManualString");	// Assign to Item1 the name of your variable

				// Read Data from the property bag
				hRes = pIPB->GetFromPropertyBag(&ItemName1,var);
				m_manualsignal=((bstr_t)(*var)).copy();
			}
				// Decrement the pointer reference count from our member variable. 
				VariantClear(&m_VBPropertyBag);
				
				// Release
				pIPB->Release();

			return S_OK;
}

STDMETHODIMP CStateMachine::Save(VARIANT *Data)
{
			BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
			VARIANT					ItemValue;

			HRESULT					hRes;			// The HRESULT value we get back from COM calls.
			_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class


			// Create Class with CoCreateInstance (definition can be found in MSDN).
			// Create the property bag wrapper class, put pointer to the Interface in pIPB
			hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);
	
			{
				// Save StateMachine path location
				ItemName = SysAllocString(L"StateMachineFile");		// Allocate the string and cast it with L to a 2 byte char (look up ANSI and Unicode strings)
				VariantInit(&ItemValue);						// Initialize our variant (does not free existing one)

				ItemValue.vt=VT_BSTR;
				ItemValue.bstrVal=m_filename.AllocSysString();

				// Add an item to the property bag via the wrapper class.
				hRes = pIPB->AddToPropertyBag(&ItemName, &ItemValue);

				// Release the string
				SysFreeString(ItemName);

				// Save StateMachine ManualString
				ItemName = SysAllocString(L"ManualString");		// Allocate the string and cast it with L to a 2 byte char (look up ANSI and Unicode strings)
				VariantInit(&ItemValue);						// Initialize our variant (does not free existing one)

				ItemValue.vt=VT_BSTR;
				ItemValue.bstrVal=m_manualsignal.AllocSysString();

				// Add an item to the property bag via the wrapper class.
				hRes = pIPB->AddToPropertyBag(&ItemName, &ItemValue);

				// Release the string
				SysFreeString(ItemName);

			}

			// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
			hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
			
			// Copy the value VB gave to us into the return value of this function (which will be returned to whatever's calling our save function)
			VariantCopy(Data, &m_VBPropertyBag);

			// Decrement the pointer reference count from our member variable. 
			VariantClear(&m_VBPropertyBag);

			// Release
			pIPB->Release();

			return S_OK;
}

void CStateMachine::LoadFile()
{
	CStdioFile *filein;
	CString tline;
	CString txt;
	int i;

	BOOL ok=TRUE;

	for(i=0;i<m_fsm.GetSize();i++)
		delete m_fsm.GetAt(i);
	m_fsm.RemoveAll();
	m_stopstate=-1;
	DeleteVars();
	m_vars=new CMapStringToPtr;

	filein=new CStdioFile;
	if(!filein->Open(m_filename,CFile::modeRead|CFile::typeText))
	{
		AfxMessageBox("Error opening file");
		delete filein;
		return;
	}
	filein->ReadString(tline);
	while(tline.Find("Stateflow")!=0) //At start of a line
	{
		if(!filein->ReadString(tline))
		{
			AfxMessageBox("No Stateflow information found.",MB_OK);
			filein->Close();
			delete filein;
			return;
		}
	}

	while(filein->ReadString(tline)&&ok)
	{
		tline.TrimLeft();
		if(tline.Find("state {")==0)
		{
			ok=ReadState(filein);
		}
		else if(tline.Find("transition {")==0)
		{
			ok=ReadConn(filein);
		}
		else if(tline.Find("data {")==0)
		{
			ok=ReadData(filein);
		}
	
	}

	filein->Close();
	delete filein;

	if(!ok)
	{
		AfxMessageBox("File Read Error or Incorrect Format");
		for(i=0;i<m_fsm.GetSize();i++)
			delete m_fsm.GetAt(i);
		m_fsm.RemoveAll();
		DeleteVars();

		return;
	}	

	HiddenSetup();
}

void CStateMachine::HiddenSetup()
{
	state *astate;
	int i;
	int maxid;
	BOOL nostop=TRUE;

	if(m_stopstate==-1)
	{
		maxid=-1;
		for(i=0;i<m_fsm.GetSize();i++)
		{
			if(m_fsm[i]->shapeid>maxid)
				maxid=m_fsm[i]->shapeid;
		}
		maxid++;
		astate=new state("Stop",maxid);
		m_fsm.Add(astate);
		m_stopstate=maxid;
	}

	for(i=0;i<m_fsm.GetSize();i++)
	{
		if(m_fsm[i]->name!="Stop")
		{
			m_fsm[i]->transitions[0]->endnum=m_stopstate;
			m_fsm[i]->transitions[1]->endnum=m_firstconn->endnum;
		}
	}
}

BOOL CStateMachine::ReadState(CStdioFile*filein)
{
	CString tline,txt;
	int tidx;
	state *newstate;
	command *newcommand;
	int id=-1;
	CString name;
	int done=0;
	BOOL makecomm;


	while(filein->ReadString(tline) && done!=2)
	{
		tline.TrimLeft();
		tline.TrimRight();
		if(tline.Find("id")==0)
		{
			txt=tline.Mid(tline.FindOneOf("1234567890"));
			if(id==-2)
			{
				id=atoi(txt.SpanIncluding("1234567890"));
				newstate->shapeid=id;
			}
			else
				id=atoi(txt.SpanIncluding("1234567890"));
			done++;
		}
		else if(tline.Find("labelString")==0)
		{
			name=tline.Mid(tline.Find('"')+1);
			name=name.Left(name.GetLength()-1);
			tidx=name.Find("\\n");
			if(tidx!=-1)
				name.Delete(tidx,2);

			newstate=new state(name,id);
			id=-2;

			filein->ReadString(tline);
			tline.TrimLeft();
			tline.TrimRight();

			txt.Empty();
			makecomm=FALSE;
			while(tline[0]=='"')
			{
				txt=txt+tline.Mid(1);
				txt=txt.Left(txt.GetLength()-1);

				//eliminates the string "\\n". 
				tidx=txt.Find("\\n");
				while(tidx!=-1)
				{
					txt.Delete(tidx,2);
					tidx=txt.Find("\\n");
					makecomm=TRUE;
				}

				//Stateflow records a " as \" (uses an escape sequence)
				//this eliminates the preceding slash.
				tidx=txt.Find("\\\"");
				while(tidx!=-1)
				{
					txt.Delete(tidx);
					tidx=txt.Find("\\\"");
				}

				//Stateflow record a \ as \\ (uses and escape sequence)
				//this turns it into one slash
				tidx=txt.Find("\\\\");
				while(tidx!=-1)
				{
					txt.Delete(tidx);
					tidx=txt.Find("\\\\");
				}

				if(makecomm==TRUE)
				{
					newcommand=new command(txt);
//					m_Locator->Locate(newcommand->componentname.AllocSysString(),&(newcommand->component));
					newstate->commands.Add(newcommand);
					makecomm=FALSE;
					txt.Empty();
				}

				filein->ReadString(tline);
				tline.TrimLeft();
				tline.TrimRight();
			}

			if(!txt.IsEmpty())
			{
				newcommand=new command(txt);
//				m_Locator->Locate(newcommand->componentname.AllocSysString(),&(newcommand->component));
				newstate->commands.Add(newcommand);
				txt.Empty();
			}

			done++;
		}
	}

	if(done<2)
		return FALSE;

	if(name=="Stop")
		m_stopstate=newstate->shapeid;

	tidx=FindState(newstate->shapeid);
	if(tidx==-1)
	{
		m_fsm.Add(newstate);
	}
	else
	{
		if(newstate->name!="")
			m_fsm[tidx]->name=newstate->name;
		if(newstate->commands.GetSize()>0)
			m_fsm[tidx]->commands.Copy(newstate->commands);
		delete newstate;
	}
	return TRUE;

}

BOOL CStateMachine::ReadConn(CStdioFile*filein)
{
	CString tline,txt;
	int tidx;
	int done=0;
	conn *newconn;
	state *newstate;
	int opt=0;

	newconn=new conn;

	newconn->shapeid=-1;
	newconn->startnum=-1;
	newconn->endnum=-1;
	newconn->trigger="";

	while(filein->ReadString(tline)&&done!=4)
	{
		tline.TrimLeft();
		tline.TrimRight();
		if(tline.Find("id")==0)
		{
			switch(opt)
			{
			case 0:
				txt=tline.Mid(tline.FindOneOf("1234567890"));
				newconn->shapeid=atoi(txt.SpanIncluding("1234567890"));
				done++;
				break;
			case 1:
				//src
				txt=tline.Mid(tline.FindOneOf("1234567890"));
				newconn->startnum=atoi(txt.SpanIncluding("1234567890"));
				done++;
				break;
			case 2:
				//dst
				txt=tline.Mid(tline.FindOneOf("1234567890"));
				newconn->endnum=atoi(txt.SpanIncluding("1234567890"));
				done++;
				break;
			}
			opt=0;
		}
		else if(tline.Find("labelString")==0)
		{
			newconn->trigger=tline.Mid(tline.Find('"')+1);
			newconn->trigger=newconn->trigger.Left(newconn->trigger.GetLength()-1);
			filein->ReadString(tline);
			tline.TrimLeft();
			tline.TrimRight();

			//Trim off the surrounding quotes.
			while(tline[0]=='"')
			{
				newconn->trigger+=tline.Mid(1);
				newconn->trigger=newconn->trigger.Left(newconn->trigger.GetLength()-1);
				filein->ReadString(tline);
				tline.TrimLeft();
				tline.TrimRight();
			}

			//There is no need for a newline-return in the trigger.
			tidx=newconn->trigger.Find("\\n");
			while(tidx!=-1)
			{
				newconn->trigger.Delete(tidx,2);
				tidx=newconn->trigger.Find("\\n");
			}
			
			//Stateflow records a " as \" (uses an escape sequence)
			//this eliminates the preceding slash.
			tidx=newconn->trigger.Find("\\\"");
			while(tidx!=-1)
			{
				newconn->trigger.Delete(tidx);
				tidx=newconn->trigger.Find("\\\"");
			}

			//Stateflow record a \ as \\ (uses and escape sequence)
			//this turns it into one slash
			tidx=newconn->trigger.Find("\\\\");
			while(tidx!=-1)
			{
				newconn->trigger.Delete(tidx);
				tidx=newconn->trigger.Find("\\\\");
			}
			
			done++;
		}
		else if(tline.Find("src")==0)
		{
			opt=1;
		}
		else if(tline.Find("dst")==0)
		{
			opt=2;
		}

		if(opt==1 && tline.Find("}")!=-1)
		{	
			//no source id--this is the initial transition.
			done++;
		}
	}

	if(done<4)
		return FALSE;

	if(newconn->startnum==-1)
	{
		delete m_firstconn;
		m_firstconn=newconn;
	}
	else
	{
		tidx=FindState(newconn->startnum);
		if(tidx==-1)
		{
			newstate=new state(newconn,newconn->startnum);
			tidx=m_fsm.Add(newstate);
		}
		else
		{
			if(newconn->trigger.Find("Stop")==0)
				m_fsm[tidx]->transitions[0]->trigger=newconn->trigger;
			else if(newconn->trigger.Find("Reset")==0)
				m_fsm[tidx]->transitions[1]->trigger=newconn->trigger;
			else
				m_fsm[tidx]->transitions.Add(newconn);
		}
		
	}	

	return TRUE;
}

BOOL CStateMachine::ReadData(CStdioFile*filein)
{
	CString tline,txt;
	int done=0;
	int i,j,arraycount=0;
	int idx,bracketcount=1;
	variant_t *val;
	CString key;

	val=new variant_t;
	val->vt=VT_EMPTY;

	while(filein->ReadString(tline)&&done<3&&bracketcount>0)
	{
		//because "size" is an optional parameter, we count opening and closing brackets
		//when bracketcount=0, the bracket matching the opening "data {" has been found,
		//and we're not going to find a size parameter.
		idx=tline.Find("{");
		while(idx!=-1)
		{
			bracketcount++;
			idx=tline.Find("{",idx+1);
		}
		idx=tline.Find("}");
		while(idx!=-1)
		{
			bracketcount--;
			idx=tline.Find("}",idx+1);
		}

		tline.TrimLeft();
		if(tline.Find("name")==0)
		{
			key=tline.Mid(tline.Find('"')+1);
			key=key.SpanExcluding("\"");
			done++;
		}
		else if(tline.Find("dataType")==0)
		{
			txt=tline.Mid(tline.Find('"')+1);
			txt=txt.SpanExcluding("\"");
			if(txt=="int16")
			{
				val->vt=VT_I2;
				val->iVal=(short)0;
			}
			else if(txt=="int32")
			{
				val->vt=VT_I4;
				val->lVal=(long)0;
 			}
			else if(txt=="single")
			{
				val->vt=VT_R4;
				val->fltVal=0.0f;
			}
			else if(txt=="double")
			{
				val->vt=VT_R8;
				val->dblVal=0.0;
			}
			else if(txt=="char"||txt=="string"||txt=="uint8")
			{
				val->vt=VT_BSTR;
				val->bstrVal=SysAllocString(L"?");
			}
			else
			{
				delete val;
				return FALSE;
			}
			done++;
		}
		else if(tline.Find("size")==0)
		{
			if(tline.Find("size")!=-1)
			{	
				txt=tline.Mid(tline.Find('"')+1);
				txt=txt.SpanExcluding("\"");
				j=atoi(txt);
				val->vt=VT_BYREF|val->vt;
				
				switch(val->vt)
				{
				case VT_BYREF|VT_I2:
					val->piVal=new short[j];
					for(i=0;i<j;i++)
						val->piVal[i]=0;
					break;
				case VT_BYREF|VT_I4:
					val->plVal=new long[j];
					for(i=0;i<j;i++)
						val->plVal[i]=0;
					break;
				case VT_BYREF|VT_R4:
					val->pfltVal=new float[j];
					for(i=0;i<j;i++)
						val->pfltVal[i]=0.0f;
					break;
				case VT_BYREF|VT_R8:
					val->pdblVal=new double[j];
					for(i=0;i<j;i++)
						val->pdblVal[i]=0.0;
					break;
				}
				arraycount=j;
			}
			done++;
		}
	}

	if(done<2)
		return FALSE;

	m_vars->SetAt(key,(void*)val);
	if(val->vt>VT_BYREF)
	{
		key+="_arraycount";
		val=new variant_t;
		val->vt=VT_I4;
		val->lVal=arraycount;
		m_vars->SetAt(key,(void*)val);
	}

	return TRUE;
}

BOOL CStateMachine::ReadOneVar(VARIANT& val, CString txt, VARTYPE vt,int& arraycount)
{
	variant_t var;
	BOOL retval;
	var.vt=val.vt;
	retval=ReadOneVar(&var, txt, vt,arraycount);
	val=var;
	return retval;
}

BOOL CStateMachine::ReadOneVar(variant_t *val, CString txt, VARTYPE vt, int& arraycount)
{
	double v[1];
	CString *sepvars;
	int i,idx,count;
	
	//ignores type casting
	if(txt[0]=='(')
	{
		txt=txt.Mid(txt.Find(')')+1);
		txt.TrimLeft();
	}

	//produces an error if trying to set a string to a non-string variable
	//or an array to a non-array variable.
	if(txt[0]=='\"' && vt!=VT_BSTR)
		return FALSE;
	if(txt[0]=='[' && vt<VT_BYREF)
		return FALSE;

	//compensates for an array with no brackets by creating brackets.
	if(txt[0]!='[' && vt>VT_BYREF)
		txt="["+txt+"]";

	val->vt=vt;
	switch(vt)
	{
	case VT_I2:
		sscanf(txt,"%sd",(short*)v);
		*val=((short*)v)[0];
		break;
	case VT_I4:
		sscanf(txt,"%ld",(long*)v);
		*val=((long*)v)[0];
		break;
	case VT_INT:
		sscanf(txt,"%d",(int*)v);
		val->intVal=((int*)v)[0];
		val->vt=VT_I4;
		break;
	case VT_R4:
		sscanf(txt,"%f",(float*)v);
		*val=((float*)v)[0];
		break;
	case VT_R8:
		sscanf(txt,"%lf",v);
		*val=v[0];
		break;
	case VT_BSTR:
		SysFreeString(val->bstrVal);
		val->bstrVal=txt.AllocSysString();
		break;
	case VT_BYREF|VT_I2:
		txt=txt.SpanExcluding("]");
		idx=txt.Find("[");
		txt=txt.Mid(idx+1);
		sepvars=SeparateVars(txt,count);
		val->piVal=new short[count];
		for(i=0;i<count;i++)
			val->piVal[i]=(short)atoi(sepvars[i]);
		arraycount=count;
		break;
	case VT_BYREF|VT_I4:
		txt=txt.SpanExcluding("]");
		idx=txt.Find("[");
		txt=txt.Mid(idx+1);
		sepvars=SeparateVars(txt,count);
		val->plVal=new long[count];
		for(i=0;i<count;i++)
			val->plVal[i]=atoi(sepvars[i]);
		arraycount=count;
		break;
	case VT_BYREF|VT_INT:
		txt=txt.SpanExcluding("]");
		idx=txt.Find("[");
		txt=txt.Mid(idx+1);
		sepvars=SeparateVars(txt,count);
		val->pintVal=new int[count];
		for(i=0;i<count;i++)
			val->pintVal[i]=atoi(sepvars[i]);
		arraycount=count;
		val->vt=VT_BYREF|VT_I4;
		break;
	case VT_BYREF|VT_R4:
		txt=txt.SpanExcluding("]");
		idx=txt.Find("[");
		txt=txt.Mid(idx+1);
		sepvars=SeparateVars(txt,count);
		val->pfltVal=new float[count];
		for(i=0;i<count;i++)
			val->pfltVal[i]=(float)atof(sepvars[i]);
		arraycount=count;
		break;
	case VT_BYREF|VT_R8:
		txt=txt.SpanExcluding("]");
		idx=txt.Find("[");
		txt=txt.Mid(idx+1);
		sepvars=SeparateVars(txt,count);
		val->pdblVal=new double[count];
		for(i=0;i<count;i++)
			val->pdblVal[i]=atof(sepvars[i]);
		arraycount=count;
		break;
	default:
		return FALSE;
		break;			
	}

	return TRUE;
}

int CStateMachine::FindNextState()
{
	int i,j,deflt,tidx,next;
	state* stt;
	conn *cn;
	CString txt;
	
	deflt=-1;
	tidx=FindState(m_currstate);
	stt=m_fsm[tidx];
	for(i=0;i<stt->transitions.GetSize();i++)
	{
		cn=stt->transitions[i];
		j=cn->trigger.Find(";");
		if(j==-1)
			txt=cn->trigger;
		else
			txt=cn->trigger.Left(j);
		txt.TrimLeft();
		txt.TrimRight();

		if(txt=="Stop")
		{
			if(m_signal=="Stop")
			{
				if(j==-1)
					ResetVars();
				else
					UpdateVars(cn);
				m_signal="";
				return cn->endnum;
			}
		}
		else if(txt=="Reset")
		{
			if(m_signal=="Reset")
			{
				if(j==-1)
				{
					ResetVars();
					UpdateVars(m_firstconn);
				}
				else
					UpdateVars(cn);
				m_signal="";
				return cn->endnum;
			}
		}
		else if(txt=="Always")
		{
			UpdateVars(cn);
			return cn->endnum;
		}
		else if(txt=="Default")
			deflt=i;
		else
		{
			next=FindNext(cn);
			if(next!=-1)
			{
				if(txt.Find("Signal")==0 || txt.Find("signal")==0)
					m_signal="";
				return next;
			}
		}
	}

	if(deflt!=-1)
	{
		cn=stt->transitions[deflt];
		UpdateVars(cn);
		return cn->endnum;
	}
	
	//if this state only has the stop and reset transitions,
	//then the only way out is to take the stop transition,
	//even though the signal isn't to stop.
	if(stt->transitions.GetSize()==2)
	{
		cn=stt->transitions[0];
		j=cn->trigger.Find(";");
		if(j==-1)
			ResetVars();
		else
			UpdateVars(cn);
		m_signal="";
		return cn->endnum;		
	}

	return -1;
}

int CStateMachine::FindNext(conn* cn)
{
	int i,comptype;
	CString line,txt,txt2;
	CString key1,key2,errortxt;
	variant_t *val1, *val2;
	VARTYPE vt,vt2;
	BOOL match,flag=FALSE;
	int j=0,idx;
	CString *sepvars;
	int count;

	//the first part of the transition line is the (set) of things that must match
	//these are all put before a semi-colon.
	line=cn->trigger.SpanExcluding(";");
	sepvars=SeparateVars(line,count);
	if(count==-1)
	{
		txt.Format("Continuing after syntax error in transition: %s",line);
		return -1;
	}

	//only valid matches (with ISAC) are variable (in)equalities,
	//separated by commas. No arrays are allowed in the transition tests.
	//Using strings with less than/greater than works like strcmp.
	for(idx=0;idx<count;idx++)
	{
		match=FALSE;
		txt=sepvars[idx];

		//find the test symbol
		i=txt.FindOneOf("!=<>~");

		//the lhs will be before the test symbol
		key1=txt.SpanExcluding("!=<>~");
		key1.TrimLeft();
		key1.TrimRight();

		//find the variable to match
		if(key1=="signal" || key1=="Signal")
		{
			val1=new variant_t;
			val1->vt=VT_BSTR;
			val1->bstrVal=m_signal.AllocSysString();
		}
		else
		{
			val1=new variant_t;
			*val1=TextToMath(key1,VT_EMPTY,errortxt);
			if(errortxt!="OK")
			{
				txt2.Format("Error reading lhs of test %s (trying next test): %s",txt,errortxt);
				AfxMessageBox(txt2);
				delete val1;
				continue;
			}
		}
		
		vt=val1->vt;
		if(vt>=VT_BYREF)
		{
			txt2.Format("No arrays allowed in transition test (lhs): %s, continuing",key1);
			AfxMessageBox(txt2);
			delete val1;
			continue;
		}

		//the rhs (txt2) will be after the test symbol (which might be two characters long
		txt2=line.Mid(i+1);
		if(txt2.FindOneOf("!=<>~")==0)
			txt2=txt2.Mid(1);
		txt2.TrimLeft();
		txt2.TrimRight();
		
		val2=new variant_t;
		*val2=TextToMath(txt2,vt,errortxt);
		if(errortxt!="OK")
		{
			key1.Format("Error reading rhs of transition test %s (trying next test): %s",txt2,errortxt);
			delete val1;
			delete val2;
			continue;
		}
		vt2=val2->vt;

		//Now sort out the type of comparison by looking at the test symbol itself.
		txt2=txt.Mid(i);
		txt=txt2.SpanIncluding("!=<>~");
		if(txt=="="||txt=="==")
			comptype=1;
		else if(txt=="!="||txt=="~="||txt=="<>")
			comptype=0;
		else if(txt=="<="||txt=="=<")
			comptype=2;
		else if(txt==">="||txt=="=>")
			comptype=3;
		else if(txt=="<")
			comptype=4;
		else if(txt==">")
			comptype=5;
		else
			continue;

		//this actually performs the comparison
		switch(vt)
		{
		case VT_BSTR:  
			if(vt2==vt)
			{ 
				j=strcmp((bstr_t)val1,(bstr_t)val2);
				switch(comptype)
				{
				case 0:
					match=(j!=0);
					break;
				case 1:
					match=(j==0);
					break;
				case 2:
					match=(j<=0);
					break;
				case 3:
					match=(j>=0);
					break;
				case 4:
					match=(j<0);
					break;
				case 5:
					match=(j>0);
					break;
				}
			}
			break;
		case VT_I2:
			switch(comptype)
			{
			case 0:
				match=((short)(*val1)!=(short)(*val2));
				break;
			case 1:
				match=((short)(*val1)==(short)(*val2));
				break;
			case 2:
				match=((short)(*val1)<=(short)(*val2));
				break;
			case 3:
				match=((short)(*val1)>=(short)(*val2));
				break;
			case 4:
				match=((short)(*val1)<(short)(*val2));
				break;
			case 5:
				match=((short)(*val1)>(short)(*val2));
				break;
			}
			break;
		case VT_I4:
			switch(comptype)
			{
			case 0:
				match=((long)(*val1)!=(long)(*val2));
				break;
			case 1:
				match=((long)(*val1)==(long)(*val2));
				break;
			case 2:
				match=((long)(*val1)<=(long)(*val2));
				break;
			case 3:
				match=((long)(*val1)>=(long)(*val2));
				break;
			case 4:
				match=((long)(*val1)<(long)(*val2));
				break;
			case 5:
				match=((long)(*val1)>(long)(*val2));
				break;
			}
			break;
		case VT_R4:						
			switch(comptype)
			{
			case 0:
				match=((float)(*val1)!=(float)(*val2));
				break;
			case 1:
				match=((float)(*val1)==(float)(*val2));
				break;
			case 2:
				match=((float)(*val1)<=(float)(*val2));
				break;
			case 3:
				match=((float)(*val1)>=(float)(*val2));
				break;
			case 4:
				match=((float)(*val1)<(float)(*val2));
				break;
			case 5:
				match=((float)(*val1)>(float)(*val2));
				break;
			}
			break;
		case VT_R8:
			switch(comptype)
			{
			case 0:
				match=((double)(*val1)!=(double)(*val2));
				break;
			case 1:
				match=((double)(*val1)==(double)(*val2));
				break;
			case 2:
				match=((double)(*val1)<=(double)(*val2));
				break;
			case 3:
				match=((double)(*val1)>=(double)(*val2));
				break;
			case 4:
				match=((double)(*val1)<(double)(*val2));
				break;
			case 5:
				match=((double)(*val1)>(double)(*val2));
				break;
			}
			break;
		}
							
		//if an incorrect match was found, this isn't the right transition.
		//we might as well stop.
		if(match!=TRUE)
			break;
	}

	if(sepvars!=NULL)
		delete[] sepvars;

	//if we didn't stop early, then we've found the right transition. Update the variables,
	//then return the ending state. Otherwise, return -1.
	if(match==TRUE)
	{
		UpdateVars(cn);
		return cn->endnum;
	}
	else
		return -1;
}

variant_t CStateMachine::MakeString(CString eqn,CString& returntxt)
{
	variant_t retval;
	variant_t *val1;
	CString key1;
	CString txt;
	CString ret;
	int i,count;
	CString *sepvars;

	txt=eqn;
	txt.TrimLeft();
	txt.TrimRight();
	if(txt.IsEmpty())
	{
		retval.vt=VT_EMPTY;
		returntxt="OK";
		return retval;
	}

	retval.vt=VT_BSTR;
	ret.Empty();
	sepvars=SeparateVars(eqn,count,"+");
	if(count==-1)
	{
		returntxt="Syntax error in string formation.";
		retval.vt=VT_EMPTY;
		return retval;
	}
	for(i=0;i<count;i++)
	{
		key1=sepvars[i];
		if(key1[0]=='?')
		{
			key1=key1.Mid(1);
			if(m_vars->Lookup(key1,(void*&)val1))
			{
				if(val1->vt!=VT_BSTR)
				{
					retval.vt=VT_EMPTY;
					returntxt.Format("Variable %s not a string.",key1);
					return retval;
				}
				ret+=val1->bstrVal;
			}
			else
			{
				retval.vt=VT_EMPTY;
				returntxt.Format("Variable %s not found.",key1);
				return retval;
			}
		}
		else
		{
			key1=key1.Mid(1);
			key1=key1.SpanExcluding("\"");
			ret+=key1;
		}

	}

	retval.bstrVal=ret.AllocSysString();
	returntxt="OK";
	return retval;
}

variant_t CStateMachine::TextToMath(CString equ,VARTYPE vt,CString &returntxt)
{
	variant_t retval;
	variant_t *val1;
	CString key1;
	CString txt,txt2;
	int i,j,k,idx,count,tmp,arridx;
	CString *sepvars;
	VARTYPE tmpvt;

	tmp=1;
	txt=equ;
	txt.TrimRight();
	txt.TrimLeft();
	if(txt.IsEmpty())
	{
		retval.vt=VT_EMPTY;
		returntxt="OK";
		return retval;
	}

	if(vt>VT_BYREF)
	{
		retval.vt=VT_EMPTY;
		returntxt="Cannot create array in equation.";
		return retval;
	}

	//vt=VT_EMPTY when using math on a lhs of a comparison, so the type is unknown
	//iterate through all variables, looking for a type. Arrays (but not array elements)
	//are invalid and return an error.
	//If no variables are found, first check for quotes --> string.
	//Then look for the error of trying to make an array.
	//Then check for decimals --> double.
	//Else assume (long) int.
	//If variables of conflicting types are found, prefer items in this order:
	//double, float, long int, short.
	//If a string and a non-string variable are found, return an error.
	if(vt==VT_EMPTY)
	{
		sepvars=SeparateVars(equ,count,"?");
		if(count==-1)
		{
			retval.vt=VT_EMPTY;
			returntxt.Format("Syntax error on lhs: %s",equ);
			return retval;
		}

		if(count>1)
		{
			for(i=1;i<count;i++)
			{
				key1=sepvars[i].SpanExcluding("[+-*/( ");
				if(m_vars->Lookup(key1,(void *&)val1))
				{
					if(val1->vt>VT_BYREF)
					{
						if(sepvars[i].Find("[")==key1.GetLength())
							tmpvt=val1->vt-VT_BYREF;
						else
						{
							retval.vt=VT_EMPTY;
							returntxt.Format("Variable %s is an array and not allowed.",key1);
							return retval;
						}
					}
					else
						tmpvt=val1->vt;
				}
				else
				{
					retval.vt=VT_EMPTY;
					returntxt.Format("Variable %s not found.",key1);
					return retval;
				}

				if(tmpvt==VT_BSTR && !(vt==VT_BSTR || vt==VT_EMPTY))
				{
						retval.vt=VT_EMPTY;
						returntxt.Format("String and non-string variable in same equation.");
						return retval;
				}
				
				switch(vt)
				{
				case VT_EMPTY:
					vt=tmpvt;
					break;
				case VT_BSTR:
					if(tmpvt!=VT_BSTR)
					{
						retval.vt=VT_EMPTY;
						returntxt.Format("String and non-string variable in same equation.");
						return retval;
					}
					else
						vt=tmpvt;
					break;
				case VT_I2:
					vt=tmpvt;
					break;
				case VT_I4:
					if(tmpvt!=VT_I2)
						vt=tmpvt;
					break;
				case VT_R4:
					if(tmpvt==VT_R4 || tmpvt==VT_R8)
						vt=tmpvt;
					break;
				case VT_R8:
					i=count; //stop loop because we won't change vt again.
					break;
				}
			}
		}
		else
		{
			if(sepvars[0].Find("\"")!=-1)
			{
				vt=VT_BSTR;
			}
			else if(sepvars[0].Find("[")!=-1)
			{
				retval.vt=VT_EMPTY;
				returntxt.Format("Array not allowed in equation.");
				return retval;
			}
			else if(sepvars[0].Find(".")!=-1)
			{
				vt=VT_R8;
			}
			else
				vt=VT_I4;
		}
	}

	if(vt==VT_BSTR)
	{
		return MakeString(equ,returntxt);
	}

	//Parse for parentheses
	txt=equ;
	i=txt.Find("(");
	j=txt.Find(")");
	k=-1;
	while(i!=-1)
	{
		//find an inner set of parentheses
		txt=txt.SpanExcluding(")");
		i=txt.ReverseFind('(');
		txt=txt.Mid(i+1);

		//find the result of that set
		k++;
		val1=new variant_t;
		key1.Format("tempvar%d",k);
		*val1=TextToMath(txt,vt,returntxt);
		if(returntxt!="OK")
		{
			retval.vt=VT_EMPTY;
			return retval;
		}
		m_vars->SetAt(key1,val1);

		//put the variable name in place of the text
		equ=equ.Left(i)+"?"+key1+equ.Mid(j+1);
		txt=equ;
		i=txt.Find("(");
		j=txt.Find(")");
	}

	retval.vt=vt;
	sepvars=SeparateVars(equ,count,"+");
	if(count==-1)
	{
		retval.vt=VT_EMPTY;
		returntxt="Syntax error.";
		return retval;
	}
	if(count==1)
	{
		delete[] sepvars;
		sepvars=SeparateVars(equ,count,"-");
		if(count==-1)
		{
			retval.vt=VT_EMPTY;
			returntxt="Syntax error.";
			return retval;
		}
		if(count==1)
		{
			delete[] sepvars;
			sepvars=SeparateVars(equ,count,"*");
			if(count==-1)
			{
				retval.vt=VT_EMPTY;
				returntxt="Syntax error.";
				return retval;
			}
			if(count==1)
			{
				delete[] sepvars;
				sepvars=SeparateVars(equ,count,"/");
				if(count==-1)
				{
					retval.vt=VT_EMPTY;
					returntxt="Syntax error.";
					return retval;
				}
				if(count==1)
				{
					key1=sepvars[0];
					if(key1[0]=='?')
					{
						key1=key1.Mid(1);
						if(key1.Find("[")!=-1)
						{
							txt2=key1.Mid(key1.Find("[")+1);
							k=txt2.ReverseFind(']');
							txt2=txt2.Left(k);
							arridx=(long)TextToMath(txt2,VT_I4,returntxt);
							if(returntxt!="OK")
							{
								txt2=returntxt;
								returntxt.Format("Cannot determine array index (%s)",txt2);
								retval.vt=VT_EMPTY;
								return retval;
							}
							key1=key1.SpanExcluding("[");
						}
						else
							arridx=-1;

						if(m_vars->Lookup(key1,(void*&)val1))
						{
							if(val1->vt!=vt)
							{
								ChangeType(val1,vt,tmp,arridx);
							}
							retval=*val1;
						}
						else
						{
							returntxt.Format("Could not find variable %s",key1);
							retval.vt=VT_EMPTY;
							return retval;
						}
					}
					else
					{
						ReadOneVar(&retval,key1,vt,i);
					}
				}
				else
				{
					retval=TextToMath(sepvars[0],vt,returntxt);
					if(returntxt!="OK")
					{
						retval.vt=VT_EMPTY;
						return retval;
					}
					for(idx=1;idx<count;idx++)
					{
						switch(vt)
						{
						case VT_I2:
							retval=(short)((short)retval/(short)TextToMath(sepvars[idx],vt,returntxt));
							break;
						case VT_I4:
							retval=(long)retval/(long)TextToMath(sepvars[idx],vt,returntxt);
							break;
						case VT_R4:
							retval=(float)retval/(float)TextToMath(sepvars[idx],vt,returntxt);
							break;
						case VT_R8:
							retval=(double)retval/(double)TextToMath(sepvars[idx],vt,returntxt);
							break;
						}
						if(returntxt!="OK")
						{
							retval.vt=VT_EMPTY;
							return retval;
						}
					}
				}
				delete[] sepvars;
			}
			else
			{
				retval=TextToMath(sepvars[0],vt,returntxt);
				if(returntxt!="OK")
				{
					retval.vt=VT_EMPTY;
					return retval;
				}
				for(idx=1;idx<count;idx++)
				{
					switch(vt)
					{
					case VT_I2:
						retval=(short)((short)retval*(short)TextToMath(sepvars[idx],vt,returntxt));
						break;
					case VT_I4:
						retval=(long)retval*(long)TextToMath(sepvars[idx],vt,returntxt);
						break;
					case VT_R4:
						retval=(float)retval*(float)TextToMath(sepvars[idx],vt,returntxt);
						break;
					case VT_R8:
						retval=(double)retval*(double)TextToMath(sepvars[idx],vt,returntxt);
						break;
					}
					if(returntxt!="OK")
					{
						retval.vt=VT_EMPTY;
						return retval;
					}
				}
				delete[] sepvars;
			}
		}
		else
		{
			retval=TextToMath(sepvars[0],vt,returntxt);
			if(returntxt!="OK")
			{
				retval.vt=VT_EMPTY;
				return retval;
			}
			for(idx=1;idx<count;idx++)
			{
				switch(vt)
				{
				case VT_I2:
					retval=(short)((short)retval-(short)TextToMath(sepvars[idx],vt,returntxt));
					break;
				case VT_I4:
					retval=(long)retval-(long)TextToMath(sepvars[idx],vt,returntxt);
					break;
				case VT_R4:
					retval=(float)retval-(float)TextToMath(sepvars[idx],vt,returntxt);
					break;
				case VT_R8:
					retval=(double)retval-(double)TextToMath(sepvars[idx],vt,returntxt);
					break;
				}
				if(returntxt!="OK")
				{
					retval.vt=VT_EMPTY;
					return retval;
				}
			}
			delete[] sepvars;
		}
	}
	else
	{
		retval=TextToMath(sepvars[0],vt,returntxt);
		if(returntxt!="OK")
		{
			retval.vt=VT_EMPTY;
			return retval;
		}
		for(idx=1;idx<count;idx++)
		{
			switch(vt)
			{
			case VT_I2:
				retval=(short)((short)retval+(short)TextToMath(sepvars[idx],vt,returntxt));
				break;
			case VT_I4:
				retval=(long)retval+(long)TextToMath(sepvars[idx],vt,returntxt);
				break;
			case VT_R4:
				retval=(float)retval+(float)TextToMath(sepvars[idx],vt,returntxt);
				break;
			case VT_R8:
				retval=(double)retval+(double)TextToMath(sepvars[idx],vt,returntxt);
				break;
			}
			if(returntxt!="OK")
			{
				retval.vt=VT_EMPTY;
				return retval;
			}
		}
		delete[] sepvars;
	}
	
	for(i=0;i<k;i++)
	{
		txt.Format("tempvar%d",i);
		m_vars->Lookup(txt,(void*&)val1);
		DeleteOneVar(val1,txt);
	}

	returntxt="OK";
	return retval;
}			

//separate variables separated by the character(s) in sep (default ","), returning a CString 
//array and the number of variables (in count). Note: the returnval is declared "new" and must
//be deleted later to prevent memory leaks!
CString *CStateMachine::SeparateVars(CString in, int& count, CString sep)
{
	CString *retval=NULL;
	int i,j,k,idx;
	CString txt,txt2;

	count=0;
	txt=in;
	txt.TrimLeft();
	txt.TrimRight();
	if(txt.IsEmpty())
	{
		return retval;
	}

	i=txt.FindOneOf(sep);
	while(i!=-1)
	{
		j=txt.Find("\"");
		if(j!=-1 && j<i)
		{
			k=txt.Find("\"",j+1);
			txt=txt.Mid(k+1);
			i=txt.FindOneOf(sep);
		}
		else
		{
			j=txt.Find("[");
			if(j!=-1 && j<i)
			{
				k=txt.Find("]",j);
				while(1)
				{
					j=txt.Find("[",j+1);
					if(j!=-1 && j<k)
						k=txt.Find("]",k+1);
					else
						break;
				}
				if(k==-1) //this should only happen on a syntax error (mismatched brackets)
				{
					count=-1;
					return retval;
				}
				txt=txt.Mid(k+1);
				i=txt.FindOneOf(sep);
			}
			else
			{
				count++;
				txt=txt.Mid(i+1);
				i=txt.FindOneOf(sep);
			}
		}
	}
	count++;

	retval=new CString[count];

	txt=in;
	txt.TrimLeft();
	txt.TrimRight();
	i=txt.FindOneOf(sep);
	idx=0;
	while(i!=-1)
	{
		j=txt.Find("\"");
		if(j!=-1 && j<i)
		{
			k=txt.Find("\"",j+1);
			retval[idx]+=txt.Left(k+1);
			txt=txt.Mid(k+1);
			i=txt.FindOneOf(sep);
		}
		else
		{
			j=txt.Find("[");
			if(j!=-1 && j<i)
			{
				k=txt.Find("]",j);
				while(1)
				{
					j=txt.Find("[",j+1);
					if(j!=-1 && j<k)
						k=txt.Find("]",k+1);
					else
						break;
				}
				retval[idx]+=txt.Left(k+1);
				txt=txt.Mid(k+1);
				i=txt.FindOneOf(sep);
			}
			else
			{
				retval[idx]+=txt.Left(i); //excludes separator
				txt=txt.Mid(i+1);
				i=txt.FindOneOf(sep);
				idx++;
			}
		}
	}
	if(idx<count)
	{
		retval[idx]+=txt;
	}

	for(idx=0;idx<count;idx++)
	{
		retval[idx].TrimLeft();
		retval[idx].TrimRight();
	}

	return retval;
}

void CStateMachine::UpdateVars(conn* cn)
{
	CString key,key1,key2;
	variant_t *val, *val2;
	variant_t inval;
	CString line,txt;
	int idx;
	int i,j,arraycount=0;
	CString *sepvars;
	CString errortxt;
	int count;

	i=cn->trigger.Find(";");
	if(i==-1) //there is no semi-colon, and hence no updating to do.
		return;

	txt=cn->trigger.Mid(i+1);
	sepvars=SeparateVars(txt,count,",");

	if(count==-1)
	{
		key.Format("Syntax error in assignment sequence %s. No assignment possible.",txt);
		AfxMessageBox(key);
		return;
	}

	for(idx=0;idx<count;idx++)
	{
		line=sepvars[idx];   //line is the full equation

		i=line.Find("=");

		//there must be a variable on the lhs
		key=line.SpanExcluding("=");
		key.TrimRight();
		key.TrimLeft();
		if(key[0]=='?')
			key=key.Mid(1);

		if(key.Find("[")!=-1)
		{
			key1=key.SpanExcluding("[");
			if(m_vars->Lookup(key1,(void*&)val))
			{
				if(val->vt>VT_BYREF && m_vars->Lookup(key1="_arraycount",(void*&)val2))
				{
					key=key.Mid(key.Find("[")+1);
					key=key.Left(key.GetLength()-1);
					j=(long)TextToMath(key,VT_I4,errortxt);
					if(errortxt!="OK")
					{
						txt.Format("Error in format (%s[%s]) (continuing): %s",key1,key,errortxt);
						AfxMessageBox(txt);
						continue;
					}
					if(j>=val2->lVal || j<0)
					{
						txt.Format("Array out of bounds (continuing)\r\nvariable: %s\r\nrequested: %d (%s)\r\nmax element: %d",key1,j,key,val2->lVal);
						AfxMessageBox(txt);
						continue;
					}
					key=key1;
				}
				else
				{
					txt.Format("Error: attempt to access element of non-array element (continuing): %s",line);
					AfxMessageBox(txt);
					continue;
				}
			}
			else
			{
				txt.Format("Cannot find variable %s (continuing)",key1);
				AfxMessageBox(txt);
				continue;
			}
		}
		else
			j=-1;

		//There are several reasons why this next would fail, (including an increment/decrement) 
		//which is why the failure is handled later.
		if(m_vars->Lookup(key,(void*&)val))
		{
			txt=line.Mid(i+1);  //txt is the rhand-side
			txt.TrimLeft();

			j=key.Find("_arraycount");
			if(j!=-1)
			{
				key1=key.Left(j);
				m_vars->Lookup(key1,(void*&)val2);
				DeleteInternal(val2);
			}

			if(val->vt>VT_BYREF && j==-1)
			{
				if(!ReadOneVar(inval,txt,val->vt,arraycount))
				{
					key2.Format("Error reading array: %s (continuing)",txt);
					AfxMessageBox(key2);
					continue;
				}
			}
			else
			{
				inval=TextToMath(txt,val->vt,errortxt);
				if(errortxt!="OK")
				{
					key2.Format("Error creating rhs: %s (continuing)",txt);
					AfxMessageBox(key2);
					continue;
				}
			}

			if(inval.vt==VT_EMPTY)
			{
				continue;
			}
			else
			{
				if(val->vt==VT_BSTR)
					SysFreeString(val->bstrVal);
				else if(val->vt>=VT_BYREF && j==-1)
				{
					switch(val->vt)
					{
					case VT_BYREF|VT_I2:
						delete val->piVal;
						break;
					case VT_BYREF|VT_I4:
						delete val->plVal;
						break;
					case VT_BYREF|VT_R4:
						delete val->pfltVal;
						break;
					case VT_BYREF|VT_R8:
						delete val->pdblVal;
						break;
					}
				}
				
				if(j>0)
				{
					switch(inval.vt)
					{
					case VT_I2:
						val->piVal[j]=inval.iVal;
						break;
					case VT_I4:
						val->plVal[j]=inval.lVal;
						break;
					case VT_R4:
						val->pfltVal[j]=inval.fltVal;
						break;
					case VT_R8:
						val->pdblVal[j]=inval.dblVal;
					}
				}
				else
				{
					*val=inval;
					j=key.Find("_arraycount");
					if(j!=-1)
					{
						arraycount=inval.lVal;
						//the following code initializes both the parameter and the new variable.
						key2="[";
						for(j=0;j<arraycount;j++)
							key2+="0,";
						key2.Left(txt.GetLength()-1);
						key2+="]";
						ReadOneVar(val2,key2,val2->vt,arraycount);
					}
				}

				if(val->vt>=VT_BYREF && j==-1)
				{
					key=key+"_arraycount";
					m_vars->Lookup(key,(void* &)val);
					val->lVal=arraycount;
					arraycount=0;
				}
			}
		}
		else 
		{
			if(key.Find("_arraycount")!=-1)
			{
				val=new variant_t;
				val->vt=VT_I4;

				txt=line.Mid(i+1);  //txt is the rhand-side
				txt.TrimLeft();
				inval=TextToMath(txt,val->vt,errortxt);
				if(errortxt!="OK")
				{
					key2.Format("Error creating rhs: %s (continuing)",txt);
					AfxMessageBox(key2);
					continue;
				}
				*val=inval;
				m_vars->SetAt(key,(void*)val);
			}
			else
			{
				i=line.Find("++");
				if(i!=-1)
				{
					key=line.SpanExcluding("+");
					if(m_vars->Lookup(key,(void*&)val))
					{
						if(val->vt==VT_I2)
							*val=(short)(((short)(*val))+1);
						else if(val->vt==VT_I4)
							*val=(long)(((long)(*val))+1);
						else
						{
							txt.Format("Warning: Tried to increment non-integer variable %s (continuing)",key);
							AfxMessageBox(txt);
						}
					}
					else
					{
						txt.Format("Bad assignment: Variable %s not found (continuing)",key);
						AfxMessageBox(txt);
					}
				}
				else
				{
					i=line.Find("--");
					if(i!=-1)
					{
						key=line.SpanExcluding("-");
						if(m_vars->Lookup(key,(void*&)val))
						{
							if(val->vt==VT_I2)
								*val=(short)(((short)(*val))-1);
							else if(val->vt==VT_I4)
								*val=(long)(((long)(*val))-1);
							else
							{
								txt.Format("Warning: Tried to decrement non-integer variable %s (continuing)",key);
								AfxMessageBox(txt);
							}
						}
						else
						{
							txt.Format("Bad assignment: Variable %s not found (continuing)",key);
							AfxMessageBox(txt);
						}
					}
					else
					{
						txt.Format("Bad assignment: Variable %s not found (continuing)",key);
						AfxMessageBox(txt);
					}
				}
			}
		}

	}	
}

CString CStateMachine::UpdateReturnVars(CString incomm, ELEMDESC*paramdesc, DISPPARAMS params, variant_t returnval)
{
	CString txt,txt2;
	CString *sepvars;
	int count;
	int i,idx,arraycount;
	//VARIANTARG *retval;
	variant_t *val, *val2;

	i=incomm.Find("(");
	txt=incomm.Mid(i+1);
	txt.TrimRight();

	//check for return variable (syntax is "=>")
	sepvars=SeparateVars(txt,count,"=");

	if(count==-1)
	{
		txt.Format("Syntax error.");
		return txt;
	}

	if(count>1)
	{
		if(count!=2 || sepvars[1].Find(">")!=0)
		{
			txt="Improper syntax in command string (return variable)";
			return txt;
		}
		txt2=sepvars[1];
		txt2=txt2.Mid(1);  //eliminates the >
		txt2.TrimLeft();
		if(txt2[0]=='?')
		{
			txt2=txt2.Mid(1);
			if(m_vars->Lookup(txt2,(void *&)val))
			{
				switch(returnval.vt)
				{
				case VT_EMPTY:
					val->vt=VT_EMPTY;
					break;
				case VT_I2:
					*val=(short)returnval;
					break;
				case VT_I4:
					*val=(long)returnval;
					break;
				case VT_INT:
					val->vt=VT_I4;
					val->lVal=returnval.intVal;
					break;
				case VT_R4:
					*val=(float)returnval;
					break;
				case VT_R8:
					*val=(double)returnval;
					break;
				case VT_BSTR:
					*val=(_bstr_t)returnval;
					break;
				default:
					val->vt=returnval.vt;
					val->byref=returnval.byref;
				}
			}
		}
		else
		{
			txt="Improper syntax in command string (return variable)";
			return txt;
		}	
	}

	txt=sepvars[0];
	txt=txt.Left(txt.GetLength()-1);
	sepvars=SeparateVars(txt,count);

	if(count==-1)
	{
		txt="Syntax error.";
		return txt;
	}

	for(i=count-1;i>=0;i--)
	{
		idx=count-i-1;
		txt2=sepvars[i];

		if((paramdesc[i].paramdesc.wParamFlags & PARAMFLAG_FOUT) ||
			(paramdesc[i].paramdesc.wParamFlags==0 && params.rgvarg[idx].vt>VT_BYREF))
		{
			if(txt2[0]=='?')
			{
				txt2=txt2.Mid(1);
				if(m_vars->Lookup(txt2,(void *&)val))
				{
					if(m_vars->Lookup(txt2+"_arraycount",(void *&)val2))
						arraycount=val2->lVal;
					else
						arraycount=1;
					if(params.rgvarg[idx].vt!=val->vt+VT_BYREF)  //if this is a byref result, we don't need to record it (because it changed during the Invoke).
						ChangeType(params.rgvarg[idx],val,val->vt,arraycount,-1);
					else
						params.rgvarg[idx].vt=val->vt;  //this keeps DeleteInternal from trying to delete the byref result.
				}
				else
				{
					txt.Format("Unreadable Output (ByRef) Variable %s",txt2);
					return txt;
				}
			}
			else
			{
				if(txt2!="NULL")
				{
					txt.Format("Invalid output (not a variable or NULL)");
					return txt;
				}
			}
		}
	}

	txt="OK";
	return txt;
}

void CStateMachine::ResetVars()
{
	variant_t *val,*val2;
	VARTYPE vt;
	POSITION t;
	CString key,key2;
	int i,arraycount;
	
	t=m_vars->GetStartPosition();
	while(t!=NULL)
	{
		m_vars->GetNextAssoc(t,key,(void *&)val);
		if(key.Find("in")==0 || key.Find("retval")==0)
		{
			DeleteOneVar(val,key);
			continue;
		}

		vt=val->vt;
		if(key.Find("_arraycount")==-1)
		{
			if(vt>VT_BYREF)
			{
				key2=key+"_arraycount";
				m_vars->Lookup(key2,(void *&)val2);
				arraycount=val2->lVal;
			}

			switch(vt)
			{
			case VT_I2:
				val->iVal=0;
				break;
			case VT_I4:
				val->lVal=0;
				break;
			case VT_R4:
				val->fltVal=0.0f;
				break;
			case VT_R8:
				val->dblVal=0.0;
				break;
			case VT_BSTR:
				SysFreeString(val->bstrVal);
				val->bstrVal=SysAllocString(L"?");
				break;
			case VT_BYREF|VT_I2:
				for(i=0;i<arraycount;i++)
					val->piVal[i]=0;
				break;
			case VT_BYREF|VT_I4:
				for(i=0;i<arraycount;i++)
					val->plVal[i]=0;
				break;
			case VT_BYREF|VT_R4:
				for(i=0;i<arraycount;i++)
					val->pfltVal[i]=0.0f;
				break;
			case VT_BYREF|VT_R8:
				for(i=0;i<arraycount;i++)
					val->pdblVal[i]=0.0;
				break;				
			}
		}
	}
}

//implement this for arrays!
CString CStateMachine::InsertVars(CString in,int flag)
{
	CString out;
	int i;
	CString txt;
	CString key;
	variant_t *val;

	i=in.Find("?");
	if(i==-1)
		return in;


	out="";
	while(i!=-1)
	{
		out+=in.Left(i);
		key=in.Mid(i+1);
		key=key.SpanExcluding(" ';:.");
		in=in.Mid(i+key.GetLength()+1);

		if(key.Find("in")==0 && flag==1)
		{
			txt="?"+key;
		}
		else if(m_vars->Lookup(key,(void *&)val))
		{
			switch(val->vt)
			{
			case VT_BSTR:
				txt=val->bstrVal;
				break;
			case VT_I2:
				txt.Format("%d",val->iVal);
				break;
			case VT_I4:
				txt.Format("%d",val->lVal);
				break;
			case VT_R4:
				txt.Format("%.4g",val->fltVal);
				break;
			case VT_R8:
				txt.Format("%.6g",val->dblVal);
				break;
			case VT_ARRAY|VT_I2:
			case VT_ARRAY|VT_I4:
			case VT_ARRAY|VT_R4:
			case VT_ARRAY|VT_R8:
				txt="[]";
				break;				
			}
		}
		else
		{
//			txt.Format("Unknown Variable %s",key);
//			MessageBox(txt);
			txt="?"+key;
		}

		i=in.Find("?");
		out+=txt;
	}

	out+=in;
	return out;
}


//turns the data in the incoming variant to another type
void CStateMachine::ChangeType(variant_t *in,VARTYPE vt,int& arraycount,int arridx)
{
	CString txt,txt2;
	int i;
	if(in->vt==vt)
		return;

	if(in->vt>VT_BYREF)
	{
		if(vt<VT_BYREF)
		{
			arraycount=1;
			if(arridx==-1)
				arridx=0;
		}
	}

	switch(in->vt)
	{
	case VT_I2:
		txt.Format("%d",(short)*in);
		break;
	case VT_I4:
		txt.Format("%d",(long)*in);
		break;
	case VT_R4:
		txt.Format("%.5f",(float)*in);
		break;
	case VT_R8:
		txt.Format("%.10f",(double)*in);
		break;
	case VT_BSTR: //string
		txt=in->bstrVal;
		break;
	case VT_BYREF|VT_I2:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%d,",in->piVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%d,",in->piVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	case VT_BYREF|VT_I4:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%d,",in->plVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%d,",in->plVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	case VT_BYREF|VT_R4:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%.5f,",in->pfltVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%.5f,",in->pfltVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	case VT_BYREF|VT_R8:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%.10f,",in->pdblVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%.10f,",in->pdblVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	}

	if(vt>VT_BYREF && in->vt<VT_BYREF)
		txt="["+txt+"]";

	ReadOneVar(in,txt,vt,arraycount);
}

void CStateMachine::ChangeType(variant_t *in,VARIANT& out, VARTYPE vt, int& arraycount,int arridx)
{
	variant_t var;
	var.vt=out.vt;
	ChangeType(in, &var, vt, arraycount,arridx);
	out=var;
}

void CStateMachine::ChangeType(VARIANT in,variant_t* out, VARTYPE vt, int& arraycount,int arridx)
{
	variant_t var;
	var=in;
	ChangeType(&var, out, vt, arraycount,arridx);
}

void CStateMachine::ChangeType(variant_t *in,variant_t *out, VARTYPE vt, int& arraycount,int arridx)
{
	CString txt,txt2;
	int i;
	VARTYPE locvt;

	if(arridx>=0 && in->vt>VT_BYREF && arridx<arraycount)
		locvt=in->vt-VT_BYREF;
	else
		locvt=in->vt;

	if(locvt>VT_BYREF)
	{
		if(vt<VT_BYREF)
		{
			arraycount=1;
			if(arridx==-1)
				arridx=0;
		}
	}

	if(locvt==VT_INT)
		locvt=VT_I4;
	if(locvt==(VT_INT|VT_BYREF))
		locvt=VT_I4|VT_BYREF;

	switch(locvt)
	{
	case VT_I2:
		txt.Format("%d",(short)*in);
		break;
	case VT_I4:
		txt.Format("%d",(long)*in);
		break;
	case VT_R4:
		txt.Format("%.5f",(float)*in);
		break;
	case VT_R8:
		txt.Format("%.10f",(double)*in);
		break;
	case VT_BSTR: //string
		txt=in->bstrVal;
		break;
	case VT_BYREF|VT_I2:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%d,",in->piVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%d,",in->piVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	case VT_BYREF|VT_I4:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%d,",in->plVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%d,",in->plVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	case VT_BYREF|VT_R4:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%.5f,",in->pfltVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%.5f,",in->pfltVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	case VT_BYREF|VT_R8:
		txt2="[";
		if(arraycount==1)
			txt2.Format("%.10f,",in->pdblVal[arridx]);
		else
		{
			for(i=0;i<arraycount;i++)
			{
				txt.Format("%.10f,",in->pdblVal[i]);
				txt2+=txt;
			}
		}
		txt=txt2.Left(txt2.GetLength()-1)+"]";
		break;
	}

	if(vt>VT_BYREF && locvt<VT_BYREF)
		txt="["+txt+"]";

	ReadOneVar(out,txt,vt,arraycount);
}

CString CStateMachine::VarTypeToText(VARTYPE vt)
{
	CString txt;

	switch(vt)
	{
	case VT_I2:
		txt="a short";
		break;
	case VT_I4:
	case VT_INT:
		txt="an int";
		break;
	case VT_R4:
		txt="a float";
		break;
	case VT_R8:
		txt="a double";
		break;
	case VT_BSTR:
		txt="a string (BSTR)";
		break;
	case VT_BYREF|VT_I2:
		txt="a short*";
		break;
	case VT_BYREF|VT_I4:
	case VT_BYREF|VT_INT:
		txt="an int*";
		break;
	case VT_BYREF|VT_R4:
		txt="a float*";
		break;
	case VT_BYREF|VT_R8:
		txt="a double*";
		break;
	default:
		txt="(unknown type)";
	}

	return txt;
}

//This function takes the current command's string and parses it, trying to force the variables
//specified by the function call into the types given by paramdesc and retvaldesc. These two values 
//are obtained through a lot of complicated calls in LocalRunSM. The return values are an array of 
//paramters and a variant of the correct return type, which can be used in a call to 
//IDispatch::Invoke. Also returned is a CString that contains potential error messages. When the 
//return value is "OK", the function worked correctly.
CString CStateMachine::CreateParams(CString incomm, ELEMDESC* paramdesc, ELEMDESC retvaldesc, 
									int numparams, DISPPARAMS* params, variant_t * returnval)
{
	//general syntax of incomm should be: "FunctionName(param1,param2,...)=>?retval"

	CString txt,txt2,txt3;
	int i,j;
	unsigned int idx;
	variant_t *val,*val2;
	CString *sepvars;
	int count,arraycount;

	params->cArgs=0;
	i=incomm.Find("(");
	txt=incomm.Mid(i+1);
	txt.TrimRight();

	if(retvaldesc.tdesc.lptdesc!=NULL)
		returnval->vt=VT_BYREF|retvaldesc.tdesc.lptdesc->vt;
	else
		returnval->vt=retvaldesc.tdesc.vt;

	if(returnval->vt==VT_INT)
		returnval->vt=VT_I4;
	else if(returnval->vt==(VT_INT|VT_BYREF))
		returnval->vt=VT_I4|VT_BYREF;

	//check for return variable (syntax is "=>")
	sepvars=SeparateVars(txt,count,"=");
	if(count==-1)
	{
		txt="Syntax error.";
		return txt;
	}

	//at this point, sepvars[0] is "FunctionName(param1,param2,...)", 
	//sepvars[1] (if it exists) is ">?retval", and count tells us if
	//sepvars[1] exists.
	if(count>1)
	{
		//check for syntax mistake.
		if(count!=2 || sepvars[1].Find(">")!=0)
		{
			txt="Improper syntax in command string (return variable)";
			return txt;
		}
		//check to make sure the function to be invoked actually returns a value.
		if(retvaldesc.tdesc.vt==VT_EMPTY || retvaldesc.tdesc.vt==VT_NULL || retvaldesc.tdesc.vt==VT_VOID)
		{
			txt="Function does not return a value";
			return txt;
		}

		txt2=sepvars[1];
		txt2=txt2.Mid(1);  //eliminates the >
		txt2.TrimLeft();  // so now, txt2 should be "?retval"
		if(txt2[0]=='?')
		{
			if(txt2.Find("[")!=-1)
			{
				txt="Element of array not valid as return variable.";
				return txt;
			}

			//get the actual variable name, delete it and reinitialize it.
			txt2=txt2.Mid(1);  
			if(m_vars->Lookup(txt2,(void*&)val))  
				DeleteOneVar(val,txt2);
			val=new variant_t;
			val->vt=returnval->vt;
			m_vars->SetAt(txt2,(void *)val);
		}
		else
		{
			txt="Improper syntax in command string (return variable)";
			return txt;
		}	
	}
	//Now we are sure we have dealt with any return value, move on to the parameters.


	txt=sepvars[0];
	txt=txt.Left(txt.GetLength()-1);
	sepvars=SeparateVars(txt,count);
	if(count==-1)
	{
		txt="Syntax error.";
		return txt;
	}
	
	if(count!=numparams)
	{
		txt.Format("You have specified %d parameters, the function takes %d.",count,numparams);
		return txt;
	}

	params->cArgs=count;
	if(count>0)
		params->rgvarg=new VARIANTARG[params->cArgs];
	else
		params->rgvarg=NULL;

	for(i=count-1;i>=0;i--)
	{
		idx=count-i-1;
	
		//set the variable to the type given by typeinfo
		if(paramdesc[i].tdesc.lptdesc!=NULL)
			params->rgvarg[idx].vt=VT_BYREF|paramdesc[i].tdesc.lptdesc->vt;
		else
			params->rgvarg[idx].vt=paramdesc[i].tdesc.vt;
		
		if(params->rgvarg[idx].vt==VT_INT)
			params->rgvarg[idx].vt=VT_I4;
		else if(params->rgvarg[idx].vt==(VT_INT|VT_BYREF))
			params->rgvarg[idx].vt=VT_I4|VT_BYREF;

		//get the text
		txt2=sepvars[i];

		if(txt2[0]=='[')
		{
			if(!(paramdesc[i].paramdesc.wParamFlags & PARAMFLAG_FOUT))
			{
				if(!ReadOneVar(params->rgvarg[idx],txt2,params->rgvarg[idx].vt,arraycount))
				{
					txt.Format("Failed to read array (%s) into parameter %d: Improper format?",txt2,i+1);
					return txt;
				}
			}
			else
			{
				txt.Format("Cannot use typed-in array (%s) in output parameter (%d). If this is both an input and output parameter, assign array to variable.",txt2,i+1);
				return txt;
			}
		}
		else if(txt2=="NULL")
		{
			if(params->rgvarg[idx].vt>VT_BYREF)
				params->rgvarg[idx].byref=NULL;
			else
			{
				txt.Format("Tried to set non-pointer parameter (%d) to NULL.",i+1);
				return txt;
			}
		}
		else if(params->rgvarg[idx].vt>VT_BYREF)
		{
			//at this point there are two possibilities: It's a variable array, or a byref output variable.
			//No math is allowed in either of these two cases.
			if(txt2.FindOneOf("+-/*")!=-1)
			{
				txt.Format("No math allowed in array and byref parameters. Parameter %d",i+1);
				return txt;
			}
			if(txt2[0]!='?')
			{
				txt.Format("Attempt to store non-array in array parameter or a byref with an invalid return variable: %s Paramter %d",txt2,i+1);
				return txt;
			}
			if(txt2.Find("[")!=-1)
			{
				txt.Format("Cannot use array reference as a byref parameter. Parameter %d",i+1);
				return txt;
			}
			txt2=txt2.Mid(1);
			
			if(m_vars->Lookup(txt2,(void *&)val))
			{
				if(val->vt>VT_BYREF)
				{
					if(m_vars->Lookup(txt2+"_arraycount",(void*&)val2))
					{
						arraycount=val2->lVal;
						ChangeType(val,params->rgvarg[idx],params->rgvarg[idx].vt,arraycount,-1);
					}
					else
					{
						txt.Format("Error finding size of array variable %s, Parameter %d",txt2,i+1);
						return txt;
					}
				}
				else
				{
					if(val->vt!=params->rgvarg[idx].vt-VT_BYREF)
					{
						if(txt2.Find("in")==0 || txt2.Find("retval")==0)
							ChangeType(val,params->rgvarg[idx].vt-VT_BYREF,arraycount,-1);
						else
						{
							txt.Format("Attempt to change type of defined variable %s for byref parameter %d",txt2,i+1);
							return txt;
						}
					}

					params->rgvarg[idx].byref=&(val->lVal); //since the information in a variant is all stored in the
															//same place, this sets all the pointers in the parameter
															//to the address of the inforamtion in the state machine variable.
				}
			}
			else
			{
				if(txt2.Find("in")==0||txt2.Find("retval")==0)
				{
					//this is a new variable. If the _arraycount companion variable has already
					//been set, it is assumed to be an array, otherwise it is a non-array and 
					//the parameter should point to 
					val=new variant_t;
					if(!m_vars->Lookup(txt2+"_arraycount",(void*&)val2))
					{
						val->vt=params->rgvarg[idx].vt-VT_BYREF;
						m_vars->SetAt(txt2,(void *)val);
						params->rgvarg[idx].byref=&(val->lVal);
					}
					else
					{
						arraycount=val2->lVal;
						val->vt=params->rgvarg[idx].vt;

						//the following code initializes both the parameter and the new variable.
						txt="[";
						for(j=0;j<arraycount;j++)
							txt+="0,";
						txt.Left(txt.GetLength()-1);
						txt+="]";
						ReadOneVar(params->rgvarg[idx],txt,params->rgvarg[idx].vt,arraycount);
						ReadOneVar(val,txt,params->rgvarg[idx].vt,arraycount);

						m_vars->SetAt(txt2,(void *)val);					
					}
				}
				else
				{
					txt.Format("Unknown variable %s in parameter %d",txt2,i+1);
					return txt;
				}
			}
		}
		else
		{
			//Now the only options are non-byref, non-array, normal variables. This is only possible for non-output variables.
			if(paramdesc[i].paramdesc.wParamFlags & PARAMFLAG_FOUT)
			{
				txt.Format("Input/Output variable problem. Non-array, non-byref output variable. (parameter %d)",i+1);
				return txt;
			}
			
			params->rgvarg[idx]=TextToMath(txt2,params->rgvarg[idx].vt,txt);
			if(txt!="OK")
			{
				txt3.Format("Error in calculating parameter %d: %s",i+1,txt);
				return txt;
			}

		}
	}

	params->rgdispidNamedArgs=NULL;
	params->cNamedArgs=0;
	txt="OK";
	return txt;
}

UINT CStateMachine::RunSM(LPVOID param)
{
	CStateMachine *obj=(CStateMachine *)param;
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);
	obj->LocalRunSM();
	return 0;
}

void CStateMachine::LocalRunSM()
{
	CString txt,txt2;
	IComponent* agentcomp;
	IDispatch* agentdisp;
	ILocator* locallocator;
	BSTR component;
	BSTR function;
	DISPID fnid;
	DISPPARAMS params={NULL,NULL,0,0};
	ITypeInfo * typeinfo;
	variant_t returnval;
//	int numparams;
	FUNCDESC * funcd;
	TYPEATTR * typeattr;
//	ELEMDESC * paramdesc;
//	ELEMDESC retvaldesc;
	UINT ArgError;
	HRESULT hRes=0;
	BOOL quit=FALSE;
	int next;
	_com_error *err;
	
	
	int tidx,i;
	UINT j;

	hRes=CoGetInterfaceAndReleaseStream(m_LocStream,IID_ILocator,(void **)&locallocator);
	if(hRes!=0)
	{
		err=new _com_error(hRes);
		txt.Format("Immediate Stop\r\nCould not create copy of locator pointer.\r\nError: (%x) %s",hRes,err->ErrorMessage());
		AfxMessageBox(txt);
		m_currstate=-1;
		delete err;
		return;
	}

	tidx=FindState(m_currstate);
	if(tidx==-1)
	{
		txt.Format("Immediate Stop\r\nCould not find state %d.",m_currstate);
		AfxMessageBox(txt);
		m_currstate=-1;
		return;
	}
	state *currstate=m_fsm[tidx];
	command *comm;

	do //while(currstate->name!="Stop")
	{
		for(i=0;i<currstate->commands.GetSize();i++)
		{
			comm=currstate->commands[i];
			component=comm->componentname.AllocSysString();
			hRes=locallocator->Locate(component,&agentcomp);
//			agentcomp=comm->component;
			if(agentcomp==NULL || hRes!=0)
			{
				txt.Format("Quitting\r\nCannot locate component: %s\r\nIn state: %s",comm->componentname,currstate->name);
				if(hRes!=0)
				{
					err=new _com_error(hRes);
					txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
					txt+=txt2;
					delete err;
				}
				AfxMessageBox(txt);
				m_signal="Stop";
				break;
			}
			hRes=agentcomp->QueryInterface(IID_IDispatch,(void **)&agentdisp);
			if(agentdisp==NULL || hRes!=0)
			{
				txt.Format("Quitting\r\nUnable to get IDispatch interface: %s\r\nIn state: %s",comm->componentname,currstate->name);
				if(hRes!=0)
				{
					err=new _com_error(hRes);
					txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
					txt+=txt2;
				}
				AfxMessageBox(txt);
				SysFreeString(component);
				m_signal="Stop";
				break; 
			}
			
			function=comm->fnname.AllocSysString();
			hRes=agentdisp->GetIDsOfNames(IID_NULL,&function,1,0,&fnid);
			if(fnid==-1 || hRes!=0)
			{
				txt.Format("Quitting\r\nFunction not found: %s\r\nIn state: %s",comm->function,currstate->name);
				if(hRes!=0)
				{
					err=new _com_error(hRes);
					txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
					txt+=txt2;
					delete err;
				}
				AfxMessageBox(txt);
				SysFreeString(component);
				SysFreeString(function);
				m_signal="Stop";
				break;
			}

			hRes=agentdisp->GetTypeInfo(0,LOCALE_SYSTEM_DEFAULT,&typeinfo);
			if(hRes!=0)
			{
				err=new _com_error(hRes);
				txt.Format("Quitting\r\nUnable to get type information of component:%s\r\nIn state: %s",comm->componentname,currstate->name);
				txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
				txt+=txt2;
				delete err;
				AfxMessageBox(txt);
				SysFreeString(component);
				SysFreeString(function);
				if(typeinfo!=NULL)
					typeinfo->Release();
				m_signal="Stop";
				break;
			}
			hRes=typeinfo->GetTypeAttr(&typeattr);
			if(hRes!=0)
			{
				err=new _com_error(hRes);
				txt.Format("Quitting\r\nUnable to get parameter descriptions of function:%s\r\nIn state: %s",comm->function,currstate->name);
				txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
				txt+=txt2;
				delete err;
				AfxMessageBox(txt);
				typeinfo->ReleaseFuncDesc(funcd);
				SysFreeString(component);
				SysFreeString(function);
				if(typeattr!=NULL)
					typeinfo->ReleaseTypeAttr(typeattr);
				typeinfo->Release();
				m_signal="Stop";
				break;
			}
			
			int i=6;
			do
			{
				if(i>6)
					typeinfo->ReleaseFuncDesc(funcd);
				i++;
				hRes=typeinfo->GetFuncDesc(i,&funcd);
			}while(i<typeattr->cFuncs && hRes==0 && funcd->memid!=fnid);

			if(hRes!=0 || i==typeattr->cFuncs)
			{
				txt.Format("Quitting\r\nUnable to get parameter descriptions of function:%s\r\nIn state: %s",comm->function,currstate->name);
				if(hRes!=0)
				{
					err=new _com_error(hRes);
					txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
					txt+=txt2;		
					delete err;
				}
				AfxMessageBox(txt);
				SysFreeString(component);
				SysFreeString(function);
				if(funcd!=NULL)
					typeinfo->ReleaseFuncDesc(funcd);
				typeinfo->ReleaseTypeAttr(typeattr);
				typeinfo->Release();
				m_signal="Stop";
				break;
			}
			
			txt2=CreateParams(comm->function,funcd->lprgelemdescParam,funcd->elemdescFunc,funcd->cParams,&params,&returnval);
			if(txt2!="OK")
			{
				txt.Format("Quitting\r\nUnable to create parameters for call of function: %s\r\nIn state: %s\r\nError:%s",comm->function,currstate->name,txt2);
				AfxMessageBox(txt);
				SysFreeString(component);
				SysFreeString(function);
				typeinfo->ReleaseFuncDesc(funcd);
				typeinfo->ReleaseTypeAttr(typeattr);
				typeinfo->Release();
				if(params.rgvarg!=NULL)
				{
					delete params.rgvarg;
					params.cArgs=0;
					params.rgvarg=NULL;
				}
				m_signal="Stop";
				break;				
			}

			try
			{
				hRes=agentdisp->Invoke(fnid,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD,&params,&returnval,NULL,&ArgError);
			}
			catch(...)
			{
				txt.Format("Immediate Stop. Unhandled Exception while calling function.\r\nFunction: %s\r\nComponent: %s\r\nIn State: %s",comm->function,comm->componentname,currstate->name);
				AfxMessageBox(txt);
				SysFreeString(component);
				SysFreeString(function);
				typeinfo->ReleaseFuncDesc(funcd);
				typeinfo->ReleaseTypeAttr(typeattr);
				typeinfo->Release();
				quit=TRUE;
				break;
			}
			if(hRes!=0)
			{
				err=new _com_error(hRes);
				txt.Format("Quitting\r\nError calling function.\r\nFunction: %s\r\nComponent: %s\r\nIn State: %s",comm->function,comm->componentname,currstate->name);
				txt2.Format("\r\nError: (%x) %s",hRes,err->ErrorMessage());
				txt+=txt2;		
				delete err;
				AfxMessageBox(txt);
				SysFreeString(component);
				SysFreeString(function);
				typeinfo->ReleaseFuncDesc(funcd);
				typeinfo->ReleaseTypeAttr(typeattr);
				typeinfo->Release();
				if(params.rgvarg!=NULL)
				{
					for(j=0;j<params.cArgs;j++)
						DeleteInternal(&(params.rgvarg[j]));
					delete params.rgvarg;
					params.cArgs=0;
					params.rgvarg=NULL;
				}
				m_signal="Stop";
				break;							
			}

			
			if(params.cArgs!=0 || returnval.vt!=VT_EMPTY)
			{
				txt2=UpdateReturnVars(comm->function,funcd->lprgelemdescParam,params,returnval);
				if(txt2!="OK")
				{
					txt.Format("Quitting\r\nUnable to update return variables of function: %s\r\nIn state: %s\r\nError:%s",comm->function,currstate->name,txt2);
					AfxMessageBox(txt);
					SysFreeString(component);
					SysFreeString(function);
					typeinfo->ReleaseFuncDesc(funcd);
					typeinfo->ReleaseTypeAttr(typeattr);
					typeinfo->Release();
					if(params.rgvarg!=NULL)
					{
						for(j=0;j<params.cArgs;j++)
							DeleteInternal(&(params.rgvarg[j]));
						delete params.rgvarg;
						params.cArgs=0;
						params.rgvarg=NULL;
					}
					m_signal="Stop";
					break;				
				}
			}

			SysFreeString(component);
			SysFreeString(function);
			typeinfo->ReleaseFuncDesc(funcd);
			typeinfo->ReleaseTypeAttr(typeattr);
			typeinfo->Release();
			if(params.rgvarg!=NULL)
			{
				for(j=0;j<params.cArgs;j++)
					DeleteInternal(&(params.rgvarg[j]));
				delete params.rgvarg;
				params.cArgs=0;
				params.rgvarg=NULL;
			}
		}
	
		if(quit==TRUE)
		{
			break;
		}
	
		if(currstate->name!="Stop")
		{
			next=FindNextState();
			if(next==-1)
			{
				m_wait=TRUE;
				return;
			}
			else
			{
				m_currstate=next;
			}

			tidx=FindState(m_currstate);
			currstate=m_fsm[tidx];
		}
	}
	while(currstate->name!="Stop");


	m_currstate=-1;
	m_reset=FALSE;

	return;
}

//Returns the m_fsm index whose associated state that has the input shapeid
int CStateMachine::FindState(int shapeid)
{
	int i;
	for(i=0;i<m_fsm.GetSize();i++)
	{
		if(shapeid==m_fsm[i]->shapeid)
			return i;
	}
	return -1;
}

STDMETHODIMP CStateMachine::get_FileName(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	_bstr_t temp;
	temp=(LPCTSTR)m_filename;

	*pVal=temp.copy();

	return S_OK;
}

STDMETHODIMP CStateMachine::put_FileName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_filename=newVal;
	return S_OK;
}

STDMETHODIMP CStateMachine::get_NumStates(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal=m_fsm.GetSize();
	return S_OK;
}

STDMETHODIMP CStateMachine::LoadSM()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if(!m_filename.IsEmpty())
		LoadFile();
	else
	{
		AfxMessageBox("No file specified, cannot load");
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CStateMachine::Start()
{
	HRESULT hRes;
	int boxret;
	if(m_fsm.GetSize()==0)
	{
		boxret=AfxMessageBox("State Machine not loaded. Load now?",MB_YESNO);
		if(boxret==IDYES)
		{
			hRes=LoadSM();
			if(hRes!=S_OK)
				return S_OK;
		}
	}

	m_currstate=m_firstconn->endnum;
	UpdateVars(m_firstconn);

//if(Reconnect()==S_OK)
	hRes=CoMarshalInterThreadInterfaceInStream(IID_ILocator,m_Locator,&m_LocStream);
	if(hRes==0)
		AfxBeginThread(RunSM,this);
	else
	{
		AfxMessageBox("Threading Problem. Cannot transfer Agent Locator.\r\nError Code: 0x%x",hRes);
	}
	
	return S_OK;
}



STDMETHODIMP CStateMachine::Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Signal(L"Reset");

	return S_OK;
}

STDMETHODIMP CStateMachine::Stop()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Signal(L"Stop");

	return S_OK;
}

STDMETHODIMP CStateMachine::get_CurrentState(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	_bstr_t temp;
	int tidx;

	if(m_currstate!=-1)
	{
		tidx=FindState(m_currstate);
		if(m_wait==TRUE)
			temp=(LPCTSTR)(m_fsm[tidx]->name+", Waiting");
		else
			temp=(LPCTSTR)m_fsm[tidx]->name;		
	}
	else
	{
		if(m_fsm.GetSize()==0)
			temp="Unloaded";
		else if(m_wait==TRUE)
		{
			m_wait=FALSE;
			temp="Stopped";
		}
		else
			temp="Stopped";
	}

	*pVal=temp.copy();

	return S_OK;
}




STDMETHODIMP CStateMachine::Signal(BSTR signal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	int nextstate;
	if(m_wait==TRUE)
	{
		m_signal=signal;
		nextstate=FindNextState();
		if(nextstate!=-1)
		{
			m_currstate=nextstate;
			m_wait=FALSE;
			HRESULT hRes=CoMarshalInterThreadInterfaceInStream(IID_ILocator,m_Locator,&m_LocStream);
			if(hRes==0)
				AfxBeginThread(RunSM,this);
			else
			{
				AfxMessageBox("Threading Problem. Cannot transfer Agent Locator.\r\nError Code: 0x%x",hRes);
			}
		}
	}
	else
	{
		m_signal=signal;
	}

	return S_OK;
}


/*
STDMETHODIMP CStateMachine::Reconnect()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	int i,j;
	state *stt;
	command *comm;
	HRESULT retval=S_OK;
	CString txt;
	
	if(m_currstate==-1)
		return S_OK;

	for(i=0;i<m_fsm.GetSize();i++)
	{
		stt=m_fsm[i];
		for(j=0;j<stt->commands.GetSize();j++)
		{
			comm=stt->commands[j];
			m_Locator->Locate(comm->componentname.AllocSysString(),&(comm->component));
			if(comm->component==NULL)
			{
				txt.Format("Unable to find component: %s\r\nIn state: %s",comm->componentname,stt->name);
				AfxMessageBox(txt);
				retval=E_FAIL;
			}
		}
	}

	return retval;
}
*/

STDMETHODIMP CStateMachine::get_ManualSignalString(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal=m_manualsignal.AllocSysString();

	return S_OK;
}

STDMETHODIMP CStateMachine::put_ManualSignalString(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_manualsignal=newVal;

	return S_OK;
}

STDMETHODIMP CStateMachine::ManualSignal()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if(!m_manualsignal.IsEmpty())
		Signal(m_manualsignal.AllocSysString());

	return S_OK;
}

STDMETHODIMP CStateMachine::Wait(int time)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Sleep(time);

	return S_OK;
}

STDMETHODIMP CStateMachine::UpdateManager(BSTR Interface, VARIANT *DATA)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}
