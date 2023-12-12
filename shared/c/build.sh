gcc test_shared.c -o build/test_shared -g

if [ $? -ne 0 ]; then
    exit 1
fi

./build/test_shared