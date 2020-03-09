#ifndef _ADD_GET_TOP_K_STOCK_PRICE_H
#define _ADD_GET_TOP_K_STOCK_PRICE_H
#include "Debug.h"
/*
Bloomberg
add {string trade, int share}, return top K greatest values of shares and corresponding trades
    =>
    unordered_map<std::string,std::multimap<int,std::string>::iterator> map
    multimap<int,std::string> sorted
    follow up: can we do better for time complexity? what is the limit of your approach
    =>
    unordered_map<std::string, list<int,std::string>::iterator> map
    list<int,std::string> sorted
    as long as we can add a new element to the end of list
 */
class AddGetTopKStockPrice
{
    std::unordered_map<std::string,std::multimap<int,std::string>::iterator> toItr;//<Stock,itrTo<Price,Stock>>
    std::multimap<int,std::string> sorted;//<Price,Stock>
public:
    AddGetTopKStockPrice(){}

    void Add(const std::string & Stock, int Price)// O(logN) time, where N is number of stocks
    {
        auto itr = toItr.find(Stock);
        if (itr != toItr.end())
            sorted.erase(itr->second);
        auto itr2 = sorted.insert({Price, Stock});
        toItr[Stock] = itr2;
    }
    std::vector<std::pair<int,std::string>> GetTopK(int K)// O(K) time
    {
        std::vector<std::pair<int,std::string>> res;
        int count = 0;
        for (auto itr = sorted.rbegin(); itr != sorted.rend() && count < K; ++itr, ++count)
            res.push_back({itr->first,itr->second});

        std::cout << "AddGetTopKStockPrice GetTopK for K=" << K << ": " << Debug::ToStr1D<int,std::string>()(res) << std::endl;
        return res;
    };
    std::pair<int,bool> Get(const std::string & Stock)
    {
        auto itr = toItr.find(Stock);
        if (itr == toItr.end())
            return {-1, false};
        return {itr->second->first, true};
    }
};
#endif
