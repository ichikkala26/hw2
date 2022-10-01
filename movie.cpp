#include <sstream>
#include <iomanip>
#include "util.h"
#include "movie.h"
#include "product.h"
#include <string.h>


using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}



  std::set<std::string> Movie::keywords() const
  {
    std::set <string> movieKeywords;
    std::set <string> nameKeywords = parseStringToWords(name_);
    std::set <string> genreKeywords = parseStringToWords(genre_);
    movieKeywords = setUnion(nameKeywords,genreKeywords);
    return movieKeywords;
  }

  std::string Movie::displayString() const
  {
      std::string myFinalString = name_;
      myFinalString.append("\n");
      myFinalString.append("Genre: ");
      myFinalString.append(genre_);
      myFinalString.append(" Rating: ");
      myFinalString.append(rating_);
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
  void Movie::dump(std::ostream& os) const
  {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
    << genre_ << "\n" << rating_ << endl;
  }