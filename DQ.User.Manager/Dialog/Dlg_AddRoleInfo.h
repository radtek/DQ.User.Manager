#pragma once


// CDlg_AddRoleInfo �Ի���

class CDlg_AddRoleInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_AddRoleInfo)

public:
	CDlg_AddRoleInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_AddRoleInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_ROLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CEdit		m_eRoleName;
	CString		m_RoleName;
public:
	CString GetRoleName() { return m_RoleName; }

	void FillPowerTree(CDataTableMediator* pTable, CString sParentID, HTREEITEM hRoot);
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
};