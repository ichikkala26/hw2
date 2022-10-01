#include <sstream>
#include <iomanip>
#include "util.h"
#include "clothing.h"
#include "product.h"
#include <string.h>


using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}



  std::set<std::string> Clothing::keywords() const
  {
    std::set <string> clothingKeywords;
    std::set <string> nameKeywords = parseStringToWords(name_);
    std::set <string> brandKeywords = parseStringToWords(brand_);
    clothingKeywords = setUnion(nameKeywords,brandKeywords);
    return clothingKeywords;
  }

  std::string Clothing::displayString() const
  {
      std::string myFinalString = name_;
      myFinalString.append("\n");
      myFinalString.append("Size: ");
      myFinalString.append(size_);
      myFinalString.append(" Brand: ");
      myFinalString.append(brand_);
      myFinalString.append("\n");
      std::stringstream a;
      a << price_;
      a.precision(2);
      myFinalString.append(a.str());
      myFinalString.append(" ");
      myFinalString.append(to_string(qty_));
      myFinalString.append(" left.");

      return myFinalString;
  }
  void Clothing::dump(std::ostream& os) const
  {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
    << size_ << "\n" << brand_ << endl;
  }