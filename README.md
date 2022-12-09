# Day-to-Day-Trading-Analysis
Day-to-Day Trading Analysis performed by retrieving data from a zipped CSV file.

You can download the file CSV here https://itarle.com/data-set-tests/.

To compile use “g++ -std=c++11 -o a scandi.cpp”. 

In the file “report.txt” you can find the result of the analysis as follows:

ABB SS Equity mean_spread  0.147277 median_spread   0.100006
ABB SS Equity mean_trade_times   715.911 median_trade_times   0
ABB SS Equity mean_trade_tick   1795.37 median_trade_tick   256
ABB SS Equity Longest time between trades   56960 Longest time between tick changes   56960

Where 
 - mean_spread is the mean of the difference between ask and bid price;
 - mean_trade_times is the mean of the time difference between two consecutive trades;
 - mean_trade_tick is the mean of the time difference among consecutive trades that have not equal trade price
 - Longest time between trades is the longest time difference between two consecutive trades
 - Longest time between tick changes is the longest time difference between two consecutive trades that have not equal trade price;

The Time difference is expressed in seconds. When the value is -1 it means that there is no enough data to perform the analysis, such as no trade.

I have taken in account only data where ASK_PRICE > BID_PRICE, No Auctions. 

The condition column in the csv file (15th column) has  { @1 M OTC UT|C UT|H UT|O XT XT|C XT|O }  different values. 
I assessed that it was a trade each time the value was “@1” or “XT” (cross-trade). 

Architecture of the code.

I retrieved the data and I constructed a map of map. The second map has key values: {“bid_price”,”ask_price”,”trade_price”,”condition”,”time”} and with value a  vector<float>, respectively.
The key of the upper map is just the STOCK_NAME.


