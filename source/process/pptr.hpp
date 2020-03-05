#ifndef PROCESS_PPTR_HPP
#define PROCESS_PPTR_HPP

#include <array>
#include <type_traits>
#include <cstdint>
#include <Windows.h>

namespace jhack
{
	/*
	 * Pptr: a pointer to a process' virtual memory.
	 * You can perform 'read' and 'write' operation on another process memory,
	 * through the 'address' and 'processHandle' attribute.
	 * For multi-level pointers, use '*' and '[]' to chain value reading.
	 * 
	 * You can initialize an instance with the following aggregate: {address, handle}
	 */
	class Pptr
	{
	public:
		/*
		 * operator[] and operator*:
		 * Provides a convenient way to resolve multiple pointers from another process.
		 * Those operators return another instance of Pptr.
		 */
		Pptr		operator[](uintptr_t offset) const
		{
			return Pptr{this->read<LPVOID>((uint8_t*)this->address + offset), this->processHandle};
		}

		Pptr		operator*() const
		{
			return Pptr{this->read<LPVOID>(this->address), this->processHandle};
		}

		/*
		 * read(LPVOID addr): copy data from a process virtual memory, and return it.
		 * The data type is provided by template argument.
		 * The value is copied when returned.
		 * Default value for addr is the attribute address of the instance.
		 *
		 * If an error occur during the reading, the value returned will be default-initialized.
		 * You may check for errors by using [Set/Get]LastError().
		 *
		 * read(buf, size, addr) provide a faster read (no additionnal copy) and return wether the operation succeed.
		 */
		template <typename ReadType>
		ReadType	read(LPVOID addr) const
		{
			ReadType	ret;
			return ReadProcessMemory(this->processHandle, addr, &ret, sizeof(ret), NULL) ? ret : ReadType();
		}

		/*
		 * Call read<ReadType>(this->address + offset).
		 */
		template <typename ReadType>
		ReadType	read(size_t offset = 0) const
		{
			return this->read<ReadType>(reinterpret_cast<const LPVOID>(reinterpret_cast<const uintptr_t>(this->address) + offset));
		}


		bool		read(void *buf, size_t size, LPVOID addr) const
		{
			return ReadProcessMemory(this->processHandle, addr, buf, size, NULL);
		}

		/*
		 * Call read(buf, size, this->address + offset).
		 */
		bool		read(void *buf, size_t size, size_t offset = 0) const
		{
			return this->read(buf, size, reinterpret_cast<const LPVOID>(reinterpret_cast<const uintptr_t>(this->address) + offset));
		}


		/*
		 * write(): copy data from current process memory to another process memory.
		 * 'size' bytes from buf will be written in another process memory address 'addr'.
		 * Default value for addr is the attribute address of the instance.
		 *
		 * the return of WriteProcessMemory() is forwarded by this function.
		 */
		bool		write(void *buf, size_t size, LPVOID addr) const
		{
			return WriteProcessMemory(this->processHandle, addr, buf, size, NULL);
		}

		/*
		 * Call write(this->address + offset).
		 */
		bool		write(void *buf, size_t size) const
		{
			return this->write(buf, size, this->address);
		}


		LPVOID	address;
		HANDLE	processHandle;
	};
};

#endif//PROCESS_PPTR_HPP