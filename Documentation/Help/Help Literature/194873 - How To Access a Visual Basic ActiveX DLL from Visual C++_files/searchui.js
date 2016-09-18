
var d = document;
PageLoaded = false;
var uplevel = false;

if(document.createAttribute) uplevel = true;;

function gsfx_drawselectlist(po, co, pn){
	
	if(failure==0){
		var lcid ;
		var potl;
		var catalog = false;

		if(po){
			catalog = true;
			if(po.type){
				potl = po.type.toLowerCase();
				if(potl.indexOf("select") > -1) ctl = po.selectedIndex;
				else ctl = 0;
			}else if(po.length){
				potl = "radio";
				ctl = -1;
				for(i=0; i<po.length; i++){
					if(po[i].checked){
						ctl = i;
						
						} 
				}
				if(ctl < 0) ctl = 0;
				
				
				
			}
		}else ctl = 0;
		
		var si = 0;
		var ms = true;

		if(po){
			if(potl.indexOf("select") > -1){
				if(po.options[ctl].value.indexOf("PRODLISTSRC=OFF") > -1) ms = false;
					catalogEntry = po[ctl].value;
			}else if(potl.indexOf("hidden") > -1){
				catalogEntry = po.value;
				if(po.value.indexOf("PRODLISTSRC=OFF") > -1) ms = false;
			}else if(potl == "radio"){
				catalogEntry = po[ctl].value;
				
				DisplayScopeElement(po[ctl].getAttribute("MT"),po[ctl].getAttribute("CC"),po);	
				if(po[ctl].value.indexOf("PRODLISTSRC=OFF") > -1) ms = false;
			}
			j = catalogEntry.indexOf('=');
			lcid = catalogEntry.substring(j+1,catalogEntry.indexOf('&'));		
		}
		
		
		var arraylen;
		if(co && co.options){
			if(catalog) arraylen = eval(pn+"_"+co.name+"_"+lcid+'.length;');
			else arraylen = eval(pn+"_"+co.name+"_"+ctl+'.length;');
			
			if(co.children && navigator.appVersion.indexOf("Macintosh") < 0){
				while(co.children.length > 0){
					for(i=0;i<co.children.length;i++){
						co.remove(co.children[i]);
					}
				}
			}else for(i=0;i<co.options.length;i++){co.options[i] = null;}
		}
	
		
		var initial = 0;
		if(co && co.options){
			if(ms){
			if(po){
			tval = fetchcookieval(lcid+"_Prod")
			if(tval != 'blank' && tval != '')
			{ 	
				tval = tval.substring(0,tval.length-1);
				var productlist = new Array();
				productlist = tval.split("$");
				
				if(productlist.length > 0)
				{
					productlist = productlist.reverse();
	
					for(i=0 ;i<productlist.length ;i++)
					{
						var productentry = new Array();
						productentry = productlist[i].toString().split("|");
						productName = unescape(productentry[0]);
						productID	= unescape(productentry[1]);
						ts1 = productName + "\",\"" + productID;
						eval("co.options[i] = new Option(\""+ts1+"\")");	
					}	
					ts1 = "----------------------------------------------------------\",\"line";	
					eval("co.options[i] = new Option(\""+ts1+"\")");		
					initial = i+1;
			}
			}
			
			
			}
				
				
				for(i=0;i<arraylen;i++){
					if(catalog)	ts = eval(pn+"_"+co.name+"_"+lcid+'['+i+']');
					else ts = eval(pn+"_"+co.name+"_"+ctl+'['+i+']');
					
					eval("co.options[i+initial] = new Option(\""+ts+"\")");
					co.disabled = false;
				}
			
			if(catalog) si = eval(pn + "_" + co.name + "_" + lcid + "default");		
			else si = eval(pn + "_" + co.name + "_" + ctl + "default");		
			
			}else{
				co.options[0] = new Option("", "");
				si = 0;
				co.disabled = true;
			}
			
			co.selectedIndex = si;
		}
	}
}

