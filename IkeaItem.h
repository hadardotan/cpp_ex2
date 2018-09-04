//
// Created by Visitor on 9/1/2018.
//

#ifndef CPP_EX2_IKEAITEM_H
#define CPP_EX2_IKEAITEM_H

#endif //CPP_EX2_IKEAITEM_H


#include <string>
#include <array>
using std::string;

/**
 * constants
 *
 */
#define FURNITURE_DIM 3


/**
 * class represent an item in IKEA store
 */
class IkeaItem
{


public:

    /**
     * default ctor
     * @param catalogNumber
     * @param itemName
     * @param price
     */
    IkeaItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString);

    /**
     * copy ctor
     * @param other
     */
    IkeaItem(IkeaItem &other);

    /**
     * empty item
     */
    IkeaItem() : _catalogNumber(""), _itemName(""), _price("") {};




protected:

    string _catalogNumber;

public:
    string getCatalogNumber() const {
        return _catalogNumber;
    }

protected:
    string _itemName;
public:
    const string &getItemName() const {
        return _itemName;
    }

protected:
    string _price;
public:
    /**
     * add quantity to exist quantity
     * @param _quantity
     */
    void updateQuantity(double _quantity);

public:
    const string &getPrice() const;

protected:
    // price per unit
    double _quantity =0;

    string _inputString;
public:
    const string &getInputString() const;


};


class FabricItem : public  IkeaItem
{

public:

    FabricItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString, const string &weight) :
            IkeaItem(catalogNumber, itemName, price, quantity, inputString)
    {
        _weight = std::stod(weight);
    }




protected:
    double _weight;
public:
    double getWeight() const {
        return _weight;
    }


};




class CandyItem : public IkeaItem
{

public:

    CandyItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString, const string &calories):
            IkeaItem(catalogNumber, itemName, price, quantity, inputString)
    {
        _calories = std::stod(calories);
    }


protected:

    double _calories;

};


class LeisureItem : public IkeaItem
{

public:
    LeisureItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString, string &author, const string &year, const string &length)
            : IkeaItem(catalogNumber, itemName, price, quantity, inputString), _author(author) //todo check move
    {
        _year = std::stoi(year);
        _length = std::stoi(length);
    }

protected:

    string _author;
    int _year; //year of publication
    int _length;
};





class FurnitureItem : public IkeaItem
{

public:

    FurnitureItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString, const string &dimensions) :
            IkeaItem(catalogNumber, itemName, price, quantity, inputString), _dimensions(dimensions){};



protected:
    string _dimensions;

};


class BigFurnitureItem : public FurnitureItem
{
public:

    BigFurnitureItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString, const string &dimensions, const string &material, const string &color) :
            FurnitureItem(catalogNumber, itemName, price, quantity, inputString, dimensions), _material(material), _color(color){};


protected:

    string _material;
    string _color;

};



class KitchenItem : public FurnitureItem
{
public:

    KitchenItem(string &catalogNumber, string &itemName, string &price, string &quantity, string &inputString, const string &dimensions, const string &capacity) :
            FurnitureItem(catalogNumber, itemName, price, quantity, inputString, dimensions), _capacity(capacity){};


protected:
    string _capacity;
};


