#include <unistd.h>
#include <algorithm>
#include <string>

#include "backend.hpp"

pool<my_root> pop;
persistent_ptr<my_root> pmem_root;

Workout::Workout(std::string workoutType, std::string distance_, std::string distanceUnits_, std::string duration_, std::string durationUnits_, std::string day_, std::string month_, std::string year_, std::string username)
{
    transaction::run(pop, [&]() {
		type = make_persistent<pmem::obj::string>(workoutType);
    	distanceUnits = make_persistent<pmem::obj::string>(distanceUnits_);
    	durationUnits = make_persistent<pmem::obj::string>(durationUnits_);
    	day = make_persistent<pmem::obj::string>(day_);
    	month = make_persistent<pmem::obj::string>(month_);
    	year = make_persistent<pmem::obj::string>(year_);
    	user = make_persistent<pmem::obj::string>(username);
    	distance = make_persistent<pmem::obj::string>(distance_);
    	duration = make_persistent<pmem::obj::string>(duration_);
	});
}

void init_pool()
{
	// create pool
    int newpool;
    if (access(PATH, F_OK) != 0) {
        pop = pool<my_root>::create(PATH, LAYOUT, PMEMOBJ_MIN_POOL);
        newpool = 1;
    } else {
        pop = pool<my_root>::open(PATH, LAYOUT);
        newpool = 0;
    }

    pmem_root = pop.root();

	if(newpool == 1) { // if pool is new, have some setup to do
		transaction::run(pop, [&]() { 
		pmem_root->master_user_list_ptr = make_persistent<pmem::obj::vector<pmem::obj::string>>();
		pmem_root->master_workout_list_ptr = make_persistent<pmem::obj::vector<Workout>>();
		});
	}
}

void persistUser(std::string username)
{
	transaction::run(pop, [&]() {
		persistent_ptr<pmem::obj::string> newUser = make_persistent<pmem::obj::string>(username);
		pmem_root->master_user_list_ptr->push_back(*newUser);
		delete_persistent<pmem::obj::string>(newUser);
	});
}

void close_pool()
{
	pop.close();
	pool<my_root>::check(PATH, LAYOUT);
}

void listUsers()
{
	auto i = pmem_root->master_user_list_ptr->begin();
    for(i; i != pmem_root->master_user_list_ptr->end(); ++i)
        cout << (*i).c_str() << endl;
}

void persistWorkout(std::string type, std::string user, std::string distanceUnits, std::string durationUnits, std::string duration, std::string distance, std::string day, std::string month, std::string year)
{
	transaction::run(pop, [&]() {
		persistent_ptr<Workout> newWorkout = make_persistent<Workout>(type, distance, distanceUnits, duration, durationUnits, day, month, year, user);
		pmem_root->master_workout_list_ptr->push_back(*newWorkout);
		delete_persistent<Workout>(newWorkout);
	});	
	// cout << "workout succesfully persisted"  << endl;
}

void listUserWorkouts(std::string username)
{
    auto i = pmem_root->master_workout_list_ptr->begin();
	int counter = 0;
    for(i; i != pmem_root->master_workout_list_ptr->end() && counter < MAX_WORKOUTS_TO_DISPLAY; ++i) {
        if(std::string((*i).user->c_str()) == username) {
            cout << (*i).type->c_str() <<\
            " " << (*i).distance->c_str() <<\
            " " << (*i).distanceUnits->c_str() <<\
            " " << (*i).duration->c_str() <<\
            " " << (*i).durationUnits->c_str() <<\
            " " << (*i).day->c_str() <<\
            " " << (*i).month->c_str() <<\
            " " << (*i).year->c_str() <<\
            " " << (*i).user->c_str() << endl;
        	counter++;
		}
    }
}

void listAllWorkouts()
{
	auto i = pmem_root->master_workout_list_ptr->begin();
	int counter = 0;
    for(i; i != pmem_root->master_workout_list_ptr->end() && counter < MAX_WORKOUTS_TO_DISPLAY; ++i) {
       cout << (*i).type->c_str() <<\
        " " << (*i).distance->c_str() <<\
        " " << (*i).distanceUnits->c_str() <<\
        " " << (*i).duration->c_str() <<\
        " " << (*i).durationUnits->c_str() <<\
        " " << (*i).day->c_str() <<\
        " " << (*i).month->c_str() <<\
        " " << (*i).year->c_str() <<\
        " " << (*i).user->c_str() << endl;
		counter++;
	}
}

int main(int argc, char *argv[])
{
	std::string command = argv[1];
	if(command == "registerUser") {
		std::string name = argv[2];
		init_pool();
		persistUser(name);
		close_pool();
	} else if(command == "addWorkout") {
		init_pool();
		std::string type = argv[2];
		std::string user = argv[3];
		std::string distanceUnits = argv[4];
		std::string durationUnits = argv[5];
		std::string duration = argv[6];
		std::string distance = argv[7];
		std::string day = argv[8];
		std::string month = argv[9];
		std::string year = argv[10];
		persistWorkout(type, user, distanceUnits, durationUnits, duration, distance, day, month, year);
		close_pool();
	} else if(command == "listUsers") {
		init_pool();
		listUsers();
		close_pool();
	} else if(command == "allWorkouts") {
		init_pool();
		listAllWorkouts();
		close_pool();
	} else if(command == "userWorkouts") {
		init_pool();
		std::string name = argv[2];
		listUserWorkouts(name);
		close_pool();
	} else {
		cout << "invalid command" << endl;
	}
	return 0;
}
