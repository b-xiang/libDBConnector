/*
*
* Title : DataBase Connection Interface Header File
* Author: wackey
* E-Mail: worcy_kiddy@126.com
* Version:1.1
* Describe:
*
* ChangeLog:
* 2011.09.14 - fixed connect database slowly(return a value need a long time),if a error host parameters infilling.
               refer function:connect(), ConnDBServer().
  2011.10.22 - add namespace "wDBConnector"
  2012.01.24 - 64bit window7 OCINumberToInt should to use OCINumberToReal, or 			 -
*/

#ifndef _DB_CONNECT_H_
#define _DB_CONNECT_H_

#include "IDBRecordSet.h"

#ifdef _WINDOWS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

enum DB_TYPE {_MYSQL_, _ORACLE_};

class IDBConnect
{
// Construction and Destruction
public:
	IDBConnect();
	virtual ~IDBConnect();

public:
	virtual bool Connect( const wchar *host, 
						  const wchar *user, 
						  const wchar *passwd, 
						  const wchar *db, 
						  const uint32 port) = 0;
	virtual void Close(void) = 0;
	virtual bool Execute(const wchar *sql) = 0;
	virtual bool StorBinData(const wchar *insertsql, const wchar *sql, const wchar *binfilename) = 0;
	virtual	bool ReadBinData(const wchar *binfilename) = 0;

	// connection status
	virtual bool IsOpen(void) = 0;

	// reserved
	//virtual int SetConnOptions(enum mysql_option option, const char *arg) = 0;

	// transaction
	virtual bool BeginTrans(void) = 0;
	virtual bool RollbackTrans(void) = 0;
	virtual bool CommitTrans(void) = 0;
	virtual bool EndTrans(void) = 0;

	virtual int GetRealString(const wchar *inbuffer, uint32 length, wchar *&outbuffer) = 0;
	virtual int GetLastError(void) = 0;
	virtual wchar *GetErrorText(void) = 0;
};

/* public interface function */
namespace wDBConnector
{
EXPORT    void SetDBType(DB_TYPE dbType);
EXPORT DB_TYPE GetDBType();
	
EXPORT IDBConnect*	 Create(DB_TYPE dbType);
EXPORT IDBRecordSet* Create(IDBConnect *pDBConn);

EXPORT void Destroy(IDBConnect *&pDBConn);
EXPORT void Destroy(IDBRecordSet *&pDBRs);

// ����Connect����ǰ��һ��Ҫ��ִ��SetDBType������
// ��������Ĭ�����ݿ����ӷ�ʽ(ORACLE)
EXPORT IDBConnect * Connect(const wchar *host, 
		   					const wchar *user, 
						    const wchar *passwd, 
						    const wchar *db, 
						    const uint32 port);

// �����ڶ����ӣ�����ExecSQL����ǰ��һ��Ҫ��ִ��SetConnectParam����
// ExecSQL����ִ��һ��SQL��伴����
EXPORT void SetConnectParam(const wchar *host, 
							const wchar *user, 
							const wchar *passwd, 
							const wchar *db, 
							const uint32 port);
EXPORT bool ExecSQL(const wchar *sql);

// ���º��� ���� �������Ӷ���ָ����¼������ָ��Ĺرպ��� + ��������������ٺ���
EXPORT void Close(IDBConnect *&pDBConn);
EXPORT void Close(IDBRecordSet *&pDBRs);

EXPORT   int  GetErrorCode(IDBConnect *pDBConn);
EXPORT wchar *GetErrorText(IDBConnect *pDBConn);
}

#endif
