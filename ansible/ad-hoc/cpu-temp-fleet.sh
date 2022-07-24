#!/bin/bash

pushd ..
ansible raspi -i $(pwd)/hosts/dev -a 'vcgencmd measure_temp' --user rod 
popd