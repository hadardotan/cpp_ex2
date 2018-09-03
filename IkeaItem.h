//
// Created by Visitor on 9/1/2018.
//

#ifndef CPP_EX2_IKEAITEM_H
#define CPP_EX2_IKEAITEM_H

#endif //CPP_EX2_IKEAITEM_H


#include <string>
#include <array>


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
    IkeaItem(std::string &catalogNumber, std::string &itemName, std::string &price, std::string &quantity) = default;

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

    std::string _catalogNumber;

public:
    std::string getCatalogNumber() const {
        return _catalogNumber;
    }

protected:
    std::string _itemName;
public:
    const std::string &getItemName() const {
        return _itemName;
    }

protected:
    std::string _price; // price per unit
    double _quantity =0;

};


class FabricItem : public  IkeaItem
{

public:

    FabricItem(IkeaItem ikeaItem, const std::string &weight) : IkeaItem(ikeaItem)
    {
        _weight = std::stod(weight);
    }




protected:
    double _weight;

};




class CandyItem : public IkeaItem
{

public:

    CandyItem(IkeaItem ikeaItem, const std::string &calories): IkeaItem(ikeaItem)
    {
        _calories = std::stod(calories);
    }


protected:

    double _calories;

};


class LeisureItem : public IkeaItem
{

public:
    LeisureItem(IkeaItem ikeaItem, const std::string &author, const std::string &year, const std::string &length)
            : IkeaItem(ikeaItem), _author(author) //todo check move
    {
        _year = std::stoi(year);
        _length = std::stoi(length);
    }

protected:

    std::string _author;
    int _year; //year of publication
    int _length;
};





class FurnitureItem : public IkeaItem
{

public:

    FurnitureItem(IkeaItem ikeaItem, const std::string &dimensions) : IkeaItem(ikeaItem), _dimensions(dimensions){};



protected:
    std::string _dimensions;

};


class BigFurnitureItem : public FurnitureItem
{
public:

    BigFurnitureItem(IkeaItem ikeaItem, const std::string &dimensions, const std::string &material, const std::string &color) :
            FurnitureItem(ikeaItem, dimensions), _material(material), _color(color){};


protected:

    std::string _material;
    std::string _color;

};



class KitchenItem : public FurnitureItem
{
public:

    KitchenItem(IkeaItem ikeaItem, const std::string &dimensions, const std::string &capacity) :
            FurnitureItem(ikeaItem, dimensions), _capacity(capacity){};


protected:
    std::string _capacity;
};


