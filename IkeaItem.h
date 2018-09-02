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






protected:

    int _catalogNumber;

public:
    int getCatalogNumber() const {
        return _catalogNumber;
    }

protected:
    std::string _itemName;
public:
    const std::string &getItemName() const {
        return _itemName;
    }

protected:
    double _price; // price per unit



};



class FabricItem : public  IkeaItem
{

public:


protected:
    double _weight;

};




class CandyItem : public IkeaItem
{


protected:

private:
    double _calories;

};


class LeisureItem : public IkeaItem
{

protected:

    std::string _author;
    int _year; //year of publication
    int _length;
};





class FurnitureItem : public IkeaItem
{

protected:
    std::array<double, FURNITURE_DIM> _dimensions;

};


//todo - desks and chairs - together???



class KitchenItem : public FurnitureItem
{


protected:
    double _capacity;
};


