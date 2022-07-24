#!/bin/bash

pushd ..
ansible raspi -i $(pwd)/hosts/dev --module-name ping --user rod 
popd
