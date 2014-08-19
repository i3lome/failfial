
Debian
====================
This directory contains files used to package vikingcoind/vikingcoin-qt
for Debian-based Linux systems. If you compile vikingcoind/vikingcoin-qt yourself, there are some useful files here.

## vikingcoin: URI support ##


vikingcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vikingcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vikingcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/vikingcoin128.png` to `/usr/share/pixmaps`

vikingcoin-qt.protocol (KDE)

