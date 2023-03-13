#!/bin/bash
rm *~ & rm .*~
rm NORMA/*~ & rm NORMA/.*~
rm files/cpp/*~ & rm files/cpp/.*~
rm files/Pascal/*~ & rm files/Pascal/.*~
read str
git add .
git commit -m "$str"
git push
