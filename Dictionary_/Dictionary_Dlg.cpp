
// Dictionary_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dictionary_.h"
#include "Dictionary_Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <fstream>
#include"resource.h"
#include "sapi.h"
#include "sphelper.h"
#pragma comment(lib, "sapi.lib")

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDictionary_Dlg 对话框



CDictionary_Dlg::CDictionary_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDictionary_Dlg::IDD, pParent)
	, m_filePath(_T(""))
	, m_addLetter(_T(""))
	, m_addNote(_T(""))
	, m_DeLetter(_T(""))
	, m_alter(_T(""))
	, m_alStr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	myQueue = new Queue<CString>(11);
	//**********************先加个空格，防止前进、后退报错
	CString t = _T("");
	myQueue->EnQueue(t);
	history_dex = 0;
}

void CDictionary_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_word);
	DDX_Text(pDX, IDC_EDIT1, m_filePath);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT3, m_addLetter);
	DDX_Text(pDX, IDC_EDIT4, m_addNote);
	DDX_Text(pDX, IDC_EDIT5, m_DeLetter);
	DDX_Text(pDX, IDC_EDIT6, m_alter);
	DDX_Text(pDX, IDC_EDIT7, m_alStr);
}

BEGIN_MESSAGE_MAP(CDictionary_Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDictionary_Dlg::OnOpenfile)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_addsearch, &CDictionary_Dlg::OnFindLetter)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &CDictionary_Dlg::OnCbnEditchangeCombo1)
	ON_BN_CLICKED(IDC_addLetter, &CDictionary_Dlg::Onaddletter)
	ON_BN_CLICKED(IDC_DeLetter, &CDictionary_Dlg::OnDeletter)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_advance, &CDictionary_Dlg::OnBnClickedaddvance)
	ON_BN_CLICKED(IDC_back, &CDictionary_Dlg::OnBnClickedback)
	ON_LBN_DBLCLK(IDC_LIST1, &CDictionary_Dlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_alter, &CDictionary_Dlg::OnBnClickedalter)
	ON_BN_CLICKED(IDC_CLEAR, &CDictionary_Dlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_voice, &CDictionary_Dlg::OnBnClickedvoice)
	ON_BN_CLICKED(IDC_BUTTON2, &CDictionary_Dlg::OnPage_)
END_MESSAGE_MAP()


// CDictionary_Dlg 消息处理程序

