#pragma once
#include "Volunteer.h"
//class Volunteer {
    Volunteer::Volunteer(int id, const string& name): id(id),name(name),orderInHand(-1) {
        this->completedOrderId = NO_ORDER;
        this->activeOrderId = NO_ORDER;
    }
    int Volunteer::getId() const {
        return this->id;
    }
    const string& Volunteer::getName() const {
        return this->name;
    }
    int Volunteer::getActiveOrderId() const {
        return this->activeOrderId;
    }
    void Volunteer::setorderInHandId(int id) {
        this->orderInHand = id;
    }
    void Volunteer::setActiveOrderId(int orderId) {
        this->activeOrderId = orderId;
    }
    int Volunteer::getorderInHandId() const {
        return this->orderInHand;
    }
    int Volunteer::getCompletedOrderId() const {
        return this->completedOrderId;
    }
    void Volunteer::setCompletedOrderId(int orderId) {
        this->completedOrderId = orderId;
    }
    bool Volunteer::isBusy() const { // Signal whether the volunteer is currently processing an order
        return (this->getActiveOrderId() != -1);
    }

//class CollectorVolunteer: public Volunteer {

    CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown):Volunteer(id,name), coolDown(coolDown), timeLeft(0){
    }
    CollectorVolunteer* CollectorVolunteer::clone() const  {
        CollectorVolunteer* volt = new CollectorVolunteer(this->getId(), this->getName(), this->coolDown);
        volt->timeLeft = this->timeLeft;
        return volt;
    }
    string CollectorVolunteer::getType() const {
        return "CV";
    }
    void CollectorVolunteer::step()  {
        if (decreaseCoolDown())
        {
            completedOrderId = activeOrderId;
            activeOrderId = NO_ORDER;
        }

    }
    int CollectorVolunteer::getCoolDown() const {
        return this->coolDown;
    }
    int CollectorVolunteer::getTimeLeft() const {
        return this->timeLeft;
    }
    int CollectorVolunteer::setTimeLeft(int timeLeft){
         this->timeLeft = timeLeft;
         return timeLeft;
    }
    
    bool CollectorVolunteer::decreaseCoolDown() {//Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
        this->timeLeft = std::max(timeLeft - 1, 0);
        return timeLeft == 0;
    }
    bool CollectorVolunteer::hasOrdersLeft() const  { return true; }
    bool CollectorVolunteer::canTakeOrder(const Order& order) const  { return (!(isBusy()) && hasOrdersLeft()); }
    void CollectorVolunteer::acceptOrder(const Order& order)  {
        this->timeLeft = this->coolDown;
        this->setActiveOrderId(order.getId());
        this->orderInHand = this->getActiveOrderId();
    }
    string CollectorVolunteer::toString() const {
        string ans = "";
        ans += "VolunteerID:" + std::to_string(this->getId()) + '\n';
        ans += "isBusy:" + Order::boolstring(this->isBusy()) + '\n';
        ans += "OrderId:" + std::to_string(this->getActiveOrderId()) + '\n';
        ans += "timeLeft:" + std::to_string(this->getTimeLeft()) + '\n';
        ans += "ordersLeft: No Limit\n";
        return ans;
    }

//class LimitedCollectorVolunteer: public CollectorVolunteer {

    LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string& name, int coolDown, int maxOrders) : CollectorVolunteer(id, name, coolDown),maxOrders(maxOrders),ordersLeft(maxOrders) {
    }
    LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const  {
        LimitedCollectorVolunteer* volt = new LimitedCollectorVolunteer(this->getId(), this->getName(), this->getCoolDown(), this->maxOrders);
        volt->setTimeLeft(this->getTimeLeft());
        volt->ordersLeft = this->ordersLeft;
        return volt;
    }
    string LimitedCollectorVolunteer::getType() const {
        return "LCV";
    }
    bool LimitedCollectorVolunteer::hasOrdersLeft() const  {
        return(ordersLeft > 0);
    }
    bool LimitedCollectorVolunteer::canTakeOrder(const Order& order) const  {
        return (hasOrdersLeft() && !(isBusy()));
    }
    void LimitedCollectorVolunteer::acceptOrder(const Order& order)  {
        this->setTimeLeft(this->getCoolDown());
        this->setActiveOrderId(order.getId());
        ordersLeft--;
    }

    int LimitedCollectorVolunteer::getMaxOrders() const {
        return this->maxOrders;
    }
    int LimitedCollectorVolunteer::getNumOrdersLeft() const {
        return this->ordersLeft;
    }
    string LimitedCollectorVolunteer::toString() const  {
        string ans="";
        ans += "VolunteerID:" + std::to_string(this->getId()) + '\n';
        ans += "isBusy:" + Order::boolstring(this->isBusy()) + '\n';
        ans += "OrderId:" + std::to_string(this->getActiveOrderId()) + '\n';
        ans += "timeLeft:" + std::to_string(this->getTimeLeft()) + '\n';
        ans += "ordersLeft:" + std::to_string(this->ordersLeft) + '\n';
        return ans;
    }

