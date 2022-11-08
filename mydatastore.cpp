
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "product.h"
#include "mydatastore.h"
#include "user.h"

    /**
     * Adds a product to the data store
     */
    void MyDataStore::addProduct(Product* p)
    {

      productDatabase.insert(p);

      std::set<std::string> currProductKeywords = p->keywords();
      std::set<std::string>::iterator it;
      for(it = currProductKeywords.begin(); it!=currProductKeywords.end(); ++it)
      {
        if(currProductKeywords.find(*it)==currProductKeywords.end())
        {
          std::set<Product*> newProductSet;
          newProductSet.insert(p);
          myDataStoreMap.insert(std::make_pair(*it, newProductSet));
        }
        else if(currProductKeywords.find(*it)!=currProductKeywords.end())
        {
          myDataStoreMap[*it].insert(p);
        }

      }
    }

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u)
    {
      userDatabase.insert(u);
      std::string userName = u->getName();
      myUserMap.insert(std::make_pair(userName, u));
    }


    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
    {
      searchVec.clear();

      std::vector<std::string>::iterator it;
      std::set<Product*> tempSet;
      std::set<Product*> searchSet;
      for(it = terms.begin(); it!=terms.end(); ++it)
      {
        std::map<std::string, std::set<Product*>>::iterator prodIt = myDataStoreMap.find(*it);
        if(prodIt != myDataStoreMap.end())
        {
          tempSet = prodIt->second;
          if(searchSet.empty())
          {
            searchSet = tempSet;
          }
          else if(!searchSet.empty())
          {
            if(type==0)
            {
              searchSet = setIntersection(tempSet,searchSet);
            }
            if(type==1)
            {
              searchSet = setUnion(tempSet,searchSet);
            }
          }
        }
      }
      
      std::set<Product*>::iterator setToVecIt;
      for(setToVecIt=searchSet.begin(); setToVecIt!=searchSet.end(); ++setToVecIt)
      {
        searchVec.push_back(*setToVecIt);
      }

      return searchVec;
    }

    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(std::ostream& ofile)
    {
      ofile << "<products>\n";
      std::set<Product*>::iterator prodDBIterator;
      for(prodDBIterator=productDatabase.begin(); prodDBIterator!=productDatabase.end(); ++prodDBIterator)
      {
          (*prodDBIterator)->dump(ofile);
          Product* copyProduct = *prodDBIterator;
          delete copyProduct;
      }
      ofile << "</products>\n";
      ofile << "<users>\n";
      std::set<User*>::iterator userDBIterator;
      for(userDBIterator=userDatabase.begin(); userDBIterator!=userDatabase.end(); ++userDBIterator)
      {
          (*userDBIterator)->dump(ofile);
          User* copyUser = *userDBIterator;
          delete copyUser;
      }
      ofile << "</users>\n";
    }

    void MyDataStore::addCart(std::string myUsername, int hitIndex)
    {
      hitIndex =  hitIndex-1;
      int searchSize = getSearchSize();
      if(hitIndex>=searchSize)
      {
        cout << "Invalid error" << endl;
        return;
      }
      std::map<std::string, User*>::iterator myUserFinder = myUserMap.find(myUsername);
      if(myUserFinder != myUserMap.end())
      {
        std::map<std::string, std::vector<Product*>>::iterator it = userCartMap.find(myUsername);
        if(it != userCartMap.end())
        {
          it->second.push_back(searchVec[hitIndex]);
        }
        else if(it == userCartMap.end())
        {
          std::vector<Product*> newCurrProdVec;
          newCurrProdVec.push_back(searchVec[hitIndex]);
          userCartMap.insert(std::make_pair(myUsername, newCurrProdVec));
        }
      }
      else
      {
        cout << "Invalid request" << endl;
      }

    }

    void MyDataStore::viewCart(std::string myUsername)
    {
      std::map<std::string, std::vector<Product*>>::iterator it = userCartMap.find(myUsername);
      if(it != userCartMap.end())
      {
        int productCounter=1;
        std::vector<Product*> userCart = it->second;
        std::vector<Product*>::iterator it2;
        for(it2=userCart.begin(); it2!=userCart.end(); ++it2)
        {
          Product* p = *it2;
          /*std::string productName = p->getName();
          productName = convToLower(productName);
          cout<<productCounter<<": "<<productName<<endl;
          productCounter++;*/
          cout<<"Item "<<productCounter<<endl;
          string productPrint = p->displayString();
          cout << productPrint <<"\n"<<endl;
          productCounter++;
        }
      }
      else
      {
        cout<<"Invalid username"<<endl;
        return;
      }
      
    }

    int MyDataStore::getSearchSize() const
    {
      int searchVecSize = searchVec.size();
      return searchVecSize;
    }

    void MyDataStore::buyCart(std::string myUsername)
    {
      std::map<std::string, std::vector<Product*>>::iterator it = userCartMap.find(myUsername);
      if(it != userCartMap.end())
      {
        std::vector<Product*> userCart = it->second;
        std::vector<Product*> tempCart;
        for(unsigned int i = 0; i < userCart.size(); i++)
        {
          int currQuantity = userCart[i]->getQty();
          double currProdPrice = userCart[i]->getPrice();
          std::map<std::string, User*>::iterator it3 = myUserMap.find(myUsername);
          User* currUser = it3->second;
          int userAvailableCredit = currUser->getBalance();

          if(currQuantity>0 && userAvailableCredit>= currProdPrice)
          {
            userCart[i]->subtractQty(1);
            currUser->deductAmount(currProdPrice);
            //userCart.erase(userCart.begin() + i);
          }
          else if(currQuantity==0 || userAvailableCredit< currProdPrice)
          {
            tempCart.push_back(userCart[i]);
          }
        }

        it->second = tempCart;
      }
      else
      {
        cout<<"Invalid username"<<endl;
        return;
      }
    }




