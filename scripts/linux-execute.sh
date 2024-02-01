
./extbin/linux/premake5-alpha16/premake5 gmake && cd output/build

gmake config=debug
gmake config=release

cp -a ../../assets ../bin/debug-linux-x86_64/assets
cp -a ../../assets ../bin/release-linux-x86_64/assets

cd ../bin/debug-linux-x86_64    && ./sandbox
cd ../release-linux-x86_64      && ./sandbox

#cd ../../../ && rm -r output && mkdir output output/bin output/bin-int output/build