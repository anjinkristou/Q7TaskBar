/*
**         add-on  : Q7TaskBar 
**         Version : 0.3 Alpha
**          
**   
**  How to Use : 
**
**         Q7TaskBarProgressBar * pTaskProg = new  Q7TaskBarProgressBar();
**		   pTaskProg->setWinId(HWND) // -> HWND 
**		   pTaskProg->setProgressState()  
**		              state:
** 					  NoProgress      
**                    IndeterminateProgress 
**                    NormalProgress  
**                    ErrorProgress  
**                    PausedProgress  
**                    AutomaticProgres
**   
/*
**         add-on  : Q7TaskBar 
**         Version : 0.3 Alpha
**          
**  How to Use : 
**
**         Q7TaskBarProgressBar * pTaskProg = new  Q7TaskBarProgressBar();
**		   pTaskProg->Q7Init(HWND)  set your HWND here 
**		   pTaskProg->setProgressState()  
**		              state:
** 					  NoProgress      
**                    IndeterminateProgress 
**                    NormalProgress  
**                    ErrorProgress  
**                    PausedProgress  
**                    AutomaticProgres
**   
**	-- setValue ( val )
**
**	-- setOverlayIcon( QPixmap * icon,QString des )
**	               icon -> icon to load 
**				   des  -> string that provides an alt text version of the information conveyed by the overlay
**	      
**  -- setRange()
**         - Min   
**         - Max
**
**   website: http://hitechoblog.comuf.com/Q7TaskBar or
**                http://hitechoblog.comuf.com/telecharger/q7taskbar-add-on-qt/
**
**				If You Like This add-on you can donate me on my paypal account 
**                                hitechoblog[at]hotmail[dot]fr
**                                              Thanks
** 
** This file contains alpha code and may not be distributed.
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#include "Q7TaskProgressBar.h"


Q7TaskProgressBar::Q7TaskProgressBar(QObject *parent)
	: QObject(parent)
	
{
	CoInitialize( NULL );
	m_min = 0;
	m_max = 100;
	m_value = 0;
	WinId    = NULL;
	pTaskBar = NULL;
	m_map    = NULL;

  RegisterWindowMessage(L"TaskbarButtonCreated");
  	
}

bool Q7TaskProgressBar::Q7Init(HWND WinID)
{
	setWinId(WinID);

	if ( QSysInfo::windowsVersion() != QSysInfo::WV_WINDOWS7 ) {
		
		qDebug("Error: i'm not on windows 7");
		this->~Q7TaskProgressBar();          
		return false;
	}

	HRESULT hr = CoCreateInstance(CLSID_TaskbarList,
		      0,
			  CLSCTX_INPROC_SERVER,
			  __uuidof(ITaskbarList3),(void**)&this->pTaskBar);

	if( FAILED(hr) )
	{
		qDebug("ERROR");
	}

	return true;

}



Q7TaskProgressBar::~Q7TaskProgressBar()
{
if ( pTaskBar != NULL) {
   pTaskBar->Release();
	}

	CoUninitialize();


}

void Q7TaskProgressBar::setProgressState(ProgressState State)
{

	if ( WinID() == NULL ) 
		return;
	
	pTaskBar->SetProgressState(WinID(),(TBPFLAG)State);


}

void Q7TaskProgressBar::setRange(int min,int max)
{
	if ( WinID() == NULL ) 
		return;
	pTaskBar->SetProgressValue(WinID(),min,max);


}


void Q7TaskProgressBar::setMaximum(int max)
{
	if ( WinID() == NULL ) 
		return;

pTaskBar->SetProgressValue(WinID(),qMin(m_min,m_max),max);
m_max = max;

}

void Q7TaskProgressBar::setMinimum(int min)
{
	if ( WinID() == NULL ) 
		return;

	pTaskBar->SetProgressValue(WinID(),min,qMax(m_min,m_max));
	m_min = min;

}

void Q7TaskProgressBar::setValue(int val)
{
 
	this->setMinimum(val);
	m_min = val;

}

void Q7TaskProgressBar::reset()
{
	if ( WinID() == NULL ) 
		return;

	this->m_min = 0;
	this->m_max = 100;
	pTaskBar->SetOverlayIcon(WinID(),NULL,L"");
	this->setProgressState(Q7TaskProgressBar::NoProgress);

	
}

void Q7TaskProgressBar::setOverlayIcon(QPixmap * icon,QString des)
{
	if ( WinID() == NULL ) 
		return;
	
	
	
	if ( icon->isNull() ) 
	{
		
		qDebug("icon is null");
		return;
	}
	m_map = icon;
	m_str = des;

	pTaskBar->SetOverlayIcon(WinID(),
		m_map->toWinHICON(),
		(LPCWSTR)QString(des).toStdString().c_str());


}

void Q7TaskProgressBar::setText(QString Text) {
	if ( m_map == NULL ) {
		qDebug("m_map = Null");
		return;
	}

	pTaskBar->SetOverlayIcon(WinID(),m_map->toWinHICON(),(LPCWSTR)QString(Text).toStdString().c_str());
}

