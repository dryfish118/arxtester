﻿#pragma once

#include "basedlg.h"
#include "arxcases.h"

class CConfigDlg : public CBaseDlg
{
// 构造
public:
	CConfigDlg(CArxCases& ac, CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARXLIST_DIALOG };
#endif

  CString m_logFile;
  CString m_filter;
  CArxCases& m_ac;
  int m_bSave;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
  void initTree();
  void checkTreeItem(BOOL bCheck);

	// 生成的消息映射函数
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedButtonFile();
  afx_msg void OnBnClickedButtonView();
  afx_msg void OnBnClickedButtonFilter();
  afx_msg void OnTvnItemChangedTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedButtonAll();
  afx_msg void OnBnClickedButtonClear();
  afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
  CTreeCtrl m_treeArx;
};