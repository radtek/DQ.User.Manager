#pragma once

#include"../COrgInfo.h"
#include"../CUserInfo.h"

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserManagerDataAccess.h                                                       ///  @brief    用户管理模块数据访问接口（所有对数据的访问都应写在此文件中）                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

class CDbUtilityMediator;
class CDataTableMediator;

/**   数据访问接口（单例模式）*/class EXPORT_USER_MANAGER CUserManagerDataService
{
public:
	~CUserManagerDataService(void);
public:
	static CUserManagerDataService*		GetInstance(void);
	static void					        DestoryInstance(void);
private:
	CUserManagerDataService();
	CUserManagerDataService(const CUserManagerDataService& rhs) { operator=(rhs); }
	CUserManagerDataService& operator=(const CUserManagerDataService&) { return *this; }
private:
	static CUserManagerDataService*		m_pSingleton;  ///<数据访问实例

public:
	/** 初始化数据访问接口
	@param csConn 数据库连接串
	@param nType  数据库类型
	*/
	bool DBInit(const CString& csConn, int nType);

	/**  释放数据库访问中介者 */
	void FreeDB();

public:
	/** 数据访问简单测试*/
	bool DoTest();

public:
	/** 查询部门信息 */
	CDataTableMediator* GetOrgInfo();
	/** 通过部门名称查询部门信息 */
	CDataTableMediator* GetOrgInfoUseOrgName(CString OrgName);
	/** 添加部门信息 */
	BOOL InsertOrgInfo(COrgInfo OrgInfo);
	/** 删除部门信息 */
	BOOL DeleteOrgInfo(CString OrgID);
	/** 删除部门子节点 */
	void DeleteChildOrgInfo(CString ParentID);
	/** 更新部门信息 */
	BOOL UpdateOrgInfo(COrgInfo OrgInfo);

public:
	/** 获取用户信息 */
	CDataTableMediator* GetBranchUser(CString ItemTxt);
	/** 添加用户信息 */
	BOOL InsertUserInfo(CUserInfo UserInfo);
	/** 删除用户 */
	BOOL DeleteUserInfo(CString UserID);
	/** 获取用户信息通过用户ID */
	CDataTableMediator* GetUserInfoUserUserID(CString UserID);
	/** 更新用户信息 */
	BOOL UpdateUserInfo(CUserInfo UserInfo);
	
private:
	CDbUtilityMediator*  m_pDB;  ///<数据访问中介者
};