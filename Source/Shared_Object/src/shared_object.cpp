/**
* \section DESCRIPTION
* This file contain all low level interface for shared memory
*
* \file shared_object.cpp
*/

#include <iostream>
#include <unistd.h>
#include <memory>

#include "shared_object.h"


std::string shared_object :: module_dbug_phrase = "SHED_OBJ:";

shared_object :: shared_object(void) : shm_id(0) , do_once(false)
{
	init_shared_block();
}

shared_object::~shared_object(void)
{
	//Destroyed memory
	distroyed_shared_block();
}

void shared_object::init_shared_block()
{
	// lock init function
	//std::lock_guard<std::mutex> lock(shm_lock);

	if(false == do_once)
	{
		// create shared memory block with private key
		shm_id = shmget(IPC_PRIVATE,block_size * sizeof(uint64_t),( 0666 |IPC_CREAT | IPC_EXCL));

		// Is shared memory allocated
		if (shm_id == -1)
		{
			//TODO : Throw execption
			std::cout << module_dbug_phrase  << "  Error: " << "Fail to create shared object \n";
			return;
		}

		// Shared memory created
		std::cout << module_dbug_phrase  << "  Info: " << "Shared block created : id " << shm_id << "\n";

		//Set init done
		do_once = true;
	}
}

void shared_object::distroyed_shared_block()
{
	// lock init function
	//std::lock_guard<std::mutex> lock(shm_lock);

	// is init done
	if(do_once)
	{
		// delete shm memory object
		if (shmctl(shm_id, IPC_RMID, nullptr) < 0)
		{
			std::cout << module_dbug_phrase  << "  Error: " << "Fail to delete shared object\n";
			return;
		}
		std::cout << module_dbug_phrase  << "  Info: " << "shared object deleted : id " << shm_id << "\n";
	}
}

void shared_object::write_shm_block(uint16_t start_from, uint16_t& write_fail_cnt)
{
	uint64_t *shm_block = nullptr;

	//attach shared memory
	shm_block = static_cast<uint64_t *>(shmat(shm_id, nullptr, 0));

	//memory attached
	if (shm_block != (void *)-1)
	{
		for(uint16_t idx = 0 ; idx < block_size ; idx++)
		{
			//start writing in shared location
			shm_block[idx] = start_from++;
		}

		//Detach memory
		if (shmdt(shm_block) == -1)
		{
			std::cout << module_dbug_phrase  << "  Error: " << "Fail to detach  : id " << shm_id << "\n";
		}
	}
	else
	{
		write_fail_cnt++;
	}
}

void shared_object::verify_shm_block(uint16_t start_from,uint16_t& read_fail_cnt)
{
	uint64_t *shm_block = nullptr;

	//attach shared memory
	shm_block = static_cast<uint64_t *>(shmat(shm_id, nullptr, 0));

	//memory attached
	if (shm_block != (void *)-1)
	{
		//Verify block
		for(uint16_t idx = 0 ; idx < block_size ; idx++)
		{
			if(shm_block[idx] != start_from)
			{
				read_fail_cnt++;
			}

			start_from++;
		}

		//Detach memory
		if (shmdt(shm_block) == -1)
		{
			std::cout << module_dbug_phrase  << "  Error: " << "Fail to detach  : id " << shm_id << "\n";
		}
	}
	else
	{
		read_fail_cnt++;
	}

}
