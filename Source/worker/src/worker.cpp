/**
* \section DESCRIPTION
* This file contain all interface for worker module
*
* \file worker.cpp
*/

#include<iostream>
#include<unistd.h>
#include "../include/worker.h"


using namespace std;

#define WORKER_DEBUG std::cout << "Worker[" << worker_name << "]  "
#define WORKER_THREAD_DEBUG std::cout << "Worker[" << thread.thread_name << "]  "

Worker::Worker(std::string name, Worker::proc_callback writer,
		Worker::proc_callback verifier) : worker_name(name)
{

	//Set Thread name
	writer_thread.thread_name  = name + "_WriterThread";

	//set writer callback
	writer_thread.callback = writer;

	//Set Thread name
	verifier_thread.thread_name  = name + "_VerifierThread";

	//set verifier callback
	verifier_thread.callback = verifier;

	//Start all threads
	start_process();

	WORKER_DEBUG << " Info: " << "Worker created \n";
}

Worker::~Worker()
{
	//Exit all running threads
	try
	{
		//Stop all running threads
		stop_process();
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
	WORKER_DEBUG << " Info: " << "Worker deleted\n";
}

void Worker::start_process()
{
	//start writer thread
	writer_thread.proc_thread = std::thread(&Worker::thread_function, this,std::ref(writer_thread));

	//start verifier thread
	verifier_thread.proc_thread = std::thread(&Worker::thread_function, this,std::ref(verifier_thread));
}

void Worker::stop_process()
{
	//Exit all running threads
	try
	{
		//Stop all running threads
		stop_thread(writer_thread);
		stop_thread(verifier_thread);
	}
	catch(std::exception& e)
	{
		WORKER_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
}

void Worker::thread_function(W_thread& thread)
{
	WORKER_THREAD_DEBUG << ": Start Running\n";

	while(true)
	{
		try
		{
			//wait for notifier
			std::unique_lock<std::mutex> lock(thread.proc_condition_lock);
			thread.proc_event.wait(lock);

			WORKER_THREAD_DEBUG << ": Info : condition ticked\n";
			{
				//lock mutex first
				std::lock_guard<std::mutex> lock(thread.get_set_lock);

				//is required to exit
				if(thread.do_exit)
				{
					WORKER_THREAD_DEBUG << ": Info : Exiting thread\n";
					break;
				}

				//is callbcak set
				if(thread.callback)
				{
					WORKER_THREAD_DEBUG << ": Info : Calling callback \n";
					thread.callback(10,10);
				}
			}
		}
		catch(std::exception& e)
		{
			WORKER_THREAD_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
		}
	}
}

void Worker::stop_thread(W_thread& thread)
{

	WORKER_THREAD_DEBUG << " Info: force exiting thread \n";

	try
	{
		//Set exit
		thread.set_exit();
		std::lock_guard<std::mutex> lock(thread.get_set_lock);

		//Notify thread
		thread.proc_event.notify_one();

		WORKER_THREAD_DEBUG << " Info: waiting for rejoin\n";

		//Waiting for thread  exit
		thread.proc_thread.join();

		WORKER_THREAD_DEBUG << " Info: Exited\n";
	}
	catch(std::exception& e)
	{
		WORKER_THREAD_DEBUG << " Error: " << e.what() << " Fn:" << __func__ << "line:" << __LINE__ << "\n";
	}
}


void Worker::write_value(uint32_t value)
{
	//lock mutex first
	//std::lock_guard<std::mutex> lock(writer_thread.proc_condition_lock);

	WORKER_DEBUG << " Info: " << "Start writing on shared object : start-> " << value << "\n";

	//Start value
	writer_thread.set_start_value(value);

	//Notify thread
	writer_thread.proc_event.notify_one();
}

void Worker::verify_value(uint32_t value)
{
	WORKER_DEBUG << " Info: " << "Start Verifing on shared object : start-> " << value << "\n";

	//lock mutex first
	//std::lock_guard<std::mutex> lock(verifier_thread.proc_condition_lock);

	//Start value
	verifier_thread.set_start_value(value);

	//Notify thread
	verifier_thread.proc_event.notify_one();
}

std::string Worker::get_worker_name()
{
	return worker_name;
}

//void Worker::add_success(uint32_t count) {
//}

//void Worker::add_failer(uint32_t count) {/
//}

//void Worker::print_stats() {
//}

void test_1(uint32_t i,uint32_t j)
{
	cout<<"testz_1 called \n";
}

void test_2(uint32_t i,uint32_t j)
{
	cout<<"testz_2 called \n";
}
int main()
{
	auto fn_1 = &test_1;
	auto fn_2 = &test_2;


	Worker w("w1",fn_1,fn_2);
	//Worker w1("w1",fn_1,fn_2);
	//Worker w2("w2",fn_1,fn_2);
	//Worker w3("w3",fn_1,fn_2);
	//sleep(3);
	cout<<"\n\n\n\n\nwriting value\n";
	w.write_value(10);
	//sleep(3);
	cout<<"\n\n\n\n\nVerifiing value\n";
	//w.verify_value(10);
	//sleep(3);
	return 0;
}

void Worker::worker_thread_params::set_exit(void)
{
	//lock mutex first
	std::lock_guard<std::mutex> lock(get_set_lock);
	do_exit = true;
}

void Worker::worker_thread_params::set_start_value(uint32_t value)
{
	//lock mutex first
	std::lock_guard<std::mutex> lock(get_set_lock);
	start_value = value;
}
