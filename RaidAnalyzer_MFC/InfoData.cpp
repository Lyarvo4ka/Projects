#include "StdAfx.h"
#include "InfoData.h"

///////////////////////////////////////////////////////////////////////////////
// --------------- CReceiver -------------------
///////////////////////////////////////////////////////////////////////////////
CReceiver::CReceiver(){ /**/ }
void CReceiver::Action()
{
	TRACE("Send Command");
}

void CReceiver::setPosition(LONGLONG & _lLBA)
{
	m_lPosition = _lLBA;
}

void CReceiver::setXorResult(BOOL &_bResultXor)
{
	m_bXorResult = _bResultXor;
}

void CReceiver::setDataCommand(LONGLONG & _lLBA , BOOL &_bResultXor)
{
	m_lPosition = _lLBA;
	m_bXorResult = _bResultXor;
}

///////////////////////////////////////////////////////////////////////////////
// --------------- CCommand -------------------
///////////////////////////////////////////////////////////////////////////////
void CCommand::setReceiver(CReceiver *_recivier)
{
	m_Recivier = _recivier;
}

CCommand::~CCommand(){ /**/ }

///////////////////////////////////////////////////////////////////////////////
// --------------- CParityCheckCommand -------------------
///////////////////////////////////////////////////////////////////////////////
CParityCheckCommand::CParityCheckCommand(){ /**/ }
CParityCheckCommand::~CParityCheckCommand()
{
	if (m_Recivier != NULL)
	{
		delete m_Recivier;
		m_Recivier = NULL;
	}
}



CParityCheckCommand::CParityCheckCommand(CReceiver *_recivier)
{
	m_Recivier = _recivier;
}

void CParityCheckCommand::Execute()
{
	m_Recivier->Action();
}

void CParityCheckCommand::setPosition(LONGLONG & _lLBA)
{
	m_Recivier->setPosition(_lLBA);
}

void CParityCheckCommand::setXorResult(BOOL &_bResultXor)
{
	m_Recivier->setXorResult(_bResultXor);
}
