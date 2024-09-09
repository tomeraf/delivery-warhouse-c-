#pragma once
#ifndef VOLUNTEER_H
#define VOLUNTEER_H
#include "Order.h"
#define NO_ORDER -1

class Volunteer {
    public:
        Volunteer(int id, const string &name);
        int getId() const;
        virtual string getType() const = 0;
        const string &getName() const;
        int getActiveOrderId() const;
        void setActiveOrderId(int orderId);
        void setCompletedOrderId(int orderId);
        int getCompletedOrderId() const;
        int getorderInHandId() const;
        void setorderInHandId(int id) ;
        bool isBusy() const; // Signal whether the volunteer is currently processing an order    
        virtual bool hasOrdersLeft() const = 0; // Signal whether the volunteer didn't reach orders limit,Always true for CollectorVolunteer and DriverVolunteer
        virtual bool canTakeOrder(const Order &order) const = 0; // Signal if the volunteer can take the order.      
        virtual void acceptOrder(const Order &order) = 0; // Prepare for new order(Reset activeOrderId,TimeLeft,DistanceLeft,OrdersLeft depends on the volunteer type)
                
        virtual void step() = 0; //Simulate volunteer step,if the volunteer finished the order, transfer activeOrderId to completedOrderId

        virtual string toString() const = 0;
        virtual Volunteer* clone() const = 0; //Return a copy of the volunteer

    protected:
        int completedOrderId; //Initialized to NO_ORDER if no order has been completed yet
        int activeOrderId; //Initialized to NO_ORDER if no order is being processed
        int orderInHand;
    
    private:
        const int id;
        const string name;

};


class CollectorVolunteer: public Volunteer {

    public:
        CollectorVolunteer(int id, const string &name, int coolDown);
        CollectorVolunteer *clone() const override;
        string getType() const;
        void step() override;
        int getCoolDown() const;
        int getTimeLeft() const;
        int setTimeLeft(int timeLeft);
        bool decreaseCoolDown();//Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order &order) const override;
        void acceptOrder(const Order &order) override;
        string toString() const override;
    
    private:
        const int coolDown; // The time it takes the volunteer to process an order
        int timeLeft; // Time left until the volunteer finishes his current order
};

class LimitedCollectorVolunteer: public CollectorVolunteer {

    public:
        LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int maxOrders);
        LimitedCollectorVolunteer *clone() const override;
        string getType() const;
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order &order) const override;
        void acceptOrder(const Order &order) override;

        int getMaxOrders() const;
        int getNumOrdersLeft() const;
        string toString() const override;
    
    private:
        const int maxOrders; // The number of orders the volunteer can process in the whole simulation
        int ordersLeft; // The number of orders the volunteer can still take
};

class DriverVolunteer: public Volunteer {

    public:
        DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep);
        DriverVolunteer *clone() const override;
        string getType() const;
        int getDistanceLeft() const;
        int getMaxDistance() const;
        void SetDistanaceLeft(int DistanaceLeft);
        int getDistancePerStep() const;  
        bool decreaseDistanceLeft(); //Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order &order) const override; // Signal if the volunteer is not busy and the order is within the maxDistance
        void acceptOrder(const Order &order) override; // Assign distanceLeft to order's distance
        void step() override; // Decrease distanceLeft by distancePerStep
        string toString() const override;

    private:
        const int maxDistance; // The maximum distance of ANY order the volunteer can take
        const int distancePerStep; // The distance the volunteer does in one step
        int distanceLeft; // Distance left until the volunteer finishes his current order
};

class LimitedDriverVolunteer: public DriverVolunteer {

    public:
        LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders);
        LimitedDriverVolunteer *clone() const override;
        string getType() const;
        int getMaxOrders() const;
        int getNumOrdersLeft() const;
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order &order) const override; // Signal if the volunteer is not busy, the order is within the maxDistance.
        void acceptOrder(const Order &order) override; // Assign distanceLeft to order's distance and decrease ordersLeft
        string toString() const override;

    private:
        const int maxOrders; // The number of orders the volunteer can process in the whole simulation
        int ordersLeft; // The number of orders the volunteer can still take
};
#endif