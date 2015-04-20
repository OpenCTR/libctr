|Building| |Coverage| |License|

|Logo|

=======
OpenCTR
=======

:repository: `libctr <https://github.com/OpenCTR/libctr>`_
:license: `GPL3 <http://www.gnu.org/licenses/gpl-3.0.html>`_
:owner: `Alex Shaw <mailto:alex.shaw.as@gmail.com>`_
:description: OpenCTR is a free, open-source, and cross-platform SDK for developing homebrew for the Nintendo 3DS.

===========
Description
===========

OpenCTR is a free, open-source, and cross-platform SDK for developing homebrew for the Nintendo 3DS.

This repository contains libctr - the software library API for OpenCTR.

========
Building
========

If you have already installed OpenCTR, libctr should already be installed.
If you would like to build libctr from source, then configure and build 
libctr like any other CMake project, with one exception. libctr requires that 
the CMake variable ``CTR_ROOT`` be set to the location of OpenCTR. When libctr 
is build as part of OpenCTR, this is set automatically. When libctr is being 
built independently of OpenCTR, this variable must be set manually. It is used 
to help libctr find a cross-compiler to use, and it also allows libctr to be 
installed to a sub-directory of OpenCTR.

=====================
Configuration Options
=====================

Pass these values to CMake to change how libctr is built.

:CMAKE_BUILD_TYPE: Build Configuration. Values are Debug/Release/RelWithDebInfo/MinSizeRel
:CMAKE_INSTALL_PREFIX: Directory to install libctr into.
:CTR_ROOT: Location of OpenCTR. Used to enable cross-compiling.
:ENABLE_DOC: Enable/Disable building the libctr API Documentation.

=============
Documentation
=============

https://openctr.github.io/

=======
Authors
=======

* Alex Shaw

=======
License
=======

OpenCTR is licensed under version 3 of the `GNU General Public License`_. 
See `LICENSE`_ for terms.


.. _GNU General Public License: http://www.gnu.org/licenses/gpl.html

.. _LICENSE: ./LICENSE.txt

.. |Building| image:: http://img.shields.io/travis/OpenCTR/libctr/master.svg?style=flat
   :alt: TravisCI build status
   :target: https://travis-ci.org/OpenCTR/libctr

.. |Coverage| image:: http://img.shields.io/coveralls/OpenCTR/libctr/master.svg?style=flat
   :alt: Coveralls.io coverage
   :target: https://coveralls.io/r/OpenCTR/libctr?branch=master

.. |License| image:: http://img.shields.io/badge/license-gpl3-blue.svg?style=flat
   :alt: GNU GPL3 License
   :target: http://www.gnu.org/licenses/gpl-3.0.html

.. |Logo| image:: https://avatars2.githubusercontent.com/u/11789047

