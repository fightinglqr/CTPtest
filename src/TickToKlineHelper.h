#pragma once
// ---- 计算k线的类 ---- //

#include <vector>
#include <string>

// k线数据结构
struct KLineDataType
{
	double open_price;   // 开盘价
	double high_price;   // 最高价
	double low_price;    // 最低价
	double close_price;  // 收盘价
	int volume;          // 这根k线上的成交量
};

class TickToKlineHelper
{
public:
	// 从本地数据构建k线，并存储到本地(假定本地数据没有丢包)
	void KLineFromLocalData(const std::string &sFilePath, const std::string &dFilePath); 
	// 从实时数据构建k线
	void KLineFromRealtimeData(CThostFtdcDepthMarketDataField *pDepthMarketData);
public:
	std::vector<double> m_priceVec; // 存储1分钟的价格
	std::vector<int> m_volumeVec; // 存储1分钟的成交量
	std::vector<KLineDataType> m_KLineDataArray;
};
