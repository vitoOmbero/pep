#!/bin/bash
#--user $UID:$GID \
#-e USER='$(USER)' \
docker container run -it \
-v $(pwd)/../../00-common:/00-common \
-v $(pwd)/../src:/workspace/src \
-v $(pwd)/../assets:/workspace/assets \
-v $(pwd)/../build:/workspace/build \
-v $(pwd)/../install:/workspace/install \
-v $(pwd):/workspace/scripts \
-w /workspace/ \
majstarz/ubuntu-sdl2-build:wip bash
