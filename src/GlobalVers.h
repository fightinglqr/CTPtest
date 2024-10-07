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

// ---- ȫ�ֱ��� ---- //
// ��������
// simnow ����� ģ���˺ŵ��û�������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
TThostFtdcInvestorIDType gInvesterID = "230274";                   // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "Gauss_1234567";        // Ͷ��������


                                                                   // �������
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // ����ָ��
char gMdFrontAddr[] = "tcp://180.168.146.187:10010";               // ģ������ǰ�õ�ַ
char *g_pInstrumentID[] = { "IF2410", "sn2411", "sc2411", "OI2501" }; // �����Լ�����б��С��ϡ���֣��������ѡһ��
int instrumentNum = sizeof(g_pInstrumentID) / sizeof(g_pInstrumentID[0]);
unordered_map<string, TickToKlineHelper> g_KlineHash;              // ��ͬ��Լ��k�ߴ洢��

                                                                   // ���ײ���
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // ����ָ��
char gTradeFrontAddr[] = "tcp://180.168.146.187:10001";            // ģ�⽻��ǰ�õ�ַ
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "sn2411";        // �����׵ĺ�Լ����
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // ��������
TThostFtdcPriceType gLimitPrice = 22735;                           // ���׼۸�

int requestID = 1; // ������


