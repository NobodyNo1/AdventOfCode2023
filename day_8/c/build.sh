gcc main.c -o build/main -g

if [ $? -ne 0 ]; then

exit 1

fi

./build/main