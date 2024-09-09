#pragma once
#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"
class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(WareHouse* wh);
        WareHouse* clone();
        void copy(WareHouse* wh);
        void config(const string& configFilePath);
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        int getCustomerCounter() const;
        int getVolunteerCounter() const;
        int getOrderCounter();
        void addCustomer(Customer* c);
        void addVolunteer(Volunteer* v);
        void close();
        void open();
        void step();
        void restore(WareHouse* backup);
    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int OrderCounter; //For assigning unique Orders IDs
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
};
#endif