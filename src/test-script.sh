CMAKE_DICT=../cmake-build-debug

TEST_APP=linda-test
SERVER=linda-server

INSTRUCTIONS_FILE=instructions.txt

make --silent --directory=$CMAKE_DICT $TEST_APP

$CMAKE_DICT/$TEST_APP $INSTRUCTIONS_FILE

