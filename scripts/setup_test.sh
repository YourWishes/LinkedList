mkdir -p ./lib/
mkdir -p ./bin/
git clone https://github.com/ThrowTheSwitch/Unity ./lib/Unity
gcc ./test/list.test.c ./src/list.c ./lib/Unity/src/unity.c -I ./src/ -I ./lib/Unity/src -o ./bin/test
chmod +x ./bin/test