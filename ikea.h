//
// Created by hadar.dotan on 9/2/18.
//

#ifndef EX2_IKEA_H
#define EX2_IKEA_H

/**
 * CONSTANTS
 */
#define STORE_MENU "1.Input stock from file\n2.Find item by catalog number\n3.Find item by name\n4.Print stock by catalog number\n5.Print stock by name\n6.Sell item\n7.Exit\n"


#define INPUT_STOCK_FROM_FILE 1
#define FIND_ITEM_BY_CAT_NUM 2
#define FIND_ITEM_BY_NAME 3
#define PRINT_STOCK_BY_CAT_NUM 4
#define PRINT_STOCK_BY_NAME 5
#define SELL_ITEM 6
#define EXIT 7

#define NUM_OF_PARAMS 13
#define END_OF_ITEM "-----"
#define MIN_NUM_OF_ITEM_LINES 4

std::string paramNames[NUM_OF_PARAMS] =
        {
                "Item",
                "Name",
                "Quantity",
                "Price",
                "Weight",
                "Calories",
                "Dimensions",
                "Material",
                "Color",
                "Capacity",
                "Author",
                "Year of publication",
                "Length"
        };



#include "IkeaItem.h"
#include <vector>
#include <fstream>
#include <utility>
#include<algorithm>
#include <iostream>


/**
 * reads content of input file called fileName and adds described item to stock
 * @param fileName
 * @return
 */
bool addItem(std::string fileName);


/**
 * finds ikea item by catalog number.
 * @param catalogNumber
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByCatalogNumber(int catalogNumber);


/**
 * finds ikea item by item name.
 * @param itemName
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByName(std::string itemName);




/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by categorical number
 */
std::string getItemsByCategoricalOrder(std::vector<IkeaItem> &items);



/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by item name alphabetically
 */
std::string getItemsByItemName(std::vector<IkeaItem> &items);



/**
 * sells an item
 * @param catalogNumber
 * @return
 */
bool sellItem(int catalogNumber);









#endif //EX2_IKEA_H
