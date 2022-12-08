
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include <iostream>
#include <cstdlib>
#include<map>
#include<variant>
#include<set>
#include "utilities.h"

int main(){
	
	map<string,map<string,vector<float>>> stock_data = map_data();
	set<string> index_names_set;
	
	for (auto key : stock_data){
		index_names_set.insert(key.first);
	}

	map<string,vector<float>> bid_ask_spread,trade_times,tick_changes,check;
	
	for (auto name : index_names_set){
		float time1 = -1.;
		float first_trade_price,diff_time;
		float bid,ask;
		
		for(int i =0; i < stock_data[name]["bid_price"].size();i++){
			bid = stock_data[name]["bid_price"][i];
			ask = stock_data[name]["ask_price"][i];

			//exclude auctions
			if(ask > bid){
				bid_ask_spread[name].push_back(ask-bid);
			
				if (stock_data[name]["condition"][i] == 1.){
					if(time1== -1.){
						time1 = stock_data[name]["time"][i];
						first_trade_price = stock_data[name]["trade_price"][i];
						continue;
						}
						
						diff_time  = stock_data[name]["time"][i]-time1;
						trade_times[name].push_back(diff_time);
						

						if(stock_data[name]["trade_price"][i] != first_trade_price){
							tick_changes[name].push_back(diff_time);
							
						}
						//update the first values of trade price and timing
						first_trade_price = stock_data[name]["trade_price"][i];	
						time1 = stock_data[name]["time"][i];
				}
			}
		}
	}
	
	

	std::ofstream report_file;
	report_file.open("report.txt");

	for (auto name : index_names_set){
		report_file << name << " " << "mean_spread  " << mean_func(bid_ask_spread[name]) << " " << "median_spread   " << median_func(bid_ask_spread[name])<<endl;
		report_file << name << " " << "mean_trade_times   " << mean_func(trade_times[name]) << " " << "median_trade_times   " << median_func(trade_times[name])<<endl;
		report_file << name << " " << "mean_trade_tick   " << mean_func(tick_changes[name]) << " " << "median_trade_tick   " << median_func(tick_changes[name])<<endl;
		report_file << name << " " << "Longest time between trades   " << longest_time(trade_times[name]) << " " << "Longest time between tick changes   " << longest_time(tick_changes[name])<<endl;
		report_file << "\n";
		report_file << "\n";
		
	}	
	report_file.close();

	return 0;


}