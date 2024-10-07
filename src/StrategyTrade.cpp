#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
#include "StrategyTrade.h"
#include "CustomTradeSpi.h"


extern std::unordered_map<std::string, TickToKlineHelper> g_KlineHash;

/* instrumentID const */
const char* Sn2411 = "Sn2411";

// �̻߳�����
std::mutex marketDataMutex;

void StrategyCheckAndTrade(TThostFtdcInstrumentIDType instrumentID, CustomTradeSpi *customTradeSpi)
{
	// ����
	std::lock_guard<std::mutex> lk(marketDataMutex);
	TickToKlineHelper tickToKlineObject = g_KlineHash.at(std::string(instrumentID));
	// ���� instrumentID ��ȷ������һ����Լ�Ĳ��ԣ���Ϊÿ����Լ�Ĳ��Բ�ͬ
    if (strcmp(instrumentID, Sn2411) == 0) {
        StrategyForSn(instrumentID, customTradeSpi, tickToKlineObject);
    }
}

void StrategyForSn(TThostFtdcInstrumentIDType instrumentID, CustomTradeSpi * customTradeSpi, TickToKlineHelper tickToKlineObject)
{
    // sn�Ĳ���
    std::vector<double> priceVec = tickToKlineObject.m_priceVec;
    if (priceVec.size() >= 3)
    {
        int len = priceVec.size();
        // ��������������Ǿ��򿪲�,��֮��������,������ʱ�����һ���۸��µ�
        if (priceVec[len - 1] > priceVec[len - 2] && priceVec[len - 2] > priceVec[len - 3])
            customTradeSpi->reqOrderInsert(instrumentID, priceVec[len - 1], 1, THOST_FTDC_D_Buy);
        else if (priceVec[len - 1] < priceVec[len - 2] && priceVec[len - 2] < priceVec[len - 3])
            customTradeSpi->reqOrderInsert(instrumentID, priceVec[len - 1], 1, THOST_FTDC_D_Buy);
    }
}
