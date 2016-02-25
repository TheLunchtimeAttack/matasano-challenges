# Tutorial for the python Matasano challenges

This tutorial is meant as an easy-to-follow guide to contributing to the
python Matasano challenges. It covers all parts of the development process and
can be used as a reference for the various aspects.

### Table of contents
<!-- MarkdownTOC depth=3 bracket=round autolink=true -->

- [The scenario](#the-scenario)
- [The setup](#the-setup)
  - [Cloning & Forking](#cloning--forking)
  - [Making changes & committing](#making-changes--committing)
  - [Pushing & pulling](#pushing--pulling)

<!-- /MarkdownTOC -->


## The scenario

You have some annoying colleague who insists that learning git is unnecessary
and has spent the past year working on a thesis which is just a single .tex 
monstrosity. You think it's time to teach them a lesson...

## The setup

First things first, time to get everything organised. You decide to use the
[Matasano challenge](http://cryptopals.com/) solutions being worked on by [The
Lunctime Attack](https://github.com/TheLunchtimeAttack/matasano-challenges).
This should provide the cryptography you need to have some fun.

### Cloning & Forking

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


