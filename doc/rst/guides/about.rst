About
=====

This document provides a basic overview of libctr: what it is, what it is *not*,
what it does, and explains the reasons behind several of its choices. After
reading this, you should have a pretty good idea of whether or not libctr is
what you are looking for - if it *fits the bill*.

Acknowledgment
--------------

libctr is *heavily* based off of `ctrulib 
<https://github.com/smealum/ctrulib>`__, by smealum.

Some parts of libctr were directly copied from ctrulib, and a large part of the
libctr architecture was influenced by the inner workings of ctrulib. 

libctr is based off of ctrulib, and would not exist without it.

Important Notice
----------------

The first and foremost disclaimer about libctr is this:
   libctr is not a catch-all, end-all, be-all solution. Some users will be
   satisfied with libctr, others will be more satisfied with libctru (by 
   smealum), and still other users will be dissatisfied with both. 

There is nothing about libctr that makes it inherently better than libctru, or 
inherently worse. It simply targets a different set of goals.

In particular, because libctr is tailored towards application and game
developers, system kernel-level homebrew like 
https://github.com/Myriachan/libkhax, 
https://github.com/shinyquagsire23/bootstrap, and
https://github.com/StapleButter/Staplehax will never be portable from libctru
to libctr. This is intentional, because libctr intentionally hides a number of
details that libctru exposes directly. This is an architectural design 
tradeoff; by focusing only on what application developers use, we can eliminate
a number of functions/params/values from libctr. This results in more readable
code, better link-time optimizations, easier compile-time static checking, 
and easier maintainability. So the choice was made to exclude certain 
functionality from libctr, even if this does reduce the potential number of 
users and use-cases.

Overview
--------

**libctr** is a library created by Alex Shaw (Symbitic) as part of OpenCTR.
It is meant to be an open source alternative to Nintendo's proprietary
commercial SDK for the Nintendo 3DS handheld game console. It allows developers
to create their own Nintendo 3DS homebrew, independent of Nintendo.

