// ItemData.cpp: implementation of the CItemData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "ItemData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemData::~CItemData()
{

}

CItemData::CItemData(UINT id,SOCKET sock,SOCKADDR_IN *addr,HWND m_hWnd)
{
    this->m_id = id;
    this->m_sock = sock;
    this->m_hWnd = m_hWnd;
    char *csIP = inet_ntoa(addr->sin_addr);
    //m_IP.Format(_T("%s"),m_str.CharToCString(csIP));
	m_IP.Format(_T("127.0.0.1"));
    //m_Address = QQ.IP2Add(m_IP);
	m_Address.Format(_T("δ֪"));
    if(m_Address.IsEmpty())
    {
        m_Address.Format(_T("δ֪"));
    }
    //��ʼ���Ի���ָ��
    /*
    m_cmd = NULL;
    m_screen = NULL;
    m_task = NULL;
    m_filedlg = NULL;
    */
}

DWORD WINAPI CItemData::OnListen(LPVOID lp)
{
    CItemData* t = (CItemData*)lp;
    t->OnBeginListen();
    return 0;
}

void CItemData::Run()
{
    ::CloseHandle(CreateThread(0,0,OnListen,(LPVOID)this,0,0));
}

void CItemData::OnBeginListen() //�ȴ�����
{
	int nRet;
    MSGINFO msg;
    memset(&msg,0,sizeof(MSGINFO));
    msg.Msg_id = SYSINFO;
    nRet = m_Mysocket.SendCommand(m_sock,(char*)&msg,sizeof(MSGINFO));
    if(nRet == SOCKET_ERROR)
    {
        MessageBox(_T("��ȡϵͳ��Ϣ��Ϣ����ʧ��"),_T("����"),MB_OK|MB_ICONWARNING);
    }
    memset(&msg,0,sizeof(MSGINFO));
    while(true)
    {
        nRet = m_Mysocket.RecvCommand(m_sock,(char*)&msg,sizeof(MSGINFO));
        if(nRet == 0)
        {
			if(WSAGetLastError()==WSAEWOULDBLOCK)  //WSAEWOULDBLOCK�Ĵ���,���ʾҪ����������
			{
				Sleep(50);
				continue;   //�����´�ѭ��
			}
			else
			{
                //������Ϣʧ�ܣ���������֪ͨ
                ::closesocket(m_sock);
                ::SendMessage(this->m_hWnd,ID_OFFLINE,this->m_id,0);
				return;
			}
		}
        else
        {
            switch(msg.Msg_id)
            {
            case SYSINFO:
                {
                    SYSTEMINFO systeminfo;
                    memset(&systeminfo,0,sizeof(SYSTEMINFO));
                    memcpy(&systeminfo,msg.context,sizeof(SYSTEMINFO));
                    GetSysVer(systeminfo);
                    ::SendMessage(m_hWnd,ID_ONLINE,(WPARAM)this,0);
                }
                break;
            }
        }
    }	
}

void CItemData::GetSysVer(SYSTEMINFO sys)
{
    this->Cam = sys.Cam;
    this->m_Ver.Format(_T("%0.2lf ���԰�"),sys.ver);
    switch(sys.os)
    {
    case 4:
        {
            this->m_OS.Format(_T("Windows 7"));
        }
        break;
    case 3:
        {
            this->m_OS.Format(_T("Windows Vista"));
        }
        break;
    case 2:
        {
            this->m_OS.Format(_T("Windows 2003"));
        }
        break;
    case 1:
        {
            this->m_OS.Format(_T("Windows XP"));
        }
        break;
    case 0:
        {
            this->m_OS.Format(_T("Windows 2000"));
        }
        break;
    default:
        {
            this->m_OS.Format(_T("δ֪ϵͳ�汾"));
        }
    }
}

SOCKET CItemData::GetSocket()
{
	return m_sock;
}