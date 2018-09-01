//
// Created by Visitor on 9/1/2018.
//

#include "IkeaItem.h"
#include<algorithm>


// todo - create enum of item names

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



//todo - comperator
//bool compareByCategoricalOrder(const )

