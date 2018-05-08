#include <stdint.h>
#include <memory>
#include <functional>
#include <unistd.h>
#include "UnitTest++/UnitTest++.h"
#include "shared_object.h"
#include "worker.h"

using namespace std;
using namespace std::placeholders;

//Unit test cases for shared object module
SUITE(shared_object)
{
    class shared_object_Fixture
    {
    public:
        uint16_t start_value;
        uint16_t shared_obj_size;
        shared_object test_obj;

        shared_object_Fixture()
        {
            start_value = 100;
            shared_obj_size = 115;
        }

    };

    TEST_FIXTURE(shared_object_Fixture, WriteAPI)
    {
        //check all byte write successfully
        CHECK_EQUAL(shared_obj_size,test_obj.write_object(start_value));
    }

    TEST_FIXTURE(shared_object_Fixture, VerifyAPI)
    {
        //write object
        test_obj.write_object(start_value);

        //verified all byte write successfully so failed count
        CHECK_EQUAL(0,test_obj.verify_object(start_value));

        //verified invalid start value check failed count == shared_obj_size
        CHECK_EQUAL(shared_obj_size,test_obj.verify_object(start_value+1));
    }
}

//Unit test cases with work and shared object module
SUITE(worker)
{
    class worker_Fixture
    {
    public:

        //shared objects
        shared_object sh_obj1;
        shared_object sh_obj2;

        //shared objects
        std::shared_ptr<Worker> worker1;
        std::shared_ptr<Worker> worker2;


        void basic_setup()
        {
            worker1 = std::shared_ptr< Worker>(new Worker("worker_1",std::bind(&shared_object::write_object, &sh_obj1, _1),
                                               std::bind(&shared_object::verify_object, &sh_obj1, _1)));

            worker2 = std::shared_ptr< Worker>(new Worker("worker_2",std::bind(&shared_object::write_object, &sh_obj2, _1),
                                               std::bind(&shared_object::verify_object, &sh_obj2, _1)));
        }

        void bind_Work1_Work2()
        {
            worker1->set_verifier(worker2);
            worker2->set_verifier(worker1);
        }

        void bind_same_worker()
        {
            worker1->set_verifier(worker1);
            worker2->set_verifier(worker2);
        }

        worker_Fixture()
        {
            basic_setup();
        }
    };

    TEST_FIXTURE(worker_Fixture, Test_SameWorker)
    {
        //bind w1 to w1 & w2 to w2
        bind_same_worker();

        //Start worker one
        worker1->start_process();
        worker2->start_process();
        usleep(1000);

        // Start writing
        worker1->write_value(100);
        usleep(1000);
        // verify value manually
        CHECK_EQUAL(0,sh_obj1.verify_object(100));
        CHECK_EQUAL(115,sh_obj2.verify_object(100));

        // Start writing
        worker2->write_value(200);
        usleep(1000);
        // verify value manually
        CHECK_EQUAL(0,sh_obj2.verify_object(200));
        CHECK_EQUAL(115,sh_obj1.verify_object(200));
    }

    TEST_FIXTURE(worker_Fixture, Test_DifferentWorker)
    {
        //bind w1 to w1 & w2 to w2
        bind_Work1_Work2();

        //Start worker one
        worker1->start_process();
        worker2->start_process();
        usleep(1000);

        // Start writing
        worker1->write_value(100);
        usleep(1000);
        // verify value manually
        CHECK_EQUAL(0,sh_obj1.verify_object(100));
        CHECK_EQUAL(115,sh_obj2.verify_object(100));

        // Start writing
        worker2->write_value(200);
        usleep(1000);
        // verify value manually
        CHECK_EQUAL(0,sh_obj2.verify_object(200));
        CHECK_EQUAL(115,sh_obj1.verify_object(200));
    }
}

int main(int, const char *[])
{
    return UnitTest::RunAllTests();
}
