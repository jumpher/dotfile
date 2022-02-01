# dotfile

Instructions

    cd into your home directory.

    Create a new git repository

      $ git init     

    Create a git ignore file that ignores everything.

      $ echo '*' > .gitignore     

    Manually add all the files that you want to add to the repo by using.

      $ git add -f filename_or_directory_name     

(Note: You can also add entire directories like ~/.config but make sure you don’t include any of your private key files or config files with plaintext passwords by mistake. One such example is irssi config which may contain a plaintext password.)

    Once that is done, commit your changes

      $ git commit -m 'commit message'    

    Add the remote origin url.

      $ git remote add origin http://yourgitrepo.com/username/reponame    

    Push the committed changes and set the upstream branch.

      $ git push --set-upstream origin master    

Congratulations! You managed to backup your dotfiles to a git repository. Now any time you update a dotfile, make sure you push the changes to the repo as well.

If you need to restore your dotfiles to a fresh system follow the instructions below:

    cd into your home directory.

    Clone the dotfiles repository to any directory.

      $ git clone http://yourgitrepo.com/username/reponame    

    cd into that directory, and copy all the contents to the home directory.

      $ cp -r .[!.]* $HOME/     
