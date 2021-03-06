//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of the BCGControlBar Library
// Copyright (C) 1998-2016 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPVisualCtrl.h : header file
//

#if !defined(AFX_BCGPVISUALCTRL_H__E8F1CF04_6B23_493B_97EE_53AD84583B04__INCLUDED_)
#define AFX_BCGPVISUALCTRL_H__E8F1CF04_6B23_493B_97EE_53AD84583B04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgcbpro.h"
#include "BCGPGraphicsManager.h"
#include "BCGPVisualContainer.h"
#include "BCGPPopupWindow.h"

#ifndef BCGP_EXCLUDE_POPUP_WINDOW

/////////////////////////////////////////////////////////////////////////////
// CBCGPInfoTipOptions

struct BCGCBPRODLLEXPORT CBCGPInfoTipOptions
{
	BOOL		m_bRoundedCorners;
	BOOL		m_bShadow;
	BYTE		m_nTransparency;	// 255 - opaque, 0 - invisible
	SIZE		m_szPadding;
	COLORREF	m_clrFill;
	COLORREF	m_clrText;
	COLORREF	m_clrBorder;
	int			m_nStemSize;

	CBCGPPopupWindow::BCGPPopupWindowStemLocation	m_StemLocation;

	CBCGPInfoTipOptions()
	{
		m_bRoundedCorners = TRUE;
		m_bShadow = TRUE;
		m_nTransparency = 240;
		m_szPadding.cx = 5;
		m_szPadding.cy = 2;
		m_clrFill = (COLORREF)-1;
		m_clrText = (COLORREF)-1;
		m_clrBorder = (COLORREF)-1;
		m_nStemSize = 10;
		m_StemLocation = CBCGPPopupWindow::BCGPPopupWindowStemLocation_None;
	}

	const CBCGPInfoTipOptions& operator= (const CBCGPInfoTipOptions& src)
	{
		m_bRoundedCorners = src.m_bRoundedCorners;
		m_bShadow		  = src.m_bShadow;
		m_nTransparency	  = src.m_nTransparency;
		m_szPadding		  = src.m_szPadding;
		m_clrFill		  =	src.m_clrFill;
		m_clrText		  =	src.m_clrText;
		m_clrBorder		  =	src.m_clrBorder;
		m_nStemSize		  = src.m_nStemSize;
		m_StemLocation	  = src.m_StemLocation;
		
		return *this;
	}
};

#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPBaseVisualCtrl window

