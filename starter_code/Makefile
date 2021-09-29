.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o qwirkle.o Board.o GameEngine.o Hand.o Player.o SerialisedData.o Menu.o Bag.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

run_test:
	./qwirkle < Tests/ExitTest.input > Tests/ExitTest.gameout
	./qwirkle < Tests/LoadCreditsTest.input > Tests/LoadCreditsTest.gameout
	./qwirkle < Tests/LoadGameTest.input > Tests/LoadGameTest.gameout
	./qwirkle < Tests/QwirkleHorizontalTest.input > Tests/QwirkleHorizontalTest.gameout
	./qwirkle < Tests/QwirkleVerticalTest.input > Tests/QwirkleVerticalTest.gameout
	./qwirkle < Tests/QwirkleSameShapeVertTest.input > Tests/QwirkleSameShapeVertTest.gameout
	./qwirkle < Tests/QwirkleSameShapeHorizTest.input > Tests/QwirkleSameShapeHorizTest.gameout
	./qwirkle < Tests/TestGameComplete.input > Tests/TestGameComplete.gameout
	./qwirkle < Tests/TestingPlayerNameValidation.input > Tests/TestingPlayerNameValidation.gameout
	./qwirkle < Tests/TestingFileNotFound.input > Tests/TestingFileNotFound.gameout
	./qwirkle < Tests/TestingIncorrectFileFormat.input > Tests/TestingIncorrectFileFormat.gameout
	./qwirkle < Tests/TestingSaveFile.input > Tests/TestingSaveFile.gameout

test_and_diff: run_test
	diff -w Tests/ExitTest.output Tests/ExitTest.gameout
	diff -w Tests/LoadCreditsTest.output Tests/LoadCreditsTest.gameout
	diff -w Tests/LoadGameTest.output Tests/LoadGameTest.gameout
	diff -w Tests/QwirkleHorizontalTest.output Tests/QwirkleHorizontalTest.gameout
	diff -w Tests/QwirkleVerticalTest.output Tests/QwirkleVerticalTest.gameout
	diff -w Tests/QwirkleSameShapeVertTest.output Tests/QwirkleSameShapeVertTest.gameout
	diff -w Tests/QwirkleSameShapeHorizTest.output Tests/QwirkleSameShapeHorizTest.gameout
	diff -w Tests/TestGameComplete.output Tests/TestGameComplete.gameout
	diff -w Tests/TestingPlayerNameValidation.output Tests/TestingPlayerNameValidation.gameout
	diff -w Tests/TestingFileNotFound.output Tests/TestingFileNotFound.gameout
	diff -w Tests/TestingIncorrectFileFormat.output Tests/TestingIncorrectFileFormat.gameout
	diff -w Tests/TestingSaveFile.output Tests/TestingSaveFile.gameout
	diff -w -y Tests/Saves/testFileOutput.expsave testFileOutput.save

setup: 
	./qwirkle < Tests/ExitTest.input > Tests/ExitTest.output
	./qwirkle < Tests/LoadCreditsTest.input > Tests/LoadCreditsTest.output
	./qwirkle < Tests/LoadGameTest.input > Tests/LoadGameTest.output
	./qwirkle < Tests/QwirkleHorizontalTest.input > Tests/QwirkleHorizontalTest.output
	./qwirkle < Tests/QwirkleVerticalTest.input > Tests/QwirkleVerticalTest.output
	./qwirkle < Tests/QwirkleSameShapeVertTest.input > Tests/QwirkleSameShapeVertTest.output
	./qwirkle < Tests/QwirkleSameShapeHorizTest.input > Tests/QwirkleSameShapeHorizTest.output
	./qwirkle < Tests/TestGameComplete.input > Tests/TestGameComplete.output
	./qwirkle < Tests/TestingPlayerNameValidation.input > Tests/TestingPlayerNameValidation.output
	./qwirkle < Tests/TestingFileNotFound.input > Tests/TestingFileNotFound.output
	./qwirkle < Tests/TestingIncorrectFileFormat.input > Tests/TestingIncorrectFileFormat.output
	./qwirkle < Tests/TestingSaveFile.input > Tests/TestingSaveFile.output