function triggerInit()
{
	var MiliDay = 86400000;
	var maturity = 1;
	var curDate = new Date();
	var visits = fetchcookieval(CookieDef);
	var parts = visits.split('_');
	if(null == visits || parts.length != 2 || isNaN(parts[0]))
	{
		setcookieval(CookieDef, '1_' + (curDate.getTime()/MiliDay - Exp));
		return false;
	}
	else
	{
		var origDate = parseInt(parts[1]);
		visits = parseInt(parts[0]);//alert(visits + ";" + maturity + ";" + (curDate.getTime()/MiliDay - Exp) + ";" + origDate);
		if
		(
			((!isNaN(Freq)) && (Freq > 0)) && ((visits >= maturity) && ((curDate.getTime()/MiliDay - Exp) >= origDate) && (Math.floor(Math.random() * Freq) == 0))
		)
		{
			setcookieval(CookieDef, visits+1 + '_' + curDate.getTime()/MiliDay);
			return true;
		}
		else
		{
			setcookieval(CookieDef, visits+1 + '_' + parts[1]);
			return false;
		}
	}
}

function fireTrigger(SurveyURL)
{
	if(triggerInit())
	{
		//if((navigator.userAgent.indexOf("MSIE") == -1 || navigator.userAgent.indexOf("Windows") == -1 || navigator.appVersion.substring(0,1) < 4)){return;}
		var sSiteID = '', sSiteRegionID = '', sReferringURL = '', P0 = '', P1 = '', P2 = '', P3 = '', P4 = '', P5 = '', P6 = '', P7 = '', P8 = '', P9 = '';		
		if(fireTrigger.arguments.length > 1){sSiteID = fireTrigger.arguments[1];}
		if(fireTrigger.arguments.length > 2){sSiteRegionID = fireTrigger.arguments[2];}
		if(fireTrigger.arguments.length > 3){sReferringURL = fireTrigger.arguments[3];}
		if(fireTrigger.arguments.length > 4){P0 = fireTrigger.arguments[4];}
		if(fireTrigger.arguments.length > 5){P1 = fireTrigger.arguments[5];}
		if(fireTrigger.arguments.length > 6){P2 = fireTrigger.arguments[6];}
		if(typeof(dialogstate) != "undefined")
		{
			P3 = dialogstate.replace("&lt;DialogState dialogID=&quot;","").substring(0,dialogstate.replace("&lt;DialogState dialogID=&quot;","").indexOf("&quot;"))
			var re = /\d+&quot; sessionID=&quot;/
			P4 = dialogstate.replace("&lt;DialogState dialogID=&quot;","").replace(re,"").substring(0,dialogstate.replace("&lt;DialogState dialogID=&quot;","").replace(re,"").indexOf("&quot;"))
		}
		if(fireTrigger.arguments.length > 9){P5 = fireTrigger.arguments[9];}
		if(fireTrigger.arguments.length > 10){P6 = fireTrigger.arguments[10];}
		
		var cv;
		var dg = "";
		var p1 = "guid=";
		var p2 = "&guid=";
		var gl = 32;	
		cv = fetchcookieval("MC1").toLowerCase();
		if(cv == "blank") cv = fetchcookieval("MC2").toLowerCase();
		if(cv != "blank")	{
			if(cv.substr(0,p1.length) == p1) { dg = cv.substr(p1.length, gl); }
			else if(cv.indexOf(p2) > -1){ dg = cv.substr(cv.indexOf(p2) + p2.length, gl); }
		}
		P6 = dg;
		
		if(fireTrigger.arguments.length > 11){P7 = fireTrigger.arguments[11];}
		if(fireTrigger.arguments.length > 12){P8 = fireTrigger.arguments[12];}
		if(fireTrigger.arguments.length > 13){P9 = fireTrigger.arguments[13];}	
		
		var fullURL = SurveyURL + '&site=' + sSiteID + '&SurveyStyle=' + SurveyStyle + '&siteregion=' + sSiteRegionID + '&url=' + sReferringURL + '&p0=' + P0 + '&p1=' + P1 + '&p2=' + P2 + '&p3=' + P3 + '&p4=' + P4 + '&p5=' + P5 + '&p6=' + P6 + '&p7=' + P7 + '&p8=' + P8 + '&p9=' + P9;
		
		if (EmailStyle == 1)
		{
			fullURL = fullURL + '&emailsurveyid=' + EmailSurveyID + '&sessionid=-1';
			/*
			var emailaddress = window.prompt(IntroText, "");
			if (emailaddress == null || emailaddress == "")
			{
				//TODO: handle null?
			}
			else
			{
				// put the responding window invisible place and just close it.		
				if (emailaddress.length > 256)
					emailaddress = emailaddress.substring(0, 256);
				var tempwindow = window.open(fullURL + "&emailaddress=" + emailaddress + "&sessionid=-1&INVITEACTION=PERSIST", '', 'height=100,width=100,menubar=no,location=no,toolbar=no,status=no,left=' + (screen.width + 500) + ',top=' + (screen.height + 500)); 
				//tempwindow.close();				
			}
			return;
			*/
		}
		if (DisplayIntroPage != '1')
			fullURL = fullURL + '&showpage=1';
		//TODO: change "full screen" or "embedded" as it appears in surveytrigger.config	
		if (SurveyStyle == null){		
			SurveyStyle = "popup";
		}
		SurveyStyle = SurveyStyle.toLowerCase();
		if (SurveyStyle == 'full screen'){		
			window.open(fullURL, '_blank', 'resizable=yes,scrollbars=yes,menubar=no,location=no,toolbar=no,status=no,left=0,top=0,height=' + (screen.height-5)+ ',width=' + (screen.width-5));
		}
		else if (SurveyStyle == "embedded")
			window.location.href=fullURL;
		else if (EmailStyle == 1)
			window.open(fullURL, '_blank', 'resizable=yes,scrollbars=yes,menubar=no,location=no,toolbar=no,status=no,left=0,top=0,height=300,width=500');
		else
			window.open(fullURL, '_blank', 'resizable=yes,scrollbars=yes,menubar=no,location=no,toolbar=no,status=no,left=0,top=0,height=500,width=725');
	}
}

