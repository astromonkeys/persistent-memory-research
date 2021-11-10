#ifndef BACKEND
#define BACKEND

#include "widgets/workout.hpp"

#include <string>

#include <libpmemobj.h>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/container/vector.hpp>
#include <libpmemobj++/container/string.hpp>
#include <libpmemobj++/make_persistent.hpp>

#define PATH "wiscular_pool"
#define LAYOUT "wiscular_layout"
#define LIBPMEMOBJ_CPP_USE_FLAT_TRANSACTION true

using namespace pmem;
using namespace pmem::obj;

struct my_root
{
public:
    /* all workouts stored in this vector
    for individual user's profiles, show only workouts where the workout's user matches the current user,
    updating the list and re-retrieving it */
    //persistent_ptr<pmem::obj::vector<Workout>> master_workout_list_ptr;

    /* maintains a list of the usernames that have registered */
    persistent_ptr<pmem::obj::vector<pmem::obj::string>> master_user_list_ptr;
private:
};

class backend
{
public:
    backend();
    bool userExists(std::string username);
    void persistUser(std::string username);
    void close();

    pool<my_root> pop;
    persistent_ptr<my_root> pmem_root;
private:
};


#endif // BACKEND
