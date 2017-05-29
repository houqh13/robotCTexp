
// 7BotSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "7BotSystemDlg.h"
#include "afxdialogex.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy7BotSystemDlg �Ի���



CMy7BotSystemDlg::CMy7BotSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy7BotSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy7BotSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy7BotSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM3, &CMy7BotSystemDlg::OnBnClickedButtonOpenCom3)
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM4, &CMy7BotSystemDlg::OnBnClickedButtonOpenCom4)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECOM3, &CMy7BotSystemDlg::OnBnClickedButtonCloseCom3)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECOM4, &CMy7BotSystemDlg::OnBnClickedButtonCloseCom4)
	ON_BN_CLICKED(IDC_BUTTON_OPENCAMERA, &CMy7BotSystemDlg::OnBnClickedButtonOpenCamera)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECAMERA, &CMy7BotSystemDlg::OnBnClickedButtonCloseCamera)
	ON_BN_CLICKED(IDC_BUTTON_FOCUS, &CMy7BotSystemDlg::OnBnClickedButtonFocus)
	ON_BN_CLICKED(IDC_BUTTON_START, &CMy7BotSystemDlg::OnBnClickedButtonStart)
	ON_MESSAGE(WM_COMERROR, &CMy7BotSystemDlg::OnComError)
	ON_MESSAGE(WM_COMSUCCESS, &CMy7BotSystemDlg::OnComSuccess)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MOVEFINISH, &CMy7BotSystemDlg::OnMoveFinish)
	ON_MESSAGE(WM_ADJUST, &CMy7BotSystemDlg::OnAdjust)
	ON_MESSAGE(WM_NEXTSTEP, &CMy7BotSystemDlg::OnNextStep)
END_MESSAGE_MAP()


// CMy7BotSystemDlg ��Ϣ�������

