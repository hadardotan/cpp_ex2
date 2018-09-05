//
// Created by hadar.dotan on 9/3/18.
//


#include <iostream>
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

    string inputString = this->_inputString;
    string oldQuantityString = "Quantity";
    string subStr1, subStr2, subStr3;
    auto quantityPos = inputString.find(oldQuantityString);
    subStr1 = inputString.substr(0,quantityPos);
    subStr2 = inputString.substr(quantityPos);
    auto newLinePos = subStr2.find("\n");
    subStr3 = subStr2.substr(newLinePos);
    this->_quantity += _quantity;
    string newQuantityString = "Quantity: "+std::to_string(IkeaItem::_quantity);
    newQuantityString = newQuantityString.erase ( newQuantityString.find_last_not_of('0') + 1, std::string::npos );
    newQuantityString = newQuantityString.erase ( newQuantityString.find_last_not_of('.') + 1, std::string::npos );
    inputString = subStr1+newQuantityString+subStr3;
    this->_inputString = inputString;

}

const string &IkeaItem::getInputString() const {
    return _inputString;
}

bool IkeaItem::isPerUnit() const {
    return _isPerUnit;
}

double IkeaItem::getQuantity() const {
    return _quantity;
}




