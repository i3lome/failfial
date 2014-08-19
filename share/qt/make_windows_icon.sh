#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/vikingcoin.png
ICON_DST=../../src/qt/res/icons/vikingcoin.ico
convert ${ICON_SRC} -resize 16x16 vikingcoin-16.png
convert ${ICON_SRC} -resize 32x32 vikingcoin-32.png
convert ${ICON_SRC} -resize 48x48 vikingcoin-48.png
convert vikingcoin-16.png vikingcoin-32.png vikingcoin-48.png ${ICON_DST}