//class DriverVolunteer : public Volunteer {

    DriverVolunteer::DriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep) : Volunteer(id,name),maxDistance(maxDistance),distanceLeft(0), distancePerStep(distancePerStep) {
    }
    DriverVolunteer* DriverVolunteer::clone() const  {
        DriverVolunteer* volt = new DriverVolunteer(this->getId(), this->getName(), this->maxDistance, this->distancePerStep);
        volt->distanceLeft = this->distanceLeft;
        return volt;
    }
    string DriverVolunteer::getType() const {
        return "DV";
    }
    int DriverVolunteer::getDistanceLeft() const {
        return this->distanceLeft;
    }
    int DriverVolunteer::getMaxDistance() const {
        return this->maxDistance;
    }
    int DriverVolunteer::getDistancePerStep() const {
        return this->distancePerStep;
    }
    void DriverVolunteer::SetDistanaceLeft(int DistanaceLeft) {
        this->distanceLeft = DistanaceLeft;
    }
    bool DriverVolunteer::decreaseDistanceLeft() { //Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
        this->distanceLeft = std::max(0, distanceLeft - distancePerStep);
        return this->distanceLeft == 0;
    }
    bool DriverVolunteer::hasOrdersLeft() const  {
        return true;
    }
    bool DriverVolunteer::canTakeOrder(const Order& order) const  { // Signal if the volunteer is not busy and the order is within the maxDistance
        return (!isBusy() && this->maxDistance >= order.getDistance());
    }
    void DriverVolunteer::acceptOrder(const Order& order)  { // Assign distanceLeft to order's distance
        this->distanceLeft=order.getDistance();
        this->setActiveOrderId(order.getId());
        this->orderInHand = this->getActiveOrderId();
    }
    void DriverVolunteer::step()  { // Decrease distanceLeft by distancePerStep
        if (decreaseDistanceLeft())
        {
            completedOrderId = activeOrderId;
            activeOrderId = NO_ORDER;
        }
    }
    string DriverVolunteer::toString() const  {
        string ans = "";
        ans += "VolunteerID:" + std::to_string(this->getId()) + '\n';
        ans += "isBusy:" + Order::boolstring(this->isBusy()) + '\n';
        ans += "OrderId:" + std::to_string(this->getActiveOrderId()) + '\n';
        ans += "distanceLeft:" + std::to_string(this->getDistanceLeft()) + '\n';
        ans += "ordersLeft: No Limit\n";
        return ans;
    }


//class LimitedDriverVolunteer : public DriverVolunteer {

    LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep, int maxOrders) :DriverVolunteer(id, name, maxDistance, distancePerStep),maxOrders(maxOrders),ordersLeft(maxOrders) {
}

    LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const {
        LimitedDriverVolunteer* volt = new LimitedDriverVolunteer(this->getId(), this->getName(), this->getMaxDistance(), this->getDistancePerStep(),this->maxOrders);
        volt->SetDistanaceLeft(this->getDistanceLeft());
        volt->ordersLeft =this->ordersLeft;
        return volt;

    }
    string LimitedDriverVolunteer::getType() const {
        return "LDV";
    }
    int LimitedDriverVolunteer::getMaxOrders() const {
        return this->maxOrders;
    }
    int LimitedDriverVolunteer::getNumOrdersLeft() const {

        return this->ordersLeft;
    }
    bool LimitedDriverVolunteer::hasOrdersLeft() const {
        return this->ordersLeft != 0;
    }
    bool LimitedDriverVolunteer::canTakeOrder(const Order& order) const { // Signal if the volunteer is not busy, the order is within the maxDistance.
        return (!isBusy() && this->getMaxDistance() >= order.getDistance() && this->hasOrdersLeft());
    }
    void LimitedDriverVolunteer::acceptOrder(const Order& order)  { // Assign distanceLeft to order's distance and decrease ordersLeft
        this->SetDistanaceLeft(order.getDistance());
        this->ordersLeft--;
        this->setActiveOrderId(order.getId());

    }
    string LimitedDriverVolunteer::toString() const {
        string ans = "";
        ans += "VolunteerID:" + std::to_string(this->getId()) + '\n';
        ans += "isBusy:" + Order::boolstring(this->isBusy()) + '\n';
        ans += "OrderId:" + std::to_string(this->getActiveOrderId()) + '\n';
        ans += "distanceLeft:" + std::to_string(this->getDistanceLeft()) + '\n';
        ans += "ordersLeft:" + std::to_string(this->ordersLeft) + '\n';
        return ans;
    }