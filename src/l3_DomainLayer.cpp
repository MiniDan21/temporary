/* Программа-заготовка для домашнего задания
*/
#include <iostream>
#include "hw/l3_DomainLayer.h"

using namespace std;


bool AutoPart::invariant() const
{   
    return !_name.empty() && _name.size() <= MAX_NAME_LENGTH
        && !_model.empty() && _model.size() <= MAX_NAME_LENGTH
        && !_mark.empty() && _mark.size() <= MAX_NAME_LENGTH
        && _cost > 0;
}

AutoPart::AutoPart(const std::string & name, const std::string & mark, const std::string & model, uint16_t cost)
    : _name(name), _model(model), _cost(cost), _in_stock(true), _mark(mark)
{
    assert(invariant());
}

AutoPart::AutoPart(const std::string & name, const std::string & mark, const std::string & model, uint16_t cost, std::vector<Order> orders)
    : _name(name), _model(model), _cost(cost), _in_stock(true), _mark(mark), _orders(orders)
{
    assert(invariant());
}

const string & AutoPart::getName() const
{
    return _name;
}

const string & AutoPart::getModel() const
{
    return _model;
}

uint16_t AutoPart::getCost() const
{
    return _cost;
}

const string & AutoPart::getMark() const
{
    return _mark;
}

bool AutoPart::inStock() const
{
    return _in_stock;
}

bool   AutoPart::write(ostream& os)
{
    writeString(os, _name);
    writeString(os, _mark);
    writeString(os, _model);
    writeNumber(os, _cost);

    return os.good();
}

void AutoPart::setOrders(const std::vector<Order> &orders)
{
    _orders = orders;
}

const std::vector<Order> &AutoPart::getOrders() const
{
    return _orders;
}

shared_ptr<ICollectable> ItemCollector::read(istream& is)
{
    string   name = readString(is, MAX_NAME_LENGTH);
    string   mark  = readString(is, MAX_NAME_LENGTH);
    string   model  = readString(is, MAX_NAME_LENGTH);
    uint16_t cost   = readNumber<uint16_t>(is);

    size_t   orders_qount = readNumber<size_t>(is);

    vector<Order> v;

    v.reserve(orders_qount);
    for(size_t i=0; i < orders_qount; ++i)
    {
        int count = readNumber<int>(is);
        std::string date = readString(is, MAX_DATE_LENGTH);

        v.push_back(Order(count, date));
    }

    return std::make_shared<AutoPart>(name, mark, model, cost);
}

AutoPart &ItemCollector::getAutoPartRef(size_t index)
{
    AutoPart & p = *static_cast<AutoPart *>(getItem(index).get());

    return p;
}