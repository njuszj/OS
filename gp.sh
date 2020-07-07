# !/bin/bash

echo "Input your comment: "
read comment
git add .
git commit -m "$comment"
git push origin master