class BCGCBPRODLLEXPORT CBCGPBaseVisualCtrl :	public CStatic,
												public CBCGPGestureBase
{
	DECLARE_DYNAMIC(CBCGPBaseVisualCtrl)

// Construction
public:
	CBCGPBaseVisualCtrl();

// Operations
public:
	void SetGraphicsManager(CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER manager, CBCGPGraphicsManagerParams* pParams = NULL);
	void SetGraphicsManager(CRuntimeClass* pRTI);

	void EnableTooltip(BOOL bEnable = TRUE, BOOL bTooltipTrackingMode = FALSE);
	BOOL IsTooltipEnabled() const {return m_bIsTooltip;}

#ifndef BCGP_EXCLUDE_POPUP_WINDOW
	void EnableInfoTip(BOOL bEnable = TRUE, CBCGPInfoTipOptions* pOptions = NULL);
	BOOL IsInfoTipEnabled() const {return m_bUsePopupWindowInTrackingMode;}
#endif

	BOOL CreatePopup(const CRect& rect, BYTE nTransparency = 255 /* from 0 to 255 */, CWnd* pWndOwner = NULL);
	static BOOL HasActivePopup()
	{
		return m_hwndHookedPopup != NULL;
	}

	CBCGPGraphicsManager* GetGraphicsManager()
	{
		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return m_pGM;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPBaseVisualCtrl)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	virtual void InitCtrl() = 0;
	virtual void OnAfterCreateWnd() {}
	virtual void OnBeforeDestroyWnd() {}
	virtual void OnWndEnabled(BOOL /*bEnable*/) {}

	virtual CBCGPRect GetRect() = 0;
	virtual void SetRect(const CBCGPRect& rect, BOOL bRedraw = FALSE) = 0;

	virtual BOOL IsDirty() = 0;
	virtual void SetDirty(BOOL bSet) = 0;

	virtual void OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip) = 0;

	virtual BOOL CopyToClipboard() = 0;
	virtual BOOL ExportToFile(const CString& strFilePath) = 0;

	// Mouse events:
	virtual BOOL OnMouseDown(int nButton, const CBCGPPoint& pt) = 0;
	virtual void OnMouseUp(int nButton, const CBCGPPoint& pt) = 0;
	virtual BOOL OnMouseDblClick(int nButton, const CBCGPPoint& pt) = 0;
	virtual void OnMouseMove(const CBCGPPoint& pt) = 0;
	virtual void OnMouseLeave() = 0;
	virtual BOOL OnMouseWheel(const CBCGPPoint& pt, short zDelta) = 0;
	virtual void OnCancelMode() = 0;

	virtual BOOL OnSetMouseCursor(const CBCGPPoint& pt) = 0;

	virtual UINT GetClickAndHoldID() = 0;
	virtual CBCGPRect GetClickAndHoldRect() = 0;

	virtual BOOL IsCloseOnClick(CPoint ptScreen);

	virtual void StartClickAndHold();
	virtual void StopClickAndHold();

	virtual void OnClickAndHoldEvent(UINT nID, const CBCGPPoint& point) = 0;

	// Keyboard events:
	virtual BOOL OnKeyboardDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual BOOL OnKeyboardUp(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;

	// Gesture events:
	virtual BOOL OnGestureEventZoom(const CBCGPPoint& ptCenter, double dblZoomFactor) = 0;
	virtual BOOL OnGestureEventPan(const CBCGPPoint& ptFrom, const CBCGPPoint& ptTo, CBCGPSize& sizeOverPan) = 0;
	virtual BOOL OnGestureEventRotate(const CBCGPPoint& ptCenter, double dblAngle) = 0;
	virtual BOOL OnGestureEventTwoFingerTap(const CBCGPPoint& ptCenter) = 0;
	virtual BOOL OnGestureEventPressAndTap(const CBCGPPoint& ptPress, long lDelta) = 0;

	virtual BOOL GetGestureConfig(CBCGPGestureConfig& /*gestureConfig*/) = 0;

	virtual BOOL OnGestureEventZoom(const CPoint& ptCenter, double dblZoomFactor)
	{
		return OnGestureEventZoom(CBCGPPoint(ptCenter), dblZoomFactor);
	}

	virtual BOOL OnGestureEventPan(const CPoint& ptFrom, const CPoint& ptTo, CSize& sizeOverPanOut)
	{
		CBCGPSize sizeOverPan = sizeOverPanOut;
		BOOL bRes = OnGestureEventPan(CBCGPPoint(ptFrom), CBCGPPoint(ptTo), sizeOverPan);
		sizeOverPanOut = sizeOverPan;

		return bRes;
	}

	virtual BOOL OnGestureEventRotate(const CPoint& ptCenter, double dblAngle)
	{
		return OnGestureEventRotate(CBCGPPoint(ptCenter), dblAngle);
	}

	virtual BOOL OnGestureEventTwoFingerTap(const CPoint& ptCenter)
	{
		return OnGestureEventTwoFingerTap(CBCGPPoint(ptCenter));
	}

	virtual BOOL OnGestureEventPressAndTap(const CPoint& ptPress, long lDelta)
	{
		return OnGestureEventPressAndTap(CBCGPPoint(ptPress), lDelta);
	}

	// Tooltip:
	virtual BOOL OnGetToolTip(const CBCGPPoint& pt, CString& strToolTip, CString& strDescr) = 0;
	virtual COLORREF GetInfoTipColor(const CBCGPPoint& /*pt*/, int /*nColor*/) { return (COLORREF)-1; }

	BOOL IsFocused() const
	{
		return m_bIsFocused;
	}

	BOOL IsPopup() const
	{
		return m_bIsPopup;
	}

	virtual void OnDrawLayeredPopup();

	void SetScale(double dblScale = 1.);	// 1 - 100%
	double GetScale() const
	{
		return m_dblScale;
	}

	virtual void DoPaint(CDC* pDC, CRect rectClip = CRect(0, 0, 0, 0));

	// Printing support
	virtual BOOL DoPrint(CDC* pDC = NULL, CPrintInfo* pInfo = NULL);

	// Non-client area:
	virtual void OnCalcBorderSize(CBCGPRect& /*rectNCArea*/) {}
	virtual void OnNcDraw(CBCGPGraphicsManager* /*pGM*/, const CBCGPRect& /*rect*/) {};
	virtual BOOL OnNcMouseDown(int /*nButton*/, const CBCGPPoint& /*pt*/) { return FALSE; }
	virtual void OnNcMouseUp(int /*nButton*/, const CBCGPPoint& /*pt*/) {}

protected:
	virtual CBCGPBaseAccessibleObject* GetVisualBaseObject() = 0;	// Returns CBCGPBaseVisualObject or CBCGPVisualContainer

// Implementation
public:
	virtual ~CBCGPBaseVisualCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPBaseVisualCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnDestroy();
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy();
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg BCGNcHitTestType OnNcHitTest(CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnBCGUpdateToolTips(WPARAM, LPARAM);
	afx_msg BOOL OnTTNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult);
	afx_msg LRESULT OnFloatStatus(WPARAM, LPARAM);
	afx_msg LRESULT OnBCGPostRedraw(WPARAM, LPARAM);
	afx_msg LRESULT OnGestureEvent(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnTabletQuerySystemGestureStatus(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnPrint(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnGetObject(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	void InitTooltip();
	void DeleteInfoTip();

	CBCGPGraphicsManager*	m_pGM;
	double					m_dblScale;
	BOOL					m_bIsCaptured;
	BOOL					m_bIsTracked;
	BOOL					m_bIsTooltip;
	CToolTipCtrl*			m_pToolTip;
	CBCGPPopupWindow*		m_pInfoTip;
	BOOL					m_bToolTipCleared;
	BOOL					m_bTooltipTrackingMode;
	CString					m_strLastDisplayedToolTip;
	CString					m_strLastDisplayedToolTipDescr;
	BOOL					m_bIsFocused;
	UINT					m_nDlgCode;
	BOOL					m_bIsPopup;
	BYTE					m_nPopupAlpha;
	BYTE					m_nPopupAlphaAnimated;
	static HHOOK			m_hookMouse;
	static HWND				m_hwndHookedPopup;
	static BOOL				m_bInPaint;

	BOOL					m_bUsePopupWindowInTrackingMode;

#ifndef BCGP_EXCLUDE_POPUP_WINDOW
	CBCGPInfoTipOptions		m_InfoTipOptions;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualCtrl window

class BCGCBPRODLLEXPORT CBCGPVisualCtrl : public CBCGPBaseVisualCtrl
{
	DECLARE_DYNAMIC(CBCGPVisualCtrl)

public:
	virtual CBCGPBaseVisualObject* GetVisualObject() = 0;

	virtual void InitCtrl()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->SetOwner(this, FALSE);
		}
	}

	virtual CBCGPRect GetRect()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->GetRect();
		}

		return CBCGPRect();
	}

	virtual void SetRect(const CBCGPRect& rect, BOOL bRedraw = FALSE)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			const CBCGPSize sizeMin = pVisualObject->GetMinSize();
			
			if (sizeMin.IsEmpty())
			{
				pVisualObject->SetRect(rect, bRedraw);
			}
			else
			{
				CBCGPRect rectMin = rect;

				rectMin.SetWidth(max(rect.Width(), sizeMin.cx));
				rectMin.SetHeight(max(rect.Height(), sizeMin.cy));

				pVisualObject->SetRect(rectMin, bRedraw);
			}
		}
	}

	virtual BOOL IsDirty()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->IsDirty();
		}

		return FALSE;
	}

	virtual void SetDirty(BOOL bSet)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->SetDirty(bSet);
		}
	}

	virtual void OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnDraw(pGM, rectClip, BCGP_DRAW_STATIC);
			pVisualObject->OnDraw(pGM, rectClip, BCGP_DRAW_DYNAMIC);
		}
	}

	virtual BOOL CopyToClipboard()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject == NULL)
		{
			return FALSE;
		}

		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return pVisualObject->CopyToClipboard(m_pGM);
	}

	virtual BOOL ExportToFile(const CString& strFilePath)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject == NULL)
		{
			return FALSE;
		}

		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return pVisualObject->ExportToFile(strFilePath, m_pGM);
	}

	virtual BOOL OnMouseDown(int nButton, const CBCGPPoint& pt)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
		{
			return pVisualObject->OnMouseDown(nButton, pt);
		}

		return FALSE;
	}

	virtual void OnMouseUp(int nButton, const CBCGPPoint& pt)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && (m_bIsCaptured || pVisualObject->GetRect().PtInRect(pt)))
		{
			pVisualObject->OnMouseUp(nButton, pt);
		}
	}

	virtual BOOL OnMouseDblClick(int nButton, const CBCGPPoint& pt)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
		{
			return pVisualObject->OnMouseDblClick(nButton, pt);
		}

		return FALSE;
	}
	
	virtual void OnMouseMove(const CBCGPPoint& pt)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && (m_bIsCaptured || pVisualObject->GetRect().PtInRect(pt)))
		{
			pVisualObject->OnMouseMove(pt);
		}
	}

	virtual void OnMouseLeave()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnMouseLeave();
		}
	}

	virtual BOOL OnMouseWheel(const CBCGPPoint& pt, short zDelta)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
		{
			return pVisualObject->OnMouseWheel(pt, zDelta);
		}

		return FALSE;
	}

	virtual BOOL OnSetMouseCursor(const CBCGPPoint& pt)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
		{
			return pVisualObject->OnSetMouseCursor(pt);
		}

		return FALSE;
	}

	virtual BOOL GetGestureConfig(CBCGPGestureConfig& gestureConfig)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->GetGestureConfig(gestureConfig);
		}
		
		return FALSE;
	}

	virtual BOOL OnGestureEventZoom(const CBCGPPoint& ptCenter, double dblZoomFactor)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(ptCenter))
		{
			return pVisualObject->OnGestureEventZoom(ptCenter, dblZoomFactor);
		}
		
		return FALSE;
	}

	virtual BOOL OnGestureEventPan(const CBCGPPoint& ptFrom, const CBCGPPoint& ptTo, CBCGPSize& sizeOverPan)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(ptFrom))
		{
			return pVisualObject->OnGestureEventPan(ptFrom, ptTo, sizeOverPan);
		}
		
		return FALSE;
	}

	virtual BOOL OnGestureEventRotate(const CBCGPPoint& ptCenter, double dblAngle)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(ptCenter))
		{
			return pVisualObject->OnGestureEventRotate(ptCenter, dblAngle);
		}
		
		return FALSE;
	}

	virtual BOOL OnGestureEventTwoFingerTap(const CBCGPPoint& ptCenter)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(ptCenter))
		{
			return pVisualObject->OnGestureEventTwoFingerTap(ptCenter);
		}
		
		return FALSE;
	}

	virtual BOOL OnGestureEventPressAndTap(const CBCGPPoint& ptPress, long lDelta)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(ptPress))
		{
			return pVisualObject->OnGestureEventPressAndTap(ptPress, lDelta);
		}
		
		return FALSE;
	}

	virtual void OnCancelMode()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnCancelMode();
		}
	}

	virtual BOOL OnKeyboardDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->OnKeyboardDown(nChar, nRepCnt, nFlags);
		}

		return FALSE;
	}

	virtual BOOL OnKeyboardUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->OnKeyboardUp(nChar, nRepCnt, nFlags);
		}

		return FALSE;
	}

	virtual BOOL OnGetToolTip(const CBCGPPoint& pt, CString& strToolTip, CString& strDescr)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
		{
			return pVisualObject->OnGetToolTip(pt, strToolTip, strDescr);
		}

		return FALSE;
	}

	virtual COLORREF GetInfoTipColor(const CBCGPPoint& pt, int nColor)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL && pVisualObject->GetRect().PtInRect(pt))
		{
			return pVisualObject->GetInfoTipColor(pt, nColor);
		}
		
		return (COLORREF)-1;
	}

	virtual CBCGPBaseAccessibleObject* GetVisualBaseObject()
	{
		return GetVisualObject();
	}

	virtual UINT GetClickAndHoldID()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->GetClickAndHoldID();
		}

		return 0;
	}

	virtual CBCGPRect GetClickAndHoldRect()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			return pVisualObject->GetClickAndHoldRect();
		}

		return CBCGPRect();
	}

	virtual void OnClickAndHoldEvent(UINT nID, const CBCGPPoint& point)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnClickAndHoldEvent(nID, point);
		}
	}

	virtual void OnAfterCreateWnd()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnAfterCreateWnd();
		}
	}

	virtual void OnBeforeDestroyWnd()
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnBeforeDestroyWnd();
		}
	}

	virtual void OnWndEnabled(BOOL bEnable)
	{
		CBCGPBaseVisualObject* pVisualObject = GetVisualObject();
		if (pVisualObject != NULL)
		{
			pVisualObject->OnWndEnabled(bEnable);
		}
	}

	afx_msg LRESULT OnChangeVisualManager(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualContainerCtrl window

class BCGCBPRODLLEXPORT CBCGPVisualContainerCtrl : public CBCGPBaseVisualCtrl
{
	DECLARE_SERIAL(CBCGPVisualContainerCtrl)

public:
	CBCGPVisualContainerCtrl(CRuntimeClass* pContainerRTI = NULL) :
		m_pContainer(NULL)
	{
		SetContainerRTI(pContainerRTI);
	}

	virtual ~CBCGPVisualContainerCtrl()
	{
		if (m_pContainer != NULL)
		{
			delete m_pContainer;
		}
	}

	virtual CBCGPVisualContainer* GetVisualContainer()
	{
		if (m_pContainer == NULL)
		{
			if (m_pContainerRTI != NULL)
			{
				m_pContainer = DYNAMIC_DOWNCAST(CBCGPVisualContainer, m_pContainerRTI->CreateObject());
			}
			else
			{
				m_pContainer = new CBCGPVisualContainer;
			}
		}

		return m_pContainer;
	}

	void SetContainerRTI(CRuntimeClass* pContainerRTI)
	{
		ASSERT(m_pContainer == NULL);

		m_pContainerRTI = pContainerRTI;

		if (m_pContainerRTI != NULL)
		{
			ASSERT(m_pContainerRTI->IsDerivedFrom(RUNTIME_CLASS(CBCGPVisualContainer)));
		}
	}

	virtual void InitCtrl()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->SetOwner(this, FALSE);
			pVisualContainer->m_bNCScrollBars = TRUE;
		}
	}

	virtual CBCGPRect GetRect()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->GetRect();
		}

		return CBCGPRect();
	}

	virtual void SetRect(const CBCGPRect& rect, BOOL bRedraw = FALSE)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->SetRect(rect, bRedraw);
		}
	}

	virtual BOOL IsDirty()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->IsDirty();
		}

		return FALSE;
	}

	virtual void SetDirty(BOOL bSet)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->SetDirty(bSet);
		}
	}

