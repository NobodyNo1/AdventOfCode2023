gcc main.c -Wtype-limits -Wextra -o build/main -g

if [ $? -ne 0 ]; then
    exit 1
fi

build/main