#!/bin/bash  
## a little helper for genenerating docs and pushing to github pages
## all localised to my desk machine filesystem

# convert the markdown bits to html
find . -name '*.md' -print0 | while read -d $'\0' f; do
  markdown "$f" > "${f%.md}.html"
done

# run doxygen, copy to appropriate repo
doxygen Doxyfile
rm -r ~/HKMS/danja.github.io/projects/dreamachine/*
cp -r docs/* ~/HKMS/danja.github.io/projects/dreamachine/
cd ~/HKMS/danja.github.io/

# oddments
mv ~/micros/dreamachine/devlog.html ~/HKMS/danja.github.io/projects/dreamachine/
mv ~/micros/dreamachine/README.html ~/HKMS/danja.github.io/projects/dreamachine/

# upload
git add -A
git commit -m 'update'
git push
