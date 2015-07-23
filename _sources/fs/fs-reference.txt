Filesystem Reference
====================

Data Structures
---------------

.. doxygendefine:: CTR_FS_MAX_FILENAME_LENGTH

.. doxygendefine:: CTR_FS_THIS

.. doxygenenum:: CtrFsMode

.. doxygenenum:: CtrFsOrigin

.. doxygenenum:: CtrFsType

.. doxygenstruct:: CtrFsStat
   :members:

.. doxygenstruct:: CtrFsStatus
   :members:

.. doxygenstruct:: CtrFsDirent
   :members:

.. doxygentypedef:: CtrFsContextData

Functions
---------

.. doxygenfunction:: ctrFsContextDataNew

.. doxygenfunction:: ctrFsContextDataFree

.. doxygenfunction:: ctrFsOpen

.. doxygenfunction:: ctrFsRead

.. doxygenfunction:: ctrFsWrite

.. doxygenfunction:: ctrFsClose

.. doxygenfunction:: ctrFsOpendir

.. doxygenfunction:: ctrFsReaddir

.. doxygenfunction:: ctrFsClosedir

.. doxygenfunction:: ctrFsStat

.. doxygenfunction:: ctrFsFstat

.. doxygenfunction:: ctrFsMkdir

.. doxygenfunction:: ctrFsRename

.. doxygenfunction:: ctrFsRmdir

.. doxygenfunction:: ctrFsUnlink

.. doxygenfunction:: ctrFsLseek

.. doxygenfunction:: ctrFsFsync

.. doxygenfunction:: ctrFsSdmcStatus

.. doxygenfunction:: ctrFsTruncate

.. doxygenfunction:: ctrFsFtruncate

.. doxygenfunction:: ctrFsGetAvailableSize

.. doxygenfunction:: ctrFsMount

