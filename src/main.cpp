#include <iostream>
#include <stdio.h>
#include <string>
#include "GlobalVers.h"

#include <windows.h>

using namespace std;

// ���ӿ�
#pragma comment (lib, "thostmduserapi.lib")
#pragma comment (lib, "thosttraderapi.lib")


int main()
{
	/* �˺�����
	cout << "�������˺ţ� ";
	scanf("%s", gInvesterID);
	cout << "���������룺 ";
	scanf("%s", gInvesterPassword);*/

	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // ��������ص�ʵ��
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // ע���¼���
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // ��������ǰ�õ�ַ
	g_pMdUserApi->Init();                                // ��������

    cout << "ctp version:" << g_pMdUserApi->GetApiVersion() << endl;


	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // ��������ʵ��
	//CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // �������׻ص�ʵ��
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // ע���¼���
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // ���Ĺ�����
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // ����˽����
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // ���ý���ǰ�õ�ַ
	g_pTradeUserApi->Init();                                      // ��������
		

	// join��Ŀ���ǵȴ�init����initҪ�����ӶԶ˷������ȵȺܶ�����
    // ctp���ļ���Ὺ����߳̽��жԶ���������ȵ�
    // join��ʱ�ڵ�CTP�Ŀ��ļ��������߳�ȫ����ɲ��ҷ���
	//g_pMdUserApi->Join();
	//g_pTradeUserApi->Join();
	


	// ת������k������
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");

    // ���߳�һֱ����ѭ��,�ȴ����ļ�������̵߳�spi��Ӧ���Լ���Ӧ�����һϵ�������Ĳ���
    char input[256];
    while (true) {
        fgets(input,sizeof(input),stdin);
        if (strcmp(input, "exit") == 0) {
            break;
        }
        Sleep(10 * 1000);
    }


    // ����ִ�н�����������˳�����
    delete pMdUserSpi;
    g_pMdUserApi->Release();

    delete pTradeSpi;
    g_pTradeUserApi->Release();
	
	getchar();
	return 0;
}