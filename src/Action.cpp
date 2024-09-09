#pragma once
#include "Action.h"

//class BaseAction{
    BaseAction::BaseAction(){
        this->status = ActionStatus::ERROR;
        this->errorMsg = "";
    }
    ActionStatus  BaseAction::getStatus() const
    {
        return status;
    }
     void BaseAction::setRelevantInfo(BaseAction* old) {
        this->status = old->status;
        this->errorMsg = old->errorMsg;
    }
     string  BaseAction::stringStatus() const {
         if (status == ActionStatus::ERROR)
             return "ERROR";
         else if (status == ActionStatus::COMPLETED)
             return "COMPLETED";
         return NULL;
     }
    void  BaseAction::complete() {
        status = ActionStatus::COMPLETED;
    }
    void  BaseAction::error(string errorMsg) {
        status = ActionStatus::ERROR;
        std::cout << "Error: " << errorMsg << '\n';


    }
    string BaseAction::getErrorMsg() const {
        return errorMsg;
    }

//class SimulateStep : public BaseAction {
    SimulateStep::SimulateStep(int numOfSteps): numOfSteps(numOfSteps){

    }
    SimulateStep::SimulateStep(SimulateStep* ss) : numOfSteps(ss->numOfSteps) {
        this->setRelevantInfo(ss);
    }
    void SimulateStep::act(WareHouse& wareHouse)  {
        for (int i = 0; i < numOfSteps; i++)
            wareHouse.step();
        this->complete();
    }
    std::string SimulateStep::toString() const  {
        return "simulateStep " + std::to_string(this->numOfSteps) + ' ' + stringStatus();
    }
    SimulateStep* SimulateStep::clone() const  {
        SimulateStep* ss = new SimulateStep(*this);
        return ss;
    }

//class AddOrder : public BaseAction {
    AddOrder::AddOrder(int id):customerId(id){
    }
    AddOrder::AddOrder(AddOrder* ao) :customerId(ao->customerId) {
        this->setRelevantInfo(ao);
    }
    void AddOrder::act(WareHouse& wareHouse)  {
        Customer* c= &wareHouse.getCustomer(customerId);
        if (c == NULL || !c->canMakeOrder())
            this->error("Cannot place this order");
        else {
            int orderId = wareHouse.getOrderCounter();
            c->addOrder(orderId);
            Order* o = new Order(wareHouse.getOrderCounter(), customerId, c->getCustomerDistance());
            wareHouse.addOrder(o);
            this->complete();
        }
    }
    string AddOrder::toString() const  {
        return "order " + std::to_string(this->customerId) + ' ' + this->stringStatus();
    }
    AddOrder* AddOrder::clone() const  {
        AddOrder* ao =  new AddOrder(*this);
        return ao;
    }

//class AddCustomer : public BaseAction {
    AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders): customerName(customerName), customerType(setCustomerType(customerType)), distance(distance), maxOrders(maxOrders) {
        
    }
    AddCustomer::AddCustomer(AddCustomer* ac) : customerName(ac->customerName), customerType(ac->customerType), distance(ac->distance), maxOrders(ac->maxOrders) {
        this->setRelevantInfo(ac);
    }
    CustomerType AddCustomer::setCustomerType(string ct) {
        if (ct._Equal("soldier"))
            return CustomerType::Soldier;
        else
            return CustomerType::Civilian;
    }
    void AddCustomer::act(WareHouse &wareHouse)
    {
        if (this->customerType == CustomerType::Soldier) {
            SoldierCustomer* SC = new SoldierCustomer(wareHouse.getCustomerCounter(), this->customerName, this->distance, this->maxOrders);
            wareHouse.addCustomer(SC);
        }
        else {
            CivilianCustomer* CC = new CivilianCustomer(wareHouse.getCustomerCounter(), this->customerName, this->distance, this->maxOrders);
            wareHouse.addCustomer(CC);
        }
        this->complete();
    }
    AddCustomer* AddCustomer::clone() const  {
        AddCustomer* ac =  new AddCustomer(*this);
        return ac;
    }
    string AddCustomer::toString() const  {
        string ans = "customer ";
        ans += this->customerName + ' ';
        if (this->customerType==CustomerType::Soldier)
        {
            ans += "soldier ";
        }
        else {
            ans += "civilian ";
        }
        ans += std::to_string(this->distance) + ' ' + std::to_string(this->maxOrders) + ' ';
        ans += this->stringStatus() + '\n';

        return ans;
    }

//class PrintOrderStatus : public BaseAction {
    PrintOrderStatus::PrintOrderStatus(int id):orderId(id) {
    }
    PrintOrderStatus::PrintOrderStatus(PrintOrderStatus* pos) :orderId(pos->orderId) {
        this->setRelevantInfo(pos);
    }
    void PrintOrderStatus::act(WareHouse& wareHouse)  {
        Order o=wareHouse.getOrder(this->orderId);
        std::cout<<o.toString()<<'\n';
        this->complete();

    }
    PrintOrderStatus* PrintOrderStatus::clone() const  {
        PrintOrderStatus* pos =  new PrintOrderStatus(*this);
        return pos;
    }
    string PrintOrderStatus::toString() const  {
        string ans = "orderStatus " + std::to_string(this->orderId);
        ans+= " " + this->stringStatus();
        return ans;
    }

