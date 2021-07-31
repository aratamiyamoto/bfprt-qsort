#!/bin/sh

build_image() {
    docker build -t bfprt-qsort docker
}

run_container() {
    CONTAINER_CMD=$1
    docker run -v $(pwd):/root/bfprt-qsort -w=/root/bfprt-qsort --rm -it bfprt-qsort /bin/bash -c "${CONTAINER_CMD}"
}

if [ $# -lt 1 ]; then
    2>&1 echo "usage: $0 <sort|profile|test>"
    exit 1
fi

CMD=$1

build_image

if [ ${CMD} == "sort" ]; then
    2>&1 echo "Not implemented."
    exit 1
elif [ ${CMD} == "profile" ]; then
    CONTAINER_CMD=" \
        mkdir -p build/ && \
        cmake -S . -B build/ && \
        make -C build/ && \
        build/samples/profile"
elif [ ${CMD} == "test" ]; then
    2>&1 echo "Not implemented."
    exit 1
fi

run_container "${CONTAINER_CMD}"
