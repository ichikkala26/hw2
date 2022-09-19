#include <sstream>
#include <iomanip>
#include "util.h"
#include "book.h"
#include "product.h"
#include <string.h>


using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author) :
    Product(category, name, price, qty),
    ISBN_(ISBN),
    author_(author)
{

}



  std::set<std::string> Book::keywords() const
  {
    std::set <string> bookKeywords;
    std::set <string> titleKeywords = parseStringToWords(name_);
    std::set <string> authorKeywords = parseStringToWords(author_);
    bookKeywords = setUnion(titleKeywords,authorKeywords);
    bookKeywords.insert(ISBN_);
    return bookKeywords;
  }
  /*
  <name>
  Author: <author> ISBN: <isbn>
  <price> <quantity> left.
*/
  std::string Book::displayString() const
  {
      std::string myFinalString = name_;
      myFinalString.append("\n");
      myFinalString.append("Author: ");
      myFinalString.append(author_);
      myFinalString.append(" ISBN: ");
      myFinalString.append(ISBN_);
      myFinalString.append("\n");
      myFinalString.append(to_string(price_));
      myFinalString.append(" ");
      myFinalString.append(to_string(qty_));
      myFinalString.append(" left.");

      return myFinalString;
  }
  void Book::dump(std::ostream& os) const
  {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    ISBN_ << "\n" << author_ << endl;
  }