#ifndef DESIGN_VENDING_MACHINE_H
#define DESIGN_VENDING_MACHINE_H
#include "Debug.h"
/*
Vending Machine
Coin and Product must be pointers, so that they can be exchanged between user and vending machine!
*/
namespace DesignVendingMachine
{
	enum Item
	{
		Coke = 0,
		Pepsi = 1,
		DrPepper = 2,
		RootBeer = 3,
	};
	enum Coin
	{
		Penny = 0,
		Nickel = 1,
		Dime = 2,
		Quarter = 3,
	};
	const std::vector<int> CoinVal({ 1, 5, 10, 25 });
	int ComputeCoinBalance(const std::vector<int> & v)
	{
		int res = 0;
		for (int i = 0; i < 4; ++i)
			res += v[i] * CoinVal[i];
		return res;
	}
	std::vector<int> SubtractCoinBalance(std::vector<int> & v, int price)//assume ComputeCoinBalance(v) >= price
	{
		std::vector<int> res(4, 0);
		for (int i = 3; i >= 0; --i)
			while (v[i] && price >= CoinVal[i])
			{
				price -= CoinVal[i];
				--v[i];
				++res[i];
			}
		return res;
	}

	
	class Product
	{
		Item mItem;
		int mPrice;
	public:
		Product(Item i, int price): mItem(i), mPrice(price) {}
		Item GetItem() { return mItem; }
		int GetPrice() { return mPrice; }
	};
	class Person
	{
		std::vector<int> mBalance;
		std::vector<Product*> mProducts;
	public:
		explicit Person(const std::vector<int> & balance) : mBalance(balance), mProducts() {}
		bool HasCoin(Coin i) const
		{
			return mBalance[(int)i] > 0;
		}
		Coin PayCoin(Coin i)
		{
			--mBalance[(int)i];
			return i;
		}
		void GetProduct(Product * p)
		{
			if (p != NULL)
				mProducts.push_back(p);
		}
		void GetRefund(std::vector<int> & v)
		{
			for (int i = 0; i < 4; ++i)
			{
				mBalance[i] += v[i];
				v[i] = 0;
			}
		}
	};
	class VendingMachine
	{
	private:
		std::vector<std::vector<Product*>> mStock;
		std::vector<int> mBalance;
		std::vector<int> mCustomerBalance;
		bool mSelected;
		Item mSelectedItem;
		int mSelectedItemPrice;
	public:
		VendingMachine() : mStock(4, std::vector<Product*>()), mBalance(4, 0), mCustomerBalance(0), mSelected(false), mSelectedItem(Coke), mSelectedItemPrice(0)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 10; ++j)
					mStock[i].push_back(new Product(Item(i), i + 10));
			for (int i = 0; i < 4; ++i)
				mBalance[i] = 10;

		}

		std::vector<std::pair<int, int>> GetItemPriceStockInfo() const//<price,stock>
		{
			
		}
		std::pair<int, bool> SelectItemGetPrice(Item i)//<price,availability>
		{
			if (mStock[(int)i].empty())
				return{ 0,false };
			mSelected = true;
			mSelectedItem = i;
			mSelectedItemPrice = mStock[(int)i].front()->GetPrice();
			return{ mSelectedItemPrice,true };
		}
		bool InsertCoin(Coin c)
		{
			++mCustomerBalance[(int)c];
			int balance = ComputeCoinBalance(mCustomerBalance);
			if (balance >= mSelectedItemPrice)
				return true;
			return false;
		}
		std::vector<int> Refund()
		{
			std::vector<int> res(mCustomerBalance);
			std::vector<int>(4, 0).swap(mCustomerBalance);
			return res;
		}
		Product * GetProduct()
		{
			if (mSelected && ComputeCoinBalance(mCustomerBalance) >= mSelectedItemPrice)
			{
				Product * p = mStock[(int)mSelectedItem].back();
				mStock[(int)mSelectedItem].pop_back();
				mSelected = false;
				std::vector<int> income = SubtractCoinBalance(mCustomerBalance, mSelectedItemPrice);
				for (int i = 0; i < 4; ++i)
					mBalance[i] += income[i];
				return p;
			}
			return NULL;
		}
	
	};
}
#endif
