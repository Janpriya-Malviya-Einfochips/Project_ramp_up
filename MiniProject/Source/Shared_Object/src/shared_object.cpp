/**
* \section DESCRIPTION
* This file contain all low level interface for shared memory
*
* \file shared_object.cpp
*/

#include <iostream>

#include "shared_object.h"


shared_object :: shared_object(void)
{
    // assign memory
    data.resize(block_size);
}

shared_object::~shared_object(void)
{
}


uint16_t shared_object::write_object(uint16_t start_from)
{
    uint16_t write_word_count = 0;

    try
    {
        //std::lock_guard<std::mutex> lock(object_locker);

        for(write_word_count = 0 ; write_word_count < block_size ; ++write_word_count,++start_from)
        {
            data[write_word_count] = start_from;
        }
    }
    catch(std::exception& e)
    {
        std::cout << "Shared_Obj:  " << " Error during write: " << e.what() << "\n";
    }

    return write_word_count;
}

uint16_t shared_object::verify_object(uint16_t start_from)
{
    uint16_t failed_word_count = 0;

    try
    {
        //std::lock_guard<std::mutex> lock(object_locker);

        for(uint16_t idx = 0 ; idx < block_size ; ++idx,++start_from)
        {
            if(data[idx] != start_from)
            {
                failed_word_count++;
            }
        }
    }
    catch(std::exception& e)
    {
        std::cout << "Shared_Obj:  " << " Error during verifing: " << e.what() << "\n";
    }

    return failed_word_count;
}
