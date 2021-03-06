Release Process
====================

* update translations (ping wumpus, Diapolo or tcatm on IRC)
* see https://github.com/vikingcoin/vikingcoin/blob/master/doc/translation_process.md#syncing-with-transifex

* * *

###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

###tag version in git

	git tag -s v(new version, e.g. 0.8.0)

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

* * *

##perform gitian builds

 From a directory containing the vikingcoin source, gitian-builder and gitian.sigs
  
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./vikingcoin
	git checkout v${VERSION}
	popd
	pushd ./gitian-builder
        mkdir -p inputs; cd inputs/

 Register and download the Apple SDK (see OSX Readme for details)
	visit https://developer.apple.com/downloads/download.action?path=Developer_Tools/xcode_4.6.3/xcode4630916281a.dmg
 
 Using a Mac, create a tarball for the 10.7 SDK
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.7.sdk.tar.gz MacOSX10.7.sdk

 Fetch and build inputs: (first time, or when dependency versions change)

	wget 'http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.tar.gz' -O miniupnpc-1.9.tar.gz
	wget 'https://www.openssl.org/source/openssl-1.0.1h.tar.gz'
	wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
	wget 'http://zlib.net/zlib-1.2.8.tar.gz'
	wget 'ftp://ftp.simplesystems.org/pub/png/src/history/libpng16/libpng-1.6.8.tar.gz'
	wget 'https://fukuchi.org/works/qrencode/qrencode-3.4.3.tar.bz2'
	wget 'https://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2'
	wget 'https://svn.boost.org/trac/boost/raw-attachment/ticket/7262/boost-mingw.patch' -O \ 
	     boost-mingw-gas-cross-compile-2013-03-03.patch
	wget 'https://download.qt-project.org/official_releases/qt/5.2/5.2.0/single/qt-everywhere-opensource-src-5.2.0.tar.gz'
	wget 'https://download.qt-project.org/archive/qt/4.6/qt-everywhere-opensource-src-4.6.4.tar.gz'
	wget 'https://protobuf.googlecode.com/files/protobuf-2.5.0.tar.bz2'
	wget 'https://github.com/mingwandroid/toolchain4/archive/10cc648683617cca8bcbeae507888099b41b530c.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/cctools/cctools-809.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/dyld/dyld-195.5.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/ld64/ld64-127.2.tar.gz'
	wget 'http://cdrkit.org/releases/cdrkit-1.1.11.tar.gz'
	wget 'https://github.com/theuni/libdmg-hfsplus/archive/libdmg-hfsplus-v0.1.tar.gz'
	wget 'http://llvm.org/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz' -O \
	     clang-llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
        wget 'https://raw.githubusercontent.com/theuni/osx-cross-depends/master/patches/cdrtools/genisoimage.diff' -O \
	     cdrkit-deterministic.patch
	cd ..
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/boost-linux.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/deps-linux.yml
	mv build/out/vikingcoin-deps-*.zip inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/qt-linux.yml
	mv build/out/qt-*.tar.gz inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/boost-win.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/deps-win.yml
	mv build/out/vikingcoin-deps-*.zip inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/qt-win.yml
	mv build/out/qt-*.zip inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/protobuf-win.yml
	mv build/out/protobuf-*.zip inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/gitian-osx-native.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/gitian-osx-depends.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../vikingcoin/contrib/gitian-descriptors/gitian-osx-qt.yml
	mv build/out/osx-*.tar.gz inputs/

 The expected SHA256 hashes of the intermediate inputs are:

    46710f673467e367738d8806e45b4cb5931aaeea61f4b6b55a68eea56d5006c5  vikingcoin-deps-linux32-gitian-r6.zip
    f03be39fb26670243d3a659e64d18e19d03dec5c11e9912011107768390b5268  vikingcoin-deps-linux64-gitian-r6.zip
    f29b7d9577417333fb56e023c2977f5726a7c297f320b175a4108cf7cd4c2d29  boost-linux32-1.55.0-gitian-r1.zip
    88232451c4104f7eb16e469ac6474fd1231bd485687253f7b2bdf46c0781d535  boost-linux64-1.55.0-gitian-r1.zip
    57e57dbdadc818cd270e7e00500a5e1085b3bcbdef69a885f0fb7573a8d987e1  qt-linux32-4.6.4-gitian-r1.tar.gz
    60eb4b9c5779580b7d66529efa5b2836ba1a70edde2a0f3f696d647906a826be  qt-linux64-4.6.4-gitian-r1.tar.gz
    60dc2d3b61e9c7d5dbe2f90d5955772ad748a47918ff2d8b74e8db9b1b91c909  boost-win32-1.55.0-gitian-r6.zip
    f65fcaf346bc7b73bc8db3a8614f4f6bee2f61fcbe495e9881133a7c2612a167  boost-win64-1.55.0-gitian-r6.zip
    70de248cd0dd7e7476194129e818402e974ca9c5751cbf591644dc9f332d3b59  vikingcoin-deps-win32-gitian-r13.zip
    9eace4c76f639f4f3580a478eee4f50246e1bbb5ccdcf37a158261a5a3fa3e65  vikingcoin-deps-win64-gitian-r13.zip
    963e3e5e85879010a91143c90a711a5d1d5aba992e38672cdf7b54e42c56b2f1  qt-win32-5.2.0-gitian-r3.zip
    751c579830d173ef3e6f194e83d18b92ebef6df03289db13ab77a52b6bc86ef0  qt-win64-5.2.0-gitian-r3.zip
    e2e403e1a08869c7eed4d4293bce13d51ec6a63592918b90ae215a0eceb44cb4  protobuf-win32-2.5.0-gitian-r4.zip
    a0999037e8b0ef9ade13efd88fee261ba401f5ca910068b7e0cd3262ba667db0  protobuf-win64-2.5.0-gitian-r4.zip

 Build vikingcoind and vikingcoin-qt on Linux32, Linux64, and Win32:
  
	./bin/gbuild --commit vikingcoin=v${VERSION} ../vikingcoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION} --destination ../gitian.sigs/ ../vikingcoin/contrib/gitian-descriptors/gitian-linux.yml
	pushd build/out
	zip -r vikingcoin-${VERSION}-linux-gitian.zip *
	mv vikingcoin-${VERSION}-linux-gitian.zip ../../../
	popd
	./bin/gbuild --commit vikingcoin=v${VERSION} ../vikingcoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win --destination ../gitian.sigs/ ../vikingcoin/contrib/gitian-descriptors/gitian-win.yml
	pushd build/out
	zip -r vikingcoin-${VERSION}-win-gitian.zip *
	mv vikingcoin-${VERSION}-win-gitian.zip ../../../
	popd
        ./bin/gbuild --commit vikingcoin=v${VERSION} ../vikingcoin/contrib/gitian-descriptors/gitian-osx-vikingcoin.yml
        ./bin/gsign --signer $SIGNER --release ${VERSION}-osx --destination ../gitian.sigs/ ../vikingcoin/contrib/gitian-descriptors/gitian-osx-vikingcoin.yml
	pushd build/out
	mv Vikingcoin-Qt.dmg ../../../
	popd
	popd

  Build output expected:

  1. linux 32-bit and 64-bit binaries + source (vikingcoin-${VERSION}-linux-gitian.zip)
  2. windows 32-bit and 64-bit binaries + installer + source (vikingcoin-${VERSION}-win-gitian.zip)
  3. OSX installer (Vikingcoin-Qt.dmg)
  4. Gitian signatures (in gitian.sigs/${VERSION}[-win|-osx]/(your gitian key)/

repackage gitian builds for release as stand-alone zip/tar/installer exe

**Linux .tar.gz:**

	unzip vikingcoin-${VERSION}-linux-gitian.zip -d vikingcoin-${VERSION}-linux
	tar czvf vikingcoin-${VERSION}-linux.tar.gz vikingcoin-${VERSION}-linux
	rm -rf vikingcoin-${VERSION}-linux

**Windows .zip and setup.exe:**

	unzip vikingcoin-${VERSION}-win-gitian.zip -d vikingcoin-${VERSION}-win
	mv vikingcoin-${VERSION}-win/vikingcoin-*-setup.exe .
	zip -r vikingcoin-${VERSION}-win.zip vikingcoin-${VERSION}-win
	rm -rf vikingcoin-${VERSION}-win

###Next steps:

* Code-sign Windows -setup.exe (in a Windows virtual machine using signtool)
 Note: only Gavin has the code-signing keys currently.

* upload builds to SourceForge

* create SHA256SUMS for builds, and PGP-sign it

* update bitcoin.org version
  make sure all OS download links go to the right versions
  
* update download sizes on bitcoin.org/_templates/download.html

* update forum version

* update wiki download links

* update wiki changelog: [https://en.vikingcoin.it/wiki/Changelog](https://en.vikingcoin.it/wiki/Changelog)

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}/${SIGNER}
	git add ${VERSION}-win/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built, repackage gitian-signed zips:

From a directory containing vikingcoin source, gitian.sigs and gitian zips

	export VERSION=(new version, e.g. 0.8.0)
	mkdir vikingcoin-${VERSION}-linux-gitian
	pushd vikingcoin-${VERSION}-linux-gitian
	unzip ../vikingcoin-${VERSION}-linux-gitian.zip
	mkdir gitian
	cp ../vikingcoin/contrib/gitian-downloader/*.pgp ./gitian/
	for signer in $(ls ../gitian.sigs/${VERSION}/); do
	 cp ../gitian.sigs/${VERSION}/${signer}/vikingcoin-build.assert ./gitian/${signer}-build.assert
	 cp ../gitian.sigs/${VERSION}/${signer}/vikingcoin-build.assert.sig ./gitian/${signer}-build.assert.sig
	done
	zip -r vikingcoin-${VERSION}-linux-gitian.zip *
	cp vikingcoin-${VERSION}-linux-gitian.zip ../
	popd
	mkdir vikingcoin-${VERSION}-win-gitian
	pushd vikingcoin-${VERSION}-win-gitian
	unzip ../vikingcoin-${VERSION}-win-gitian.zip
	mkdir gitian
	cp ../vikingcoin/contrib/gitian-downloader/*.pgp ./gitian/
	for signer in $(ls ../gitian.sigs/${VERSION}-win/); do
	 cp ../gitian.sigs/${VERSION}-win/${signer}/vikingcoin-build.assert ./gitian/${signer}-build.assert
	 cp ../gitian.sigs/${VERSION}-win/${signer}/vikingcoin-build.assert.sig ./gitian/${signer}-build.assert.sig
	done
	zip -r vikingcoin-${VERSION}-win-gitian.zip *
	cp vikingcoin-${VERSION}-win-gitian.zip ../
	popd

- Upload gitian zips to SourceForge

- Announce the release:

  - Add the release to bitcoin.org: https://github.com/vikingcoin/vikingcoin.org/tree/master/_releases

  - Release sticky on vikingcointalk: https://vikingcointalk.org/index.php?board=1.0

  - Vikingcoin-development mailing list

  - Optionally reddit /r/Vikingcoin, ...

- Celebrate 
