/*****************************************************************************/
/* vsthost.h : main header file for the VSTHOST application                  */
/*****************************************************************************/

/******************************************************************************
Copyright (C) 2006  Hermann Seib

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#if !defined(AFX_VSTHOST_H__9052BAF5_9D44_11D5_8163_4000001054B2__INCLUDED_)
#define AFX_VSTHOST_H__9052BAF5_9D44_11D5_8163_4000001054B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "SmpVSTHost.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CVsthostApp:
// See vsthost.cpp for the implementation of this class
//

class CWorkThread;
class CSpecAsioHost;
class CVsthostApp : public CWinApp
{
public:
	CVsthostApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVsthostApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWorkThread * pWorkThread;
	float * emptyBuf[2];
	DWORD dwRest;
	DWORD dwLastTime;
	UINT nTimerMSecs;
	UINT wTID;
	TIMECAPS tc;
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;
    int nTypeWIn, nTypeWOut;
    BOOL bNoSave;
    CWnd *pMidiKeyb;
	DWORD dwStartStamp;
	BOOL bEngRunning;

protected:
	void SaveSetup();
	void LoadSetup();
	BOOL LoadWaveOutDevice(CString sDevice, int &nBufSz);
	BOOL LoadWaveInDevice(CString sDevice, int nBufSz = 4410);
    bool SetAsioChannels(LPCSTR lpszChnIn = "", LPCSTR lpszChnOut = "");
	void SetupLatency();
	void HRTimer();
    static void CALLBACK TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

public:
	CSmpVSTHost vstHost;
    CSpecAsioHost *pAsioHost;
	CString sWaveMapper;

public:
	//{{AFX_MSG(CVsthostApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnMididev();
	afx_msg void OnWavedev();
	afx_msg void OnEngStart();
	afx_msg void OnUpdateEngStart(CCmdUI* pCmdUI);
	afx_msg void OnEngineRestart();
	afx_msg void OnUpdateEngineRestart(CCmdUI* pCmdUI);
	afx_msg void OnAsioCpl();
	afx_msg void OnUpdateAsioCpl(CCmdUI* pCmdUI);
	afx_msg void OnMidikeyb();
	afx_msg void OnUpdateMidikeyb(CCmdUI* pCmdUI);
	afx_msg void OnMidikeybProperties();
	afx_msg void OnUpdateMidikeybProperties(CCmdUI* pCmdUI);
	afx_msg void OnAsioChn();
	afx_msg void OnUpdateAsioChn(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void OnEffIdle(int nEffect = -1);
    void SetMidiKeybDlg(CWnd *pWnd) { pMidiKeyb = pWnd; }
	void SendResult(float **pBuffers, int nLength);
	void FullStop();
	void EngineStart();
	void EngineStop();
    BOOL IsEngineRunning() { return bEngRunning; }
	BOOL SetTimer(UINT nMSecs=0);
	CMDIChildWnd * CreateChild(CRuntimeClass *pClass, UINT nResource, HMENU hMenu = NULL, HACCEL hAccel = NULL);
	BOOL LoadEffect(LPCSTR lpszFileName, int *pnEffect=NULL, int nUniqueId = 0);
	void FillPopup(CMenu* pPopupMenu, int nEffect);
    float * GetEmptyBuffer() { return emptyBuf[0]; }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSTHOST_H__9052BAF5_9D44_11D5_8163_4000001054B2__INCLUDED_)
