# Makefile to build app.wt, the Wiscular app
clean:
	@rm -f wiscular.wt
	@echo "Cleaned."

build: widgets/*.cpp main.cpp backend.cpp
	@g++ -std=c++14 -o wiscular.wt main.cpp widgets/*.cpp -lwtfcgi -lwt -lpmemobj
	@g++ -o wiscular_backend backend.cpp -lpmemobj
	@echo "App built."

restart:
	@$(MAKE) stop
	@$(MAKE) run

count:
	@wc -l *.cpp widgets/*.cpp widgets/*.hpp

run:
	@sudo systemctl start apache2

stop:
	@sudo systemctl stop apache2

deploy: widgets/*.cpp main.cpp backend.cpp
	@$(MAKE) build
	@sudo systemctl stop apache2	
	@cp wiscular.wt /var/www/wt
	@cp wiscular_backend /var/www/wt
	@cp -r assets /var/www/wt
	@sudo systemctl start apache2
	@echo "Server is running."
