/**
* \section DESCRIPTION
* This file contain all interface for worker module
*
* \file worker.h
*/

#include<string>
#include<memory>
#include<thread>
#include<mutex>
#include<functional>
//#include<shared_ptr>
#include<condition_variable>


/**
 * \class worker
 * \brief worker class  to write  and  verify shared memory when every  ticked
 */
class Worker
{
public:

    /**
     * \brief Callback function for writer & verifier threads
     */
	typedef std::function<void(uint32_t start_from,uint32_t faier_cnt )> proc_callback;


private:

	/**
	 * \class worker_thread_params
	 * \brief Single thread parameters. Thread will wait for condition  and when every
	 * 		  ticked it will call register callback for process
	 */
	typedef struct worker_thread_params
	{
		//! flag to indicate to close thread
		bool do_exit;

		//! start value for verify or write in shared object
		uint32_t start_value;

		//! number of failed attempts
		uint32_t failed_cnt;

		//! number of success attempts
		uint32_t success_cnt;

		//! name of thread
		std::string thread_name;

		//! thread object
		std::thread proc_thread;

		//! mutex lock for waiting condition
		std::mutex proc_condition_lock;

		//! mutex lock for pocess callbacks
		std::mutex get_set_lock;

		//! condition  variable to tick
		std::condition_variable proc_event;

		//! call back function for verifier or writer
		proc_callback callback;

		worker_thread_params() :do_exit(false), callback(nullptr),
			start_value(0), failed_cnt(0), success_cnt(0)
		{

		}

	    /**
	     * Set exit
	     */
		void set_exit(void);

	    /**
	     * Set exit
	     */
		void set_start_value(uint32_t value);


	}W_thread;

	//! Name of worker
	std::string worker_name;

	//! Thread  object  for write process
	W_thread writer_thread;

	//! Thread  object  for verify process
	W_thread verifier_thread;

	//! Next worker
	//std::weak_ptr<Worker> next_worker;

private:

    /**
     * Thread function for start sepecific task
     *
     * \param[in] W_thread& thread
     * - worker thread object
     */
	void  thread_function(W_thread& thread);

    /**
     * Stop thread
     *
     * \param[in] W_thread& thread
     * - worker thread object
     */
	void stop_thread(W_thread& thread);


    /**
     * Start process to start all thread
     * \param[in] void
     */
	void  start_process();

    /**
     * Stop all running threads
     * \param[in] void
     */
	void  stop_process();

public:

    /**
     * Worker constructor
     *
     * \param[in] name 			: Name of worker
     * \param[in] proc_callback : write callback to write on shared object
     * \param[in] verifier		: verify callback to verify shared object
     */
	Worker(std::string name,proc_callback writer,proc_callback verifier);

    /**
     * Worker distructor
     */
	~Worker();


    /**
     * Start writing on shared object
     * \param[in] value		: Start value
     */
	void  write_value(uint32_t value);

    /**
     * Start verifing on shared object
     * \param[in] value		: Start value
     */
	void  verify_value(uint32_t value);

    /**
     * Get worker name
     * \return string : worker name
     */
	std::string get_worker_name();

	//add success count
	//void add_success(uint32_t count);

	//add success count
	//void add_failer(uint32_t count);

	//Print stats
	//void print_stats();
};
