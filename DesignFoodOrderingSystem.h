#ifndef _DESIGN_FOOD_ORDERING_SYSTEM_H
#define _DESIGN_FOOD_ORDERING_SYSTEM_H
#include "Debug.h"
/*

 */
namespace DesignFoodOrderingSystem
{
    struct CompositeUserID
    {
        std::string name;
        std::string phone;//to distinguish duplicated user names
        std::string timestamp;//to distinguish duplicated user orders
        bool operator==(const CompositeUserID & rhs) const
        {
            return name == rhs.name && phone == rhs.phone && timestamp == rhs.timestamp;
        }
    };
    struct CompositeUserIDHash
    {
        size_t operator()(const CompositeUserID & id) const
        {
            size_t res = 17;
            res = res * 31 + std::hash<std::string>()(id.name);
            res = res * 31 + std::hash<std::string>()(id.phone);
            res = res * 31 + std::hash<std::string>()(id.timestamp);
            return res;
        }
    };
    struct UserData
    {
        std::string address;
        std::string creditCard;
        std::string email;
    };
    struct Order
    {
        std::unordered_map<std::string, int> foodCount;
        int totalCount;
        int totalPrice;
    };
    struct Cook
    {
        std::string foodName;
        std::unordered_set<CompositeUserID, CompositeUserIDHash> users;
    };

    class FoodOrderingSystem
    {
        std::unordered_map<CompositeUserID, Order, CompositeUserIDHash> userOrder;
        std::unordered_map<CompositeUserID, UserData, CompositeUserIDHash> userInfo;
        std::unordered_map<std::string, int> foodPrice;
        std::unordered_map<std::string, int> foodStock;
        std::list<Cook> cookQue;
        std::unordered_map<std::string, std::list<Cook>::iterator> foodToCook;

    public:
        FoodOrderingSystem(){}

        void PlaceOrder(const CompositeUserID & id, std::string food)
        {

        }
        void CheckOut(const CompositeUserID & id)
        {

        }

    private:
        int CountCookFood(const Cook & c)
        {
            int res = 0;
            for (const auto & u : c.users)
                if (userOrder.count(u) && userOrder[u].foodCount.count(c.foodName))
                    res += userOrder[u].foodCount[c.foodName];
            return res;
        }
    };
}
#endif
