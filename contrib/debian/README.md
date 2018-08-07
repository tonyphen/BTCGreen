
Debian
====================
This directory contains files used to package btcgreend/btcgreen-qt
for Debian-based Linux systems. If you compile btcgreend/btcgreen-qt yourself, there are some useful files here.

## btcgreen: URI support ##


btcgreen-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install btcgreen-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your btcgreen-qt binary to `/usr/bin`
and the `../../share/pixmaps/btcgreen128.png` to `/usr/share/pixmaps`

btcgreen-qt.protocol (KDE)

