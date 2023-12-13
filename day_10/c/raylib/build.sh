gcc vis.c -lraylib -o  build/vis -g

if [ $? -ne 0 ]; then
    exit 1
fi

build/vis