//class PrintCustomerStatus: public BaseAction {
    PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId){
    }
    PrintCustomerStatus::PrintCustomerStatus(PrintCustomerStatus* pcs) : customerId(pcs->customerId) {
        this->setRelevantInfo(pcs);
    }
    void PrintCustomerStatus::act(WareHouse& wareHouse)  {
        Customer* c = &wareHouse.getCustomer(this->customerId);
        std::cout << "CustomerID :" << std::to_string(this->customerId) << '\n';
        vector<int> ordersIds = wareHouse.getCustomer(this->customerId).getOrdersIds();
        for (int i = 0; i < ordersIds.size(); i++)
        {
            std::cout << "OrderId: " << std::to_string(ordersIds.at(i)) << '\n';
            std::cout << "OrderStatus: " << wareHouse.getOrder(ordersIds.at(i)).stringStatus()<<'\n';
        }
        std::cout << "numOrdersLeft: " << std::to_string(c->getMaxOrders() - c->getNumOrders()) << '\n';
        this->complete();
    }
    PrintCustomerStatus* PrintCustomerStatus::clone() const  {
        PrintCustomerStatus* pcs = new PrintCustomerStatus(*this);
        
        return pcs;
    }
    string PrintCustomerStatus::toString() const  {
        string ans =  "customerStatus " + std::to_string(this->customerId) + ' ' + this->stringStatus();
        return ans;
    }

//class PrintVolunteerStatus : public BaseAction {
    PrintVolunteerStatus::PrintVolunteerStatus(int id) : volunteerId(id) {
    }
    PrintVolunteerStatus::PrintVolunteerStatus(PrintVolunteerStatus* pvs) : volunteerId(pvs->volunteerId) {
        this->setRelevantInfo(pvs);
    }
    void PrintVolunteerStatus::act(WareHouse& wareHouse)  {
        std::cout << wareHouse.getVolunteer(volunteerId).toString() << '\n';
        this->complete();
    }
    PrintVolunteerStatus* PrintVolunteerStatus::clone() const  {
        PrintVolunteerStatus* pvs = new PrintVolunteerStatus(*this);
        
        return pvs;
    }
    string PrintVolunteerStatus::toString() const  {
        return "volunteerStatus " + std::to_string(this->volunteerId) + ' '  + this->stringStatus();
    }

//class PrintActionsLog : public BaseAction {
    PrintActionsLog::PrintActionsLog() {
        
    }
    PrintActionsLog::PrintActionsLog(PrintActionsLog* pal) {
        this->setRelevantInfo(pal);
    }
    void PrintActionsLog::act(WareHouse& wareHouse)  {
        vector<BaseAction*> actions = wareHouse.getActions();
        for (int i = 0; i < actions.size(); i++)
        {
            std::cout << actions.at(i)->toString() << '\n';
        }
        this->complete();
    }
    PrintActionsLog* PrintActionsLog::clone() const  {
        PrintActionsLog* pal = new PrintActionsLog(*this);
        return pal;
    }
    string PrintActionsLog::toString() const  {
        return "log" + this->stringStatus();
    }

//class Close : public BaseAction {
    Close::Close() {

    }
    Close::Close(Close* c) {
        this->setRelevantInfo(c);
    }
    void Close::act(WareHouse& wareHouse)  {
        wareHouse.close();
        this->complete();
    }
    Close* Close::clone() const  {
        Close* c = new Close(*this);
        return c;
    }
    string Close::toString() const  {
        return "";
    }

//class BackupWareHouse : public BaseAction {
    BackupWareHouse::BackupWareHouse() {
        
    }
    BackupWareHouse::BackupWareHouse(BackupWareHouse* bwh) {
        this->setRelevantInfo(bwh);
    }
    void BackupWareHouse::act(WareHouse& wareHouse)  {
        backup = wareHouse.clone();
        this->complete();
    }
    BackupWareHouse* BackupWareHouse::clone() const  {
        BackupWareHouse* BW = new BackupWareHouse(*this);
        return BW;
    }
    string BackupWareHouse::toString() const  {
        return "backup " + this->stringStatus();
    }

//class RestoreWareHouse : public BaseAction {
    RestoreWareHouse::RestoreWareHouse() {

    }
    RestoreWareHouse::RestoreWareHouse(RestoreWareHouse* rwh) {
        this->setRelevantInfo(rwh);

    }
    void RestoreWareHouse::act(WareHouse& wareHouse)  {
        if (backup == NULL)
            this->error("No backup available");
        else
        {
            wareHouse.restore(backup);
            this->complete();
        }
    }
    RestoreWareHouse* RestoreWareHouse::clone() const  {
        RestoreWareHouse* RW = new RestoreWareHouse(*this);
        return RW;
    }
    string RestoreWareHouse::toString() const  {
        return "Restore " + this->stringStatus();
    }
