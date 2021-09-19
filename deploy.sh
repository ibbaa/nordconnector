#!/bin/sh
cp -f build/Release/bin/nordc /usr/local/bin
scp -i /home/alwin/.ssh/id_rsa build/Release/bin/nordc root@kronos:/usr/local/bin
