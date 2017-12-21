#ifndef DESIGN_RESTAURANT_H
#define DESIGN_RESTAURANT_H
#include "Debug.h"
/*
I. Design Restaurant:
	1. In a restaurant, the waiter takes order from the customer.
	2. The waiter waits for the order to be ready and once ready serves the dishes to the customer.
These are the different actors in the model and I have listed the different actions against each other:
Customer
	1. selects the dish from the menu and call upon a waiter
	2. places the order
	3. enjoys his meal once the dish is served on his plate
	4. asks for the bill
	5. pays for the service
Waiter
	1. responds to the customers call on the table he is waiting
	2. takes the customer's order
	3. places the order in the pending order queue
	4. waits for the order ready notifications
	5. once notification is received, collects the dish and serves the dish to the corresponding customer
	6. receives the bill request from customer
	7. asks the cashier to prepare the bill
	8. gives the bill to the customer and accepts the payment
Cashier
	1. accepts the prepared bill request from the waiter for the given order details
	2. prepares the bills and hands it over to the waiter
	3. accepts the cash from the waiter towards the order
Cook
	1. gets the next order from the pending order queue
	2. prepares the dish and push the order to finish order queue
	3. sends a notification that the order is ready

II. Design McDonalds:
	1. the customer selects the burger and directly places the order with the cashier
	2. the customer waits for the order ready notification.
	   customer upon being notified that the order is ready collects the burger himself.
Customer
	1. pays the cash to the cashier and places his order, get a token number and receipt
	2. waits for the intimation that order for his token is ready
	3. upon intimation/notification, he collects the burger and enjoys his drink
Cashier
	1. takes an order and payment from the customer
	2. upon payment, creates an order and places it into the order queue
	3. provide token and receipt to the customer
Cook
	1. gets the next order from the queue
	2. prepares the burger
	3. places the burger in the completed order queue
	4. places a notification that order for token is ready

III. Deisgn Restaurant Reservation System
*/
namespace DesignRestaurant
{
	struct Order;
	class Person 
	{
	public:

	};
	class Customer : public Person
	{
	public:
		void PlaceOrder(Person * waiter, std::vector<int> & items)
		{

		}
		void PayOrder(Person * waiter)
		{

		}
	};
	class Waiter : public Person
	{
	public:
		void EnqueueCook(Person * customer, std::vector<int> & items)
		{

		}
		void DequeueCook(Order * order)
		{

		}
		void EnqueueCashier(Person * customer)
		{

		}
		void DequeueCashier(Order * order)
		{

		}

	};
	class Cashier : public Person
	{
	public:

	};
	class Cook : public Person
	{
	public:

	};
	struct Order
	{
		Person * customer;
		std::vector<int> menuItem;
		int amount;
	};
	class Restaurant
	{
		friend class Waiter;
		std::unordered_map<Customer*, Order*> m_customerOrder;
		std::queue<Order*> m_cookQueue;
		std::queue<Order*> m_cashierQueue;
		std::queue<Order*> m_customerQueue;
		Cashier m_cashier;
		Cook m_cook;
	public:
		void Update()
		{

		}
	};
}
#endif