protected:
	virtual BOOL OnMouseDown(int nButton, const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(pt))
		{
			return pVisualContainer->OnMouseDown(nButton, pt);
		}

		return FALSE;
	}

	virtual void OnMouseUp(int nButton, const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && (m_bIsCaptured || pVisualContainer->GetRect().PtInRect(pt)))
		{
			pVisualContainer->OnMouseUp(nButton, pt);
		}
	}

	virtual BOOL OnMouseDblClick(int nButton, const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(pt))
		{
			return pVisualContainer->OnMouseDblClick(nButton, pt);
		}

		return FALSE;
	}
	
	virtual void OnMouseMove(const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && (m_bIsCaptured || pVisualContainer->GetRect().PtInRect(pt)))
		{
			pVisualContainer->OnMouseMove(pt);
		}
	}

	virtual void OnMouseLeave()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnMouseLeave();
		}
	}

	virtual BOOL OnMouseWheel(const CBCGPPoint& pt, short zDelta)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(pt))
		{
			return pVisualContainer->OnMouseWheel(pt, zDelta);
		}

		return FALSE;
	}

	virtual BOOL OnSetMouseCursor(const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(pt))
		{
			return pVisualContainer->OnSetMouseCursor(pt);
		}

		return FALSE;
	}
	
	virtual BOOL GetGestureConfig(CBCGPGestureConfig& gestureConfig)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->GetGestureConfig(gestureConfig);
		}
		
		return FALSE;
	}

	virtual BOOL OnGestureEventZoom(const CBCGPPoint& ptCenter, double dblZoomFactor)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(ptCenter))
		{
			return pVisualContainer->OnGestureEventZoom(ptCenter, dblZoomFactor);
		}
		
		return FALSE;
	}
	
	virtual BOOL OnGestureEventPan(const CBCGPPoint& ptFrom, const CBCGPPoint& ptTo, CBCGPSize& sizeOverPan)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(ptFrom))
		{
			return pVisualContainer->OnGestureEventPan(ptFrom, ptTo, sizeOverPan);
		}
		
		return FALSE;
	}
	
	virtual BOOL OnGestureEventRotate(const CBCGPPoint& ptCenter, double dblAngle)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(ptCenter))
		{
			return pVisualContainer->OnGestureEventRotate(ptCenter, dblAngle);
		}
		
		return FALSE;
	}
	
	virtual BOOL OnGestureEventTwoFingerTap(const CBCGPPoint& ptCenter)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(ptCenter))
		{
			return pVisualContainer->OnGestureEventTwoFingerTap(ptCenter);
		}
		
		return FALSE;
	}
	
	virtual BOOL OnGestureEventPressAndTap(const CBCGPPoint& ptPress, long lDelta)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(ptPress))
		{
			return pVisualContainer->OnGestureEventPressAndTap(ptPress, lDelta);
		}
		
		return FALSE;
	}
	
	virtual void OnCancelMode()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnCancelMode();
		}
	}

	virtual BOOL OnKeyboardDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->OnKeyboardDown(nChar, nRepCnt, nFlags);
		}

		return FALSE;
	}

	virtual BOOL OnKeyboardUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->OnKeyboardUp(nChar, nRepCnt, nFlags);
		}

		return FALSE;
	}

	virtual BOOL OnGetToolTip(const CBCGPPoint& pt, CString& strToolTip, CString& strDescr)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(pt))
		{
			return pVisualContainer->OnGetToolTip(pt, strToolTip, strDescr);
		}

		return FALSE;
	}

	virtual COLORREF GetInfoTipColor(const CBCGPPoint& pt, int nColor)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL && pVisualContainer->GetRect().PtInRect(pt))
		{
			return pVisualContainer->GetInfoTipColor(pt, nColor);
		}
		
		return (COLORREF)-1;
	}

	virtual void OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rectClip)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnDraw(pGM, rectClip);
		}
	}

