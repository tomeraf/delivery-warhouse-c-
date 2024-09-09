#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Order.h"
class Customer {
    public:
        Customer(int id, const string &name, int locationDistance, int maxOrders);
        Customer(int id, const string& name, int locationDistance, int maxOrders, vector<int> ordersId);
        const string &getName() const;
        int getId() const;
        int getCustomerDistance() const;
        int getMaxOrders() const; //Returns maxOrders
        int getNumOrders() const; //Returns num of orders the customer has made so far
        void setOrdersIds(vector<int>& orderIds);
        bool canMakeOrder() const; //Returns true if the customer didn't reach max orders
        const vector<int> &getOrdersIds() const;
        int addOrder(int orderId); //return OrderId if order was added successfully, -1 otherwise
        ~Customer();
        virtual Customer *clone() const = 0; // Return a copy of the customer

        
    private:
        const int id;
        const string name;
        const int locationDistance;
        const int maxOrders;
        vector<int> ordersId;
};


class SoldierCustomer: public Customer {
    public:
        SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders);
        SoldierCustomer(SoldierCustomer* SC);
        SoldierCustomer *clone() const override;
    
    private:
        
};

class CivilianCustomer: public Customer {
    public:
        CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders);
        CivilianCustomer(CivilianCustomer* CC);
        CivilianCustomer *clone() const override;
    
    private:
        
};
#endif