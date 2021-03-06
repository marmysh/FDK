﻿namespace SoftFX.Extended.Core
{
    using System;
    using System.Linq;
    using SoftFX.Extended.Data;
    using SoftFX.Lrp;

    unsafe struct FxDataTrade
    {
        #region Creating and Converting

        public static FxDataTrade Create(string connectionString)
        {
            var handle = Native.TradeServer.Create(connectionString);
            return new FxDataTrade(handle);
        }

        public FxDataTrade(LPtr handle)
        {
            this.handle = handle;
        }

        public FxHandle Handle
        {
            get
            {
                return new FxHandle(this.handle);
            }
        }

        public FxDataClient DataClient
        {
            get
            {
                return new FxDataClient(this.handle);
            }
        }

        #endregion

        #region Server Methods

        public FxOrder OpenNewOrder(string operationId, string symbol, TradeCommand command, TradeRecordSide side, double priceThreshold, double volume, double? stopLoss, double? takeProfit, DateTime? expiration, string comment, int timeoutInMilliseconds)
        {
            if (operationId == null)
                operationId = string.Empty;

            this.VerifyInitialized();

            var order = new FxOrder(symbol, (int)command, side, priceThreshold, volume, stopLoss, takeProfit, expiration, comment);

            return Native.TradeServer.OpenNewOrder(this.handle, operationId, order, (uint)timeoutInMilliseconds); 
        }

        public FxOrder ModifyOrder(string operationId, string orderId, string clientId, string symbol, TradeRecordType type, TradeRecordSide side,
                                        double volume, double? newActivationPrice, double? newStopLoss, double? newTakeProfit, DateTime? newExpiration, string newComment, int timeoutInMilliseconds)
        {
            if (operationId == null)
                operationId = string.Empty;

            if (newComment == null)
                newComment = string.Empty;

            this.VerifyInitialized();

            var order = new FxOrder(orderId, clientId, symbol, (int)type, side, newActivationPrice, volume, newStopLoss, newTakeProfit, newExpiration, newComment);

            return Native.TradeServer.ModifyOrder(this.handle, operationId, order, (uint)timeoutInMilliseconds);
        }

        public void DeleteOrder(string operationId, string orderId, string clientID, TradeRecordSide side, int timeoutInMilliseconds)
        {
            if (operationId == null)
                operationId = string.Empty;

            this.VerifyInitialized();

            Native.TradeServer.DeleteOrder(this.handle, operationId, orderId, clientID, side, (uint)timeoutInMilliseconds);
        }

        public ClosePositionResult CloseOrder(string operationId, string orderId, double? closingVolume, int timeoutInMilliseconds)
        {
            if (operationId == null)
                operationId = string.Empty;

            this.VerifyInitialized();

            return Native.TradeServer.CloseOrder(this.handle, operationId, orderId, closingVolume, (uint)timeoutInMilliseconds);
        }

        public bool CloseByOrders(string firstOrderId, string secondOrderId, int timeoutInMilliseconds)
        {
            this.VerifyInitialized();

            return Native.TradeServer.CloseByPositions(this.handle, firstOrderId, secondOrderId, (uint)timeoutInMilliseconds);
        }

        public int CloseAllOrders(int timeoutInMilliseconds)
        {
            this.VerifyInitialized();

            return (int)Native.TradeServer.CloseAllPositions(this.handle, (uint)timeoutInMilliseconds);
        }

        public TradeRecord[] GetOrders(DataTrade dataTrade, int timeoutInMilliseconds)
        {
            this.VerifyInitialized();

            var orders = Native.TradeServer.GetRecords(this.handle, (uint)timeoutInMilliseconds);

            return orders.Select(o => new TradeRecord(dataTrade, o))
                         .ToArray();
        }

        public LPtr GetTradeTransactionReportsAndSubscribeToNotifications(TimeDirection direction, bool subscribe, DateTime? from, DateTime? to, int preferedBufferSize, int timeoutInMilliseconds)
        {
            this.VerifyInitialized();

            return Native.TradeServer.GetTradeTransactionReportsAndSubscribe(this.handle, (int)direction, subscribe, from, to, (UInt32)preferedBufferSize, (UInt32)timeoutInMilliseconds);
        }

        public void UnsubscribeTradeTransactionReports(int timeoutInMilliseconds)
        {
            this.VerifyInitialized();

            Native.TradeServer.UnsubscribeTradeTransactionReports(this.handle, (uint)timeoutInMilliseconds);
        }

        #endregion

        #region Local Methods

        public TradeRecord[] GetCacheOrders(DataTrade dataTrade)
        {
            this.VerifyInitialized();

            var orders = Native.TradeCache.GetRecords(this.handle);

            return orders.Select(o => new TradeRecord(dataTrade, o))
                         .ToArray();
        }

        public Position[] GetCachePositions()
        {
            this.VerifyInitialized();

            return Native.TradeCache.GetPositions(this.handle);
        }

        public AccountInfo GetCacheAccountInfo()
        {
            this.VerifyInitialized();

            return Native.TradeCache.GetAccountInfo(this.handle);
        }

        #endregion

        void VerifyInitialized()
        {
            if (this.handle.IsZero)
                throw new InvalidOperationException(string.Format("Cannot use not initialized {0} object.", this.GetType().Name));
        }

        #region Members

        readonly LPtr handle;

        #endregion
    }
}
