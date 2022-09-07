.PHONY: all build replication mk install uninstall clean dvi dist tests leaks cpplint gcov_report test
BD=build/
CC=gcc
APP=$(BD)calc.app
CFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lstdc++ -lgtest -lgtest_main
FLAGS= -Wall -Wextra -Werror -std=c++17
MAN=./Doc

all: clean build

build: clean mk replication
	cd $(BD); qmake calc.pro
	make -C $(BD)
	cd $(BD); rm -rf *.c *.h *.cpp *.ui *.o *.icns
	cp style.css $(APP)/Contents/MacOS

replication:
	cp calc.pro $(BD)
	cp calc_en_US.ts $(BD)
	cp main.cpp $(BD)
	cp model/modelCalc.cpp $(BD)model/
	cp model/*.h  $(BD)model/
	cp controller/*.h $(BD)controller/
	cp viewer/*.cpp $(BD)viewer/
	cp viewer/*.h $(BD)viewer/
	cp viewer/*.ui $(BD)viewer/
	cp conteiners_SQ/*.h $(BD)conteiners_SQ/
	cp PlotLibrary/qcustomplot.cpp build/PlotLibrary/qcustomplot.cpp
	cp PlotLibrary/qcustomplot.h build/PlotLibrary/qcustomplot.h
	cp PlotLibrary/GPL.txt build/PlotLibrary/GPL.txt

mk:
	mkdir $(BD)
	mkdir $(BD)conteiners_SQ
	mkdir $(BD)controller
	mkdir $(BD)model
	mkdir $(BD)viewer
	mkdir $(BD)PlotLibrary

install: clean uninstall build
	make clean

uninstall: 
	rm -rf $(BD)

clean:
	rm -rf test *.a *.so *.o *.cfg *.gcda *.gcno *.html *.info *.dSYM report backup_Smart_Calc2

dvi:
	open Doc/documantation.html

dist: clean
	rm -rf backup_Smart_Calc2
	mkdir backup_Smart_Calc2
	cp -R conteiners_SQ backup_Smart_Calc2/conteiners_SQ
	cp -R controller backup_Smart_Calc2/
	cp -R model backup_Smart_Calc2/
	cp -R viewer backup_Smart_Calc2/
	cp -R PlotLibrary backup_Smart_Calc2/
	cp Makefile *.pro *.cpp *.user *.css *.ts backup_Smart_Calc2/
	tar -cvzf $(HOME)/Desktop/backup_Smart_Calc2.tgz backup_Smart_Calc2/
	rm -rf backup_Smart_Calc2/

tests: clean
	$(CC) $(FLAGS) test.cpp model/modelCalc.cpp -o test $(GTESTFLAGS)
	./test

leaks: clean tests
	leaks --atExit -- ./test

cpplint: clean
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl model/*.cpp
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl model/*.h
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl viewer/*.cpp
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl viewer/*.h
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl controller/*.h
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl conteiners_SQ/*.h
	python3 ../materials/linters/cpplint.py --extensions=cpp,h,inl test.cpp
	rm CPPLINT.cfg


gcov_report: clean
	$(CC) $(CFLAGS) test.cpp model/modelCalc.cpp -o test $(GTESTFLAGS)
	./test
	lcov --no-external -c -d . -o tests.info
	genhtml tests.info -o report
	open -a "Google Chrome" report/index.html
	# xdg-open report/index.html
