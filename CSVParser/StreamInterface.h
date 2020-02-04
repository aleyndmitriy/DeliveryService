#pragma once

#include "..\CoreData.h"
#include<iosfwd>
std::istream& operator>>(std::istream& stream, Location& obj);
std::ostream& operator<<(std::ostream& stream, const Location& obj);

std::istream& operator>>(std::istream& stream, Customer& obj);
std::ostream& operator<<(std::ostream& stream, const Customer& obj);