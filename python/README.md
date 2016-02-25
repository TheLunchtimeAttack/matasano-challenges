# Python solutions

Directory containing the python solutions.

Code can be found in the [matasano/](matasano) folder, which is the top level
of the project. Subfolders containing `__init__.py` behave as submodules.

**Note**: We use `python3` throughout this project. This document assumes
`python` is symlinked to `python3`.

## Running files

Due to the folder structure, you need to run all commands from this folder.

For example:
```
$ pwd
~/matasano-challenges/python
$ python
>>> import matasano.set1.c1
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t 
```

Alternatively, in one command:
```bash
$ python -m matasano.set1.c1
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t 
```

## Running tests

Tests can be found in the [tests/](tests) directory. These will be
automatically run using the `make test` command.
