#include <unistd.h>
#include <algorithm>

#include "backend.hpp"

backend::backend()
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
		transaction::run(pop, [&]() { pmem_root->master_user_list_ptr = make_persistent<pmem::obj::vector<pmem::obj::string>>();
		});
	}
}

bool backend::userExists(std::string username)
{
	//auto a = *(pmem_root->master_user_list_ptr);
	//auto i = pmem_root->master_user_list_ptr->begin();
    //for(i; i != pmem_root->master_user_list_ptr->end(); ++i)
     //   if((*i).compare(username) == 0) return true;

    return false;
}

void backend::persistUser(std::string username)
{
	transaction::run(pop, [&]() {
		persistent_ptr<pmem::obj::string> newUser = make_persistent<pmem::obj::string>(username);
		pmem_root->master_user_list_ptr->push_back(*newUser);
		delete_persistent<pmem::obj::string>(newUser);
	});
}

void backend::close()
{
	pop.close();
	pool<my_root>::check(PATH, LAYOUT);
}
