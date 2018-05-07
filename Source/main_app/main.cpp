/**
* \section DESCRIPTION
* Start application from here
*
* \file main.cpp
*/
#include<functional>
#include<iostream>
#include<chrono>

#include "shared_object.h"
#include "worker.h"


using namespace std;
using namespace std::placeholders;

#define MAX_OBJECT_COUNT 4

std::thread gPrimaryThread;

void primary_thread()
{
	//Setup objects
	shared_object sh_obj[MAX_OBJECT_COUNT];
	std::shared_ptr<Worker> w1 = std::shared_ptr < Worker> (new Worker("worker_1",
					std::bind(&shared_object::write_object, &sh_obj[0], _1),
					std::bind(&shared_object::verify_object, &sh_obj[0], _1)));
	std::shared_ptr<Worker> w2 = std::shared_ptr < Worker> (new Worker("worker_2",
					std::bind(&shared_object::write_object, &sh_obj[1], _1),
					std::bind(&shared_object::verify_object, &sh_obj[1], _1)));
	std::shared_ptr<Worker> w3 = std::shared_ptr < Worker> (new Worker("worker_3",
					std::bind(&shared_object::write_object, &sh_obj[2], _1),
					std::bind(&shared_object::verify_object, &sh_obj[2], _1)));
	std::shared_ptr<Worker> w4 = std::shared_ptr < Worker> (new Worker("worker_4",
					std::bind(&shared_object::write_object, &sh_obj[3], _1),
					std::bind(&shared_object::verify_object, &sh_obj[3], _1)));

	//Setup up linked list
	w1->set_next_worker(w2);
	w2->set_next_worker(w3);
	w3->set_next_worker(w4);
	w4->set_next_worker(w1);

	//start threads
	w1->start_process();
	w2->start_process();
	w3->start_process();
	w4->start_process();


	do
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		w1->write_value(100);
		w2->write_value(200);
		w3->write_value(300);
		w4->write_value(400);

		std::cout << "Is required to run continue[y/n]\n";
		bool is_continue = false;
		uint8_t choise;
		std::cin >> choise;

		if((choise == 'y') || (choise == 'Y'))
		{
			continue;
		}

		w1->print_statics();
		w2->print_statics();
		w3->print_statics();
		w4->print_statics();
		break;
	}while(true);
}




int main()
{
	gPrimaryThread = std::thread(primary_thread);
	gPrimaryThread.join();
	return 0;
}
