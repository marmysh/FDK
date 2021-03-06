#pragma once

#pragma warning (push)
#pragma warning (disable : 4275)
#pragma warning (disable : 4251)

#include "FxOrder.h"
#include "AssetInfo.h"

class CORE_API CFxExecutionReport
{
public:
	double ExecutedVolume;
	Nullable<double> InitialVolume;
	double LeavesVolume;
	Nullable<double> TradeAmount;
	Nullable<double> AveragePrice;
	Nullable<double> Price;
	double TradePrice;
	Nullable<double> StopPrice;
	Nullable<double> TakeProfit;
	Nullable<double> StopLoss;
	double Balance;
	double Commission;
	double AgentCommission;
	double Swap;
	Nullable<CDateTime> Expiration;
	Nullable<CDateTime> Created;
	Nullable<CDateTime> Modified;
public:
	string OrderId;
	string ClientOrderId;
	string Symbol;
	string Text;
	string ClosePositionRequestId;
	wstring Comment;
	vector<CAssetInfo> Assets;
public:
	FxExecutionType ExecutionType;
	FxOrderStatus OrderStatus;
	FxOrderType OrderType;
public:
	FxRejectReason RejectReason;
	FxTradeRecordSide OrderSide;
	int32 ReportsNumber;
public:
	CFxExecutionReport();
public:
public:
	bool TryGetTradeRecord(CFxOrder& order)const;
private:
	bool TryGetPosition(CFxOrder& order)const;
	bool TryGetPositionFromMarket(CFxOrder& order)const;
	bool TryGetPositionFromPosition(CFxOrder& order)const;
	bool TryGetStopOrder(CFxOrder& order)const;
	bool TryGetLimitOrder(CFxOrder& order)const;
public:
	bool TryGetClosedPosition(string& orderId, double& leavesVolume, double& commission, double& agentCommission, double& swap) const;
	bool TryGetDeletedOrder(string& orderId) const;
	bool TryGetActivatedOrder(string& orderId) const;
public:
	bool IsReject()const;
	bool IsExpired()const;
	bool IsCanceled()const;
	void Reject();
	const string& GetOrderId()const;
private:
	void CopyCommonFieldsToRecord(CFxOrder& order)const;
	bool CopyCreatedAndModifiedDateTime(CFxOrder& order)const;
};

#pragma warning (pop)
