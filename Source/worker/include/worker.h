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
	typedef std::function<uint16_t (uint16_t start_from )> proc_callback;

private:

	/**
	 * \class worker_thread_params
	 * \brief Single thread parameters. Thread will wait for condition  and when every
	 * 		  ticked it will call register callback for process
	 */
	typedef struct Worker_thread_params
	{
		//! flag to indicate to close thread
		bool do_exit;

		//! mutex lock for waiting condition
		std::mutex proc_condition_lock;

		//! condition  variable to tick
		std::condition_variable proc_condition_event;

		//! thread object
		std::thread proc_thread;

		//! mutex lock for process callbacks
		std::mutex get_set_lock;

		Worker_thread_params() :do_exit(false)
		{
		}

		~Worker_thread_params()
		{

		}

		/**
		 * Thread function to start thread
		 */
		void  thread_function(Worker& WorkerObject);

		/**
		 * Thread function to start thread
		 */
		void  start_thread(Worker& WorkerObject);

		/**
		 * Thread function to start thread
		 */
		void  stop_thread(void);

		/**
		 * Thick thread and perform registered action
		 */
		void process_tick(uint32_t value);

	}Wrkr_th;

	//! worker id
	uint16_t worker_id;

	//! call back function for verifier or writer
	proc_callback Writer_callback;

	//! call back function for verifier or writer
	proc_callback Verifier_callback;

	//! number of failed attempts
	uint32_t failed_cnt;

	//! number of success attempts
	uint32_t success_cnt;

	//! Name of worker
	std::string worker_name;

	//! Thread  object  for write process
	Wrkr_th worker_thread;

	//! start value for verify or write in shared object
	uint32_t start_value;

	//! Verifier worker
	std::weak_ptr<Worker> mNxt_worker;

private:

	//! Do work
	void do_work(void);

	//! set unique id
	void  set_object_unique_id();
public:

    /**
     * Worker constructor
     *
     * \param[in] name 			: Name of worker
     * \param[in] proc_callback : write callback to write on shared object
     * \param[in] verifier		: verify callback to verify shared object
     */
	Worker(std::string name, proc_callback writer,proc_callback verifier);

    /**
     * Worker distructor
     */
	~Worker();

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

    /**
     * Start writing on shared object
     * \param[in] value		: Start value
     */
	void  write_value(uint32_t value);

    /**
     * Start writing on shared object
     * \param[in] value		: Start value
     */
	uint32_t  verify_value(uint32_t value,proc_callback verifier);

	/**
     * Start verifing on shared object
     * \param[in] value		: Start value
     */
	void  set_next_worker(std::weak_ptr<Worker> next_worker);

    /**
     * Get worker name
     * \return string : worker name
     */
	std::string get_worker_name();

    /**
     * Get worker name
     * \return string : worker name
     */
	void print_statics(void);
};
