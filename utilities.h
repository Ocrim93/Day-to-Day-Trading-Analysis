
#include<iostream>
#include<string>
#include <sstream>
#include <locale>
#include <iomanip>

using std::string; using std::map;
using std::endl;using std::cout;
using std::map; using std::vector;
using std::fstream; using std::stringstream;
using std::set;

string& rightTrim (string& str, string& chars ){

	str.erase(str.find_last_not_of(chars) +1 );
	return str;
}


string& leftTrim(string& str, string& chars ){

	str.erase(0,str.find_first_not_of(chars));
	return str;
}


string trim(string& str, string& chars){

	
	return leftTrim(rightTrim(str,chars),chars);
}

float convert_Date_to_seconds(string date_string){

	std::tm t = {};
    std::istringstream ss(date_string);
    float seconds ;
    if (ss >> std::get_time(&t, "%Y%m%d"))
    {
        seconds = std::mktime(&t);
	}
	return seconds;
}


map<string,map<string,vector<float>>> map_data(){

	map<string,map<string,vector<float>>> stock_data ;

	fstream file;

	file.open("scandi.csv");

	string line,word,name;

	long int c = 0;
	while(!file.eof()){   // check the end of file 
		
		getline(file,line);

		stringstream s(line);
		//file >> line;
		//cout << line<<"\n";
		string chars = " ";
		char at = '@';
		int counting = 1;
		float date_in_seconds;

		while (getline(s,word,',')){
			
			trim(word,chars);
			
			switch (counting){
				case 1:
					name = word;
					if(stock_data.find(name) == stock_data.end()){

						vector<float> bid_price;
						vector<float> ask_price;
						vector<float> trade_price;
						//vector<float> bid_volume;
						//vector<float> ask_volume;
						//vector<float> trade_volume;
						//vector<float> update_type;
						vector<float> time;
						//vector<float> date;
						vector<float> condition;

						map<string,vector<float>> temp_map ;

						temp_map.insert({"bid_price",bid_price});
						temp_map.insert({"ask_price",ask_price});
						temp_map.insert({"trade_price",trade_price});
						//temp_map.insert({"bid_volume",bid_volume});
						//temp_map.insert({"ask_volume",ask_volume});
						//temp_map.insert({"trade_volume",trade_volume}); 
						//temp_map.insert({"update_type",update_type});
						temp_map.insert({"time",time}); 
						//temp_map.insert({"date",date});
						temp_map.insert({"condition",condition});

						stock_data.insert({name,temp_map});
					}

					break;

				case 3:
					stock_data[name]["bid_price"].push_back(std::stof(word));
					break;
				case 4:
					stock_data[name]["ask_price"].push_back(std::stof(word));
					break;
				case 5:
					stock_data[name]["trade_price"].push_back(std::stof(word));
					break;	
				/*case 6:
					stock_data[name]["bid_volume"].push_back(std::stof(word));
					break;
				case 7:
					stock_data[name]["ask_volume"].push_back(std::stof(word));
					break;
				case 8:
					stock_data[name]["trade_volume"].push_back(std::stof(word));
					break;						
				case 9:
					stock_data[name]["update_type"].push_back(std::stof(word));
					break;*/	
				case 11:
					date_in_seconds = convert_Date_to_seconds(word);
					break;
				case 12:
					stock_data[name]["time"].push_back(std::stof(word)+date_in_seconds);
					break;
				case 15:
					if (word.find(at) != string::npos || word == "XT" ){
						stock_data[name]["condition"].push_back(1.);
					}
					else{
						stock_data[name]["condition"].push_back(0.);
					}
					break;
				}	
				if (counting == 15){ 
					counting =1;
					}						
				counting++;
					
			
		}		

			
	}
	
	file.close();
	
	return stock_data;
}	

double longest_time(vector<float>& stl_v){
	int n = stl_v.size();
	if (n==0){return -1;}
	double max = -1;
	for (auto el : stl_v){
		if(el > max){
			max = el;
			}	
		}
	return max;

	
}


double mean_func(vector<float>& stl_v){
	int n = stl_v.size();
	if (n==0){return -1;}

	double sum = 0;
	for (auto el : stl_v){
		sum += el;
	}
	return sum/n;
}

double median_func(vector<float> stl_v){
	
	sort(stl_v.begin(), stl_v.end());
	
	int n = stl_v.size();

	if (n==0){return -1;}

	if (n % 2 == 0 ){
		return (stl_v[n/2]+ stl_v[n/2-1])/2.;
	}
	else{
		return stl_v[(n-1)/2];
	}
}