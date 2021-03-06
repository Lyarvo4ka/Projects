#include "windows.h"
#include <QString>
#include "vqtconvert.h"

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////
// QEventEx
//////////////////////////////////////////////////////////////////////////////////////////
class QEventEx 
{
private:
    HANDLE m_hEvent;

public:
    QEventEx(bool manualReset, bool initialState, const QString name);    
    virtual ~QEventEx();
    HANDLE GetEvent() const;
    void ResetEvent();
    void SetEvent();
    void PulseEvent();
    bool WaitEvent(DWORD timeoutMillis = INFINITE) const;
};

//////////////////////////////////////////////////////////////////////////////////////////
// QAutoResetEvent
//////////////////////////////////////////////////////////////////////////////////////////
class QAutoResetEvent : public QEventEx
{
public:
    explicit QAutoResetEvent(bool initialState = false, const QString name = "");
};

//////////////////////////////////////////////////////////////////////////////////////////
// QManualResetEvent
//////////////////////////////////////////////////////////////////////////////////////////
class QManualResetEvent : public QEventEx
{
public:
    explicit QManualResetEvent(bool initialState = false, const QString name = "");
};
