#include "print.hpp"

#include <ostream>

#include "formatter.h"

void print(const std::string& text, std::ostream& out) {
  out << formatter(text);
}