BOOL CDictionary_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	//使窗口能接受文件
	DragAcceptFiles(TRUE);
	//使按钮部分失效
	GetDlgItem(IDC_addsearch)->EnableWindow(false);
	GetDlgItem(IDC_DeLetter)->EnableWindow(false);
	GetDlgItem(IDC_CLEAR)->EnableWindow(false);
	GetDlgItem(IDC_advance)->EnableWindow(false);
	GetDlgItem(IDC_back)->EnableWindow(false);
	GetDlgItem(IDC_alter)->EnableWindow(false);
	GetDlgItem(IDC_voice)->EnableWindow(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDictionary_Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDictionary_Dlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	//dc.SetBkMode(TRANSPARENT);
	//CBitmap bit;
	//bit.LoadBitmapW(IDB_BITMAP1);
	//CDC Mem;
	//Mem.CreateCompatibleDC(&dc);
	//Mem.SelectObject(&bit);
	//dc.StretchBlt(0, 0, 727, 487, &Mem, 0, 0, 727, 487, SRCCOPY);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDictionary_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDictionary_Dlg::OnOpenfile()
{
	// TODO:  在此添加控件通知处理程序代码

	ifstream fin(m_filePath.GetBuffer(), ios::in);
	if (m_filePath.IsEmpty())
	{
		MessageBox(_T("请将文件拖至对话框！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CString temp1;
	CString temp2;
	char a[100] = { 0 };
	char b[100] = { 0 };
	while (!fin.eof())
	{
		fin.getline(a, 100);
		fin.getline(b, 100);
		temp1 = a;
		temp2 = b;
		//显示在列表框
		m_word.AddString(temp1+_T("  ")+temp2);
		//插入平衡二叉树
		AVLNode* Node = new AVLNode;
		Node->letter = a;
		Node->note = b;
		myTree.Insert(Node);
	}
	fin.close();
	m_filePath.ReleaseBuffer();
	MessageBox(_T("导入成功！"), _T("提示"), MB_OK);
	GetDlgItem(IDC_DeLetter)->EnableWindow(true);
	GetDlgItem(IDC_CLEAR)->EnableWindow(true);
	GetDlgItem(IDC_alter)->EnableWindow(true);
}


void CDictionary_Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	int nFileCount = DragQueryFile(hDropInfo, -1, NULL, 0);
	TCHAR *strFilePath;
	int dwSize;
	if (nFileCount == 1)
	{
		dwSize = DragQueryFile(hDropInfo, 0, NULL, 0);
		strFilePath = new TCHAR[dwSize + 1];
		if (strFilePath)
		{
			DragQueryFile(hDropInfo, 0, strFilePath, dwSize + 1);
			//获得拖放文件的路径名
			m_filePath.Format(_T("%s"), strFilePath);
			UpdateData(FALSE);
			delete[]strFilePath;
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
	DragFinish(hDropInfo);
	Invalidate();
}

//查找单词
void CDictionary_Dlg::OnFindLetter()
{
	// TODO:  在此添加控件通知处理程序代码
	CString find=_T("");
	m_combo.GetWindowTextW(find);
	if (myTree.Search(find) == nullptr)
	{
		MessageBox(_T("不存在的单词！"), _T("提示"), MB_OK);
		return;
	}
	else
	{
		CString temp = find + _T("  ") + myTree.Search(find)->note;
		int dex = m_word.FindStringExact(-1, temp);
		if (dex == LB_ERR)
		{
			MessageBox(_T("未找到此单词！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		m_word.SetCurSel(dex);
		MessageBox(_T("已找到！"), _T("提示"), MB_OK);
		GetDlgItem(IDC_back)->EnableWindow(true);
		//记录最近十次记录
		CString t;
		if (myQueue->IsFull() == true)
			myQueue->DeQueue(t);
		myQueue->EnQueue(find);
		history_dex = myQueue->getRear();
	}
}

//用户输入文本，显示下拉框
void CDictionary_Dlg::OnCbnEditchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	//让光标不消失
	::SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
	CString find = _T("");
	m_combo.GetWindowTextW(find);
	if (!find.IsEmpty())
	{
		GetDlgItem(IDC_addsearch)->EnableWindow(true);
		GetDlgItem(IDC_voice)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_addsearch)->EnableWindow(false);
		GetDlgItem(IDC_voice)->EnableWindow(false);
	}
	//删除下拉框
	int len = m_combo.GetCount();
	for (int i = 0; i < len; i++)
		m_combo.DeleteString(0);
	//************************找到单词10个
	int sum = 0;
	for (int i = 0; i <m_word.GetCount(); i++)
	{
		CString t;
		m_word.GetText(i, t);
		//截取
		int dex = t.Find(_T(" "));
		t = t.Left(dex);
		//存在子串
		if (t.Find(find) != -1)
		{
			m_combo.AddString(t);
			sum++;
		}
		if (sum >= 10)
			break;
	}
	if (find.IsEmpty())
		m_combo.ResetContent();
	m_combo.ShowDropDown();
}


void CDictionary_Dlg::Onaddletter()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_addLetter.IsEmpty())
	{
		MessageBox(_T("请输入添加的单词！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (m_addNote.IsEmpty())
	{
		if (MessageBox(_T("确认不添加中文意思？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
			return;
	}
	AVLNode* Node = new AVLNode;
	Node->letter = m_addLetter;
	Node->note = m_addNote;
	myTree.Insert(Node);
	CString temp = m_addLetter + _T("  ") + m_addNote;
	m_word.AddString(temp);
	int dex = m_word.FindStringExact(-1, temp);
	m_word.SetCurSel(dex);
	MessageBox(_T("已添加！"), _T("提示"), MB_OK);
	GetDlgItem(IDC_addsearch)->EnableWindow(true);
	GetDlgItem(IDC_DeLetter)->EnableWindow(true);
	GetDlgItem(IDC_CLEAR)->EnableWindow(true);
}


void CDictionary_Dlg::OnDeletter()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_DeLetter.IsEmpty())
	{
		MessageBox(_T("请输入删除的单词！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (myTree.Search(m_DeLetter) == false)
	{
		MessageBox(_T("未找到此单词！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CString temp = m_DeLetter + _T("  ") + myTree.Search(m_DeLetter)->note;
	int dex = m_word.FindStringExact(-1, temp);
	m_word.SetCurSel(dex);
	if (MessageBox(_T("确认删除？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		myTree.Remove(m_DeLetter);
		m_word.DeleteString(dex);
		MessageBox(_T("已删除！"), _T("提示"), MB_OK);
	}
}

void CDictionary_Dlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (MessageBox(_T("确认退出？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		delete myQueue;
		CDialogEx::OnClose();
	}
}


void CDictionary_Dlg::OnBnClickedaddvance()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_back)->EnableWindow(true);
	//******************重要当只有一个元素时，会报错，先加个空格进去
	history_dex++;
	CString temp = myQueue->Get_element(history_dex);
	m_combo.SetWindowTextW(temp);
	if (history_dex + 1 >= myQueue->getRear())
		GetDlgItem(IDC_advance)->EnableWindow(false);
}


void CDictionary_Dlg::OnBnClickedback()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_advance)->EnableWindow(true);
	history_dex--;            //保存的是队尾的下标
	CString temp = myQueue->Get_element(history_dex);
	m_combo.SetWindowTextW(temp);
	if (history_dex <= myQueue->getFront())
		GetDlgItem(IDC_back)->EnableWindow(false);
}

//在List内双击鼠标左键
void CDictionary_Dlg::OnLbnDblclkList1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	int t = m_word.GetCurSel();
	m_word.GetText(t, temp);
	int dex = temp.Find(_T(" "));
	temp = temp.Left(dex);
	m_DeLetter = temp;
	UpdateData(false);
}

//*****************修改单词
void CDictionary_Dlg::OnBnClickedalter()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_alter.IsEmpty()||m_alStr.IsEmpty())
	{
		MessageBox(_T("请输入单词或注释！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (myTree.Search(m_alter) == false)
	{
		MessageBox(_T("未找到此单词！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CString temp = m_alter + _T("  ") + myTree.Search(m_alter)->note;
	int dex = m_word.FindStringExact(-1, temp);
	if (dex == LB_ERR)
	{
		MessageBox(_T("未找到此单词！"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	m_word.SetCurSel(dex);
	if (MessageBox(_T("确认修改？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		//******************把原来的删除，插入新的
		m_word.DeleteString(dex);
		m_word.AddString(m_alter+_T("  ")+m_alStr);
		myTree.Search(m_alter)->note = m_alStr;
		MessageBox(_T("已修改！"), _T("提示"), MB_OK);
	}
}


void CDictionary_Dlg::OnBnClickedClear()
{
	// TODO:  在此添加控件通知处理程序代码
	if (MessageBox(_T("确认清空？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		m_word.ResetContent();
		GetDlgItem(IDC_addsearch)->EnableWindow(false);
		GetDlgItem(IDC_DeLetter)->EnableWindow(false);
		GetDlgItem(IDC_CLEAR)->EnableWindow(false);
		GetDlgItem(IDC_back)->EnableWindow(false);
		GetDlgItem(IDC_alter)->EnableWindow(false);
	}
}

//*************************发音
void CDictionary_Dlg::OnBnClickedvoice()
{
	// TODO:  在此添加控件通知处理程序代码
	CString find = _T("");
	m_combo.GetWindowTextW(find);
	if (myTree.Search(find) == nullptr)
	{
		MessageBox(_T("不存在的单词！"), _T("提示"), MB_OK);
		return;
	}
	ISpVoice *pSpVoice;        // 重要COM接口
	::CoInitialize(NULL);         // COM初始化
	// 获取ISpVoice接口
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoice);
	pSpVoice->SetVolume(60);
	pSpVoice->Speak(find, SPF_DEFAULT, NULL);

	pSpVoice->Release();
	::CoUninitialize();
}


void CDictionary_Dlg::OnPage_()
{
	// TODO:  在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://dict.youdao.com/"), NULL, NULL, SW_SHOWNORMAL);
}