BOOL CMy7BotSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for (int i = 0; i < 2; i++)
	{
		m_thCom[i] = NULL;
		m_dlgCom[i] = NULL;
		m_bMoveFinish[i] = true;
	}
	m_bReverse = false;
	m_thCamera = NULL;
	m_bFocusing = false;
	m_bScanning = false;

	GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSECAMERA)->EnableWindow(FALSE);

	arm.theta[6] = PI / 4;
	center.x = 0.0;
	center.y = 265.0;
	center.z = 200.0;
	radius = 100.0;
	angle = 0.0;
	delta = 5.0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy7BotSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy7BotSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy7BotSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy7BotSystemDlg::OnBnClickedButtonOpenCom3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[0] = new CComRcvThread(_T("Com3"), 0);
	if (m_thCom[0]->CreateThread())
	{
		GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(TRUE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonOpenCom4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[1] = new CComRcvThread(_T("Com4"), 1);
	if (m_thCom[1]->CreateThread())
	{
		GetDlgItem(IDC_BUTTON_OPENCOM4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(TRUE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonCloseCom3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[0]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
	GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(FALSE);

	KillTimer(0);

	// �رմ���
	if (m_dlgCom[0] != NULL)
	{
		m_dlgCom[0]->SendMessage(WM_CLOSE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonCloseCom4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCom[1]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
	GetDlgItem(IDC_BUTTON_OPENCOM4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(FALSE);

	KillTimer(1);

	// �رմ���
	if (m_dlgCom[1] != NULL)
	{
		m_dlgCom[1]->SendMessage(WM_CLOSE);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonOpenCamera()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCamera = (CCameraThread *)AfxBeginThread(RUNTIME_CLASS(CCameraThread));
	if (m_thCamera != NULL)
	{
		GetDlgItem(IDC_BUTTON_OPENCAMERA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLOSECAMERA)->EnableWindow(TRUE);

		SetTimer(99, 100, NULL);
	}
}


void CMy7BotSystemDlg::OnBnClickedButtonCloseCamera()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_thCamera->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
	m_thCamera = NULL;
	GetDlgItem(IDC_BUTTON_OPENCAMERA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSECAMERA)->EnableWindow(FALSE);

	KillTimer(99);
}


LRESULT CMy7BotSystemDlg::OnComError(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		AfxMessageBox(_T("Com3�޷��򿪣�"));

		m_thCom[0]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
		m_thCom[0] = NULL;
		GetDlgItem(IDC_BUTTON_OPENCOM3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CLOSECOM3)->EnableWindow(FALSE);
	}
	else if (wParam == 1)
	{
		AfxMessageBox(_T("Com4�޷��򿪣�"));

		m_thCom[1]->PostThreadMessage(WM_CLOSETHREAD, NULL, NULL);
		m_thCom[1] = NULL;
		GetDlgItem(IDC_BUTTON_OPENCOM4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CLOSECOM4)->EnableWindow(FALSE);
	}

	return 0;
}


LRESULT CMy7BotSystemDlg::OnComSuccess(WPARAM wParam, LPARAM lParam)
{
	SetTimer(wParam, 200, NULL);

	// �򿪴������������Ϣ
	if (m_dlgCom[wParam] == NULL)
	{
		m_dlgCom[wParam] = new CSerialDlg(_T("Serial Monitor : ") + m_thCom[wParam]->m_sCom, (CWnd *)this);
		m_dlgCom[wParam]->Create(IDD_SERIAL_DIALOG);
	}
	m_dlgCom[wParam]->ShowWindow(SW_SHOW);

	return 0;
}


void CMy7BotSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for (int i = 0; i < 2; i++)
	{	
		if (nIDEvent == i)
		{
			m_thCom[i]->PostThreadMessage(WM_RECEIVE, NULL, NULL);
		}
	}

	if (nIDEvent == 99)
	{
		if (m_bFocusing)
		{
			m_thCamera->PostThreadMessage(WM_FRESHFRAME, true, true);
		}
		else
		{
			if (m_bScanning && m_bMoveFinish[0] && m_bMoveFinish[1])
			{
				m_thCamera->PostThreadMessage(WM_SAVEFRAME, NULL, (long)angle);
			}
			else
			{
				m_thCamera->PostThreadMessage(WM_FRESHFRAME, false, false);
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMy7BotSystemDlg::OnBnClickedButtonFocus()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	calculate();

	for (int i = 0; i < 2; i++)
	{
		m_thCom[i]->PostThreadMessage(WM_MOVEANGLE, (WPARAM)arm.theta, NULL);
		m_bMoveFinish[i] = false;
	}
	m_bFocusing = true;
}


void CMy7BotSystemDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	calculate();

	for (int i = 0; i < 2; i++)
	{
		m_thCom[i]->PostThreadMessage(WM_MOVEANGLE, (WPARAM)arm.theta, NULL);
		m_bMoveFinish[i] = false;
	}
	m_bFocusing = false;
	m_bScanning = true;
	
	GetDlgItem(IDC_BUTTON_FOCUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
}


LRESULT CMy7BotSystemDlg::OnMoveFinish(WPARAM wParam, LPARAM lParam)
{
	m_bMoveFinish[wParam] = true;
	//if (!m_bFocusing && m_bMoveFinish[0] && m_bMoveFinish[1])
	//{
	//	m_thCamera->PostThreadMessage(WM_SAVEFRAME, NULL, (long)angle);
	//}
	return 0;
}


LRESULT CMy7BotSystemDlg::OnAdjust(WPARAM wParam, LPARAM lParam)
{
	double bx = *(double *)(wParam + 0 * sizeof(double));
	double by = *(double *)(wParam + 1 * sizeof(double));
	double dth = *(double *)(wParam + 2 * sizeof(double));	// dth>0����˳ʱ�����
	double dd = *(double *)(wParam + 3 * sizeof(double));

	double dx = ALPHATAN * (2 * radius - DELTA) * bx / 1280;
	double dz = ALPHATAN * (2 * radius - DELTA) * by / 1280;
	double dD = (1 / dd - 1) * (2 * radius - DELTA);

	j6.x += (- vec56.y * dx + vec56.x * dD) * 1;
	j6.y += (vec56.x * dx + vec56.y * dD) * 1;
	j6.z += dz * 1;
	arm.theta[5] += dth * 1;
	if (arm.theta[5] > 2 * PI)
	{
		arm.theta[5] -= 2 * PI;
	}

	arm.IK5(j6, vec56);

	m_thCom[0]->PostThreadMessage(WM_MOVEANGLE, (WPARAM)arm.theta, NULL);
	m_bMoveFinish[0] = false;

	return 0;
}


LRESULT CMy7BotSystemDlg::OnNextStep(WPARAM wParam, LPARAM lParam)
{
	if (!m_bReverse)
	{
		angle += delta;
		if (calculate())
		{
			angle = - delta;
			m_bReverse = true;
			calculate();
		}
	}
	else
	{
		angle -= delta;
		if (calculate())
		{
			angle = 0;
			m_bReverse = false;
			m_bScanning = false;
			GetDlgItem(IDC_BUTTON_FOCUS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			m_thCamera->video.release();
			return 0;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_thCom[i]->PostThreadMessage(WM_MOVEANGLE, (WPARAM)arm.theta, NULL);
		m_bMoveFinish[i] = false;
	}
	return 0;
}


// CMy7BotSystemDlg �������


int CMy7BotSystemDlg::calculate()
{
	j6 = PVector(center);
	vec67 = PVector(1.0, 0.0, 0.0);

	j6.x += radius * sin(angle / 180 * PI);
	j6.y -= radius * cos(angle / 180 * PI);
	vec56.x = - sin(angle / 180 * PI);
	vec56.y = cos(angle / 180 * PI);
	
	return arm.IK6(j6, vec56, vec67);
}
