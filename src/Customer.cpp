#pragma once
#include "Customer.h"
//class Customer {

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders):id(id),name(name),locationDistance(locationDistance),maxOrders(maxOrders){
        
    }
Customer::Customer(int id, const string& name, int locationDistance, int maxOrders, vector<int> ordersId) :id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders),ordersId(ordersId) {

    }
    const string& Customer::getName() const {
        return this->name;
    }
    int Customer::getId() const {
        return this->id;
    }
    int Customer::getCustomerDistance() const {
        return this->locationDistance;
    }
    int Customer::getMaxOrders() const { //Returns maxOrders
        return this->maxOrders;
    }
    int Customer::getNumOrders() const { //Returns num of orders the customer has made so far
        return this->ordersId.size();
    }
    bool Customer::canMakeOrder() const { //Returns true if the customer didn't reach max orders
        return (this->getNumOrders() < this->maxOrders);
    }
    const vector<int>& Customer::getOrdersIds() const {
        return this->ordersId;
    }
    void Customer::setOrdersIds(vector<int>& orderIds) {
        this->ordersId = orderIds;
    }
    int Customer::addOrder(int orderId) { //return OrderId if order was added successfully, -1 otherwise
        if (canMakeOrder())
        {
            ordersId.push_back(orderId);
            return orderId;
        }
        else
        {
            return -1;
        }
    }

    Customer::~Customer()
    {
        ordersId.clear();
    }

//class SoldierCustomer: public Customer {
    SoldierCustomer::SoldierCustomer(int id, const string& name, int locationDistance, int maxOrders)
        : Customer(id, name, locationDistance, maxOrders) {
    }
    SoldierCustomer::SoldierCustomer(SoldierCustomer* SC) : Customer(SC->getId(), SC->getName(), SC->getCustomerDistance(), SC->getMaxOrders(),SC->getOrdersIds()){
    }
    SoldierCustomer* SoldierCustomer::clone() const {
        SoldierCustomer* cust = new SoldierCustomer(*this);
        return cust;
    }

//class CivilianCustomer: public Customer {

    CivilianCustomer::CivilianCustomer(int id, const string& name, int locationDistance, int maxOrders): Customer(id, name, locationDistance, maxOrders) {
    }
    CivilianCustomer::CivilianCustomer(CivilianCustomer* CC) : Customer(CC->getId(), CC->getName(), CC->getCustomerDistance(), CC->getMaxOrders(), CC->getOrdersIds()) {
    }
    CivilianCustomer* CivilianCustomer::clone() const {
        CivilianCustomer* cust = new CivilianCustomer(*this);
        return cust;
    }