#!/bin/bash
#--user $UID:$GID \
#-e USER='$(USER)' \
docker container run -it \
-v $(pwd)/../src:/workspace/src \
-v $(pwd)/../build:/workspace/build \
-v $(pwd)/../install:/workspace/install \
-v $(pwd):/workspace/scripts \
-w /workspace/ \
majstarz/ubuntu-sdl2-build:wip bash
