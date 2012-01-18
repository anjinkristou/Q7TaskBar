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

#ifndef Q7TASKPROGRESSBAR_H
#define Q7TASKPROGRESSBAR_H
#include <QtCore\QObject>
#include <QtGui\QPixmap>
#include <QtCore\QSysInfo>
#include <Shobjidl.h>



class Q7TaskProgressBar : public QObject
{

	Q_OBJECT
	
public:

	  enum ProgressState {
       NoProgress      = 0,
       IndeterminateProgress = 0x1,
       NormalProgress  = 0x2,
       ErrorProgress   = 0x4,
       PausedProgress  = 0x8,
       AutomaticProgress   = 0x10
    };

	Q7TaskProgressBar(QObject * parent);
    ~Q7TaskProgressBar();

	bool Q7Init(HWND WinID);


	int 	maximum()  {return m_max;} 
	int 	minimum() {return m_min;}
	int     value()   {return m_value;}
	QString Text()    {return m_str;}
	
	void setWinId(HWND id)
	{
		WinId = id;
	}

	HWND WinID()
	{
       return WinId;
	}

	
	public slots:
		void setProgressState(ProgressState State);
		void setMinimum(int min);
		void setMaximum(int max);
		void setValue(int val);
		void setText(QString Text); 
		void reset();
		void setRange(int min,int max);
		void setOverlayIcon( QPixmap * icon,QString des);


private:
	ITaskbarList3* pTaskBar;
	HWND WinId;
	int m_min;
	int m_max;
	int m_value;
	QString m_str; 
	QPixmap * m_map;

	
	
	

};

#endif
