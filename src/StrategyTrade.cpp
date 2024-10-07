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

// 线程互斥量
std::mutex marketDataMutex;

void StrategyCheckAndTrade(TThostFtdcInstrumentIDType instrumentID, CustomTradeSpi *customTradeSpi)
{
	// 加锁
	std::lock_guard<std::mutex> lk(marketDataMutex);
	TickToKlineHelper tickToKlineObject = g_KlineHash.at(std::string(instrumentID));
	// 根据 instrumentID 来确认走哪一个合约的策略，因为每个合约的策略不同
    if (strcmp(instrumentID, Sn2411) == 0) {
        StrategyForSn(instrumentID, customTradeSpi, tickToKlineObject);
    }
}

void StrategyForSn(TThostFtdcInstrumentIDType instrumentID, CustomTradeSpi * customTradeSpi, TickToKlineHelper tickToKlineObject)
{
    // sn的策略
    std::vector<double> priceVec = tickToKlineObject.m_priceVec;
    if (priceVec.size() >= 3)
    {
        int len = priceVec.size();
        // 最后连续三个上涨就买开仓,反之就卖开仓,这里暂时用最后一个价格下单
        if (priceVec[len - 1] > priceVec[len - 2] && priceVec[len - 2] > priceVec[len - 3])
            customTradeSpi->reqOrderInsert(instrumentID, priceVec[len - 1], 1, THOST_FTDC_D_Buy);
        else if (priceVec[len - 1] < priceVec[len - 2] && priceVec[len - 2] < priceVec[len - 3])
            customTradeSpi->reqOrderInsert(instrumentID, priceVec[len - 1], 1, THOST_FTDC_D_Buy);
    }
}
