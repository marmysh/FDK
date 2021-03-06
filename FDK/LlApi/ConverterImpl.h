#pragma once

class CConverterImpl
{
public:
    vector<CFxCurrencyInfo> CurrenciesFromHandle(void* handle);
	vector<CFxSymbolInfo> SymbolsFromHandle(void* handle);
	CFxSessionInfo SessionInfoFromHandle(void* handle);
	CNotification NotificationFromHandle(void* handle);
	CFxQuote QuoteFromHandle(void* handle);
	string ProtocolVersionFromHandle(void* handle);
	CFxAccountInfo AccountInfoFromHandle(void* handle);
	CFxPositionReport PositionFromHandle(void* handle);
	CFxTradeTransactionReport TradeTransactionReportFromHandle(void* handle);
	CFxExecutionReport ExecutionReportFromHandle(void* handle);
	void GetLogoutInfoFromHandle(void* handle, string& text, FxLogoutReason& reason, int32& code);
};