public:
	virtual BOOL CopyToClipboard()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer == NULL)
		{
			return FALSE;
		}

		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return pVisualContainer->CopyToClipboard(m_pGM);
	}

	virtual BOOL ExportToFile(const CString& strFilePath)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer == NULL)
		{
			return FALSE;
		}

		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return pVisualContainer->ExportToFile(strFilePath, m_pGM);
	}

	virtual BOOL CopyFullImageToClipboard()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer == NULL)
		{
			return FALSE;
		}

		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return pVisualContainer->CopyToClipboard(m_pGM, TRUE);
	}

	virtual BOOL ExportFullImageToFile(const CString& strFilePath)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer == NULL)
		{
			return FALSE;
		}

		if (m_pGM == NULL)
		{
			m_pGM = CBCGPGraphicsManager::CreateInstance();
		}

		return pVisualContainer->ExportToFile(strFilePath, m_pGM, TRUE);
	}

protected:
	virtual CBCGPBaseAccessibleObject* GetVisualBaseObject()
	{
		return GetVisualContainer();
	}

	virtual UINT GetClickAndHoldID()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->GetClickAndHoldID();
		}

		return 0;
	}

	virtual CBCGPRect GetClickAndHoldRect()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->GetClickAndHoldRect();
		}

		return CBCGPRect();
	}

	virtual void OnClickAndHoldEvent(UINT nID, const CBCGPPoint& point)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnClickAndHoldEvent(nID, point);
		}
	}

	virtual void OnCalcBorderSize(CBCGPRect& rectNCArea)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnCalcBorderSize(rectNCArea);
		}
	}

	virtual void OnNcDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& rect)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnNcDraw(pGM, rect);
		}
	}

	virtual BOOL OnNcMouseDown(int nButton, const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			return pVisualContainer->OnNcMouseDown(nButton, pt);
		}

		return FALSE;
	}

	virtual void OnNcMouseUp(int nButton, const CBCGPPoint& pt)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnNcMouseUp(nButton, pt);
		}
	}

	virtual void OnAfterCreateWnd()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnAfterCreateWnd();
		}
	}

	virtual void OnBeforeDestroyWnd()
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnBeforeDestroyWnd();
		}
	}

	virtual void OnWndEnabled(BOOL bEnable)
	{
		CBCGPVisualContainer* pVisualContainer = GetVisualContainer();
		if (pVisualContainer != NULL)
		{
			pVisualContainer->OnWndEnabled(bEnable);
		}
	}

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	CRuntimeClass*			m_pContainerRTI;
	CBCGPVisualContainer*	m_pContainer;

	afx_msg LRESULT OnChangeVisualManager(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPVISUALCTRL_H__E8F1CF04_6B23_493B_97EE_53AD84583B04__INCLUDED_)
