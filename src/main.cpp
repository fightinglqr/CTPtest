#include <iostream>
#include <stdio.h>
#include <string>
#include "GlobalVers.h"

#include <windows.h>

using namespace std;

// 链接库
#pragma comment (lib, "thostmduserapi.lib")
#pragma comment (lib, "thosttraderapi.lib")


int main()
{
	/* 账号密码
	cout << "请输入账号： ";
	scanf("%s", gInvesterID);
	cout << "请输入密码： ";
	scanf("%s", gInvesterPassword);*/

	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // 设置行情前置地址
	g_pMdUserApi->Init();                                // 连接运行

    cout << "ctp version:" << g_pMdUserApi->GetApiVersion() << endl;


	// 初始化交易线程
	cout << "初始化交易..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
	//CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // 创建交易回调实例
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // 注册事件类
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // 设置交易前置地址
	g_pTradeUserApi->Init();                                      // 连接运行
		

	// join的目的是等待init，而init要做连接对端服务器等等很多事情
    // ctp库文件里会开多个线程进行对端连接请求等等
    // join此时在等CTP的库文件的其他线程全部完成并且返回
	//g_pMdUserApi->Join();
	//g_pTradeUserApi->Join();
	


	// 转换本地k线数据
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");

    // 主线程一直进行循环,等待库文件里的子线程的spi响应，以及响应后进行一系列其他的操作
    char input[256];
    while (true) {
        fgets(input,sizeof(input),stdin);
        if (strcmp(input, "exit") == 0) {
            break;
        }
        Sleep(10 * 1000);
    }


    // 这里执行结束，则进行退出操作
    delete pMdUserSpi;
    g_pMdUserApi->Release();

    delete pTradeSpi;
    g_pTradeUserApi->Release();
	
	getchar();
	return 0;
}