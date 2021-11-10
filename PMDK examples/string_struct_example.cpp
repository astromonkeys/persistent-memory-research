/* string_struct_example.cpp */
/* Authored by Noah Zurn nzurn@wisc.edu, do whatever you want with this code */

#include <unistd.h>

#include <libpmemobj.h>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/container/string.hpp>

#define PATH "poolfile"

/*
recommended, makes pmem::obj::transaction an alias for pmem::obj::flat_transaction instead of pmem::obj::basic_transaction. Unlike basic_transaction, flat_transaction does not abort automatically in case of transactional functions (like make_persistent) failures. Instead, abort will happen only if an exception is not caught before the outermost transaction ends.
*/
#define LIBPMEMOBJ_CPP_USE_FLAT_TRANSACTION true

using namespace std;
using namespace pmem;
using namespace pmem::obj;

struct my_struct {
	persistent_ptr<pmem::obj::string> my_string_ptr;
};

struct my_root {
	persistent_ptr<my_struct> string_struct_ptr;
	p<int> the_int; // gives us an int variable residing on pmem
};

int main(int argc, char *argv[]) {
if(argc != 2 & argc != 3) {
cout << "Usage: " << argv[0] << " [init|print] <string_to_persist>" << endl; exit(EXIT_FAILURE);
}

pool<my_root> pop; // POP is an abbreviation of Pool Object Pointer
persistent_ptr<my_root> pmem_root; // pointer to our my_root struct, this is what we will use quite frequently

std::string command = std::string(argv[1]);

// create pool
if (access(PATH, F_OK) != 0) { // checks if the file specified by PATH exists. There are other ways to determine if the pool needs to be opened or created, this is just mine.
pop = pool<my_root>::create(PATH, "some_layout", PMEMOBJ_MIN_POOL);
} else {
pop = pool<my_root>::open(PATH, "some_layout");
}

pmem_root = pop.root();

if(command.compare("init") == 0) {
	if(argc != 3) { 
		cout << "Invalid command." << endl; 
cout << "Usage: " << argv[0] << " [init|print] <string_to_persist>" << endl; 
pop.close(); // close the pool
exit(EXIT_FAILURE);
	}
	// allocate pmem (we could allocate and initialize the data in a single transaction, but here I split them up)
	pmem::obj::transaction::run(pop, [&]() {
		// allocate pmem for string_struct, stored on the root
		pmem_root->string_struct_ptr = make_persistent<my_struct>();
		// allocate pmem for string_struct’s string member, initializing it to “one”
		pmem_root->string_struct_ptr->my_string_ptr = make_persistent<pmem::obj::string>("one");
	});

// initialize the data
std::string persist_me = argv[2];
transaction::run(pop, [&]() {
*(pmem_root->string_struct_ptr->my_string_ptr.get()) = persist_me; // set our string to the command line arg
pmem_root->the_int = 19;
});

// do NOT do this...
// pmem_root->the_int = 10;
// changing a p<> variable outside of a transaction is a volatile modification, not what we want
cout << "Data persisted successfully" << endl;
pop.close(); // safely close the pool
exit(EXIT_SUCCESS);
} else if(command.compare("print") == 0) {
	// get printable version of pmem::obj::string
	cout << "Persisted string: " << pmem_root->string_struct_ptr->my_string_ptr->c_str() << endl;
	cout << "Int on pmem: " << to_string(pmem_root->the_int) << endl;
} else { 
cout << "Invalid command." << endl; 
cout << "Usage: " << argv[0] << " [init|print] <string_to_persist>" << endl; 
pop.close();
exit(EXIT_FAILURE);
}

return 0;


}

