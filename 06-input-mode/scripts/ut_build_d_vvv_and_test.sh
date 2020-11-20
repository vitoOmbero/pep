#!/bin/bash

cd /workspace || exit

#sudo usermod -aG sudo $USER

./scripts/ut_idempinit_workspace.sh

cd /workspace/build/Debug || exit

cmake ../../src -DPEP_DEBUG=ON -DPEP_VERBOSE=ALL && make && make install

cd /workspace/install/bin/Tests/Debug || exit

./app.out

cd /workspace/scripts || exit

# TODO: how to auto register must be tested items?
# python3 test_execution.py

# TODO: secure user and group for dev 
# chmod -R 2777 /workspace
