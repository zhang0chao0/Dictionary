
// Dictionary_Dlg.cpp : ʵ���ļ�
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


// CDictionary_Dlg �Ի���



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
	//**********************�ȼӸ��ո񣬷�ֹǰ�������˱���
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


// CDictionary_Dlg ��Ϣ�������

BOOL CDictionary_Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//ʹ�����ܽ����ļ�
	DragAcceptFiles(TRUE);
	//ʹ��ť����ʧЧ
	GetDlgItem(IDC_addsearch)->EnableWindow(false);
	GetDlgItem(IDC_DeLetter)->EnableWindow(false);
	GetDlgItem(IDC_CLEAR)->EnableWindow(false);
	GetDlgItem(IDC_advance)->EnableWindow(false);
	GetDlgItem(IDC_back)->EnableWindow(false);
	GetDlgItem(IDC_alter)->EnableWindow(false);
	GetDlgItem(IDC_voice)->EnableWindow(false);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDictionary_Dlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	//dc.SetBkMode(TRANSPARENT);
	//CBitmap bit;
	//bit.LoadBitmapW(IDB_BITMAP1);
	//CDC Mem;
	//Mem.CreateCompatibleDC(&dc);
	//Mem.SelectObject(&bit);
	//dc.StretchBlt(0, 0, 727, 487, &Mem, 0, 0, 727, 487, SRCCOPY);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDictionary_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDictionary_Dlg::OnOpenfile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	ifstream fin(m_filePath.GetBuffer(), ios::in);
	if (m_filePath.IsEmpty())
	{
		MessageBox(_T("�뽫�ļ������Ի���"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
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
		//��ʾ���б��
		m_word.AddString(temp1+_T("  ")+temp2);
		//����ƽ�������
		AVLNode* Node = new AVLNode;
		Node->letter = a;
		Node->note = b;
		myTree.Insert(Node);
	}
	fin.close();
	m_filePath.ReleaseBuffer();
	MessageBox(_T("����ɹ���"), _T("��ʾ"), MB_OK);
	GetDlgItem(IDC_DeLetter)->EnableWindow(true);
	GetDlgItem(IDC_CLEAR)->EnableWindow(true);
	GetDlgItem(IDC_alter)->EnableWindow(true);
}


void CDictionary_Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
			//����Ϸ��ļ���·����
			m_filePath.Format(_T("%s"), strFilePath);
			UpdateData(FALSE);
			delete[]strFilePath;
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
	DragFinish(hDropInfo);
	Invalidate();
}

