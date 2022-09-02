#!/bin/bash  
## just a little helper for getting docs to my github pages

cp -r docs/* ~/HKMS/danja.github.io/projects/dreamachine/
cd ~/HKMS/danja.github.io/
git add -A
git commit -m 'update'
git push
