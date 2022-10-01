#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "datastore.h"
#include "user.h"
#include "util.h"

using namespace std;


class MyDataStore: public DataStore {
public:

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void addCart(std::string myUsername, int hitIndex);

    void viewCart(std::string myUsername);

    void buyCart(std::string myUsername);

    int getSearchSize() const;

    

private:
    std::map<std::string, std::set<Product*>> myDataStoreMap;
    std::map<std::string, User*> myUserMap;
    std::map<std::string, std::vector<Product*>> userCartMap;
    std::vector<Product*> searchVec;
    std::set<Product*> productDatabase;
    std::set<User*> userDatabase;

};

#endif
