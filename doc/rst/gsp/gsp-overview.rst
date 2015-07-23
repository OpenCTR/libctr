GSP Overview
============

This is an overview of the GSP API.

See :doc:`gsp-reference` for more information.

Introduction
------------

GSP is an API for controlling and accessing the DMP PICA GPU. libgsp provides
APIs for obtaining access to the GPU, which is a kernel-owned service, as well
as providing APIs for generating command buffers, which perform various
rendering operations in order to display a result.

Please note that libgsp is a very low-level software library: Memory 
management, command-buffer controls, matrix and viewpoint operations, and
vertex buffer caches are all left to the application. This allows much greater
control, but it also increases developer responsibility. Developers seeking a
more high-level library are encouraged to use wrappers like libctrxx, which
provides a fully object-oriented interface to libgsp. libctrxx is not ready for
use at this time, and more information will be available shortly.

Concepts
--------

