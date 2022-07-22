#!/bin/bash

pushd ..
ansible raspi -m shell -a 'sudo shutdown --halt +1'  --inventory $(pwd)/hosts/dev --user rod --private-key ~/.ssh/id_rsa 
popd