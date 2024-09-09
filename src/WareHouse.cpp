#pragma once
#include "WareHouse.h"
//class WareHouse {
    WareHouse::WareHouse(const string &configFilePath): isOpen(false),customerCounter(0),volunteerCounter(0), OrderCounter(0){
        this->config(configFilePath);
    }
    WareHouse::WareHouse(WareHouse* wh) {
        for (int i = 0; i < wh->actionsLog.size(); i++)
        {
            this->actionsLog.push_back(wh->actionsLog.at(i)->clone());
        }
        for (int i = 0; i < wh->volunteers.size(); i++)
        {
            this->volunteers.push_back(wh->volunteers.at(i)->clone());
        }
        for (int i = 0; i < wh->pendingOrders.size(); i++)
        {
            this->pendingOrders.push_back(wh->pendingOrders.at(i)->clone());
        }
        for (int i = 0; i < wh->inProcessOrders.size(); i++)
        {
            this->inProcessOrders.push_back(wh->inProcessOrders.at(i)->clone());
        }
        for (int i = 0; i < wh->completedOrders.size(); i++)
        {
            this->completedOrders.push_back(wh->completedOrders.at(i)->clone());
        }
        for (int i = 0; i < wh->customers.size(); i++)
        {
            this->customers.push_back(wh->customers.at(i)->clone());
        }
        this->customerCounter = wh->customerCounter;
        this->OrderCounter = wh->OrderCounter;
        this->volunteerCounter = wh->volunteerCounter;
        this->isOpen = wh->isOpen;
    }
    void WareHouse::copy(WareHouse* wh) {
        for (int i = 0; i < wh->actionsLog.size(); i++)
        {
            this->actionsLog.push_back(wh->actionsLog.at(i)->clone());
        }
        for (int i = 0; i < wh->volunteers.size(); i++)
        {
            this->volunteers.push_back(wh->volunteers.at(i)->clone());
        }
        for (int i = 0; i < wh->pendingOrders.size(); i++)
        {
            this->pendingOrders.push_back(wh->pendingOrders.at(i)->clone());
        }
        for (int i = 0; i < wh->inProcessOrders.size(); i++)
        {
            this->inProcessOrders.push_back(wh->inProcessOrders.at(i)->clone());
        }
        for (int i = 0; i < wh->completedOrders.size(); i++)
        {
            this->completedOrders.push_back(wh->completedOrders.at(i)->clone());
        }
        for (int i = 0; i < wh->customers.size(); i++)
        {
            this->customers.push_back(wh->customers.at(i)->clone());
        }
        this->customerCounter = wh->customerCounter;
        this->OrderCounter = wh->OrderCounter;
        this->volunteerCounter = wh->volunteerCounter;
        this->isOpen = wh->isOpen;
    }
    void WareHouse::config(const string& configFilePath) {
        std::vector<std::string> outputs;
        std::ifstream infile(configFilePath);
        string line;
        while (std::getline(infile, line)) {
            string words [6];
            string word = "";
            int i = 0;
            std::istringstream linereader(line);
            while (std::getline(linereader, word, ' ') && i<6) {
                words[i]=word;
                    i++;
            }
            string name = words[1];
            string type = words[2];
            if (words[0] == "customer")
            {
                int distance = stoi(words[3]);
                int maxOrders = stoi(words[4]);
                if (type == "soldier")
                {
                    SoldierCustomer* SC = new SoldierCustomer(customerCounter, name, distance, maxOrders);
                    this->addCustomer(SC);
                }
                else//civilian
                {
                    CivilianCustomer* CC = new CivilianCustomer(customerCounter, name, distance, maxOrders);
                    this->addCustomer(CC);
                }
            }
            else//Volunteers
            {
                int CD = stoi(words[3]);
                if (type == "collector")
                {
                    CollectorVolunteer* CV = new CollectorVolunteer(volunteerCounter, name, CD);
                    this->addVolunteer(CV);
                }
                else if (type == "limited_collector") {
                    LimitedCollectorVolunteer* LCV = new LimitedCollectorVolunteer(volunteerCounter, name, CD, stoi(words[4]));
                    this->addVolunteer(LCV);
                }
                else //drivers
                {
                    int maxD = stoi(words[3]);
                    int step = stoi(words[4]);
                    if (type == "driver") {
                        DriverVolunteer* DV = new DriverVolunteer(volunteerCounter, name, maxD, step);
                        this->addVolunteer(DV);
                    }
                    else // limited_driver
                    {
                        LimitedDriverVolunteer* LDV = new LimitedDriverVolunteer(volunteerCounter, name, maxD, step, stoi(words[5]));
                        this->addVolunteer(LDV);
                    }
                }
            }
        }
    }
    void WareHouse::start(){
        this->open();
        std::cout<<"Warehouse is open!"<<'\n';
        while (isOpen)
        {
            char s[712];
            std::cin.getline(s, 712);
            string words[10];
            std::istringstream line(s);
            string word;
            int i = 0;
            while (std::getline(line, word, ' ')) {
                words[i] = word;
                i++;
            }
            string action = words[0];
            if (action._Equal("step")) {
                SimulateStep* step = new SimulateStep(stoi(words[1]));
                addAction(step);
            }
            else if (action._Equal("order")) {
                AddOrder* order = new AddOrder(stoi(words[1]));
                addAction(order);
            }
            else if (action._Equal("customer")) {
                AddCustomer* customer = new AddCustomer(words[1], words[2], stoi(words[3]), stoi(words[4]));
                addAction(customer);
            }
            else if (action._Equal("orderStatus")) {
                PrintOrderStatus* orderstatus = new PrintOrderStatus(stoi(words[1]));
                addAction(orderstatus);
            }
            else if (action._Equal("customerStatus")) {
                PrintCustomerStatus* customerstatus = new PrintCustomerStatus(stoi(words[1]));
                addAction(customerstatus);
            }
            else if (action._Equal("volunteerStatus")) {
                PrintVolunteerStatus* vstatus = new PrintVolunteerStatus(stoi(words[1]));
                addAction(vstatus);
            }
            else if (action._Equal("log")) {
                PrintActionsLog* logger = new PrintActionsLog();
                addAction(logger);
            }
            else if (action._Equal("close")) {
                Close* close = new Close();
                addAction(close);
            }
            else if (action._Equal("backup")) {
                BackupWareHouse* BU = new BackupWareHouse();
                addAction(BU);
            }
            else if (action._Equal("restore")) {
                RestoreWareHouse* restore = new RestoreWareHouse();
                addAction(restore);
            }
        }
    }
    void WareHouse::addOrder(Order* order) {
        this->pendingOrders.push_back(order);
        OrderCounter++;
    }
    void WareHouse::addAction(BaseAction* action) {
        action->act(*this);
        this->actionsLog.push_back(action);
    }
    Customer& WareHouse::getCustomer(int customerId) const {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers.at(i)->getId() == customerId) {
                return *customers.at(i);
            }
        }
        Customer* c = NULL;
        return *c;
    }
    Volunteer& WareHouse::getVolunteer(int volunteerId) const {
        for (int i = 0; i < volunteers.size(); i++)
        {
            if (volunteers.at(i)->getId() == volunteerId) {
                return *volunteers.at(i);
            }
        }
        Volunteer* v = NULL;
        return *v;
    }
    Order& WareHouse::getOrder(int orderId) const {
        for (int i = 0; i < pendingOrders.size(); i++)
        {
            if (pendingOrders.at(i)->getId() == orderId) {
                return *pendingOrders.at(i);
            }
        }
        for (int i = 0; i < inProcessOrders.size(); i++)
        {
            if (inProcessOrders.at(i)->getId() == orderId) {
                return *inProcessOrders.at(i);
            }
        }
        for (int i = 0; i < completedOrders.size(); i++)
        {
            if (completedOrders.at(i)->getId() == orderId) {
                return *completedOrders.at(i);
            }
        }
        Order* o = NULL;
        return *o;
    }
    int WareHouse::getCustomerCounter() const {
        return customerCounter;
    }
    int WareHouse::getVolunteerCounter() const {
        return volunteerCounter;
    }
    int WareHouse::getOrderCounter()  {
        return OrderCounter;
    }
    void WareHouse::addCustomer(Customer* c) {
        customers.push_back(c);
        customerCounter++;
    }
    void WareHouse::addVolunteer(Volunteer* v) {
        volunteers.push_back(v);
        volunteerCounter++;
    }
    const vector<BaseAction*>& WareHouse::getActions() const {
        return this->actionsLog;
    }
    void WareHouse::close() {
        for (int i = 0; i < pendingOrders.size(); i++)
        {
            string ans = "";
            Order* o = pendingOrders.at(i);
            ans += std::to_string(o->getId()) + " , CustomerID: " + std::to_string(o->getCustomerId());
            ans += " , Status: " + o->stringStatus() + '\n';
            std::cout << ans;
            delete o;
        }
        for (int i = 0; i < inProcessOrders.size(); i++)
        {
            string ans = "";
            Order* o = inProcessOrders.at(i);
            ans += std::to_string(o->getId()) + " , CustomerID: " + std::to_string(o->getCustomerId());
            ans += " , Status: " + o->stringStatus() + '\n';
            std::cout << ans;
            delete o;
        }
        for (int i = 0; i < completedOrders.size(); i++)
        {
            string ans = "";
            Order* o = completedOrders.at(i);
            ans += std::to_string(o->getId()) + " , CustomerID: " + std::to_string(o->getCustomerId());
            ans += " , Status: " + o->stringStatus() + '\n';
            std::cout << ans;
            delete o;
        }
        isOpen = false;
        for (int i = 0; i < actionsLog.size(); i++){delete actionsLog.at(i);}
        for (int i = 0; i < volunteers.size(); i++) { delete volunteers.at(i); }
        for (int i = 0; i < customers.size(); i++) { delete customers.at(i); }

    }
    void WareHouse::open() {
        this->isOpen = true;
    }
    void WareHouse::step() {
        for (int i = 0; i < pendingOrders.size(); i++) {
            Order* o = pendingOrders.at(i);
            bool found = false;
            for (int m = 0; m < volunteers.size() && !found; m++) {
                Volunteer* v = volunteers.at(m);
                if (o->getStatus() == OrderStatus::PENDING) {
                    if ((v->getType()._Equal("CV") || v->getType()._Equal("LCV")) && v->canTakeOrder(*o)) {
                        v->acceptOrder(*o);
                        o->setCollectorId(v->getId());
                        o->setStatus(OrderStatus::COLLECTING);
                        inProcessOrders.push_back(o);
                        pendingOrders.erase(pendingOrders.begin() + i);
                        found = true;
                        i--;
                    }
                }
                else if (o->getStatus() == OrderStatus::COLLECTING)
                    if ((v->getType()._Equal("DV") || v->getType()._Equal("LDV")) && v->canTakeOrder(*o)) {
                        v->acceptOrder(*o);
                        o->setDriverId(v->getId());
                        o->setStatus(OrderStatus::DELIVERING);
                        inProcessOrders.push_back(o);
                        pendingOrders.erase(pendingOrders.begin() + i);
                        found = true;
                        i--;
                    }

            }
        }
        for (int i = 0; i < volunteers.size(); i++) {
            Volunteer* v = &getVolunteer(i);
            v->step();
            if(!v->isBusy() && v->getorderInHandId()!=-1){
                Order* o = &this->getOrder(v->getCompletedOrderId());
                if (v->getType()._Equal("CV") || v->getType()._Equal("LCV")) {
                    pendingOrders.push_back(o);
                    inProcessOrders.erase(std::find(inProcessOrders.begin(), inProcessOrders.end(), o));
                    v->setorderInHandId(-1);
                    if (v->getType()._Equal("LCV") && !v->hasOrdersLeft()) {
                        volunteers.erase(std::find(volunteers.begin(), volunteers.end(), v));
                        delete v;
                        i--;
                    }
                }
                else{ //if (v->getType()._Equal("DV") || v->getType()._Equal("LDV")) {
                    completedOrders.push_back(o);
                    inProcessOrders.erase(std::find(inProcessOrders.begin(), inProcessOrders.end(), o));
                    o->setStatus(OrderStatus::COMPLETED);
                    v->setorderInHandId(-1);
                    if (v->getType()._Equal("LDV") && !v->hasOrdersLeft()) {
                        volunteers.erase(std::find(volunteers.begin(), volunteers.end(), v));
                        delete v;
                        i--;
                    }
                }
            }
        }

    }
    void WareHouse::restore(WareHouse* backup)
    {
        this->copy(backup);
    }
    WareHouse* WareHouse::clone() {
        WareHouse* wh = new WareHouse(this);
        return wh;
    }
