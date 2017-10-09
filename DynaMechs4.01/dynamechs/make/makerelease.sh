#!/bin/tcsh

echo Remove CVS, lib, bin, and obj directories...
find $1 -name "CVS*" -exec /bin/rm -rf {} \;
find $1 -name "*~" -exec /bin/rm {} \;
find $1 -name core -exec /bin/rm {} \;
/bin/rm -rf $1/bin $1/lib $1/obj
/bin/rm -rf $1/loaders

echo Creating tar file...
tar cf $1.tar $1
cp $1.tar $1.tar.bak

echo Creating gzip file...
gzip -9 $1.tar

echo Creating bzip2 file...
mv $1.tar.bak $1.tar
bzip2 $1.tar

echo Creating zip file...
zip -r $1.zip $1
