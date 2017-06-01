
// Dictionary_Dlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include"AVL.h"
#include "循环队列.h"

// CDictionary_Dlg 对话框
class CDictionary_Dlg : public CDialogEx
{
// 构造
public:
	CDictionary_Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DICTIONARY__DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 查找的单词
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
	//保存10个单词
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
