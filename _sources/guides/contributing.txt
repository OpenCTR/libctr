Contributing
============

This document provides guidelines to anyone who wishes to contribute to OpenCTR
and/or libctr.

Requirements
------------

There is absolutely no requirement for who is able to contribute to libctr.
Anyone interested may contribute. There are, however, several requirements
on what will be accepted into libctr.

libctr does have somewhat strict critera concerning what is permitted to become
part of the public API, the part that developers use. To be included, a
component (be it a function, file, structure, or any combination thereof) should
meet the following criteria:

   1. Is it neccessary?
   2. Will it probably undergo substantial changes very soon?
   3. Is it efficient enough to be used in production quality code?
   4. Is it easy to use correctly, and hard to use incorrectly?
   5. Is it as small as possible, without being any smaller?

Those criteria reflect some of the most desirable characteristics in an API. As
long as they are followed, we can always be positive that *any* changes to
libctr will never hurt it, only add to it. Any pull requests or commits which
publicly expose an API which violates any of those principles will be rejected,
as will any changes to an existing API which cause it to violate a criteria.

Documentation is also a required criteria. Any file, function, macro, or type
added without any documentation will be removed. We believe that an API is
useless without documentation, as without it, there is no way that new or
returning users will be able to use it correctly (and you yourself will
probably become a "returning user" yourself in a few weeks).

Pull Requests
-------------

The recommended way of making a change to the master branch of libctr is through
GitHub pull requests. Just clone libctr, make your changes, and then submit it
as a pull request.

Developers should add their name and email address to the ``.mailmap`` file as
part of their pull requests. This helps us automatically track who is
responsible for what.

It is recommended (though not required) that developers use ``clang-format`` to
format their code to the libctr guidelines before they merge their work. A
``.clang-format`` file is provided in the root of libctr, and should have all
the required settings.

Joining OpenCTR
---------------

OpenCTR is an organization on GitHub. As such, individual developers can join
OpenCTR, which gives them access to the OpenCTR repositories, including libctr.

The OpenCTR project is not currently accepting new developers at this time. We
are still getting everything setup, and we have limited experience with
distributed development. Once everything has reached stable, we will begin
accepting new members.

Documentation Writers
---------------------

OpenCTR takes great pride in it's emphasis on developer documentation. *Nothing*
in OpenCTR should ever be left undocumented. If you see something that is, do
not hesitate to bring it to our attention. Pull requests that add or improve
documentation are always welcome.

Technical writers are always welcome to contribute. If you are unable to
contribute personally, even professional recommendations and tips will always
be welcome.

Translations
------------

At this time, OpenCTR is written primarily in english, but this will not always
be the case. We are currently working on an infrastructure that will support
more multilingual documentation for our projects. Once this is completed, we
will need volunteers who are willing to translate the developer documentation.

People who have experience with translating english into any of the following
languages will be very valuable:

* Spanish
* French
* Chinese (Mandarin)
* Japanese
* Arabic
* Italian
* German

Instructions on adding translations to libctr will be added in the future.

