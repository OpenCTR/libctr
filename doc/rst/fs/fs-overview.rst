Filesystem Overview
===================

This is an overview of the Filesystem API.

Organization
------------

The CTR filesystem is organized logically into several layers. The first layer
is the *media type*, the physical block storage location. There are three 
usable media types:
1. The NAND flash memory.
2. The external SDMC card.
3. The Gamecard.

On the Nintendo 3DS, an *archive* is a collection of files and directories.
An archive is stored on a *media type*. Each archive has a unique name and id,
which reflect the type of data stored on it. Several archives managed by the
system include: RomFS (stored on the gamecard), SDMC (contains all files and
directories on the SD card), and ExtSaveData (Application Save Data; may be
stored on the gamecard or SDMC card). Each archive is mounted using its
name.

After an archive is *mounted*, it can be used like a traditional filesystem.
The libfs API is mostly centered around using the SDMC archive as the main
filesystem, because most homebrew software will not have an accessable
Gamecard, and using the NAND as a general-purpose filesystem is not supported.
Future versions of libctr will (hopefully) add support for using Save Data, but
that will be accessed through a separate API.

There is experimental support for mounting the NAND as a read-only filesystem,
but this is still experimental, and not recommended for general use. 

The primary filesystem for most libctr applications will be the SDMC, because
that is the only filesystem they can be guarenteed of having.

Mounting
--------

A filesystem must be mounted before it can be used.

See :doc:`fs-reference` for more information.

