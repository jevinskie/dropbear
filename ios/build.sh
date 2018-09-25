#!/usr/bin/env bash

set -e

autoconf
autoheader

rm -rf ios-build
mkdir -p ios-build
pushd ios-build

CC="ccache xcrun --sdk iphoneos clang -arch arm64" LD="xcrun --sdk iphoneos ld" ../configure CFLAGS="-Oz -flto -miphoneos-version-min=9.0" LDFLAGS="-Oz -flto -miphoneos-version-min=9.0" --host=arm64-apple-ios9.0.0
make -j8

jtool --sign --inplace dropbearmulti

mkdir -p deb-root
pushd deb-root

mkdir -p DEBIAN
cp ../../ios/control DEBIAN/
cp ../../ios/extrainst_ DEBIAN/
cp ../../ios/prerm DEBIAN/


mkdir -p Library/LaunchDaemons
cp ../../ios/com.jevinskie.dropbear.plist Library/LaunchDaemons/

mkdir -p usr/local/bin
mkdir -p usr/local/sbin
mkdir -p usr/local/libexec
cp ../dropbearmulti usr/local/bin/

pushd usr/local/bin
ln -s dropbearmulti dbclient
ln -s dropbearmulti ssh
ln -s dropbearmulti dropbearkey
ln -s dropbearmulti dropbearconvert
ln -s dropbearmulti scp
popd

pushd usr/local/sbin
ln -s ../bin/dropbearmulti dropbear
popd

pushd usr/local/libexec
ln -s ../bin/dropbearmulti sftp-server
popd

mkdir -p etc/dropbear

echo "Installed-Size: $(du -I DEBIAN -ks . | cut -f 1)" >> DEBIAN/control

popd

COPYFILE_DISABLE=1 $THEOS/bin/fakeroot.sh -r $THEOS/bin/dm.pl -Zlzma -b deb-root com.jevinskie.dropbearmulti-arm64_2018.76_1+iphoneos-arm.deb

popd
