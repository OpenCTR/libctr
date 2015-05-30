|Logo|

========
 libctr 
========

|Release| 

|License|

OpenCTR is a free, open-source, and cross-platform SDK for developing 
Nintendo 3DS homebrew.

This repository contains libctr - the software library API for OpenCTR.

===============
Getting Started
===============

libctr is installed as part of the OpenCTR SDK. 

Download and install the latest version of the OpenCTR SDK from 
https://github.com/OpenCTR/OpenCTR/releases/latest

Alternatively, libctr can be built from source using CMake.
This requires several advanced CMake settings, and is not 
recommended for inexperienced users.

=============
Documentation
=============

Documentation for libctr is available online at 
https://openctr.github.io/libctr/

Also, the documentation can be manually generated from source, by passing 
``-DENABLE_DOC=ON`` to CMake.

=======
License
=======

**libctr** is licensed under the `GNU General Public License v3.0`_. 

See `LICENSE.txt`_ for terms.

===============
Acknowledgments
===============

Credit goes to smealum for ctrulib, which provides the basis of ~90% of 
the code logic.

.. |Logo| image:: https://openctr.github.io/_static/logo.svg
   :alt: OpenCTR Logo
   :width: 250px
   :target: https://openctr.github.io/

.. |Release| image:: https://img.shields.io/github/release/OpenCTR/libctr.svg?style=flat-square&label=Release
   :alt: Latest Release
   :target: https://github.com/OpenCTR/libctr/releases/latest

.. |License| image:: https://img.shields.io/github/license/OpenCTR/libctr.svg?style=flat-square&label=License
   :alt: GNU General Public License v3.0
   :target: http://choosealicense.com/licenses/gpl-3.0/

.. _`GNU General Public License v3.0`: http://www.gnu.org/licenses/gpl.html

.. _`LICENSE.txt`: ./LICENSE.txt

