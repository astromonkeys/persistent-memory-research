#ifndef BACKEND
#define BACKEND

#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/container/vector.hpp>
#include <libpmemobj++/container/string.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/make_persistent.hpp>

#define PATH "wiscular_pool"
#define LAYOUT "wiscular_layout"
#define LIBPMEMOBJ_CPP_USE_FLAT_TRANSACTION true
#define MAX_WORKOUTS_TO_DISPLAY 15

using namespace pmem;
using namespace pmem::obj;
using namespace std;

class Workout
{
public:
    Workout(std::string workoutType, std::string distance_, std::string distanceUnits_, std::string duration_, std::string durationUnits_, std::string day_, std::string month_, std::string year_, std::string username);
    persistent_ptr<pmem::obj::string> type, user, distanceUnits, durationUnits, duration, distance, day, month, year;
};

struct my_root
{
public:
    persistent_ptr<pmem::obj::vector<pmem::obj::string>> master_user_list_ptr;
    persistent_ptr<pmem::obj::vector<Workout>> master_workout_list_ptr;
private:
};

#endif // BACKEND
