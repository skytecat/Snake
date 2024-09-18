CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
GTESTFLAGS=-lgtest -lm

all: test

install: uninstall
	cd gui && cd desktop && qmake the_best_games.pro && make && make clean && rm Makefile && mkdir ../../build && mv the_best_games.app/$(UI_BIN) ../../build
	open build/the_best_games.app

install_term:
	$(CC)  $(CFLAGS) backend/snake_controller.cc backend/snake_model.cc gui/cli/snake_view.cc backend/snake_main.cc -lncurses -o snake
	./snake

test: clean
	$(CC) $(CFLAGS) backend/snake_model.cc tests/snake_test.cc $(GTESTFLAGS) -o test
	./test

gcov_report: clean
	$(CC) $(CFLAGS) --coverage backend/snake_model.cc tests/snake_test.cc $(GTESTFLAGS) -o coverage
	./coverage
	lcov -t "result" -o res.info  --ignore-errors inconsistent -c -d .
	lcov --remove res.info /c++/13 /usr/local/include/gtest -o filtered_coverage.info
	genhtml -o report filtered_coverage.info
	open report/index.html

clean:
	rm -rf snake test *.gc* coverage report *.info build tetris

brew:
	cd
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

lcov:
	brew install lcov
