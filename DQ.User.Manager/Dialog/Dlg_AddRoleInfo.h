#pragma once

#include "../DataAccess/CRoleInfo.h"

// CDlg_AddRoleInfo 对话框

class CDlg_AddRoleInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_AddRoleInfo)

public:
	CDlg_AddRoleInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_AddRoleInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_ROLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CEdit			m_eRoleName;
	CEdit			m_eDescription;
	CBCGPTreeCtrl	m_wndMod;
	vector<CString>	m_pCurRola;
	int				m_OperateType;
	CRoleInfo		m_RoleInfo;
public:
	/** 设置角色信息 */
	void SerRoleInfo(CRoleInfo RoleInfo) { m_RoleInfo = RoleInfo; }
	CRoleInfo GetRoleInfo() { return m_RoleInfo; }
	void SetOperateType(int OperateType) { m_OperateType = OperateType; }
	/** 设置当前选中角色 */
	void		SetRola(vector<CString> pRola) { m_pCurRola = pRola; }
	/** 获取当前选中权限 */
	vector<CString>		GetRolePower() { return m_pCurRola; }
	void FillModeTree(HTREEITEM hParent, const CString& csParent);
	void GetSelChildNode(vector<CString>* pRola, HTREEITEM pRoot);
	/** 设置父节点选中 */
	void	SetParentCheck(HTREEITEM hTree, BOOL bCheck);
	/** 设置子节点选中 */
	void	SetChildCheck(HTREEITEM hTree, BOOL bCheck);
	/** 设置树节点选中 */
	void	SetTreeNodeSel(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot);
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickTreeRolePower(NMHDR *pNMHDR, LRESULT *pResult);
};
