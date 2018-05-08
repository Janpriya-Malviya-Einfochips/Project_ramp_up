/**
* \section DESCRIPTION
* Start application from here
*
* \file main.cpp
*/
#include <signal.h>
#include<functional>
#include<iostream>
#include<chrono>

#include "shared_object.h"
#include "worker.h"


using namespace std;
using namespace std::placeholders;

#define MAX_OBJECT_COUNT 4

std::thread gPrimaryThread;
bool do_exit = false;

void Exit_Singal_handler(int sig)
{
    std::cout << "\nCancling Primary thread due to signal event \n";
    pthread_cancel(gPrimaryThread.native_handle());
    do_exit = true;
}


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
    w1->set_verifier(w2);
    w2->set_verifier(w1);
    w3->set_verifier(w4);
    w4->set_verifier(w1);

    //start threads
    w1->start_process();
    w2->start_process();
    w3->start_process();
    w4->start_process();


    do
    {
        std::cout << "\nAre you want to start write and verify process [y/n]: ";
        uint8_t choise;
        std::cin >> choise;

        if((choise == 'y') || (choise == 'Y'))
        {
            w1->write_value(100);
            w2->write_value(200);
            w3->write_value(300);
            w4->write_value(400);
            continue;
        }
        else
        {
            //Exit from thread
            do_exit = true;
            break;
        }
    }
    while(true);
}




int main()
{
    //register signal handler
    signal(SIGINT, Exit_Singal_handler);

    //Start main thread
    gPrimaryThread = std::thread(primary_thread);

    //Waiting for any signal
    while(!do_exit)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout.flush();
    gPrimaryThread.join();
    return 0;
}
