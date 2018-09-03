//
// Created by hadar.dotan on 9/3/18.
//


#include "IkeaItem.h"

IkeaItem::IkeaItem(std::string &catalogNumber, std::string &itemName, std::string &price, std::string &quantity)
{

    _catalogNumber = catalogNumber;
    _itemName = itemName;
    _price = price;
    _quantity = std::stod(quantity); //todo check

};



IkeaItem::IkeaItem(IkeaItem &other)
{
    _catalogNumber = other._catalogNumber;
    _itemName = other._itemName;
    _price = other._price;
    _quantity = other._quantity;

}




