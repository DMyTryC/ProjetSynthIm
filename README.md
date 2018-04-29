# ProjetSynthIm

How to push to a repository :
-----------------------------
Step 1. Make sure you are working on a branch 
* if you don't work on a branch : 
	* git branch : list current branches
	* git branch "nameBranchLocal" : create a branch with "nameBranchLocal"
	* git checkout "nameBranchLocal" : move to the "nameBranchLocal"

Step 2. Commit changes of your local repository
		
Step 3. Fetch and merge the changes to the current branch
* Commands to execute :
	* git remote -v : list the remote repositories
	* git fetch "nameRemoteRepo" : fetches the files made to the remote repository "name"
	* git merge "nameRemoteRepo"/"nameBranchRemote" "nameBranchLocal" : Merges the files on the "nameRemoteRepo"/"nameBranchRemote" with the "nameBranchLocal" branchs
				
Step 5. Push the changes to the remote branch
* Recommit if needed
* Push the changes to the remote repository : 
	* git push "nameRemoteRepo" "nameBranchLocal" : This creates a remote repository branch with the same name as the local branch (if it doesn't exist), if it does exist, will push to the remote branch otherwise
