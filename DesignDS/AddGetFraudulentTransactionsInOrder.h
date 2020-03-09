#ifndef _ADD_GET_FRAUDULENT_TRANSACTIONS_IN_ORDER_H
#define _ADD_GET_FRAUDULENT_TRANSACTIONS_IN_ORDER_H
#include "Debug.h"
/*
Bloomberg

 */
class AddGetFraudulentTransactionsInOrder
{
public:
    struct Transaction
    {
        Transaction(const std::string & name_, int val_, int timestamp_, const std::string & location_)
        : name(name_), val(val_), timestamp(timestamp_), location(location_), isFraud(false)
                {}
        std::string name;
        int val;
        int timestamp;
        std::string location;
        bool isFraud;
    };
    AddGetFraudulentTransactionsInOrder(){}
private:
    std::list<Transaction> transactionList;
    std::unordered_map<std::string, std::vector<std::list<Transaction>::iterator>> usrToTransactions;
public:
    void Add(const std::string & name, int val, int timestamp, const std::string & location)
    {
        transactionList.push_back({name, val, timestamp, location});
        usrToTransactions[name].push_back(std::prev(transactionList.end()));
        if (usrToTransactions[name].size() >= 2 && (*std::prev(usrToTransactions[name].end()))->timestamp - (*std::prev(std::prev(usrToTransactions[name].end())))->timestamp <= 60)
            (*std::prev(usrToTransactions[name].end()))->isFraud = true;
    }

    std::vector<Transaction> GetAllTransactionsInOrder()
    {
        std::vector<Transaction> res;
        for (const auto & t : transactionList)
            res.push_back(t);

        std::ostringstream oss;
        for (const auto & t : res)
            oss << "[" << t.name << "," << t.val << "," << t.timestamp << "," << t.location << "," << t.isFraud << "],";
        std::cout << "GetAllTransactionsInOrder: " << oss.str() << std::endl;
        return res;
    }

    std::vector<Transaction> GetAllFradulentTransactionsInOrder()
    {
        std::vector<Transaction> res;
        for (const auto & t : transactionList)
            if (t.isFraud)
                res.push_back(t);

        std::ostringstream oss;
        for (const auto & t : res)
            oss << "[" << t.name << "," << t.val << "," << t.timestamp << "," << t.location << "," << t.isFraud << "],";
        std::cout << "GetAllFraudulentTransactionsInOrder: " << oss.str() << std::endl;
        return res;
    }
};
#endif
