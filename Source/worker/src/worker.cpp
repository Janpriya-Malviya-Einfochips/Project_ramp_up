/**
* \section DESCRIPTION
* This file contain all interface for worker module
*
* \file worker.cpp
*/

#include<iostream>
#include<unistd.h>
#include "worker.h"

using namespace std;

#define WORKER_DEBUG std::cout << "Worker[" << worker_name << "]  "

Worker::Worker(std::string name, proc_callback writer, proc_callback verifier) :
		worker_name(name), Writer_callback(writer), Verifier_callback(verifier), failed_cnt(0), success_cnt(0)
{
	//WORKER_DEBUG << " Info: " << "Worker created \n";
}


Worker::~Worker()
{
	//Exit all running threads
	try
	{
		//Stop all running threads
		stop_process();

		//Print thread statics
		print_statics();
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
	//WORKER_DEBUG << " Info: " << "Worker deleted\n";
}


void Worker::start_process()
{
	//Exit all running threads
	try
	{
		//WORKER_DEBUG << " Info: " << "Starting\n";

		//Start writer thread , which will wait for start writing
		worker_thread.start_thread(*this);
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
	//WORKER_DEBUG << " Info: " << "Worker started\n";
}

void Worker::stop_process()
{
	//Exit all running threads
	try
	{
		//WORKER_DEBUG << " Info: " << "Stopping\n";

		//Start writer thread , which will wait for start writing
		worker_thread.stop_thread();
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
	//WORKER_DEBUG << " Info: " << "Worker stopped successfully\n";
}


void Worker::Worker_thread_params::start_thread(Worker& WorkerObject)
{
	//lock mutex so no one can change parameters
	std::lock_guard<std::mutex> lock(get_set_lock);

	//set exit false
	do_exit = false;

	//Start thread function
	proc_thread = std::thread(&Worker::Worker_thread_params::thread_function,this,std::ref(WorkerObject));
}

void Worker::Worker_thread_params::stop_thread(void)
{
	{
		//lock mutex so no one can change parameters
		std::lock_guard<std::mutex> lock(get_set_lock);

		//set exit false
		do_exit = true;

		//Notify thread
		proc_condition_event.notify_one();
	}

	//wait for rejoin
	proc_thread.join();
}

void Worker::Worker_thread_params::thread_function(Worker& WorkerObject)
{
	while(true)
	{
		//std::cout << "Worker[" << WorkerObject.get_worker_name() << "]  " << " Thread running.\n";

		//Waiting on condition variable
		std::unique_lock<std::mutex> lock(proc_condition_lock);
		proc_condition_event.wait(lock);

		//std::cout << "Worker[" << WorkerObject.get_worker_name() << "]  " << " Event received \n";
		{
			//lock mutex first
			std::lock_guard<std::mutex> lock(get_set_lock);

			try
			{
				//is required to exit
				if(do_exit)
				{
					std::cout << "Worker[" << WorkerObject.get_worker_name() << "]  " << " Exiting thread\n";
					break;
				}

				//Perform assigned work algorithm
				//std::cout << "Worker[" << WorkerObject.get_worker_name() << "]  " << " do assigned job \n";
				WorkerObject.do_work();
			}
			catch(std::exception& e)
			{
				std::cout << "Worker[" << WorkerObject.get_worker_name() << "]  " << " Error found " << e.what() << "\n";
			}
		}
	}
}

//! Do work
void Worker :: do_work(void)
{
	try
	{
		// call writer
		if(Writer_callback)
		{
			//success count
			uint32_t write_success_cnt = 0;

			//success count
			uint32_t verify_failed_cnt = 0;

			//called write callback
			//WORKER_DEBUG << " Info: " << "Calling writing callback \n";
			write_success_cnt = Writer_callback(start_value);

			//Inform next work to verify my data
			std::shared_ptr<Worker> ptr = mNxt_worker.lock();

			//call Verifier
			if(ptr.use_count())
			{
				//WORKER_DEBUG << " Info: " << "Calling verifying callback \n";
				verify_failed_cnt = ptr->verify_value(start_value,Verifier_callback);
			}

			//Update Status
			failed_cnt  += verify_failed_cnt;
			success_cnt += (write_success_cnt - verify_failed_cnt);
		}
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
}

void Worker::write_value(uint32_t value)
{
	//WORKER_DEBUG << " Info: " << "Start writing on shared object : start-> " << value << "\n";

	//lock mutex so no one can change parameters
	std::lock_guard<std::mutex> lock(worker_thread.get_set_lock);

	//set start value
	start_value = value;

	//Notify thread
	worker_thread.proc_condition_event.notify_one();
	//WORKER_DEBUG << " Info: " << "Inform worker successfully \n";
}

void Worker :: set_next_worker(std::weak_ptr<Worker> next_worker)
{
	//lock mutex so no one can change parameters
	std::lock_guard<std::mutex> lock(worker_thread.get_set_lock);

	//set next worker
	mNxt_worker =  next_worker;
}

uint32_t Worker :: verify_value(uint32_t value,proc_callback verifier)
{
	//success count
	uint32_t verify_failed_cnt = 0;

	//WORKER_DEBUG << " Info: " << "Verifying on shared object : start-> " << value << "\n";
	try
	{
		if(verifier)
		{
			//WORKER_DEBUG << " Info: " << "Calling verifier \n";
			verify_failed_cnt = verifier(value);
		}
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
	return verify_failed_cnt;
}

std::string Worker::get_worker_name()
{
	return worker_name;
}

void Worker::print_statics()
{
	WORKER_DEBUG << " Info: " << "Success: " << success_cnt  << " Failer: "<< failed_cnt << "\n";
}
