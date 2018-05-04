/**
* \section DESCRIPTION
* This file contain all low level interface for shared memory
*
* \file shared_object.h
*/

#include <sys/shm.h>
#include <stdint.h>
#include <mutex>
#include <string>
/**
 * \class shared_object
 * \brief class to handle with shared memory
 */
class shared_object
{
public:

	//! Shared memory block size
	constexpr static uint16_t block_size = 115;

	//! Shared memory block size
	static std::string module_dbug_phrase;

private:
	//! Shared memory block id
	int shm_id;

	//! flag to indicate init is done
	bool do_once;

	//! flag to indicate init is done

	//!mutex lock for do read/write operation
	//std::mutex shm_lock;
	//! Init shared memory block
	void init_shared_block();

	//! Init shared memory block
	void distroyed_shared_block();

public:
    /**
     * \brief    Shared object class constructor
     */
	shared_object(void);

	//shared_object(shared_object& shm_object);
	//shared_object(shared_object&& shm_object);
	//shared_object& operator = (shared_object& shm_object);
	//shared_object& operator = (shared_object&& shm_object);

    /**
     * \brief    Shared object class destructor
     */
	~shared_object(void);


    /**
     * \brief
     */
	void write_shm_block(uint16_t start_from,uint16_t& write_fail_cnt);

    /**
     * \brief
     */
	void verify_shm_block(uint16_t start_from,uint16_t& read_fail_cnt);
};
