#!/bin/bash

pushd ..
ansible raspi -i $(pwd)/hosts/dev --module-name ping --user rod  --private-key ~/.ssh/id_rsa 
popd
