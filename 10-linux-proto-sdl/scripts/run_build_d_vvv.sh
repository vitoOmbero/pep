#!/bin/bash

#--user $UID:$GID \
#-e USER='$(USER)' \

docker container run -t \
-v $(pwd)/../src:/workspace/src \
-v $(pwd)/../build:/workspace/build \
-v $(pwd)/../install:/workspace/install \
-v $(pwd):/workspace/scripts \
-w /workspace/ \
--entrypoint /workspace/scripts/ut_build_d_vvv_and_test.sh \
majstarz/ubuntu-sdl2-build:wip
