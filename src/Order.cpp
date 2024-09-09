#pragma once
#include "Order.h"
//class Order {
    Order::Order(int id, int customerId, int distance):id(id),customerId(customerId),distance(distance) {
        this->status = OrderStatus::PENDING;
        this->collectorId = NO_VOLUNTEER;
        this->driverId = NO_VOLUNTEER;
    }
 string Order::stringStatus() const {
        if (status == OrderStatus::PENDING)
            return "PENDING";
        else if (status == OrderStatus::COLLECTING)
            return "COLLECTING";
        else if (status == OrderStatus::DELIVERING)
            return "DELIVERING";
        else if (status == OrderStatus::COMPLETED)
            return "COMPLETED";
        return NULL;
    }
 Order* Order::clone() const {
     Order* o = new Order(this->id, this->customerId, this->distance);
     o->collectorId = this->collectorId;
     o->driverId = this->driverId;
     o->status = this->status;
     return o;
 }
  string Order::boolstring(bool b) {
     if (b)
         return "true";
     return "false";
    }

    int Order::getId() const {
        return this->id;
    }
    int Order::getCustomerId() const {
        return this->customerId;
    }
    void Order::setStatus(OrderStatus status) {
        this->status = status;
    }
    void Order::setCollectorId(int collectorId) {
        this->collectorId = collectorId;
    }
    void Order::setDriverId(int driverId) {
        this->driverId = driverId;
    }
    int Order::getCollectorId() const {
        return this->collectorId;
    }
    int Order::getDriverId() const {
        return this->driverId;
    }
    OrderStatus Order::getStatus() const {
        return this->status;
    }
    int Order::getDistance() const {
        return this->distance;
    }
    const string Order::toString() const {
        string ans = "";
        ans += "OrderId:" + std::to_string(this->getId()) + '\n';
        ans +=  "OrderStatus:" + this->stringStatus() + '\n';
        ans += "CustomerID:" + std::to_string(this->getCustomerId()) + "\n" ;
        if (this->collectorId==-1)
        {
            ans += "Collector: None\n";
        }
        else
        {
            ans +=  "Collector:" + std::to_string(this->getCollectorId()) + '\n';
        }
        if (this->driverId == -1)
        {
            ans += "Driver: None\n";
        }
        else
        {
            ans += "Driver:" + std::to_string(this->getDriverId()) + '\n';
        }
        return ans;
    }