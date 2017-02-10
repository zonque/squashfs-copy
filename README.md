cpsquashfs
==========

A simple tool that copies a squashfs image from one file or device to another.
It reads the superblock first, checks the magic and and then copies the number
of bytes used in that squashfs over to the target.

