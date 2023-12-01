gcc main.c -std=c99 -o build/main

if [ $? -ne 0 ]; then
    exit 1
fi

./build/main