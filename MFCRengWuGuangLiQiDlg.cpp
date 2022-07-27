
// MFCRengWuGuangLiQiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCRengWuGuangLiQi.h"
#include "MFCRengWuGuangLiQiDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCRengWuGuangLiQiDlg 对话框



CMFCRengWuGuangLiQiDlg::CMFCRengWuGuangLiQiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCRENGWUGUANGLIQI_DIALOG, pParent)
{
	//对话框图标更改
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);IDI_ICON1 IDR_MAINFRAME
}

void CMFCRengWuGuangLiQiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMFCRengWuGuangLiQiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCRengWuGuangLiQiDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CMFCRengWuGuangLiQiDlg::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CMFCRengWuGuangLiQiDlg::OnBnClickedBtnClose)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CMFCRengWuGuangLiQiDlg::OnRclickList1)
	ON_COMMAND(ID_CLOSE_PROCESS, &CMFCRengWuGuangLiQiDlg::OnCloseProcess)
END_MESSAGE_MAP()


// CMFCRengWuGuangLiQiDlg 消息处理程序

BOOL CMFCRengWuGuangLiQiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//给列表添加列，LVCFMT_LEFT列表的风格
	m_list.InsertColumn(0, _T("编号"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("进程名"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(2, _T("PID编号"), LVCFMT_LEFT, 300);
	//添加网格线和整行选取
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//调用获取进程的函数
	BrowserProcess();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCRengWuGuangLiQiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCRengWuGuangLiQiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCRengWuGuangLiQiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//遍历进程
void CMFCRengWuGuangLiQiDlg::BrowserProcess()
{
	//获取进程快照
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	//
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return;
	
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	BOOL bMore = Process32First(hProcessSnap, &pe32);
	int i = 0;
	CString str;

	while (bMore)
	{
		//MessageBox(pe32.szExeFile);
		str.Format(_T("%d"), i+1);
		m_list.InsertItem(i, str);
		m_list.SetItemText(i, 1, pe32.szExeFile);

		str.Format(_T("%d"),pe32.th32ProcessID);
		m_list.SetItemText(i, 2, str);

		bMore = Process32Next(hProcessSnap, &pe32);
		i++;
	}
}


void CMFCRengWuGuangLiQiDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CMFCRengWuGuangLiQiDlg::OnBnClickedBtnRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	//重新拍照，然后需要调用DeleteAllltems清除之前的数据，不然会一直累加
	BrowserProcess();
}


void CMFCRengWuGuangLiQiDlg::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	//这个函数可以获取鼠标所在行的行数，如何没有点会返回一个-1

	int nSel = m_list.GetSelectionMark();
	if (nSel < 0)
		return;
	//获取第二列的PID文本
	CString strPID = m_list.GetItemText(nSel, 2);
	//我们需要把这个字符数字文本转换成为数字
	DWORD dwPID = _wtoi(strPID);

	//打开进程,第一个参数获取权限，二个是否继承什么，三个我们的进程id
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (hProcess == NULL)
	{
		MessageBox(L"打开进程失败");
		return;
	}

	//关闭进程
	TerminateProcess(hProcess, 0);

	Sleep(1000);
	//关闭之后刷新一遍
	OnBnClickedBtnRefresh();
}


void CMFCRengWuGuangLiQiDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pSubMenu = menu.GetSubMenu(0);
	POINT pos;
	GetCursorPos(&pos);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x,
		pos.y, this);
	*pResult = 0;
}


void CMFCRengWuGuangLiQiDlg::OnCloseProcess()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnClose();
}
