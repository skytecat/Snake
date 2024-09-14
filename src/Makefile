CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
TETRIS_SOURCE = brick_game/tetris/*.c gui/cli/front.c
GTESTFLAGS=-lgtest -lm

all: test

install: uninstall
	cd gui && cd desktop && cd the_best_games && qmake the_best_games.pro && make && make clean && rm Makefile && mkdir ../../../build && mv the_best_games.app/$(UI_BIN) ../../../build
	open build/the_best_games.app

install_tetris:
	gcc -Wall -Werror -Wextra -std=c11 $(TETRIS_SOURCE) -lncurses -o tetris
	./tetris

install_term_snake:
	$(CC)  $(CFLAGS) brick_game/snake/snake_controller.cc brick_game/snake/snake_model.cc gui/cli/snake_view.cc brick_game/snake/snake_main.cc -lncurses -o snake
	./snake

uninstall:
	rm -rf build

clang:
	cp ../materials/linters/.clang-format .
	find . \( -name "*.h" -o -name "*.cc" -o -name "*.c" -o -name "*.cpp" \) | xargs clang-format -n
	rm -rf .clang-format

dvi:
	open documentation.md

dist: install
	mkdir -p dist
	cp  -R ./build/the_best_games.app ./dist
	cp ./documentation.md ./dist
	cd ./dist && tar cvzf the_best_games.tgz *
	cd ./dist && rm -R the_best_games.app documentation.md

test: clean
	$(CC) $(CFLAGS) brick_game/snake/snake_model.cc tests/test.cc $(GTESTFLAGS) -o test
	./test

gcov_report: clean
	$(CC) $(CFLAGS) --coverage brick_game/snake/snake_model.cc tests/test.cc $(GTESTFLAGS) -o coverage
	./coverage
	lcov -t "result" -o res.info  --ignore-errors inconsistent -c -d .
	lcov --remove res.info /c++/13 /usr/local/include/gtest -o filtered_coverage.info
	genhtml -o report filtered_coverage.info
	open report/index.html

clean:
	rm -rf snake test *.gc* coverage report *.info build tetris