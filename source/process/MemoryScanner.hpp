#ifndef PROCESS_SCANNER_HPP
#define PROCESS_SCANNER_HPP

#include <Windows.h>
#include <list>
#include <type_traits>

namespace jhack
{
	/*
	 * MemoryScanner: a wrapper for a signature scanner.
	 * It search for a byte pattern in a given process' memory.
	 * The Scanner need 3 parameters: a Process Handle, a Byte Pattern, and a mask.
	 * The mask is constructed like this:
	 *  'x' : the byte is included in the pattern. (NB: any other char is fine)
	 *  '?' : the byte is ignored in the pattern.
	 *  '\0': end of the mask. It is required to compute the pattern length.
	 * 
	 * The function store the result in a container,
	 * which is only accessible through an iterator, or const_iterator.
	 *
	 * When using iterator, the Scanner will perform a scan before each iterator incrementation.
	 * Thus, you can perform signature scan in a 'lazy' approach.
	 * But, you need to perform one scanNext() before using iterator.
	 */
	class MemoryScanner
	{
		// hidden iterator forward declaration
		template <typename BaseIteratorCheck>
		struct _iterator;

	public:
		// declaration of the iterator types
		// NB: iterator isn't convertible to const_iterator !
		using Container = std::list<LPVOID>;
		using iterator = _iterator<void>;
		using const_iterator = Container::const_iterator;

		MemoryScanner() = default;
		MemoryScanner(HANDLE _ProcessHandle, const BYTE *_pattern, const char *_mask);

		/*
		 * scan(): perform a complete scan of the process.
		 * Return a const_iterator to the first result.
		 * It must be tested with this->end() to check if any pattern has been found.
		 */
		MemoryScanner::iterator			scan();
		/*
		 * scanNext(): perform a scan of the process, until a match is found.
		 * Return the address of the pattern, or NULL if no match has been found.
		 */
		LPVOID							scanNext();

		/*
		 * hasScanned(): Check if a scan has already been done.
		 */
		bool							hasScanned() const;

		/*
		 * clear(): reset the scanner, in order to perform a new scan.
		 */
		void							clear();

		/*
		 * setBeginoffset(): reset the scanner (call to this->clear())
		 * and change the start scanning address.
		 */
		void							setBeginOffset(size_t offset);

		MemoryScanner::iterator			begin();
		MemoryScanner::const_iterator	begin() const;
		MemoryScanner::iterator			end();
		MemoryScanner::const_iterator	end() const;

	public:
		HANDLE		processHandle;
		const BYTE	*pattern;
		const char	*mask;

	private:
		Container	_result;
		bool		_hasScanned = false;
		size_t		_internalOffset = 0;

		friend MemoryScanner::iterator;

	public:
		using BaseIterator = Container::iterator;
	};


	/*
	 * BaseIteratorCheck: check if the base class of MemoryScanner::iterator is an input_iterator
	 * (or any of its subclasses). If the check failed, you must change the container '_result' in MemoryScanner.
	 */
	template <typename BaseIteratorCheck = std::enable_if<std::is_base_of<std::input_iterator_tag, MemoryScanner::BaseIterator::iterator_category>::value>::type>
	struct MemoryScanner::_iterator : public MemoryScanner::BaseIterator
	{
		using iterator_category	= std::input_iterator_tag;
		using value_type		= LPVOID;
		using difference_type	= ptrdiff_t;
		using pointer			= LPVOID*;
		using reference			= LPVOID&;

		_iterator(const MemoryScanner::BaseIterator &it, MemoryScanner &_src)
			: MemoryScanner::BaseIterator(it), src(_src)
		{}

		_iterator<>&	operator++()
		{
			src.scanNext();
			dynamic_cast<MemoryScanner::BaseIterator*>(this)->operator++();
			return *this;
		}

		_iterator<>		operator++(int)
		{
			_iterator	result = *this;

			src.scanNext();
			dynamic_cast<MemoryScanner::BaseIterator*>(this)->operator++(int());
			return result;
		}

		MemoryScanner	&src;
	};
}

#endif//PROCESS_SCANNER_HPP