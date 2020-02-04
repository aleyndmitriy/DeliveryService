#pragma once
#include "..\CoreData.h"

#pragma once
#include<boost/iterator/iterator_facade.hpp>
#include <fstream>
#include<cctype>

//https://en.cppreference.com/w/cpp/io/basic_istream/seekg
//https://en.cppreference.com/w/cpp/io/basic_istream

template<typename T> class CSVParser
{
private:
	class ConstCSVParserIterator : public boost::iterator_facade <ConstCSVParserIterator, T, boost::forward_traversal_tag >
	{
	private:
		friend class boost::iterator_core_access;
		std::istream* _stream;
		std::istream_iterator<T> _iterator;
		bool equal(ConstCSVParserIterator const& other) const;
		T& dereference() const;
		void increment();
		void deleteEmptyString();
	public:
		constexpr ConstCSVParserIterator();
		ConstCSVParserIterator(const  ConstCSVParserIterator& other) = default;
		ConstCSVParserIterator(std::istream& InputStream);
	};
	std::string _fileName;
	std::unique_ptr<std::istream> _csvFile;
public:
	using const_iterator = ConstCSVParserIterator;
	using value_type = T;
	using reference = value_type &;
	using const_reference = const value_type &;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	CSVParser() = default;
	CSVParser(const CSVParser& src) = delete;
	CSVParser& operator=(const CSVParser& src) = delete;
	CSVParser(const char* fileName);
	CSVParser(std::string fileName);
	CSVParser(CSVParser&& rhs) = default;
	CSVParser& operator=(CSVParser&& src) = default;
	~CSVParser() = default;
	const_iterator begin() const;
	const_iterator end() const;
};

template <typename T> constexpr CSVParser<T>::ConstCSVParserIterator::ConstCSVParserIterator() :_stream(nullptr), _iterator()
{

}

template <typename T> CSVParser<T>::ConstCSVParserIterator::ConstCSVParserIterator(std::istream& InputStream) : _stream(&InputStream), _iterator()
{
	deleteEmptyString();
	_stream->ignore(std::numeric_limits<std::streamsize>::max(), (int)'\n');
	_iterator = std::istream_iterator<T>(*_stream);
}

template <typename T> void CSVParser<T>::ConstCSVParserIterator::deleteEmptyString()
{
	std::istream::pos_type position = _stream->tellg();
	int ch = 0;
	while (_stream->eof() == false) {
		ch = _stream->get();
		if (ch == 10) {
			position = _stream->tellg();
		}
		if (!std::isspace(ch)) {
			_stream->seekg(position);
			return;
		}
	}
}

template <typename T> T& CSVParser<T>::ConstCSVParserIterator::dereference() const
{
	return const_cast<T&>(*_iterator);
}

template <typename T> void CSVParser<T>::ConstCSVParserIterator::increment()
{
	deleteEmptyString();
	++_iterator;
}

template <typename T> bool CSVParser<T>::ConstCSVParserIterator::equal(typename CSVParser<T>::ConstCSVParserIterator const& other) const
{
	return _iterator == other._iterator;
}
template<typename T> CSVParser<T>::CSVParser(std::string fileName) :_fileName(fileName), _csvFile(std::make_unique<std::
	ifstream>(fileName, std::ios_base::in))
{
	
}

template<typename T> CSVParser<T>::CSVParser(const char* fileName) :CSVParser<T>(std::string(fileName))
{

}

template <typename T> typename CSVParser<T>::ConstCSVParserIterator CSVParser<T>::begin() const {
	CSVParser<T>::const_iterator itr(*_csvFile.get());
	return itr;
}

template <typename T> typename CSVParser<T>::ConstCSVParserIterator CSVParser<T>::end() const {
	return CSVParser<T>::const_iterator();
}
