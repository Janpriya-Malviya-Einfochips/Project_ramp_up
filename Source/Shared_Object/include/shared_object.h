/**
* \section DESCRIPTION
* This file contain all low level interface for shared memory
*
* \file shared_object.h
*/


#include <stdint.h>
#include <mutex>
#include <vector>

/**
 * \class shared_object
 * \brief class to handle with shared memory
 */
class shared_object
{
public:
	//! Shared memory block size
	constexpr static uint16_t block_size = 115;

private:

	//! data
	std::vector<uint16_t> data;

	//! mutex lock for waiting condition
	std::mutex object_locker;

public:
	/**
	 * \brief    Shared object class constructor
	 */
	shared_object(void);

	/**
	 * \brief    Shared object class destructor
	 */
	~shared_object(void);


	/**
	 * \brief
	 */
	uint16_t write_object(uint16_t start_from);

	/**
	 * \brief
	 */
	uint16_t verify_object(uint16_t start_from);
};
