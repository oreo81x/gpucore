
./extbin/linux/premake5-alpha16/premake5 gmake && cd output/build

gmake config=debug
gmake config=release

#cd ../../ && rm -r output && mkdir output output/bin output/bin-int output/build