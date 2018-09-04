//
// Created by hadar.dotan on 9/3/18.
//


#include "IkeaItem.h"

IkeaItem::IkeaItem(string &catalogNumber, string &itemName, string &price, string &quantity, string  &inputString)
{

    _catalogNumber = catalogNumber;
    _itemName = itemName;
    _price = price;
    _quantity = std::stod(quantity); //todo check
    _inputString = inputString;

};



IkeaItem::IkeaItem(IkeaItem &other)
{
    _catalogNumber = other._catalogNumber;
    _itemName = other._itemName;
    _price = other._price;
    _quantity = other._quantity;
    _inputString = other._inputString;

}


const std::string &IkeaItem::getPrice() const
{
    return _price;
}

void IkeaItem::updateQuantity(double _quantity)
{

    double oldQuantity = IkeaItem::_quantity;
    string inputString = IkeaItem::_inputString;
    string oldQuantityString = "Quantity: "+std::to_string(oldQuantity);

    auto pos = inputString.find(oldQuantityString);

    IkeaItem::_quantity += _quantity;
    string newQuantityString = "Quantity: "+std::to_string(IkeaItem::_quantity);

    size_t len = oldQuantityString.length();
    inputString.replace(pos, pos+len, newQuantityString);
    IkeaItem::_inputString = inputString;


}

const string &IkeaItem::getInputString() const {
    return _inputString;
}




