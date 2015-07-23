Filesystem Overview
===================

This is an overview of the Filesystem API.

Files
-----

The files required to use the Filesystem API are:

======== ===========
Filename Description
-------- -----------
ctr/fs.h Header file for the Filesystem module.
libctr.a Static library file containing the Filesystem modules.
======== ===========

Concepts
--------

On the Nintendo 3DS, files and directories are organized together in a
container called an *archive*. An archive is stored on a physical block
storage device (NAND, SDMC, or Gamecart). Each archive has a unique name and
id, which reflect the type of data stored on it. Archives are managed entirely
by the system software, but they must be mounted by the user before they can be
used.

Some example archives present on retail 3DS units include:
* RomFS -- Stored on the gamecart. Contains the read-only game data.
* SDMC -- An archive that automatically maps to a SD card (if available).
Although usable on all 3DS units, most commercial games do not access the
SD card directly.
* SaveData -- Application-specific save data. May be stored on a gamecard,
on the SD card, or in the internal NAND, depending on the game and user
settings.

After an archive has been mounted, it can be used and accessed like a
traditional filesystem (e.g. with ``open()``, ``close()``, ``fopen()``,
``fclose()``, etc.).

Using
-----

The SDMC is the primary filesystem most applications will use. Very few
(probably none at all) homebrew developers will be able to release their
applications on commercial game cartridges, and access to the NAND is
strictly controlled by security settings, so it may not always be
available to homebrew. The SD card is the only filesystem most homebrew
can be guarenteed of having, because homebrew is usually launched from an SD
card.

Applications which require access to the NAND will probably be better off using
`ctrulib <https://github.com/smealum/ctrulib>`__.

By default, the SDMC is mounted automatically during libctr startup. The global
filesystem context (``CTR_FS_THIS``) is initalized to use the SD filesystem.
The libfs API should be usable as soon as applications begin. Applications
which wish to use the C Standard Library I/O functions can enable newlib
integration by calling ``ctrFsMount()``, which mounts an archive as the
default filesystem to use in newlib. Calling ``ctrFsMount(CTR_FS_THIS)`` at the
beginning of a program allows use of the full standard I/O functions.

Context Data
------------

Like most of libctr, the filesystem API uses context data as a way of avoiding
global variables. A filesystem context represents a session with the filesystem
service, one archive to access, and several cached settings.

The global context in libfs is ``CTR_FS_THIS``, which is created automatically
during startup, and should **never be allocated or deallocated by the user**.

