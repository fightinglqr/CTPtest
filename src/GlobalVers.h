#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

#include <windows.h>

using namespace std;

// ---- 全局变量 ---- //
// 公共参数
// simnow 申请的 模拟账号的用户名密码
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "230274";                   // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "Gauss_1234567";        // 投资者密码


                                                                   // 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针
char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址
char *g_pInstrumentID[] = { "IF2410", "sn2411", "sc2411", "OI2501" }; // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = sizeof(g_pInstrumentID) / sizeof(g_pInstrumentID[0]);
unordered_map<string, TickToKlineHelper> g_KlineHash;              // 不同合约的k线存储表

                                                                   // 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针
char gTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "sn2411";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 22735;                           // 交易价格

int requestID = 1; // 请求编号


