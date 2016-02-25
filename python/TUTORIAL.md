# Tutorial for the python Matasano challenges

This tutorial is meant as an easy-to-follow guide to contributing to the
python Matasano challenges. It covers all parts of the development process and
can be used as a reference for the various aspects.

A lot of the workflow included here is how I like to organise my work.
However, Git can be used in many different ways, and you should use it however
you feel happiest. Though I would strongly recommend getting into good habits
earlier on and trying to use git to its fullest.

### Table of contents
<!-- MarkdownTOC depth=3 bracket=round autolink=true -->

- [The Scenario](#the-scenario)
- [The Setup](#the-setup)
  - [Cloning & forking](#cloning--forking)
  - [Making changes & committing](#making-changes--committing)
  - [Pushing & pulling](#pushing--pulling)
- [Working on code](#working-on-code)
  - [Packages in python](#packages-in-python)
  - [Organising your work](#organising-your-work)

<!-- /MarkdownTOC -->


## The Scenario

You have some annoying colleague who insists that learning git is unnecessary
and has spent the past year working on a thesis which is just a single .tex 
monstrosity. You think it's time to teach them a lesson...

## The Setup

First things first, time to get everything organised. You decide to use the
[Matasano challenge](http://cryptopals.com/) solutions being worked on by [The
Lunctime Attack](https://github.com/TheLunchtimeAttack/matasano-challenges).
This should provide the cryptography you need to have some fun.

### Cloning & forking

Time to get a local copy of the repository:
```bash
$ git clone git@github.com:TheLunchtimeAttack/matasano-challenges.git
Cloning into 'matasano-challenges'...
...

```
(Don't have ssh keys set up with github? Find more info
[here](https://help.github.com/articles/generating-an-ssh-key/))

Great! So now we have the branch `master` set up to track from 
TheLunchtimeAttack's repository:
```bash
$ git remote -v
origin  https://github.com/TheLunchtimeAttack/matasano-challenges (fetch)
origin  https://github.com/TheLunchtimeAttack/matasano-challenges (push)
$ git branch -a
* master
  remotes/origin/HEAD -> origin/master
  remotes/origin/master

```
Hmm... but it would be nice to have our own version of the repository on
GitHub so we can share it with our colleagues later! We'll need to fork the
repository to our own GitHub account. Visit [the repo
page](https://github.com/TheLunchtimeAttack/matasano-challenges) and click the
fork button. Now we can add this repository as another 'remote' branch
in git.
```bash
$ git remote add me git@github.com:mygitusername/matasano-challenges.git
$ git remote -v
origin  https://github.com/TheLunchtimeAttack/matasano-challenges (fetch)
origin  https://github.com/TheLunchtimeAttack/matasano-challenges (push)
me git@github.com:mygitusername/matasano-challenges.git (fetch)
me git@github.com:mygitusername/matasano-challenges.git (push)

```
Cool! So git now has two possible remote repositories it knows about.

Let's make a new *local* branch, and set it to track to a *remote* branch
on my fork:
```bash
$ git checkout -b tutorial # Creates a new branch and switches to it.
Switched to a new branch 'tutorial'
$ git push -u me tutorial # Creates a new branch in the repo 'me' called tutorial
...
To git@github.com:mygitusername/matasano-challenges.git
 * [new branch]      tutorial -> tutorial
Branch tutorial set up to track remote branch tutorial from me. 
```
We can find out even more information if we want:
```bash
$ git remote show me
* remote me
  Fetch URL: git@github.com:mygitusername/matasano-challenges.git
  Push  URL: git@github.com:mygitusername/matasano-challenges.git
  HEAD branch: master
  Remote branches:
    master   tracked
    tutorial tracked
  Local branch configured for 'git pull':
    tutorial merges with remote tutorial
  Local refs configured for 'git push':
    master   pushes to master   (up to date)
    tutorial pushes to tutorial (up to date)
```

Aah. Too much information...


### Making changes & committing

Time to start making some changes. A good starting point is a readme file
explaining the project. Once that's done, we can add it:
```bash
$ git status
On branch tutorial
Your branch is up-to-date with 'me/tutorial'.
Untracked files:
  (use "git add <file>..." to include in what will be committed)

    python/TUTORIAL.md

nothing added to commit but untracked files present (use "git add" to track)

$ git add python/TUTORIAL.md
$ git status
On branch tutorial
Your branch is up-to-date with 'me/tutorial'.
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

    new file:   python/TUTORIAL.md
```

Ok, so we'll commit those change with `git commit` and write a nice commit
message.

### Pushing & pulling

If we don't have a tool to display Markdown, we can always push it to the repo
and see how it would look like.
```bash
$ git push tutorial
```

Since we set the branch tutorial to automatically push to the repository `me`,
this worked fine. However, if we want, we can be more specific and write `git
push me tutorial`.

As an aside, here is a lovely diagram giving an overview of the different git
commands:
![Git data transport from osteele.com](tutorial/img/git-transport.png)

Now that we've pushed our recent changes to our own fork of the repo. Suppose
we now want to check whether there have been any changes to the main repo
with new functionality we want to use:
```bash
$ git pull origin master
From https://github.com/TheLunchtimeAttack/matasano-challenges
 * branch            master     -> FETCH_HEAD
Already up-to-date.
```
Everything up-to-date for now, that's fine. If not we could decide whether it
would be worth merging the changes (a quick `git log master` to see what
recent commits have done) and then `git merge master` to bring the new changes
from `master` into our `tutorial` branch.

## Working on code

Now that the respository is all set up, time to start writing some code.
First thing to do is read the [README](README.md) to see if there's any
relevant information.

### Packages in python

From the README:

> Due to the folder structure, you need to run all commands from this folder.
For example:
```bash
$ pwd
~/matasano-challenges/python
$ python
>>> import matasano.set1.c1
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t 
```  


So if we create a new directory for our program, we can use it in the same way.
```bash
$ mkdir tutorial
$ cd tutorial
~/work/matasano/python/tutorial
$ touch __init__.py
```
This created a new directory called `tutorial`, and `touch __init__.py` creates an
empty file called `__init__.py` which is needed by python to understand that 
the `tutorial` folder should be treated like a python package.

We can also make a small python file to check that it can import the matasano 
files properly.

```python
# python/matasano/tutorial/example.py
from matasano.util.byte_xor import byte_list_xor
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\n\t python -m example.py <string to encrypt>")
        quit()

    input_str = sys.argv[1]

    # Convert string to list of bytes
    byte_list_input = [ord(c) for c in input_str]

    # XOR the string with the byte 1 (flips last bit)
    output_list = byte_list_xor(byte_list_input, [1]*len(input_str))

    # Convert list back to string
    output_str = "".join(chr(b) for b in output_list)

    print("The encrypted string is: {}".format(output_str))
```

The first `if` statement here makes sure the code only runs when we call it
directly (and not, for example, when imported by an external package). 

The rest of the example takes the string provided by the user as input and
XORs each byte with 1. Let's see it in action:

```bash
$ python -m tutorial.example 'Hello, world!'
The encrypted string is: Idmmn-!vnsme 
```

It works! We used the `python -m` command while in the `python/` directory to
tell python to import our file `example` from the `tutorial` package/folder.

### Organising your work

Now we have a good base for writing our code, it's important to save our
progress by creating a commit.

We want to treat the `tutorial` branch we created as a sort of pseudo-master
branch. That is, it's best to make changes in another new branch, and only 
merge them back to the `tutorial` branch once we are confident they are good.

This means that if we want to go back and work on some other part of the code,
we don't need to worry about whether the current changes have broken
something.

Even though we've made changes, have new untracked files (and may have made
staged or unstaged changes to tracked files) git is happy to let us change to
a new branch.

This is because there is no confusion over what to do with the recent changes.

However, suppose we tried to change to a branch which has a different state:
```bash
$ git checkout master
error: Your local changes to the following files would be overwritten by checkout:
  python/TUTORIAL.md
Please, commit your changes or stash them before you can switch branches.
Aborting
```
Git doesn't like it! Since the version of `python/TUTORIAL.md` in the master
branch you want to checkout is different than the version you made changes to,
so it can't handle it.

Create a new branch which will be dedicated to writing the code:
```bash
$ git checkout -b code
M python/TUTORIAL.md
Switched to a new branch 'code'
```
Note that it tells you about modifications to *tracked* files, but doesn't
care about untracked files (they are ignored for now).

Add and commit the new files we added and we're good to continue.