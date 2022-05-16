// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif

#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPatternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CPatternGeneratorView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CPatternGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

CPatternGeneratorView::CPatternGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	x = 400;
	y = 200;
	x1 = 300 + 150 * cos(3);
	y1 = 200 + 150 * sin(3);

}

CPatternGeneratorView::~CPatternGeneratorView()
{

}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing

void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen Pen;
	Pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&Pen);
	pDC->Ellipse(450, 350, 150, 50);
	pDC->SelectObject(pOldPen);

	CPen Pen1;
	Pen1.CreatePen(PS_SOLID, 2, RGB(0,255,0 ));
	CPen* pOldPen1 = pDC->SelectObject(&Pen1);
	pDC->Ellipse(400, 300, 200, 100);
	pDC->SelectObject(pOldPen1);

	CPen Pen2;
	Pen2.CreatePen(PS_SOLID, 1, RGB(0, 0,255));
	CPen* pOldPen2 = pDC->SelectObject(&Pen2);
	pDC->Ellipse(330, 230, 270, 170);
	pDC->SelectObject(pOldPen2);


	CPen Pen3;
	Pen3.CreatePen(PS_SOLID, 1, RGB(255, 0,0));
	CPen* pOldPen3 = pDC->SelectObject(&Pen3);
	pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);
	pDC->SelectObject(pOldPen3);

	CPen Pen4;
	Pen4.CreatePen(PS_SOLID, 1, RGB(255,0,0));
	CPen* pOldPen4 = pDC->SelectObject(&Pen4);
	pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	pDC->SelectObject(pOldPen4);
		
}


// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGeneratorDoc)));
	return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers


void CPatternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPatternGeneratorView::StartThread, this);

}


void CPatternGeneratorView::OnButtonStop()
{
	m_pCurrentThread->SuspendThread();
	
}


void CPatternGeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CPatternGeneratorView::StartThread(LPVOID Param)
{
	CPatternGeneratorView* pView = (CPatternGeneratorView*)Param;

	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		j = j + 6;
		pView->x = 300 + 100 * cos(j);//for inner loop
		pView->y = 200 + 100 * sin(j);

		pView->x1 = 300 + 150 * cos(j + 5);//for outer loop
		pView->y1 = 200 + 150 * sin(j+5);

		pView->Invalidate();

		Sleep(400);


	}

	// TODO: Add your implementation code here.
	return 0;
}
