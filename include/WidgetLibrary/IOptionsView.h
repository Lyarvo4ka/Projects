#ifndef IOPTIONSVIEW_H
#define IOPTIONSVIEW_H

#include <windows.h>

class IOptionsView
{
public:
	virtual void setNumberReadBads( int repeat_count ) = 0;
	virtual void setChirp( int bChirp ) = 0;
	virtual void setEndBeep( int bBeep ) = 0;
	virtual void setCRCBeep( int bBeep ) = 0;

public:	// signals
	virtual void ChirpChanged( int ) = 0;
	virtual void EndBeepChanged( int ) = 0;
	virtual void CRCBeepChanged( int ) = 0;
};


#endif 