function DisplayScopeElement(mt,cc,catalogElem)
{

	var hideMT ,hideCC ;
	
	if(mt != null && mt.length > 0)
	{
		mtrow = d.getElementById("InMT_row");
		mtrow1 = d.getElementById("InMT_row1");
		if(mtrow && mtrow1)
		{		
			if(mt.toLowerCase() == "false")
			{	
				mtrow.style.display = "none";
				mtrow1.style.display = "none";
				hideMT = true;		
			}
			else
			{
				mtrow.style.display = "block";
				mtrow1.style.display = "block";
			}
		}
	}
	else hideMT = true;
	if(cc != null && cc.length > 0)
	{
		ccrow = d.getElementById("InCC_row");
		ccrow1 = d.getElementById("InCC_row1");
		if(ccrow && ccrow1)
		{
			if(cc.toLowerCase() == "false")
			{	
				ccrow.style.display = "none";
				ccrow1.style.display = "none";
				hideCC = true;		
			}
			else
			{
				ccrow.style.display = "block";
				ccrow1.style.display = "block";

			}
		}
	}
	else hideCC = true;
	
		var scope = document.getElementById("Scope_row");
		if(scope) 
		{
			if(hideMT & hideCC) scope.style.display = "none"; 
			else scope.style.display = "block"; 
		}
	
	
}



function getUrlParam(param){
	var rv = "";
	var q = new Array();
	if(param.indexOf("_") > 0) {
		argParam = param.split("_")[1];
	} else {
		argParam = param;
	}
	var here = document.location.href;	
	q = here.split("?");
	if(q.length > 1){
		var argarray = new Array();
		argarray = q[1].toString().split("&");
		var keyval;
		for(i=0; i<argarray.length; i++){
			keyval = argarray[i].toString().split("=");
			if(keyval[0].toLowerCase() == argParam.toLowerCase()){
				if(uplevel)	rv = decodeURI(keyval[1]);				else rv = unescape(keyval[1]);
				break;
			}
		}
	}
	
	if(rv == "") {
		rv = unescape(fetchcookieval(param));
		if(rv == "blank") { rv = ""; }
	}
	return rv;
}


function GetContentIDEntry(ct)
{
var cdid = "";
if(ct != 'blank' && ct != '') { 
	cdid = ct.split("&")[1].split("=")[1];
}		
return cdid ;

}


function AppendSelect(catalogElement,selectElement,webpartName,selectName){
gsfx_drawselectlist(catalogElement,selectElement,webpartName)
tval = fetchcookieval(webpartName + '_' + selectName )
if(tval != "blank"){
	for(i=0; i<selectElement.options.length; i++){
		if(selectElement.options[i].value == unescape(tval)){
			selectElement.selectedIndex = i;
			break;
		}
	}
}

}

function AppendRadio(radioElement,webpartName,radioName){

tval = fetchcookieval(webpartName + '_' + radioName )
if(tval != "blank"){
	for(i=0; i<radioElement.length; i++){
		if(radioElement[i].value == unescape(tval)){
			radioElement[i].checked = true;
			radioElement[i].click();
			break;
		}
	}
}

}

function AppendText(textElement,webpartName,textName,defaultstring)
{
	if(textElement)
	{
		tval = fetchcookieval(webpartName + '_' + textName)
			if(tval != 'blank' && tval != '')
			{ 
				textElement.value =UnicodeFixup(unescape(tval)); 
			} 
			else 
			{ 
				textElement.value = defaultstring;
			}
	}		
}

function AdvSrchText(textElement,webpartName,textName){
	var arg = getUrlParam(webpartName + '_' + textName);
	if(arg != ""){
		textElement.value = arg;
	}

}

function AdvSrchSelect(catalogElement,selectElement,webpartName,selectName){

gsfx_drawselectlist(catalogElement,selectElement,webpartName)
var arg = getUrlParam(webpartName + "_" + selectName);
if(arg != ""){
	for(i=0; i<selectElement.options.length; i++){
		if(selectElement.options[i].value.toLowerCase() == arg.toLowerCase())
		{	selectElement.selectedIndex = i;
			break;
		}
	}
}

}

function AdvSrchCheckBox(catalogElement,scopeName)
{
	cbElement   = document.getElementById(scopeName);
	
	if(cbElement)
	{
		if(catalogElement)
		{
			var contentID;
			
			if(catalogElement.length > 0)
			{
				for(i=0;i<catalogElement.length;i++)
				{
					if(catalogElement[i].checked) contentID = GetContentIDEntry(catalogElement[i].value);
				}
			}
			else
			{
				contentID = GetContentIDEntry(catalogElement.value);	
			}	
			tval = fetchcookieval(scopeName + "_" +  contentID);
						
			if(tval != 'blank' && tval != '')
			{
				if(tval == "0") cbElement.checked = false;
				else cbElement.checked = true;
			}
		
		}
	
	}

}


