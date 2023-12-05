gcc main.c -o build/main

if [ $? -ne 0 ]; then 

    exit 1
fi

./build/main