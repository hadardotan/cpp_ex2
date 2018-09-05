//
// Created by hadar.dotan on 9/2/18.
//

#ifndef EX2_IKEA_H
#define EX2_IKEA_H

/**
 * CONSTANTS
 */
#include <vector>

#include "IkeaItem.h"

#include <fstream>
#include <utility>
#include<algorithm>
#include <iostream>

/**
 * Constants
 */

/**
 * Output messages
 */

#define STORE_MENU "1.Input stock from file\n2.Find item by catalog number\n3.Find item by name\n4.Print stock by catalog number\n5.Print stock by name\n6.Sell item\n7.Exit\n"
#define ILLEGAL_ITEM_FIELDS "illegal item fields\n"
#define ILLEGAL_LINE_PARAM "illegal line param\n"
#define ILLEGAL_CAT_NUM "Illegal catalog number\n"
#define ITEM_NOT_FOUND "Item not found\n"
#define ENTER_UNIT "Please enter number of items\n"
#define ENTER_QUANTITY "Please enter desired quantity\n"
#define NO_STOCK "Not enough stock to sell\n"
#define ILLEGAL_QUANTITY "Illegal quantity\n"
#define ENTER_PATH "please enter file path:\n"
#define ENTER_CAT_NUM "please enter catalog number:\n"
#define ENTER_ITEM_NAME "please enter item name:\n"
#define ILLEGAL_PATH "Illegal file path\n"
#define END_OF_ITEM "-----"


/**
 * Fields
 */
static const std::vector<std::string> paramNames
        {
                "Item",
                "Name",
                "Quantity",
                "Price"
        };
#define WEIGHT "Weight"
#define CALORIES "Calories"
#define DIM "Dimensions"
#define MATERIAL "Material"
#define COLOR "Color"
#define CAPACITY "Capacity"
#define AUTHOR "Author"
#define YEAR "Year of publication"
#define LEN "Length"


/**
 * Menu buttons
 */
#define INPUT_STOCK_FROM_FILE 1
#define FIND_ITEM_BY_CAT_NUM 2
#define FIND_ITEM_BY_NAME 3
#define PRINT_STOCK_BY_CAT_NUM 4
#define PRINT_STOCK_BY_NAME 5
#define SELL_ITEM 6
#define EXIT 7

#define MAX_MENU_BUTTON 7
#define MIN_NUM_OF_ITEM_LINES 4
#define MAX_NUM_OF_ITEM_LINES 7





/**
 * reads content of input file called fileName and adds described item to stock
 * @param fileName
 * @return
 */
void addItem(const std::string fileName);


/**
 * finds ikea item by catalog number.
 * @param catalogNumber
 * @return string represent item if the item was found, or "item not found" if item wasnt found
 */
std::string getItemByCatalogNumber(std::string catalogNumber);


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
void getItemsByCategoricalOrder(std::vector<IkeaItem*> &items);



/**
 *
 * @param items
 * @return string represent current ikea item by input file format, sorted by item name alphabetically
 */
void getItemsByItemName(std::vector<IkeaItem> &items);



/**
 * sells an item
 * @param catalogNumber
 * @return
 */
string sellItem(string catalogNumber);




#endif //EX2_IKEA_H