//���ҵ���
void CDictionary_Dlg::OnFindLetter()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString find=_T("");
	m_combo.GetWindowTextW(find);
	if (myTree.Search(find) == nullptr)
	{
		MessageBox(_T("�����ڵĵ��ʣ�"), _T("��ʾ"), MB_OK);
		return;
	}
	else
	{
		CString temp = find + _T("  ") + myTree.Search(find)->note;
		int dex = m_word.FindStringExact(-1, temp);
		if (dex == LB_ERR)
		{
			MessageBox(_T("δ�ҵ��˵��ʣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		m_word.SetCurSel(dex);
		MessageBox(_T("���ҵ���"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_back)->EnableWindow(true);
		//��¼���ʮ�μ�¼
		CString t;
		if (myQueue->IsFull() == true)
			myQueue->DeQueue(t);
		myQueue->EnQueue(find);
		history_dex = myQueue->getRear();
	}
}

//�û������ı�����ʾ������
void CDictionary_Dlg::OnCbnEditchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ù�겻��ʧ
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
	//ɾ��������
	int len = m_combo.GetCount();
	for (int i = 0; i < len; i++)
		m_combo.DeleteString(0);
	//************************�ҵ�����10��
	int sum = 0;
	for (int i = 0; i <m_word.GetCount(); i++)
	{
		CString t;
		m_word.GetText(i, t);
		//��ȡ
		int dex = t.Find(_T(" "));
		t = t.Left(dex);
		//�����Ӵ�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_addLetter.IsEmpty())
	{
		MessageBox(_T("��������ӵĵ��ʣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (m_addNote.IsEmpty())
	{
		if (MessageBox(_T("ȷ�ϲ����������˼��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
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
	MessageBox(_T("����ӣ�"), _T("��ʾ"), MB_OK);
	GetDlgItem(IDC_addsearch)->EnableWindow(true);
	GetDlgItem(IDC_DeLetter)->EnableWindow(true);
	GetDlgItem(IDC_CLEAR)->EnableWindow(true);
}


void CDictionary_Dlg::OnDeletter()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_DeLetter.IsEmpty())
	{
		MessageBox(_T("������ɾ���ĵ��ʣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (myTree.Search(m_DeLetter) == false)
	{
		MessageBox(_T("δ�ҵ��˵��ʣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CString temp = m_DeLetter + _T("  ") + myTree.Search(m_DeLetter)->note;
	int dex = m_word.FindStringExact(-1, temp);
	m_word.SetCurSel(dex);
	if (MessageBox(_T("ȷ��ɾ����"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		myTree.Remove(m_DeLetter);
		m_word.DeleteString(dex);
		MessageBox(_T("��ɾ����"), _T("��ʾ"), MB_OK);
	}
}

void CDictionary_Dlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (MessageBox(_T("ȷ���˳���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		delete myQueue;
		CDialogEx::OnClose();
	}
}


void CDictionary_Dlg::OnBnClickedaddvance()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_back)->EnableWindow(true);
	//******************��Ҫ��ֻ��һ��Ԫ��ʱ���ᱨ���ȼӸ��ո��ȥ
	history_dex++;
	CString temp = myQueue->Get_element(history_dex);
	m_combo.SetWindowTextW(temp);
	if (history_dex + 1 >= myQueue->getRear())
		GetDlgItem(IDC_advance)->EnableWindow(false);
}


void CDictionary_Dlg::OnBnClickedback()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_advance)->EnableWindow(true);
	history_dex--;            //������Ƕ�β���±�
	CString temp = myQueue->Get_element(history_dex);
	m_combo.SetWindowTextW(temp);
	if (history_dex <= myQueue->getFront())
		GetDlgItem(IDC_back)->EnableWindow(false);
}

//��List��˫��������
void CDictionary_Dlg::OnLbnDblclkList1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	int t = m_word.GetCurSel();
	m_word.GetText(t, temp);
	int dex = temp.Find(_T(" "));
	temp = temp.Left(dex);
	m_DeLetter = temp;
	UpdateData(false);
}

//*****************�޸ĵ���
void CDictionary_Dlg::OnBnClickedalter()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_alter.IsEmpty()||m_alStr.IsEmpty())
	{
		MessageBox(_T("�����뵥�ʻ�ע�ͣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (myTree.Search(m_alter) == false)
	{
		MessageBox(_T("δ�ҵ��˵��ʣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	CString temp = m_alter + _T("  ") + myTree.Search(m_alter)->note;
	int dex = m_word.FindStringExact(-1, temp);
	if (dex == LB_ERR)
	{
		MessageBox(_T("δ�ҵ��˵��ʣ�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	m_word.SetCurSel(dex);
	if (MessageBox(_T("ȷ���޸ģ�"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		//******************��ԭ����ɾ���������µ�
		m_word.DeleteString(dex);
		m_word.AddString(m_alter+_T("  ")+m_alStr);
		myTree.Search(m_alter)->note = m_alStr;
		MessageBox(_T("���޸ģ�"), _T("��ʾ"), MB_OK);
	}
}


void CDictionary_Dlg::OnBnClickedClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox(_T("ȷ����գ�"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		m_word.ResetContent();
		GetDlgItem(IDC_addsearch)->EnableWindow(false);
		GetDlgItem(IDC_DeLetter)->EnableWindow(false);
		GetDlgItem(IDC_CLEAR)->EnableWindow(false);
		GetDlgItem(IDC_back)->EnableWindow(false);
		GetDlgItem(IDC_alter)->EnableWindow(false);
	}
}

//*************************����
void CDictionary_Dlg::OnBnClickedvoice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString find = _T("");
	m_combo.GetWindowTextW(find);
	if (myTree.Search(find) == nullptr)
	{
		MessageBox(_T("�����ڵĵ��ʣ�"), _T("��ʾ"), MB_OK);
		return;
	}
	ISpVoice *pSpVoice;        // ��ҪCOM�ӿ�
	::CoInitialize(NULL);         // COM��ʼ��
	// ��ȡISpVoice�ӿ�
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoice);
	pSpVoice->SetVolume(60);
	pSpVoice->Speak(find, SPF_DEFAULT, NULL);

	pSpVoice->Release();
	::CoUninitialize();
}


void CDictionary_Dlg::OnPage_()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, _T("open"), _T("http://dict.youdao.com/"), NULL, NULL, SW_SHOWNORMAL);
}

