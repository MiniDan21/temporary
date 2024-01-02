/* 
MIT License 

Copyright (c) 2019 МГТУ им. Н.Э. Баумана, кафедра ИУ-6, Михаил Фетисов, 

Программа-заготовка для домашнего задания
*/

#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

const size_t MAX_NAME_LENGTH    = 50;
const size_t MAX_DATE_LENGTH    = 11;


class Order
{
    int _count;
    std::string _date;
public:
    Order() = delete;
    Order(int count, std::string date)
        : _count(count), _date(date)
    {}
    int getCount() const { return _count; }
    std::string getDate() const { return _date; }
};


class AutoPart : public ICollectable
{
    std::string _name;
    std::string _mark;
    std::string _model;
    uint16_t    _cost;
    bool        _in_stock;
    std::vector<Order> _orders;


protected:
    bool invariant() const;

public:
    AutoPart() = delete;
    AutoPart(const AutoPart & p) = delete;

    AutoPart & operator = (const AutoPart & p) = delete;

    AutoPart(const std::string & name, const std::string & mark, const std::string & model, uint16_t cost);
    AutoPart(const std::string & name, const std::string & mark, const std::string & model, uint16_t cost, std::vector<Order> orders);

    const std::string & getName() const;
    const std::string & getModel() const;
    const std::string & getMark() const;
    uint16_t       getCost() const;
    bool       inStock() const;

    void setOrders(const std::vector<Order> & visits);
    const std::vector<Order> &getOrders() const;

    virtual bool   write(std::ostream& os) override;
};


class ItemCollector: public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream& is) override;

    AutoPart & getAutoPartRef(size_t index);
};

#endif // HW_L3_DOMAIN_LAYER_H