function AdvSrchRadio(radioElement,webpartName,radioName){
var arg = getUrlParam(webpartName + "_" + radioName);
if(arg != ""){
	for(i=0; i<radioElement.length; i++){
		if(radioElement[i].value.toLowerCase() == arg.toLowerCase())
		{
			radioElement[i].checked = true;
			radioElement[i].click();
			break;
		}
	}
}
}

function SubmitSelect(selectElement,webpartName,selectName)
{
	srch_setcookieval(webpartName + "_" + selectName,escape(selectElement.options[selectElement.selectedIndex].value));
}


function SubmitCheckBox(cbElement,catalogElement,hdncbElement,scopeName,defvalue)
{
	var scopeRow = d.getElementById(scopeName +"_row");
	if(scopeRow)
	{
		if(scopeRow.style.display == "block" | scopeRow.style.display == "")
		{
			if(cbElement.checked) hdncbElement.value = "true";
			else hdncbElement.value = "false";
		}	
		else hdncbElement.value = defvalue ;
	}	
	
	if(catalogElement)
	{
		var contentID;
		if(catalogElement.length > 0)
		{
			for(i=0;i<catalogElement.length;i++)
			{
				if(catalogElement[i].checked) contentID = GetContentIDEntry(catalogElement[i].value);
			}
		}
		else contentID = GetContentIDEntry(catalogElement.value);
		
		if(cbElement.checked) setcookieval(scopeName + "_" +  contentID,"1");
		else setcookieval(scopeName + "_" +  contentID,"0");

	}	


}


function SubmitText(textElement,leftTextElement,webpartName,textName,defaultstring,productElement,catalogElement)
{
if(productElement && productElement.options)
{
	
	var prodName = productElement.options[productElement.selectedIndex].text;
	var prodID = productElement.options[productElement.selectedIndex].value;
	var lcid = "1033";
	var catSelected = -1;
	var catalogEntry ;
	if(prodID != '' && (prodID.toLowerCase().indexOf("msall") < 0))
	{ 
		if(catalogElement)
		{
			
			if(catalogElement.length)
			{
				for(i=0; i<catalogElement.length; i++){
					if(catalogElement[i].checked) catSelected = i;
				}
					
					if(catSelected < 0) catSelected = 0;
					catalogEntry = catalogElement[catSelected].value;	
						
			}
			else
			{
				catalogEntry = catalogElement.value;
			
			}
		}
		
		j = catalogEntry.indexOf('=');
		lcid = catalogEntry.substring(j+1,catalogEntry.indexOf('&'));
		tval = fetchcookieval(lcid + "_Prod")
	
		if(tval != 'blank' && tval != '')
		
		{ 
			if(tval.indexOf(prodID + '$') < 0)
			{ 
				//Check if no. of products in cookie > 10
				if(tval.split("$").length > 10)
				{
					
					tval = tval.substring(tval.indexOf('$') + 1 ,tval.length);
				}
				setcookieval(lcid + "_Prod",tval + escape(prodName) + '|' + escape(prodID) + '$');	
									
			}
		}
		else
		{
			setcookieval(lcid +"_Prod",escape(prodName) + '|' + escape(prodID) + '$');
		}
	}
}
	if(leftTextElement.value == defaultstring) leftTextElement.value = '';
	textElement.value = leftTextElement.value;
	srch_setcookieval(webpartName+ "_" + textName, UnicodeFixup(escape(leftTextElement.value)));
}



function SubmitRadio(radioElement,webpartName,radioName)
{
for(i=0;i<radioElement.length;i++){
		if(radioElement[i].checked){
			srch_setcookieval(webpartName + '_' + radioName,escape(radioElement[i].value));
			
		}
	}
}

function ChangeLink(prd)
{
	if(document.getElementById)
	{
		var advLink = document.getElementById("advLinkRt");
		if(advLink) advLink.href = advLink.href + "&Product=" + prd;
	}
}

