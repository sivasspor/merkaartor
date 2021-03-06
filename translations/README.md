Merkaartor currently uses Qt Linguist and Transifex to translate stuff. Although
you might be tempted to change translations in git repo directly, please don't.
Translation files are meant to be updated via Transifex.com only, and pulled
into the repository before version release.

The regular workflow is:

0) From time to time, update translation files on Transifex:
    
    $ lupdate -no-obsolete Merkaartor.pro
    $ tx push -s

   This pushes the original english strings to Transifex, updating the database and
   allowing new strings to be downloaded.

1) Before release, Transifex data should be pulled and commited into the
repository. This is not necessary, but serves as a backup in case something
terrible happens to Transifex.

    $ tx pull
    $ git commit translations/*.ts

2) During release, the regular qt tools are used to bundle translations.
