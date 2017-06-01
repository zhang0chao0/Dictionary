
// Dictionary_Dlg.h : ͷ�ļ�
//

#pragma once

#include "afxwin.h"
#include"AVL.h"
#include "ѭ������.h"

// CDictionary_Dlg �Ի���
class CDictionary_Dlg : public CDialogEx
{
// ����
public:
	CDictionary_Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DICTIONARY__DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_word;
	afx_msg void OnOpenfile();
	CString m_filePath;
	afx_msg void OnDropFiles(HDROP hDropInfo);
public:
	AVLTree myTree;
	// ���ҵĵ���
	CComboBox m_combo;
	afx_msg void OnFindLetter();
	afx_msg void OnCbnEditchangeCombo1();
public:
	CString m_addLetter;
	CString m_addNote;
	afx_msg void Onaddletter();
	CString m_DeLetter;
	afx_msg void OnDeletter();
	afx_msg void OnClose();
	afx_msg void OnBnClickedaddvance();
	afx_msg void OnBnClickedback();
public:
	//����10������
	Queue<CString>* myQueue;
	int history_dex;
	afx_msg void OnLbnDblclkList1();
	CString m_alter;
	CString m_alStr;
	afx_msg void OnBnClickedalter();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedvoice();
	afx_msg void OnPage_();
};
