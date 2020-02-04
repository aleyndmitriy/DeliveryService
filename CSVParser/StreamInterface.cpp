#include"StreamInterface.h"
#include<iostream>
#include <iomanip>

std::ios_base::iostate readField(std::istream& stream, char* fieldBuffer, const std::streamsize buffLength, const char delim)
{
	stream.getline(fieldBuffer, buffLength, delim);
	if (stream.rdstate() == std::ios_base::failbit) {
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), (int)delim);
	}
	return stream.rdstate();
}

std::istream& operator>>(std::istream& stream, Location& obj) {
	stream.clear();
	stream >> std::ws;
	if (readField(stream, obj.loc_id, UUID_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.code, CODE_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.desc, DESCRIPTION_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.zip, ZIP_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.city, CITY_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.region, REGION_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.country, COUNTRY_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	stream.ignore(std::numeric_limits<std::streamsize>::max(), (int)',');
	char tempBuffer[GEOCOORDINATE_LENGTH];
	if (readField(stream, tempBuffer, GEOCOORDINATE_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	obj.latitude = std::atof(tempBuffer);
	if (readField(stream, tempBuffer, GEOCOORDINATE_LENGTH, '\n') != std::ios_base::goodbit) {
		return stream;
	}
	obj.longitude = std::atof(tempBuffer);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Location& obj) {
	stream << obj.loc_id << ',' << obj.code << ',' << obj.desc << ',' <<
		obj.zip << ',' << obj.city << ',' << obj.region << ',' <<
		obj.country << ',' << ',' << obj.latitude << ',' << obj.longitude << std::endl;
	return stream;
}

std::istream& operator>>(std::istream& stream, Customer& obj) {
	stream.clear();
	stream >> std::ws;
	if (readField(stream, obj.cus_id, UUID_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.code, CODE_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.desc, DESCRIPTION_LENGTH, ',') != std::ios_base::goodbit) {
		return stream;
	}
	if (readField(stream, obj.loc_id, UUID_LENGTH, '\n') != std::ios_base::goodbit) {
		return stream;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Customer& obj) {
	stream << obj.cus_id << ',' << obj.code << ',' << obj.desc << ',' << obj.loc_id << std::endl;
	return stream;
}