function ShowSurveyWindow(SurveyURL)
{
	var sSiteID = '', sSiteRegionID = '', sReferringURL = '', P0 = '', P1 = '', P2 = '', P3 = '', P4 = '', P5 = '', P6 = '', P7 = '', P8 = '', P9 = '';	
	if(ShowSurveyWindow.arguments.length > 1){sSiteID = ShowSurveyWindow.arguments[1];}
	if(ShowSurveyWindow.arguments.length > 2){sSiteRegionID = ShowSurveyWindow.arguments[2];}
	if(ShowSurveyWindow.arguments.length > 3){sReferringURL = ShowSurveyWindow.arguments[3];}
	if(ShowSurveyWindow.arguments.length > 4){P0 = ShowSurveyWindow.arguments[4];}
	if(ShowSurveyWindow.arguments.length > 5){P1 = ShowSurveyWindow.arguments[5];}
	if(ShowSurveyWindow.arguments.length > 6){P2 = ShowSurveyWindow.arguments[6];}
	if(ShowSurveyWindow.arguments.length > 7){P3 = ShowSurveyWindow.arguments[7];}
	if(ShowSurveyWindow.arguments.length > 8){P4 = ShowSurveyWindow.arguments[8];}
	if(ShowSurveyWindow.arguments.length > 9){P5 = ShowSurveyWindow.arguments[9];}
	//if(ShowSurveyWindow.arguments.length > 10){P6 = ShowSurveyWindow.arguments[10];}	
	var cv;
	var dg = "";
	var p1 = "guid=";
	var p2 = "&guid=";
	var gl = 32;	
	cv = fetchcookieval("MC1").toLowerCase();
	if(cv == "blank") cv = fetchcookieval("MC2").toLowerCase();
	if(cv != "blank")	{
		if(cv.substr(0,p1.length) == p1) { dg = cv.substr(p1.length, gl); }
		else if(cv.indexOf(p2) > -1){ dg = cv.substr(cv.indexOf(p2) + p2.length, gl); }
	}
	P6 = dg;
			
	if(ShowSurveyWindow.arguments.length > 11){P7 = ShowSurveyWindow.arguments[11];}
	if(ShowSurveyWindow.arguments.length > 12){P8 = ShowSurveyWindow.arguments[12];}
	if(ShowSurveyWindow.arguments.length > 13){P9 = ShowSurveyWindow.arguments[13];}
	// NOTE: if added more or less Pi parameter, remember to change SurveyDataManager::DefaultPParameterLength, now is 10 (P0-P9)
	
	
	var fullURL = SurveyURL + '&site=' + sSiteID + '&siteregion=' + sSiteRegionID + '&url=' + sReferringURL + '&p0=' + P0 + '&p1=' + P1 + '&p2=' + P2 + '&p3=' + P3 + '&p4=' + P4 + '&p5=' + P5 + '&p6=' + P6 + '&p7=' + P7 + '&p8=' + P8 + '&p9=' + P9;
	
	if (DisplayIntroPage == '0')
		fulURL = fullURL + '&showpage=1';

	//TODO: change "full screen" or "embedded" as it appears in surveytrigger.config			
	if (SurveyStyle == null){		
			SurveyStyle = "popup";
		}
	SurveyStyle = SurveyStyle.toLowerCase();
	if (SurveyStyle == 'full screen'){		
		window.open(fullURL, '_blank', 'resizable=yes,scrollbars=yes,menubar=no,location=no,toolbar=no,status=no,fullscreen=yes');
	}
	else if (SurveyStyle == "embedded")
		window.location.href=fullURL;
	else
		window.open(fullURL, '_blank', 'resizable=yes,scrollbars=yes,menubar=no,location=no,toolbar=no,status=no,left=0,top=0,height=500,width=725');
	if (window.event != null) window.event.cancelBubble = true;
	//return false;
}